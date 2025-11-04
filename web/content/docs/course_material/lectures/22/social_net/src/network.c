#include "network.h"

// ===== CREATE NETWORK =====
Network* create_network() {
    Network* net = (Network*)malloc(sizeof(Network));
    net->num_people = 0;
    for (int i = 0; i < MAX_PEOPLE; i++) net->people[i] = NULL;
    return net;
}

// ===== FREE NETWORK =====
void free_network(Network* net) {
    for (int i = 0; i < net->num_people; i++) {
        if (net->people[i] != NULL) {
            free(net->people[i]->friends);
            free(net->people[i]);
        }
    }
    free(net);
}

// ===== CREATE PERSON =====
Person* create_person(const char* name) {
    Person* p = (Person*)malloc(sizeof(Person));
    strncpy(p->name, name, 29);
    p->name[29] = '\0';
    p->friends = NULL;
    p->num_friends = 0;
    return p;
}

// ===== ADD PERSON =====
void add_person(Network* net, const char* name) {
    if (net->num_people >= MAX_PEOPLE) { printf("Network is full!\n"); return; }
    if (find_person(net, name) != NULL) { printf("Person '%s' already exists!\n", name); return; }
    net->people[net->num_people++] = create_person(name);
    printf("Added '%s' to the network.\n", name);
}

// ===== FIND PERSON =====
Person* find_person(Network* net, const char* name) {
    for (int i = 0; i < net->num_people; i++)
        if (strcmp(net->people[i]->name, name) == 0) return net->people[i];
    return NULL;
}

// ===== PRINT NETWORK =====
void print_network(Network* net) {
    if (net->num_people == 0) { printf("Network is empty!\n"); return; }
    printf("\n=== Social Network ===\n");
    for (int i = 0; i < net->num_people; i++)
        print_person_friends(net->people[i]);
    printf("======================\n");
}

// ===== PRINT PERSON FRIENDS =====
void print_person_friends(Person* p) {
    printf("%s's friends: ", p->name);
    if (p->num_friends == 0) printf("(none)");
    else for (int i = 0; i < p->num_friends; i++) {
        printf("%s", p->friends[i]->name);
        if (i < p->num_friends - 1) printf(", ");
    }
    printf("\n");
}

// ===== SAVE NETWORK =====
void save_network(Network* net) {
    FILE* fp = fopen(FILENAME, "w");
    if (!fp) { printf("Error opening file for writing!\n"); return; }
    fprintf(fp, "%d\n", net->num_people);
    for (int i = 0; i < net->num_people; i++) fprintf(fp, "%s\n", net->people[i]->name);
    for (int i = 0; i < net->num_people; i++) {
        Person* p = net->people[i];
        for (int j = 0; j < p->num_friends; j++) {
            int idx = -1;
            for (int k = 0; k < net->num_people; k++) if (net->people[k] == p->friends[j]) { idx = k; break; }
            if (idx > i) fprintf(fp, "%s,%s\n", p->name, p->friends[j]->name);
        }
    }
    fclose(fp);
    printf("Network saved to '%s'.\n", FILENAME);
}

// ===== LOAD NETWORK =====
void load_network(Network* net) {
    FILE* fp = fopen(FILENAME, "r");
    if (!fp) { printf("No saved network found.\n"); return; }

    for (int i = 0; i < net->num_people; i++) {
        if (net->people[i] != NULL) {
            free(net->people[i]->friends);
            free(net->people[i]);
        }
    }
    net->num_people = 0;

    int num_people;
    fscanf(fp, "%d\n", &num_people);
    for (int i = 0; i < num_people; i++) {
        char name[30];
        fgets(name, 30, fp);
        name[strcspn(name, "\n")] = '\0';
        add_person(net, name);
    }

    char line[100];
    while (fgets(line, 100, fp)) {
        line[strcspn(line, "\n")] = '\0';
        char* name1 = strtok(line, ",");
        char* name2 = strtok(NULL, ",");
        if (name1 && name2) {
            Person* p1 = find_person(net, name1);
            Person* p2 = find_person(net, name2);
            if (p1 && p2) {
                p1->friends = realloc(p1->friends,(p1->num_friends+1)*sizeof(Person*));
                p1->friends[p1->num_friends++] = p2;
                p2->friends = realloc(p2->friends,(p2->num_friends+1)*sizeof(Person*));
                p2->friends[p2->num_friends++] = p1;
            }
        }
    }
    fclose(fp);
    printf("Network loaded from '%s'.\n", FILENAME);
}

// ===== FRIENDS OF FRIENDS HELPER =====
void find_fof_recursive(Network* net, Person* p, Person* origin, int current_depth, int max_depth, int* visited) {
    if (current_depth >= max_depth) return;

    for (int i = 0; i < p->num_friends; i++) {
        Person* f = p->friends[i];
        int idx = -1;
        for (int j = 0; j < net->num_people; j++) if (net->people[j] == f) { idx = j; break; }
        if (!visited[idx]) {
            visited[idx] = 1;
            for (int d = 0; d <= current_depth; d++) printf("  ");
            printf("-> %s (depth %d)\n", f->name, current_depth+1);
            find_fof_recursive(net, f, origin, current_depth+1, max_depth, visited);
        }
    }
}

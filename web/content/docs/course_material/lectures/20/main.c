#include <stdio.h>

typedef enum RelStatus {
    NotMentioned,
    Single,
    Engaged,
    Married
} RelStatus;

char rel_status_string[4][20] = {
    "Not Mentioned",
    "Single",
    "Engaged",
    "Married"
} ;

typedef struct Person {
    char name[100];
    int age;
    RelStatus relstatus;
} Person;

typedef struct SocialNet {
    Person members[100];
    int size;
} SocialNet;

void print_network(SocialNet* net) {
    printf("Name\tAge\tRel Status\n");
    for (int i = 0; i < net->size; i++) {
        Person* p = &(net->members[i]);
        printf("%s\t%d\t%s\n", p->name, p->age, rel_status_string[p->relstatus]);
    }
}

int main(int argc, char** argv) {
    
    printf("%d\t", argc);
    for (int i = 0; i < argc; i++) {
        printf("%s\t", argv[i]);
    }
    printf("\n");
    
    SocialNet social_net = {
        .members = {
            { "Alice",    24,  NotMentioned},
            { "Bob",      28,  Married},
            { "Charlie",  20,  Single},
        } ,
        .size = 3
    };
    // print_network(&social_net);
    return 0;
}
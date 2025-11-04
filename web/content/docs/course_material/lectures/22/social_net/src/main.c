#include "network.h"

// Function declarations for friendship-related operations
void remove_person(Network* net, const char* name);
void remove_friendship(Network* net, const char* name1, const char* name2);
int count_mutual_friends(Network* net, const char* name1, const char* name2);
Person* find_most_popular(Network* net);
void shortest_path(Network* net, const char* start_name, const char* end_name);
void suggest_friends(Network* net, const char* name);
int count_total_friendships(Network* net);
void print_sorted_by_friends(Network* net);

void menu() {
    printf("\n========= Mini Social Network =========\n");
    printf("1. Add Person\n");
    printf("2. Add Friendship\n");
    printf("3. Display Network\n");
    printf("4. Find Friends of Friends\n");
    printf("5. Save Network\n");
    printf("6. Load Network\n");
    printf("7. Remove Person\n");
    printf("8. Remove Friendship\n");
    printf("9. Count Mutual Friends\n");
    printf("10. Find Most Popular Person\n");
    printf("11. Shortest Path Between People\n");
    printf("12. Suggest Friends\n");
    printf("13. Count Total Friendships\n");
    printf("14. Print Sorted by Number of Friends\n");
    printf("0. Exit\n");
    printf("=======================================\n");
}

int main() {
    Network* net = create_network();
    load_network(net);

    int choice;
    char name1[30], name2[30];

    while (1) {
        menu();
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter name: ");
                fgets(name1, 30, stdin);
                name1[strcspn(name1, "\n")] = '\0';
                add_person(net, name1);
                break;

            case 2: {
                printf("Enter first person: ");
                fgets(name1, 30, stdin);
                name1[strcspn(name1, "\n")] = '\0';
                printf("Enter second person: ");
                fgets(name2, 30, stdin);
                name2[strcspn(name2, "\n")] = '\0';
                Person* p1 = find_person(net, name1);
                Person* p2 = find_person(net, name2);
                if (!p1 || !p2) {
                    printf("One or both people not found.\n");
                    break;
                }
                p1->friends = realloc(p1->friends, (p1->num_friends + 1) * sizeof(Person*));
                p1->friends[p1->num_friends++] = p2;
                p2->friends = realloc(p2->friends, (p2->num_friends + 1) * sizeof(Person*));
                p2->friends[p2->num_friends++] = p1;
                printf("Friendship added between %s and %s.\n", name1, name2);
                break;
            }

            case 3:
                print_network(net);
                break;

            case 4: {
                printf("Enter name: ");
                fgets(name1, 30, stdin);
                name1[strcspn(name1, "\n")] = '\0';
                Person* p = find_person(net, name1);
                if (!p) { printf("Person not found.\n"); break; }

                int depth;
                printf("Enter depth: ");
                scanf("%d", &depth);
                getchar();

                int visited[MAX_PEOPLE] = {0};
                int idx = -1;
                for (int i = 0; i < net->num_people; i++)
                    if (net->people[i] == p) { idx = i; break; }
                if (idx >= 0) visited[idx] = 1;

                printf("Friends of friends for %s:\n", p->name);
                find_fof_recursive(net, p, p, 0, depth, visited);
                break;
            }

            case 5:
                save_network(net);
                break;

            case 6:
                load_network(net);
                break;

            case 7:
                printf("Enter name to remove: ");
                fgets(name1, 30, stdin);
                name1[strcspn(name1, "\n")] = '\0';
                remove_person(net, name1);
                break;

            case 8:
                printf("Enter first person: ");
                fgets(name1, 30, stdin);
                name1[strcspn(name1, "\n")] = '\0';
                printf("Enter second person: ");
                fgets(name2, 30, stdin);
                name2[strcspn(name2, "\n")] = '\0';
                remove_friendship(net, name1, name2);
                break;

            case 9:
                printf("Enter first person: ");
                fgets(name1, 30, stdin);
                name1[strcspn(name1, "\n")] = '\0';
                printf("Enter second person: ");
                fgets(name2, 30, stdin);
                name2[strcspn(name2, "\n")] = '\0';
                printf("Mutual friends count: %d\n",
                       count_mutual_friends(net, name1, name2));
                break;

            case 10: {
                Person* popular = find_most_popular(net);
                if (popular)
                    printf("Most popular person: %s (%d friends)\n",
                           popular->name, popular->num_friends);
                else
                    printf("No people in network.\n");
                break;
            }

            case 11:
                printf("Enter start person: ");
                fgets(name1, 30, stdin);
                name1[strcspn(name1, "\n")] = '\0';
                printf("Enter end person: ");
                fgets(name2, 30, stdin);
                name2[strcspn(name2, "\n")] = '\0';
                shortest_path(net, name1, name2);
                break;

            case 12:
                printf("Enter name: ");
                fgets(name1, 30, stdin);
                name1[strcspn(name1, "\n")] = '\0';
                suggest_friends(net, name1);
                break;

            case 13:
                printf("Total friendships: %d\n", count_total_friendships(net));
                break;

            case 14:
                print_sorted_by_friends(net);
                break;

            case 0:
                save_network(net);
                free_network(net);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    free_network(net);
    return 0;
}

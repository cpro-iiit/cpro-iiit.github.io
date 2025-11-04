#ifndef FRIENDSHIPS_H
#define FRIENDSHIPS_H

#include "network.h"

void add_friendship(Network* net, const char* name1, const char* name2);
void remove_friendship(Network* net, const char* name1, const char* name2);
void remove_person(Network* net, const char* name);
int count_mutual_friends(Network* net, const char* name1, const char* name2);
Person* find_most_popular(Network* net);
int shortest_path(Network* net, const char* name1, const char* name2);
void suggest_friends(Network* net, const char* name);
int count_total_friendships(Network* net);
void print_sorted_by_friends(Network* net);
void find_friends_of_friends(Network* net, const char* name, int depth);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "friendships.h"

// ===== ADD FRIENDSHIP (already implemented) =====
void add_friendship(Network* net, const char* name1, const char* name2) {
    Person* p1 = find_person(net, name1);
    Person* p2 = find_person(net, name2);
    if(!p1 || !p2){ printf("One or both people not found!\n"); return; }
    if(p1==p2){ printf("Cannot befriend yourself!\n"); return; }

    for(int i=0;i<p1->num_friends;i++) if(p1->friends[i]==p2){ printf("Already friends!\n"); return; }

    p1->friends = realloc(p1->friends,(p1->num_friends+1)*sizeof(Person*));
    p1->friends[p1->num_friends++]=p2;
    p2->friends = realloc(p2->friends,(p2->num_friends+1)*sizeof(Person*));
    p2->friends[p2->num_friends++]=p1;
    printf("Friendship created between '%s' and '%s'!\n",name1,name2);
}

// ===== REMOVE FRIENDSHIP =====
void remove_friendship(Network* net, const char* name1, const char* name2){
    Person *p1=find_person(net,name1), *p2=find_person(net,name2);
    if(!p1 || !p2){ printf("One or both people not found!\n"); return; }

    // remove p2 from p1
    int idx=-1;
    for(int i=0;i<p1->num_friends;i++) if(p1->friends[i]==p2){ idx=i; break; }
    if(idx!=-1){
        for(int i=idx;i<p1->num_friends-1;i++) p1->friends[i]=p1->friends[i+1];
        p1->num_friends--;
        p1->friends = realloc(p1->friends,p1->num_friends*sizeof(Person*));
    }

    // remove p1 from p2
    idx=-1;
    for(int i=0;i<p2->num_friends;i++) if(p2->friends[i]==p1){ idx=i; break; }
    if(idx!=-1){
        for(int i=idx;i<p2->num_friends-1;i++) p2->friends[i]=p2->friends[i+1];
        p2->num_friends--;
        p2->friends = realloc(p2->friends,p2->num_friends*sizeof(Person*));
    }

    printf("Friendship removed between '%s' and '%s'\n",name1,name2);
}

// ===== REMOVE PERSON =====
void remove_person(Network* net,const char* name){
    Person* p=find_person(net,name);
    if(!p){ printf("Person not found!\n"); return; }

    // remove from friends
    for(int i=0;i<p->num_friends;i++){
        Person* f=p->friends[i];
        int idx=-1;
        for(int j=0;j<f->num_friends;j++) if(f->friends[j]==p){ idx=j; break; }
        if(idx!=-1){
            for(int j=idx;j<f->num_friends-1;j++) f->friends[j]=f->friends[j+1];
            f->num_friends--;
            f->friends=realloc(f->friends,f->num_friends*sizeof(Person*));
        }
    }

    free(p->friends);

    // remove from network
    int idx=-1;
    for(int i=0;i<net->num_people;i++) if(net->people[i]==p){ idx=i; break; }
    if(idx!=-1){
        free(net->people[idx]);
        for(int i=idx;i<net->num_people-1;i++) net->people[i]=net->people[i+1];
        net->num_people--;
    }

    printf("Person '%s' removed from network\n",name);
}

// ===== COUNT MUTUAL FRIENDS =====
int count_mutual_friends(Network* net,const char* name1,const char* name2){
    Person *p1=find_person(net,name1), *p2=find_person(net,name2);
    if(!p1 || !p2) return 0;
    int count=0;
    for(int i=0;i<p1->num_friends;i++)
        for(int j=0;j<p2->num_friends;j++)
            if(p1->friends[i]==p2->friends[j]) count++;
    return count;
}

// ===== FIND MOST POPULAR =====
Person* find_most_popular(Network* net){
    if(net->num_people==0) return NULL;
    Person* popular=net->people[0];
    int max=popular->num_friends;
    for(int i=1;i<net->num_people;i++)
        if(net->people[i]->num_friends>max){ popular=net->people[i]; max=popular->num_friends; }
    return popular;
}

// ===== SHORTEST PATH (BFS) =====
int shortest_path(Network* net,const char* name1,const char* name2){
    Person* start=find_person(net,name1);
    Person* end=find_person(net,name2);
    if(!start||!end) return -1;
    if(start==end) return 0;

    int* visited=calloc(net->num_people,sizeof(int));
    int* dist=calloc(net->num_people,sizeof(int));
    int* queue=malloc(net->num_people*sizeof(int));
    int front=0,rear=0;

    // map person pointer to index
    int start_idx=-1,end_idx=-1;
    for(int i=0;i<net->num_people;i++){
        if(net->people[i]==start) start_idx=i;
        if(net->people[i]==end) end_idx=i;
    }

    queue[rear++]=start_idx; visited[start_idx]=1; dist[start_idx]=0;

    while(front<rear){
        int cur_idx=queue[front++];
        Person* cur=net->people[cur_idx];
        for(int i=0;i<cur->num_friends;i++){
            // find index
            int f_idx=-1;
            for(int j=0;j<net->num_people;j++) if(net->people[j]==cur->friends[i]){ f_idx=j; break; }
            if(!visited[f_idx]){
                visited[f_idx]=1;
                dist[f_idx]=dist[cur_idx]+1;
                if(f_idx==end_idx){
                    int res=dist[f_idx];
                    free(visited); free(dist); free(queue);
                    return res;
                }
                queue[rear++]=f_idx;
            }
        }
    }

    free(visited); free(dist); free(queue);
    return -1;
}

// ===== SUGGEST FRIENDS =====
void suggest_friends(Network* net,const char* name){
    Person* p=find_person(net,name);
    if(!p){ printf("Person not found!\n"); return; }

    printf("Suggested friends for %s:\n",name);

    for(int i=0;i<net->num_people;i++){
        Person* candidate=net->people[i];
        if(candidate==p) continue;

        // already a friend?
        int already=0;
        for(int j=0;j<p->num_friends;j++) if(p->friends[j]==candidate) { already=1; break; }
        if(already) continue;

        int mutual=count_mutual_friends(net,name,candidate->name);
        if(mutual>0) printf(" - %s (%d mutual friend%s)\n",candidate->name,mutual,(mutual>1?"s":""));
    }
}

// ===== COUNT TOTAL FRIENDSHIPS =====
int count_total_friendships(Network* net){
    int total=0;
    for(int i=0;i<net->num_people;i++){
        for(int j=0;j<net->people[i]->num_friends;j++){
            // count only if friend index > i
            int idx=-1;
            for(int k=0;k<net->num_people;k++) if(net->people[k]==net->people[i]->friends[j]){ idx=k; break; }
            if(idx>i) total++;
        }
    }
    return total;
}

// ===== PRINT SORTED BY FRIENDS =====
int cmp_desc(const void* a,const void* b){
    Person* p1=*(Person**)a;
    Person* p2=*(Person**)b;
    return p2->num_friends - p1->num_friends;
}

void print_sorted_by_friends(Network* net){
    if(net->num_people==0){ printf("Network is empty!\n"); return; }
    Person** arr=malloc(net->num_people*sizeof(Person*));
    for(int i=0;i<net->num_people;i++) arr[i]=net->people[i];
    qsort(arr,net->num_people,sizeof(Person*),cmp_desc);
    for(int i=0;i<net->num_people;i++)
        printf("%s (%d friend%s)\n",arr[i]->name,arr[i]->num_friends,(arr[i]->num_friends==1?"":"s"));
    free(arr);
}

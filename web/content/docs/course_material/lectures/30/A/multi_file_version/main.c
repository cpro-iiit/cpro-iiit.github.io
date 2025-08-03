#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "social_net.h"

int main() {
	// SocialNet s = {
	// 	.members = {
	// 		{ "Ramu", 19, Single, .friends_size = 0},
	// 		{ "Ammu", 21, Engaged, .friends_size = 0},
	// 		{ "Vinod", 24, Married, .friends_size = 0}
	// 	},
	// 	.size = 3
	// };

    SocialNet s = { .size = 0 };
    Person A = { "Ramu", 19, Single, .friends_size = 0};
    append(s.members, A);
    Person B = { "Ammu", 21, Engaged, .friends_size = 0};
    append(s.members, B);
    Person C = { "Vinod", 24, Married, .friends_size = 0};
    append(s.members, C);
    
    
	add_friend(element_at(s.members, 0) , element_at(s.members, 1) );
	add_friend(&(s.members[0]) , &(s.members[2]) );
	add_friend(&(s.members[1]) , &(s.members[2]) );
	add_friend(&(s.members[2]) , &(s.members[0]) );
	
	print_socialnet(&s);

	
	return 0;
}

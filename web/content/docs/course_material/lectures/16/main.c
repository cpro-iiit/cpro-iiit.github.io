
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int** social_net = malloc(4*sizeof(int*))
    social_net[0] =  malloc(3*sizeof(int));
    social_net[1] = malloc(1*sizeof(int));
    social_net[2] = NULL;
    social_net[3] = malloc(3*sizeof(int));

    (social_net[0])[0] = 1;
    (social_net[0])[1] = 2;
    (social_net[0])[2] = 3;    

    (social_net[1])[0] = 1;


    (social_net[3])[0] = 0;
    (social_net[3])[1] = 2;
    (social_net[3])[2] = 1;    


     
    for(int i = 0; i < 4; i++) {
        if (social_net[i] != NULL)  free(social_net[i]);
    }
    free(social_net);
    return 0;
}
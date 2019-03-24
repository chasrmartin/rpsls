/* pick.c -- choose a play for RPSLS randomly */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "roshambo.h"

const char * pick(){

    return plays[rand()%TABLE_SIZE];
}
#ifdef MAIN
/* this main exists to test the ramndomness because it was
 * unnecessarily hairy getting rand seeded correctly.
 *
 * $ make picktest
 *
 * will build and run the test.
 */
 
int main(int argc, char * argv[]){
    srand(getms());
    for(int ix=0; ix<atoi(argv[1]); ix++){
        printf("Play: %s\n", pick());
    }
    return 0;
}
#endif      

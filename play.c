/* play.c -- top level player program for roshambo game
 * =================================================================
 *
 * This is a worked example for Cole D's assignment.
 *
 * ABSTRACT
 *
 *      The problem is to play roshambo ("Rock, paper, scissors")
 *      multiple times, where the player runs a referee and two player
 *      processes using fork(2)/exec(2) and the players communicate
 *      with the referee via UNIX-domain sockets.
 *
 * SYNOPSIS
 *
 *      $ play n
 *
 *      where n is the number of times to play the overall game
 *
 * AUTHOR
 *
 *      Charlie Martin <chasrmartin@gmail.com>
 *
 * =================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "roshambo.h"

int main(int argc, char * argv[]) {
    int plays = 1;              /* Number of times to play, default 1 */
    int ix ;                    /* Utility index */
    pid_t pid;                  /* Child process pid for fork(2) */
    int wstatus;                /* status from wait */
    fprintf(stderr, "Started master player program.\n");

    if(argc == 1){
        fprintf(stderr, "No argument given, defaulting to %d\n", plays);
    } else {
        plays = atoi(argv[1]);
    }

    for(ix = 0; ix < plays; ix++){
        if((pid = fork()) < 0){
            fprintf(stderr,"fork(2) failed!");
            exit(pid);
        } else if (pid == 0){   /* child process */
            execl("referee","referee", 0);
            fprintf(stderr,"execl failed?!\n");
        } else {                /* parent process */
            wait(&wstatus);
        }
    }
    fprintf(stderr, "games over!\n");
    exit(0);
}
 

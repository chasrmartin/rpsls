/* referee.c -- referee roshambo games
 * =================================================================
 * Referees a single gave of RPSLF.
 * =================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "roshambo.h"

int main(int argc, char * argv[]){
    pid_t pid;                  /* for fork(2) */
    int wstatus;                /* for wait(2) */
    int ix;                     /* utility index */
    char p_name[50];            /* player process name */
    int server_fd ;             /* server file descriptor */
    struct sockaddr server_s ;  /* socket description */
    socklen_t sock_len;         /* for accept(2) */
    int client_fd ;             /* client fd for connection */
    char bufr[BUFSIZ];          /* buffer for reads */
    char answers[2][BUFSIZ];    /* player 1 in answers[0] */
    int results ;
    fprintf(stderr, "Starting referee.\n");

    /*
     * Create the server-side socket
     */
    server_s.sa_family = AF_UNIX;
    strcpy(server_s.sa_data, SERVER_NAME);
    server_fd = socket(AF_UNIX, SOCK_STREAM,0);
    unlink(SERVER_NAME);        /* make sure the socket is cleared */
    if(bind(server_fd, &server_s, sizeof(server_s)) < 0){
        perror("Can't bind!");
        exit(-1);
    }
    if(listen(server_fd,4) < 0){
        perror("listen failed!");
        exit(-1);
    }
    // assert if we got here we have the socket
    
    // just doing this to save duplicate code
    for(ix=0; ix < 2; ix++){    
        sprintf(p_name, "player%d", ix+1);
        if((pid = fork()) < 0){ /* error */
            fprintf(stderr, "Fork failed?!\n");
        } else if (pid == 0) {  /* child process */
            fprintf(stderr, ">  Running player %s\n", p_name);
            execl("player", p_name,0);
        } else {                /* still the referee */
            fprintf(stderr, ">Waiting for %s\n", p_name);
            if((client_fd = accept(server_fd, &server_s, &sock_len)) == -1){
                perror("accept failed!");
                exit(1);
            }
            bzero(bufr,BUFSIZ); /* clear the buffer */
            read(client_fd, bufr, BUFSIZ);
            fprintf(stderr,"Got message from client: %s\n", bufr);

            strcpy(bufr,"GO");
            write(client_fd, bufr, BUFSIZ);

            read(client_fd, bufr, BUFSIZ);
            fprintf(stderr,"Got message from client: %s\n", bufr);
            strcpy(answers[ix], bufr);
            strcpy(bufr,"STOP");
            write(client_fd, bufr, BUFSIZ);

            wait(&wstatus);
            close(client_fd);
        }
    }
    fprintf(stderr, "player1: %s player2: %s\n", answers[0], answers[1]);
    if((results = score(answers[0], answers[1])) < 0){
        printf("Player 1 wins!\n");
    } else if (results == 0) {
        printf("DRAW!\n");
    } else {
        printf("Player 2 wins!\n");
    }
            
    close(server_fd);   
    fprintf(stderr, "End referee.\n");
    exit(0);
}

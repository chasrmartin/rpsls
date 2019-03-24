/* player.c -- player roshambo games
 * =================================================================
 * Simulates one player in the Big Bang Theory extended roshambo
 * game.  ("Rock paper scissors lizard spock")
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
    int ix;                     /* utility index var */
    int server_fd ;             /* file descriptor of the server */
    struct sockaddr server_s ;  /* socket descriptor */
    char bufr[BUFSIZ];          /* data buffer for socket reads */
    fprintf(stderr, ">  Starting player %s.\n", argv[0]);
    srand(getms());             /* seed PRNG */

    /*
     * Create the client-side socket
     */
    server_s.sa_family = AF_UNIX; /* UNIX domain socket */
    strcpy(server_s.sa_data,SERVER_NAME);
    if((server_fd = socket(AF_UNIX, SOCK_STREAM,0)) < 0){
        perror("Socket creattion failed!");
        exit(-1);
    }
    if(connect(server_fd, &server_s, sizeof(server_s)) < 0){
        perror("Socket connect failed!");
        exit(-1);
    }
    bzero(bufr, BUFSIZ);        /* initialize the buffer in case */
    // send ready message
    strcpy(bufr,"player_ready");
    write(server_fd, bufr, BUFSIZ);
    do {
        read(server_fd, bufr, BUFSIZ);
        if (strcmp("GO",bufr) == 0 ){
            strcpy(bufr, pick());
            write(server_fd, bufr, BUFSIZ);
        }
    } while (strcmp(bufr, "STOP"));
        
    close(server_fd);
    fprintf(stderr, ">  End.\n");
    exit(0);
}

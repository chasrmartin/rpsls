/* Constants and other random stuff for the roshambo game */

#ifndef ROSHAMBO_H
#define ROSHAMBO_H
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define LIZARD 3
#define SPOCK 4

#define ROSHAMBO_MAX 2
#define SPOCK_MAX 4
#define TABLE_SIZE (SPOCK_MAX+1)

#define SEED 2687               /* 390th prime */
#define SERVER_NAME "R_SERVER"
static const char * plays[] = {
    "ROCK",
    "PAPER",
    "SCISSORS",
    "LIZARD",
    "SPOCK"
};      

int getms();                           /* get msec for seed */
const char * pick();                   /* pick a move */
int score(const char *, const char *); /* score moves */

#endif


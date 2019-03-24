/* score.c -- determine winning pair for roshambo with BBT extensions */

/* Canonically:
 * 'As Sheldon explains, "Scissors cuts paper, paper covers rock, rock
 *  crushes lizard, lizard poisons Spock, Spock smashes scissors,
 *  scissors decapitates lizard, lizard eats paper, paper disproves
 *  Spock, Spock vaporizes rock, and as it always has, rock crushes
 *  scissors."'
 * Reference:
 *  https://the-big-bang-theory.com/rock-paper-scissors-lizard-spock/
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "roshambo.h"

/* -1, 0, 1 for [X][Y] loses, draws, wins */
static int scoring[TABLE_SIZE][TABLE_SIZE] = {
    /*R,  P,  S,  L,  SP */
    { 0, -1,  1,  1, -1},            /* ROCK */
    {-1,  0,  1, -1, -1},            /* PAPER */
    {-1,  1,  0,  1, -1},            /* SCISSORS */
    {-1,  1, -1,  0,  1},            /* LIZARD */
    { 1, -1,  1, -1,  0}             /* SPOCK */
};

static int get_ix(const char * play){
    int ix;
    for(ix=0; ix < TABLE_SIZE; ix++)
        if(strcmp(plays[ix], play) == 0)
            return ix;
    return TABLE_SIZE;
}

int score(const char * p1_play, const char * p2_play){
    return scoring[get_ix(p1_play)][get_ix(p2_play)];
}

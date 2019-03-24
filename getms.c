/* return the time in ms */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include "roshambo.h"
static struct timeval tv;
int getms() {
    if(gettimeofday(&tv,NULL) < 0) {
        return -1;
    } else {
        return tv.tv_usec;
    }
}

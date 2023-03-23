#include "utmplib.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show_info(struct utmp* utp)
{
    if (utp->ut_type != USER_PROCESS) {
        return;
    }
    printf("user name: %-8.8s", utp->ut_user);
    printf(" ");
    printf("the tty : %-8.8s", utp->ut_line);
    printf(" ");
    printf("the time : %10d", utp->ut_tv.tv_usec);
    printf(" ");
    printf("host : (%s)", utp->ut_host);
    printf("\n");
}

void func()
{
    struct utmp* utbuffp;
    if (utmp_open(UTMP_FILE) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }

    while ((utbuffp = utmp_next()) != (struct utmp*)NULL) {
        show_info(utbuffp);
    }
    utmp_close();
    return;
}

int main(void)
{
    func();
    exit(1);
}

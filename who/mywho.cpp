//the implement of who
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SHOWHOST
void func();
void show_info(struct utmp* utp);
int main(void){
    func();
    exit(1);
}

void func(){
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);
    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
        perror(UTMP_FILE);
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen){
        show_info(&current_record);
    }
    close(utmpfd);

    return;

}

void show_info(struct utmp* utp){
//only printf message when type is user
    if (utp->ut_type != USER_PROCESS)
        return;
    printf("user name : %-8.8s", utp->ut_user);
    printf(" ");
    printf("the tty : %-8.8s", utp->ut_line);
    printf(" ");
//    there is no ut_time here
//    struct timeval tv;
//    gettimeofday(&tv, nullptr);
//    utp->ut_tv.tv_sec = tv.tv_sec;
//    utp->ut_tv.tv_usec = tv.tv_usec;
    printf("the time : %10d", utp->ut_tv.tv_usec);
    printf(" ");
#ifdef SHOWHOST
   printf("host : (%s)", utp->ut_host); 
#endif
   printf("\n");
}

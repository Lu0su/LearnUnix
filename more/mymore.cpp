/*
 second version, solve the ls /bin | ./mymore.cpp problem
 normally ls /bin | will put all information to the stdin
 the stdin will full of character and the getchar() will
 not work very well
 
 the /dev/tty will help us to read from input dev rather
 than stdin buf

 use it here!

 ----------------------------------------------
 this should not be the final
 2023 3.9 Thursday
 */
#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINElEN 512

void do_more(FILE*);
int see_more(FILE*);

int main(int argc, char* argv[]){
   FILE* fp;
      if (argc == 1){
          //stdin is a FILE*
          //no prameter, go with stdin
        do_more(stdin);
      } else {
          //prameter exist then go whit the filename
        while (--argc){
            if ((fp = fopen(*(++argv), "r")) != nullptr){
                do_more(fp);
                fclose(fp);
            } else {
                exit(1);
            }
        }
        return 0;
    }
}
//no prameter, print out what ever you input
void do_more(FILE* fp) {
    char line[LINElEN];//buf for input/file input
    int num_of_lines = 0;
    int relpy;
    FILE* fp_tty;
    if (!(fp_tty = fopen("/dev/tty", "r"))){
        perror("open tty false");
        exit(1);
    }
    while (fgets(line, LINElEN, fp)){
        //if lines > 24 the "more ?" should show up
        if (num_of_lines == PAGELEN){
            //get retrun from see_more
            relpy = see_more(fp_tty);
            if (relpy == 0){
                //q -> 0 -> break -> exit
                break;
            }
            // if PAGELEN show 24 new line
            // if /n show 1 new line
            num_of_lines -= relpy;
        }
        //meet eof -> exit
        if (fputs(line, stdout) == EOF){
            exit(1);
        }
        //total <= 24 lines
        num_of_lines++;
    }
}
// options
int see_more(FILE* cmd){
    int c;
    printf("\033[7m more? \033[m");
    while ((c = getc(cmd)) != EOF){
        if (c == 'q')
            return 0;
        if (c == ' ')
            return PAGELEN;
        if (c == '\n')
            return 1;
    }
    return 0;
}

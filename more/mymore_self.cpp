// try to make it myself
#include <stdlib.h>
#include <stdio.h>

#define LINES 24
#define BUF 512

//read from fp
void showLines(FILE* fp);
// read from /dev/tty to get the cmd input
int options(FILE* fp);

int main(int argc, char* argv[]){
    if (argc == 1){
        //no prameter read from stdin
        showLines(stdin);
    } else {
        // there one or more prameter exist, process them one by one
        while (--argc){
            //no need to process the first premeter, it is the program name
            FILE* fp;
            if ((fp = fopen(*(++argv), "r")) == nullptr){
                perror("open file false");
                exit(1);
            }
            showLines(fp);
            fclose(fp);
            //no need to worry the ls /bin | more
            //in that case, argc == 1
        }
    }
}

void showLines(FILE* fp){
    if (!fp) return;
    FILE* fp_tty;
    if ((fp_tty = fopen("/dev/tty", "r")) == nullptr){
        exit(1);
    }
    char buf[BUF];
    int numsOFLine = LINES;
    //input to the buf
    while (fgets(buf, BUF, fp)){
        if (numsOFLine == 0){
            //only when the numsOFLine gose to 0
            //we show more
            int res = options(fp_tty);
            if (res == -1){
                exit(1);
            }
            numsOFLine += res;
        }
        --numsOFLine;
        //you need to output it to the stdout
        if (fputs(buf, stdout) == EOF){
            exit(1);
        }
    } 
}

int options(FILE* cmd){
    //read directly from the cmd rather than stdin
    //if (!cmd) return -1;
    int ch;
    printf("\033[7m more? \033[m"); 
    while ((ch = getc(cmd)) != EOF){
        switch(ch){
            case 'q':
                //this func do not take control of this program.
                //so we do not exit here.
                return -1;
                break;
            case ' ':
                return LINES;
                break;
            case '\n':
                return 1;
                break;
            default:
                //blocked the func
                //wait for the cmd input
                continue;
        }
    }
}

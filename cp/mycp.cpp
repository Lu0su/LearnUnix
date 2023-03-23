#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 4096
// flags for creat
#define COPYMODE 0644

void oops(const char*, const char*);

int main(int argc, char* argv[])
{
    int  in_fd, out_fd, nchars;
    char buf[BUFSIZE];
    if (argc != 3) {
        fprintf(stderr, "usage: %s source destination\n", *argv);
        exit(1);
    }

    if ((in_fd = open(argv[1], O_RDONLY)) == -1) {
        oops("can not open", argv[1]);
    }

    // do not know how
    if ((out_fd = creat(argv[2], COPYMODE)) == -1) {
        oops("cannot creat", argv[2]);
    }

    // read how much it read, and eof return 0, error return -1
    // for the one, while is not really necessarry, if can do it also
    // but while is suggested
    while ((nchars = read(in_fd, buf, BUFSIZE)) > 0) {
        printf("read %d chars", nchars);
        // write return how much it write, return -1 for error
        if (write(out_fd, buf, nchars) != nchars) {
            oops("write error to ", argv[2]);
        }
    }

    if (nchars == -1) {
        oops("read error from", argv[1]);
    }

    if (close(in_fd) == -1 || close(out_fd) == -1) {
        oops("error closing", "");
    }
}

void oops(const char* s1, const char* s2)
{
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(1);
}

#include "stdio.h"
#include "fdict.h"

int pn(int key, int val){
    printf("  %d \t=>\t %d\n", key, val);
}

int main(){
    FDict *fd = fd_new();
    fd_insert(fd, 102, 19);
    fd_insert(fd, 10, 2);
    fd_insert(fd, 89, 2);
    fd_insert(fd, 350, 2);
    fd_insert(fd, 5, 2);
    fd_each(fd, pn);
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~");
    fd_remove(fd, 5);
    fd_each(fd, pn);

    return 0;
}

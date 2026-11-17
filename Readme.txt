Name : Aditya Raj 
Roll : 2401MC56


SET NO : 2


Q1 : 
Changes : vm.c -> Implemented a helper function to change permissions

Added declaration in defs.h : int             change_perm(pde_t *pgdir, uint , int , int);

Added system call and its declarations subsequently: 
#define SYS_mprotect 23
#define SYS_munprotect 24

For protest file the  code was as follows: 

#include "types.h"
#include "stat.h"
#include "user.h"


int main(void)
{
    printf(1,"Roll : 2401MC56\n");
    char *p;
    int pid;


    p = sbrk(4096);


    if (p == (char *)-1)
    {
        printf(1, "sbrk failed\n");
        exit();
    }


    p[0] = 'A';


    printf(1, "Initial value: %c\n", p[0]);


    if (mprotect(p, 1) < 0)
    {
        printf(1, "mprotect failed\n");
        exit();
    }


    printf(1, "After mprotect, read: %c\n", p[0]);


    pid = fork();


    if (pid < 0)
    {
        printf(1, "fork failed\n");
        exit();
    }


    if (pid == 0)
    {
        p[0] = 'B';
        printf(1, "Child write unexpectedly succeeded\n");
        exit();
    }


    wait();


    printf(1, "After child termination, parent reads: %c\n", p[0]);


    if (munprotect(p, 1) < 0)
    {
        printf(1, "munprotect failed\n");
        exit();
    }


    p[0] = 'C';


    printf(1, "After munprotect, write succeeded: %c\n", p[0]);


    printf(1, "Unaligned address test: %d\n", mprotect(p + 1, 1));


    printf(1, "Zero length test: %d\n", mprotect(p, 0));


    printf(1, "Out of range test: %d\n", mprotect(p + 4096, 1));


    exit();
}

It perfectly captured the expected outputs because of the correct implementation of the files!




Q2 : For question 2 : 
Added priority variable in proc.h
In proc.c -> Added scheduler logic and what to do when a runnable process is found i.e to assign a default priority of 10 
Then in scheduler logic scanned through the ptable for processes and then picked the one with lowest priority 

Wrote schedtest as per given guidelines to obtain the result!
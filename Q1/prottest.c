
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
#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
    printf(1, "Roll no : 2401MC56\n");
    int priorities[3] = {5, 10, 15};
    int pids[3];
    int i;
    volatile int j;

    set_priority(getpid(), 1);

    for (i = 0; i < 3; i++)
    {
        pids[i] = fork();

        if (pids[i] < 0)
        {
            printf(1, "Fork failed\n");
            exit();
        }

        if (pids[i] == 0)
        {
            set_priority(getpid(), priorities[i]);

            for (j = 0; j < 100000000; j++)
                ;

            printf(1, "Priority %d finished\n", priorities[i]);
            exit();
        }
    }

    for (i = 0; i < 3; i++)
        wait();

    printf(1, "Done\n");

    exit();
}

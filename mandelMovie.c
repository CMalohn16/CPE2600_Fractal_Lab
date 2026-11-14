/**
* @file mandelMovie.c
* @author Charlie Malohn
* @date 11/14/2026
* @class CPE2600 - 121
* @brief Creates a video zooming into the madelbrot set using varying numbers of child processes
* Compile with makefile and run with ./mandel
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_PROCESSORS 3
#define NUM_IMAGES 5


/**
 * @brief Exits the program gracefully
 */
void exitProgram() {
    sem_unlink("/mysem");
    exit(0);
}


int main(int argc, char *argv[])
{
    signal(SIGINT, exitProgram);

    sem_t *sem = sem_open("/mysem", O_CREAT, 0666, MAX_PROCESSORS);
    // sem_close(sem);
    // sem_unlink("/mysem");
    // return 0;

    for (int image_num = 0; image_num < NUM_IMAGES; image_num++)
    {
        sem_wait(sem);
        int pid = fork();
        if (pid == 0)
        {
            printf("Process %d is waiting\n", getpid());
            usleep(1000000);
            printf("Process %d is done\n", getpid());
            //execl("mandel", "-o", "cool.bmp", (char *) NULL);
            sem_post(sem);
            exit(0);
        }
    }

    for (int i = 0; i < MAX_PROCESSORS; i++)
    {
        sem_wait(sem);
        printf("i: %d\n", i);
    }

    sem_close(sem);
    exitProgram();

}

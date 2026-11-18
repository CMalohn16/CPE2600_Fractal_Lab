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

#define MAX_NAME_LEN 100
#define NUM_IMAGES 50

#define X_OFFSET_STR "0.331"
#define Y_OFFSET_STR "0.391"


/**
 * @brief Exits the program gracefully
 */
void exitProgram() {
    sem_unlink("/mysem");
    exit(0);
}


int main(int argc, char *argv[])
{
    char c;

    // Caps at 14 processors by default
	int maxProc = 14;

	while((c = getopt(argc,argv,"p:"))!=-1) {
		if (c == 'p')
		{
            maxProc = atoi(optarg);
		}
	}

    signal(SIGINT, exitProgram);

    sem_t *sem = sem_open("/mysem", O_CREAT, 0666, maxProc);

    for (int image_num = 0; image_num < NUM_IMAGES; image_num++)
    {
        sem_wait(sem);
        int pid = fork();
        if (pid == 0)
        {
            printf("Process %d is active\n", getpid());
            char filename[MAX_NAME_LEN];
            char scaleStr[25];
            sprintf(filename, "images/mandel%d.jpg", image_num);
            sprintf(scaleStr, "%f", 2.0 / ((image_num + 1) * (image_num + 1)));
            execl("mandel", "mandel", 
                "-x", X_OFFSET_STR,
                "-y", Y_OFFSET_STR,
                "-s", scaleStr, 
                "-o", filename, 
                "-p", "/mysem", 
                (char *) NULL);
        }
    }

    for (int i = 0; i < maxProc; i++)
    {
        sem_wait(sem);
        printf("i: %d\n", i);
    }

    sem_close(sem);
    exitProgram();

}

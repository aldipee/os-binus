#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h> 
#include <sys/wait.h>

/**
 * Process Flow Requirement:
 * P1: Parent Proses
 * P2 dan P3 merupakan child proses dari P1
 * P4 dan P5 merupakan child proses dari P3
 * 
 * 
 * Syncronization Requirement:
 * 1. Program membuat P1 yang merupakan parent proses
 * 2. Kemudian setelah P1 dibuat, P1 akan membuat P2 terlebih dahulu, kemudian dilanjutkan ke P3
 * 3. Kemudian P3 akan membuat P4 terlebih dahulu, kemudian dilanjutkan ke P5
 * 
 * 
 * Output Requirement: 
 * Setiap prosess parent maupun child proses akan menampilkan PID nya masing-masing
 * Apabila proses tersebut memiliki sebuah proses parent, maka proses tersebut akan menampilkan PID dari parent prosesnya
 * 
 */

int main() {

    // pid_p1 is the parent process, so we dont need to create it
    pid_t pid_p2, pid_p3, pid_p4, pid_p5;
    int status;


    printf("P1 (Root Process) PID: %d\n", getpid());

    // Create a new child process for p2
    pid_p2 = fork();

    // If new child process fails to create
    if(pid_p2 < 0){
        printf("Failed to create new child process (P2)\n");
        exit(EXIT_FAILURE);
    }

    if(pid_p2 == 0){
        // Now we are in child process for p2
        printf("P2 PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(1);
        printf("P2 Process Done\n");
        exit(EXIT_SUCCESS);
    }


    // Create a new child process for p3
    // Back to parent process or (P1)
    pid_p3 = fork();

    if(pid_p3 < 0){
        printf("Failed to create new child process (P3)\n");
        exit(EXIT_FAILURE);
    }

    if(pid_p3 == 0){
        printf("P3 PID: %d, Parent PID: %d\n", getpid(), getppid());

        // Now we are in child process for p3
        // lets create a new child process for p4
        pid_p4 = fork();

        if(pid_p4 < 0){
            printf("Failed to create new child process (P4)\n");
            exit(EXIT_FAILURE);
        }

        if(pid_p4 == 0){
            // Now we are in child process for p4
            printf("P4 PID: %d, Parent PID: %d\n", getpid(), getppid());
            sleep(1);
            printf("P4 Process Done\n");
            exit(EXIT_SUCCESS);
        }

        // Create a new child process for p5
        pid_p5 = fork();

        if(pid_p5 < 0){
            printf("Failed to create new child process (P5)\n");
            exit(EXIT_FAILURE);
        }

        if(pid_p5 == 0){
            // Now we are in child process for p5
            printf("P5 PID: %d, Parent PID: %d\n", getpid(), getppid());
            sleep(1);
            printf("P5 Process Done\n");
            exit(EXIT_SUCCESS);
        }


        // We are in parent process for p3
        // So P3 will wait for all of its child process P4 and P5 to finish

        // Wait for all child process to finish
        waitpid(pid_p4, &status, 0);
        waitpid(pid_p5, &status, 0);

        printf("P3: All child process (P4 and P5) has been finished\n");
        exit(EXIT_SUCCESS);
    }

    waitpid(pid_p2, &status, 0);
    waitpid(pid_p3, &status, 0);

    printf("P1: All child process (P2 and P3) has been finished\n");
    printf("P1 Process Done\n");

    

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGV 10

void com1_puis_com2_et_com3(char **com1, char **com2, char **com3) 
{
    int pid1 = fork();

    if (pid1 == 0) {
        execv(com1[0], com1);
        perror("Erreur dans com 1");
        exit(1);
    } else {
        int status;
        wait(&status);

        int pid2 = fork();

        if(pid2== 0) {

            int pid3 = fork();
            if(pid3 == 0) {
                execv(com3[0], com3);
                perror("Erreur dans com 2");
                exit(1);
            } else if (pid3 > 0) {
                execv(com2[0], com2);
                perror("Erreur dans com 3");
                exit(1);
            }
        } else if (pid2 > 0) {
            wait(&status);
        }
    }
} 

char **Ligne2Argv(char *ligne) {

    char **argv = (char**)malloc(MAX_ARGV * sizeof(char *));
    char *li = strdup(ligne);

    int i = 0;

    char *l = strtok(li, " ");

    while (l) {

        argv[i] = l;
        l = strtok(NULL, " ");
        i++;
    }

    return argv;
}


int main() {
    char *com1 = "Affiche 2 com1";
    char *com2 = "Affiche 3 com2";
    char *com3 = "Affiche 5 com3";


    char **argv1 = Ligne2Argv(com1);
    char **argv2 = Ligne2Argv(com2);
    char **argv3 = Ligne2Argv(com3);

    com1_puis_com2_et_com3(argv1, argv2, argv3);

    return 0;

}
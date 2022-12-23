//Author: TAYAB FAROOQ
//Description: parent process recives input form keyboard,
//Using pipe message is sent to child 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){
int pipefd[2]; 
int pid;
char message[100];
char buffToRecieveMessage[100];

int r = pipe(pipefd);
if (r == -1){
    perror("pipifd faild to create");
    return -1;
}

pid = fork();
if (pid == -1){
    perror("Fork Faild");
    return -1;
}

if (pid == 0){
    close(pipefd[0]);
    write(pipefd[1], buffToRecieveMessage, strlen(buffToRecieveMessage)+1);
}else if (pid > 0){
    close(pipefd[0]);
    read(STDIN_FILENO, message, sizeof(message)+1);   
    printf("parent recieved : %s\n", message); 
}else{
    perror("pipeFD faild");
}

return 0;
}

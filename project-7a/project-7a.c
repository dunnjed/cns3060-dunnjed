#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>//Used for the getpid() and kill() functions;



void parentSIGUSR1handler(int sig);
void parentSIGUSR2handler(int sig);
void childSIGUSR1handler(int sig);
void childSIGUSR2handler(int sig);



int main(int argc, char* argv[])
{

    printf("Name: Jed Dunn\nClass: CS3060\nSection: 601\n"); 


    struct sigaction actionOne;
    actionOne.sa_handler = parentSIGUSR1handler;
    sigemptyset(&actionOne.sa_mask);
    actionOne.sa_flags = SA_RESTART;

    struct sigaction actionTwo;
    actionTwo.sa_handler = parentSIGUSR2handler;
    sigemptyset(&actionTwo.sa_mask);
    actionTwo.sa_flags = SA_RESTART;

    sigaction(SIGUSR1,&actionOne,NULL);
    sigaction(SIGUSR2,&actionTwo,NULL);


    struct sigaction actionThree;
    struct sigaction actionFour;



    pid_t childpid;
    childpid = fork();

    if(childpid == 0)
    {
        //printf("Process ID: %d\n",childpid);
        //printf("From chlid process, Process ID: %d\n",getpid());

        actionThree.sa_handler = childSIGUSR1handler;
        sigemptyset(&actionThree.sa_mask);
        actionThree.sa_flags = SA_RESTART;

        actionFour.sa_handler = childSIGUSR2handler;
        sigemptyset(&actionFour.sa_mask);
        actionFour.sa_flags = SA_RESTART;

        sigaction(SIGUSR1,&actionThree,NULL);
        sigaction(SIGUSR2,&actionFour,NULL);

        printf("The child process is now running and is waiting for a 'task start' signal from the parent.\n");

        sigset_t set;
        sigfillset(&set);
        sigdelset(&set,SIGUSR1);
        sigsuspend(&set);//Now waiting for SIGUSR1 from parent.

        //The signal has been received from the parent.
        printf("The child is notifying the parent that it is starting its task.\n");

        sleep(3);//This allows time for the parent to block and wait for the SIGUSR1 signal from the child.

        if(kill(getppid(),SIGUSR1) != 0)//Sending the parent the SIGUSR1 signal.
            perror("An error occurred when the child sent the SIGUSR1 signal to the parent.\n");
        
        //The child process will now do some useless fork
        int i;
        for(i = 0; i < 1000; i++);

        
        printf("The child process has now completed its work.\n");
        sigaddset(&set,SIGUSR1);
        sigdelset(&set,SIGUSR2);//Setting the mask to suspend until SIGUSR2 received from parent.
        sigsuspend(&set);//The child is now suspending until SIGUSR2 is received from parent.

        //The SIGUSR2 signal has now been received from the parent.
        printf("The child process is now going to tell the parent that its work is done.\n");
        
        if(kill(getppid(),SIGUSR2) != 0)//Sending the parent the SIGUSR2 signal.
            perror("An error occurred when the child sent the SIGUSR2 signal to the parent.\n");

        printf("The child process is now terminating.\n");



    }
    else
    {
        //printf("Process ID: %d\n",childpid);
        printf("A child process has been created.\n");
        sleep(3);

        printf("The parent process is now notifying the child to start its task.\n");

        if(kill(childpid,SIGUSR1) != 0)//Sending the child the SIGUSR1 signal.  
            perror("An error occurred when the parent sent the SIGUSR1 signal to the child.\n");

        sigset_t set;
        sigfillset(&set);
        sigdelset(&set,SIGUSR1);
        sigsuspend(&set);//Now waiting for SIGUSR1 from child.

        //The SIGUSR1 signal has now been recieved from the child.
        sleep(3);//This call will allow the child time to do some work.

        if(kill(childpid,SIGUSR2) != 0)//Sending the child the SIGUSR2 signal.  
            perror("An error occurred when the parent sent the SIGUSR2 signal to the child.\n");

        printf("The parent sent the SIGUSR2 signal to the child.\n");

        sigaddset(&set,SIGUSR1);
        sigdelset(&set,SIGUSR2);//Setting the mask to suspend until SIGUSR2 received from child.
        sigsuspend(&set);//The parent is now suspending until SIGUSR2 is received from child.

        //The parent has now received the SIGUSR2 signal from the child.
        printf("The parent process is now terminating.\n");
    }


    return 0;
}


void parentSIGUSR1handler(int sig)
{
    printf("**** Parent SIGUSR1 handler – Received a 'task started' signal from child ****\n");
}

void parentSIGUSR2handler(int sig)
{
    printf("**** Parent SIGUSR2 handler – Received a 'task completed' signal from the child ****.\n");
}

void childSIGUSR1handler(int sig)
{
    printf("**** Child SIGUSR1 handler – Received a 'task start' signal from the parent process ****\n");
}

void childSIGUSR2handler(int sig)
{
    printf("**** Child SIGUSR2 handler – Received a ‘task complete verification’ signal from parent ****\n");
}



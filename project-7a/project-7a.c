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
    //Step 1
    printf("Name: Jed Dunn\nClass: CS3060\nSection: 601\n"); 


    struct sigaction actionOne;
    actionOne.sa_handler = parentSIGUSR1handler;//This is a pointer to the function that will handle the signal.
    sigemptyset(&actionOne.sa_mask);//These would be additional signals that I want to block while in the handler. I won't worry about any other signals.
    actionOne.sa_flags = SA_RESTART;//The power point slides say to assign SA_RESTART to sa.flags in order to restart any system calls interrupted by this signal once the signal handler has finished. That is why I assign SA_RESTART to sa_flags.

    struct sigaction actionTwo;
    actionTwo.sa_handler = parentSIGUSR2handler;
    sigemptyset(&actionTwo.sa_mask);
    actionTwo.sa_flags = SA_RESTART;
    //Step 2
    sigaction(SIGUSR1,&actionOne,NULL);
    sigaction(SIGUSR2,&actionTwo,NULL);


    struct sigaction actionThree;
    struct sigaction actionFour;



    pid_t childpid;
    childpid = fork();
    //Step 3
    if(childpid == 0)
    {

        actionThree.sa_handler = childSIGUSR1handler;
        sigemptyset(&actionThree.sa_mask);
        actionThree.sa_flags = SA_RESTART;

        actionFour.sa_handler = childSIGUSR2handler;
        sigemptyset(&actionFour.sa_mask);
        actionFour.sa_flags = SA_RESTART;
        //Step 6
        sigaction(SIGUSR1,&actionThree,NULL);
        sigaction(SIGUSR2,&actionFour,NULL);
        //Step 7
        printf("The child process is now running and is waiting for a 'task start' signal from the parent.\n");

        sigset_t set;
        sigfillset(&set);
        sigdelset(&set,SIGUSR1);
        //Step 7 continued
        sigsuspend(&set);//Now waiting for SIGUSR1 from parent.

        //Step 9
        //The signal has been received from the parent.
        printf("The child is notifying the parent that it is starting its task.\n");
        
        //Step 9 continued
        sleep(3);//This allows time for the parent to block and wait for the SIGUSR1 signal from the child.
    
        //Step 9 continued
        if(kill(getppid(),SIGUSR1) != 0)//Sending the parent the SIGUSR1 signal.
            perror("An error occurred when the child sent the SIGUSR1 signal to the parent.\n");
       
        //Step 9 continued
        //The child process will now do some useless work
        int i;
        for(i = 0; i < 1000; i++);

        //Step 10
        printf("The child process has done its work.\n");
        sigaddset(&set,SIGUSR1);
        sigdelset(&set,SIGUSR2);//Setting the mask to suspend until SIGUSR2 received from parent.
        //Step 10 continued
        sigsuspend(&set);//The child is now suspending until SIGUSR2 is received from parent.

        //Step 12
        //The SIGUSR2 signal has now been received from the parent.
        printf("The child process is telling the parent that its work is done.\n");
       
        //Step 12 continued
        if(kill(getppid(),SIGUSR2) != 0)//Sending the parent the SIGUSR2 signal.
            perror("An error occurred when the child sent the SIGUSR2 signal to the parent.\n");

        //Step 12 continued
        printf("The child process is now terminating.\n");



    }
    else
    {
        //Step 4
        printf("A child process has been created.\n");
        //Step 5
        sleep(3);
        //Step 8
        printf("The parent process is now notifying the child to start its task.\n");
        //Step 8 continued
        if(kill(childpid,SIGUSR1) != 0)//Sending the child the SIGUSR1 signal.  
            perror("An error occurred when the parent sent the SIGUSR1 signal to the child.\n");

        sigset_t set;
        sigfillset(&set);
        sigdelset(&set,SIGUSR1);
        //Step 8 continued
        sigsuspend(&set);//Now waiting for SIGUSR1 from child.
        
        //Step 11
        //The SIGUSR1 signal has now been recieved from the child.
        sleep(3);//This call will allow the child time to do some work.

        //Step 11 continued
        if(kill(childpid,SIGUSR2) != 0)//Sending the child the SIGUSR2 signal.  
            perror("An error occurred when the parent sent the SIGUSR2 signal to the child.\n");

        //Step 11 continued
        printf("The parent sent the SIGUSR2 signal to the child.\n");

        sigaddset(&set,SIGUSR1);
        sigdelset(&set,SIGUSR2);//Setting the mask to suspend until SIGUSR2 received from child.
        //Step 11 continued
        sigsuspend(&set);//The parent is now suspending until SIGUSR2 is received from child.

        //Step 13
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
    printf("**** Child SIGUSR2 handler – Received a 'task complete verification' signal from parent ****\n");
}



#include <stdio.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


typedef int bool;

void terminalStatus(bool);
void terminalCleanup(int);
void enterNonCanonicalMode();
void noFileArgsExist();
void fileArgsExist(char*);
void printPercentagePrompt(int numOfLinesPrompt, int totalLinesInFile);
void erasePercentagePrompt(char* filePath);
void printBytesReadPrompt(int bytesRead);
void eraseBytesPrompt();


#define SAVE_STATUS 1
#define RESTORE_STATUS 2


int main(int argc, char* argv[])
{
    signal(SIGINT,terminalCleanup);
    terminalStatus(SAVE_STATUS);
    enterNonCanonicalMode();

    if(argc == 1)//There are no command line args.
    {
        noFileArgsExist();
    }
    else//There should be only one command line argument.
    {
        fileArgsExist(argv[1]);
    }

    terminalStatus(RESTORE_STATUS); 

    return 0;
}

void fileArgsExist(char* filePath)
{
    int totalLinesInFile = 0;
    bool isFirstPercentagePrompt = 1;

    FILE *fp = fopen(filePath,"r");
    if(fp == NULL)
        perror(filePath);

    int tempChar = 0;
    while( (tempChar = fgetc(fp)) != EOF)
    {
        if(tempChar == '\n')
        {
            totalLinesInFile++;
        }
    }

    fseek(fp,0,SEEK_SET);//set the fp file stream back to the beginning.
        
    
    bool continuePrinting = 1;
    bool printOneLine = 0;
    int numOfLines = 0;//Use to determine when 23 lines have been read.
    int numOfLinesPrompt = 0;//Used to determine the total percetnage of the file that has been read.
    int c;
    while( (c = fgetc(fp)) != EOF)
    {
       if(continuePrinting)
       {
           if(printOneLine)//This if statement will be entered if the 'Enter' key was pressed.
           {
              putchar(c);

              if(c == '\n')
              {
                continuePrinting = 0;
                printOneLine = 0;
                numOfLinesPrompt++;

                printPercentagePrompt(numOfLinesPrompt, totalLinesInFile);
              }

           }
           
           else//The program will return to this else statement up and including when 23 lines have been printed.
           {
                putchar(c);
                if(c == '\n')
                {
                    numOfLines++;
                    numOfLinesPrompt++;
                }

                if(numOfLines != 0 && numOfLines % 23 == 0)//Once 23 lines have been read.
                {
                    if(isFirstPercentagePrompt)//If this is the first time that 23 lines have been read.
                    {
                        //Then print the file percentage prompt along with the file name.
                        double percentage = (((double)numOfLinesPrompt/(double)totalLinesInFile)*100);
                        printf("\033[7m%s %d%%\033[m",filePath, (int)percentage);
                        isFirstPercentagePrompt = 0;
                    }
                    else//If this is not the first time 23 lines have been read, then only print the file percentage prompt without the file name.
                    {
                        printPercentagePrompt(numOfLinesPrompt, totalLinesInFile);
                    }
                    continuePrinting = 0;
                    numOfLines = 0;
                }
            }
       }

       else
       {
            char userInput = 0;
            userInput = getchar();
            
            if(userInput == 'q')
            {
                terminalStatus(RESTORE_STATUS);
                exit(0);    
            }
            else if(userInput == 10)//10 is the ASCII decimal code for the 'Return' key. This means that only one line will be printed out.
            {
                //erase the percentage prompt before continuing
                erasePercentagePrompt(filePath);

                putchar(c);
                if(c == '\n')
                    numOfLinesPrompt++;

                continuePrinting = 1;
                printOneLine = 1;
            }
            else if(userInput == 32)//32 is the ASCII decimal code for 'Space' key. This means that 23 lines will be printed out.
            {
                continuePrinting = 1;
                printOneLine = 0;
                
                //erase the percentage prompt before continuing
                erasePercentagePrompt(filePath);

                putchar(c);
                if(c == '\n')
                {
                    numOfLines++;
                    numOfLinesPrompt++;
                }
            }
       }

    }
    erasePercentagePrompt(filePath);
    printPercentagePrompt(numOfLinesPrompt, totalLinesInFile);
    printf("\n");

    fclose(fp);
    

}

void printPercentagePrompt(int numOfLinesPrompt, int totalLinesInFile)
{
    double percentage = (((double)numOfLinesPrompt/(double)totalLinesInFile)*100);
    printf("\033[7m%d%%\033[m",(int)percentage);
}

void erasePercentagePrompt(char* filePath)
{
    const int MAX_REMAINDER_STR_LEN = 6;
    int i;
    int maxLength = strlen(filePath) + MAX_REMAINDER_STR_LEN;

    for(i = 0; i < maxLength; i++)
    printf("\b \b");
}

void noFileArgsExist()
{
    int bytesRead = 0;

    FILE *fp;
    fp = fdopen(0,"r");//0 is the file descriptor for stdin.
    
    bool continuePrinting = 1;
    bool printOneLine = 0;
    int numOfLines = 0;//Use to determine when 23 lines have been read.

    int c;
    while( (c = fgetc(fp)) != EOF)
    {
       bytesRead++;
       
       if(continuePrinting)
       {
           if(printOneLine)//This if statement will be entered if the 'Enter' key was pressed.
           {
              putchar(c);

              if(c == '\n')
              {
                continuePrinting = 0;
                printOneLine = 0;

                printBytesReadPrompt(bytesRead);
              }

           }
           
           else//The program will return to this else statement up and including when 23 lines have been printed.
           {
                putchar(c);
                if(c == '\n')
                {
                    numOfLines++;
                }

                if(numOfLines != 0 && numOfLines % 23 == 0)//Once 23 lines have been read.
                {
                    
                    printBytesReadPrompt(bytesRead);
                    
                    continuePrinting = 0;
                    numOfLines = 0;
                }
            }
       }

       else
       {
            char userInput = 0;
            userInput = getchar();
            
            if(userInput == 'q')
            {
                terminalStatus(RESTORE_STATUS);
                exit(0);    
            }
            else if(userInput == 10)//10 is the ASCII decimal code for the 'Return' key. This means that only one line will be printed out.
            {
                //erase the bytes read prompt before continuing
                eraseBytesPrompt();

                putchar(c);
                if(c == '\n')
                    numOfLines++;

                continuePrinting = 1;
                printOneLine = 1;
            }
            else if(userInput == 32)//32 is the ASCII decimal code for 'Space' key. This means that 23 lines will be printed out.
            {
                continuePrinting = 1;
                printOneLine = 0;
                
                //erase the bytes read prompt before continuing
                eraseBytesPrompt();

                putchar(c);
                if(c == '\n')
                {
                    numOfLines++;
                    
                }
            }
       }

    }
    eraseBytesPrompt();
    printBytesReadPrompt(bytesRead);
    printf("\n");

    fclose(fp);

    
}

void printBytesReadPrompt(int bytesRead)
{
    printf("\033[7mbytes %d\033[m",bytesRead);
}

void eraseBytesPrompt()
{
    const int MAX_BYTES_PROMPT_LENGTH  = 30;//I'm guessing that the maximum length of the bytes read prompt won't be longer than 30 characters.
    int i;
    
    for(i = 0; i < MAX_BYTES_PROMPT_LENGTH; i++)
    printf("\b \b");
}

void terminalStatus(bool statusFlag)
{
    static struct termios originalMode;
    static int originalTermStatusSaved = 0;

    if(statusFlag == SAVE_STATUS)
    {
        tcgetattr(0, &originalMode);
        originalTermStatusSaved = 1;
    }
    else if(originalTermStatusSaved && statusFlag == RESTORE_STATUS)
    {
        tcsetattr(0, TCSANOW, &originalMode);
    }

}

void terminalCleanup(int signum)
{
    if(signum == SIGINT)
    {
        terminalStatus(RESTORE_STATUS);
        printf("Original terminal settings have been restored.\n");
        
        exit(1);
    }
}

void enterNonCanonicalMode()
{
    struct termios terminalState;

    tcgetattr(0, &terminalState);
    terminalState.c_lflag &= ~ICANON;//Turns of canonical mode
    terminalState.c_lflag &= ~ECHO;//Turns of echoing of input in terminal.
    terminalState.c_cc[VMIN] = 1;//Allows for only getting 1 char at a time.
    tcsetattr(0, TCSANOW, &terminalState);
}

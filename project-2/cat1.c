#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printInputWithLineNums(void);
void printInputWO_LineNums(void);
void printFileWithLineNums(void);
void printFileWO_LineNums(void);


char printLineNum[] = "-n";
int newLine  = 13;



int main(int argc, char* argv[])
{
    
    
    //If the argument list contains 2 args, and the second arg is "-n",
    //then that means the input comes from standard input and it is
    //sent to standard output, but the output will be printed with
    //line numbers.
    if(argc == 2 && strcmp(printLineNum,argv[1]) == 0)
    {
        printInputWithLineNums();
        
    }
    
    else//Then print typed input to standard output without line numbers.
    {
        printInputWO_LineNums();
    }

    

    return 0;
}


void printInputWithLineNums(void)
{

    int c;
        int lineNum = 0;
        int newLineCount = 0;       
           
        while((c = getchar()) != EOF)
        {
            if((newLineCount % 2) == 0)
            {
                printf("     %d  ",++lineNum);
                newLineCount++;
            }
            if(c != 10)
            {
                putchar(c);
            }
            else
            {   
                putchar(c);
                newLineCount++;    
            }
        }
        
}

void printInputWO_LineNums(void)
{
       
    int c;
    while((c = getchar()) != EOF)
    {
        putchar(c);
    }
}




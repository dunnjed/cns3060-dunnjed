#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum args{frmStdinWithLineNum,frmStdinWO_LineNum,frmFileWithLineNum,frmFileWO_LineNum,invalidOption}args;


void printInputWithLineNums(void);
void printInputWO_LineNums(void);
void printFileWithLineNums(void);
void printFileWO_LineNums(void);
args checkCmdLineArgs(int argc, char* argv[]);


char printLineNum[] = "-n";
int newLine  = 13;

//fopen();


int main(int argc, char* argv[])
{
    args option;
    option = checkCmdLineArgs(argc,argv);
   
    if(option == frmStdinWithLineNum)
    {
        printInputWithLineNums();
        
    }
    else if(option == invalidOption)
    {
        printf("Invalid Option Entered\n");
    }
    else if(option == frmFileWithLineNum)
    {
        printFileWithLineNums();
    }
    else if(option == frmFileWO_LineNum)
    {
        printFileWO_LineNums();
    }
    else//Then print typed input to standard output without line numbers.
    {
        printInputWO_LineNums();
    }


    return 0;
}

args checkCmdLineArgs(int argc, char* argv[])
{
    //If the argument list contains 2 args, and the second arg is "-n",
    //then that means the input comes from standard input and it is
    //sent to standard output, but the output will be printed with
    //line numbers.
    //Example: ./cat1 -n
    if(argc == 2 && strcmp(printLineNum,argv[1]) == 0)
    {
        return frmStdinWithLineNum;
    }
    //Examples of rejected options: ./cat1 -s OR ./cat1 -ns OR ./cat1 -notAnOption OR ./cat1 -not an option
    else if(argc >= 2 && argv[1][0] == '-' && (argv[1][1] != 'n' || strlen(argv[1]) > 2))
    {
        return invalidOption;
    }
    //Examples: ./cat1 -n file1 file2 file3 ...
    else if(argc > 2 && strcmp(printLineNum,argv[1]) == 0)
    {
        return frmFileWithLineNum;
    }
    //Examples: ./cat1 file OR ./cat1 file1 file2 file3 ...
    else if(argc >= 2)
    {
        return frmFileWO_LineNum;
    }
    else//(argc == 1)
    {
        frmStdinWO_LineNum;
    }


}   

void printFileWithLineNums()
{
    

}

void printFileWO_LineNums()
{


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




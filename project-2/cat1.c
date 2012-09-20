#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum args{frmStdinWithLineNum,frmStdinWO_LineNum,frmFileWithLineNum,frmFileWO_LineNum,invalidOption}args;

const short PRINT_WITH_LINE_NUMS = 1;
const short PRINT_WITHOUT_LINE_NUMS = 0;

void printInputWithLineNums(void);
void printInputWO_LineNums(void);
void printFile(int argc, char *argv[],short printLineNums,int argStartIndex);
void printFileWO_LineNums(int argc, char *argv[]);
args checkCmdLineArgs(int argc, char *argv[]);


char printLineNum[] = "-n";
int newLine  = 13;

//fopen();


int main(int argc, char *argv[])
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
        int argStartIndex = 2;
        printFile(argc,argv,PRINT_WITH_LINE_NUMS,argStartIndex);
    }
    else if(option == frmFileWO_LineNum)
    {
        int argStartIndex = 1;
        printFile(argc,argv,PRINT_WITHOUT_LINE_NUMS,argStartIndex);

    }
    else//Then print typed input to standard output without line numbers.
    {
        printInputWO_LineNums();
    }


    return 0;
}

args checkCmdLineArgs(int argc, char *argv[])
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

//This is guaranteed to have 3 more more arguments in argv with the 
//second argument being "-n". The checkCmdLineArgs function already
//verified this.
void printFile(int argc, char *argv[],short printLineNums,int argStartIndex)
{
    int i;
    for(i = argStartIndex; i < argc; i++)
    {
        FILE *in;
        in = fopen(argv[i],"r");
        if(in == NULL)
        {
            perror(argv[i]);
            //printf("%p\n",in);

        }

        else
        {   
            const int BUF_SIZE = 128;
            const int CHARS_IN_BUF = 127;
            int lineNum = 0;
            char buffer[BUF_SIZE];
            size_t result;
            int errorFlag;
            int eofFlag;
            
            //Set all of the locations in the buffer to null;
            memset(buffer,'\0',BUF_SIZE);
            //buffer[BUF_SIZE - 1] = '\0';

            //Copy in data into all of the spots of the buffer except for the
            //last spot, which is already '\0',which will make this buffer
            //a null terminated string. It will now print out correctly
            //using printf.
            result = fread(buffer,sizeof(char),CHARS_IN_BUF,in);
            
            errorFlag = ferror(in);
            eofFlag = feof(in);
            //clearerr(in);
            
                        

            while(result == CHARS_IN_BUF)
            {   
                if(printLineNums)
                {   
                    if(lineNum == 0)
                    {
                        printf("%6d  ",++lineNum);
                    }   
                    int j;
                    for(j = 0;j < BUF_SIZE;j++)
                    {
                        putchar(buffer[j]);
                        if(buffer[j] == '\n' && j != BUF_SIZE-1)
                            printf("%6d  ",++lineNum);
                    }
                }
                else
                    printf("%s",buffer);


                result = fread(buffer,sizeof(char),CHARS_IN_BUF,in);
                
                errorFlag = ferror(in);
                eofFlag = feof(in);


            }

            //This if statement is entered if the file reached EOF
            //I can safely print out the remaing part of the buffer
            //that still contains data from the file.
            if(eofFlag != 0)//feof returns a nonzero value if there was an error
            {
                buffer[result] = '\0';
                if(printLineNums)
                {   
                    if(lineNum == 0)
                    {
                        printf("%6d  ",++lineNum);
                    }   
                    int j;
                    for(j = 0;j < result;j++)
                    {
                        putchar(buffer[j]);
                        if(buffer[j] == '\n' && j != result-1)
                            printf("%6d  ",++lineNum);
                    }
                }               
                else
                    printf("%s",buffer);

            }
            else if(errorFlag != 0)
            {
                printf("An error occured, cannot read the rest of %s.",argv[i]);
            }
            

            //fflush(in);//Flush the buffer before reading in a new file.
            
            //clear the error flags
            clearerr(in);

        }

        fclose(in);
    }

}

//This is guaranteed to have 2 more more arguments in argv with the 
//second argument being the first file name, with possibly more file names
//coming after the first file name.
//The checkCmdLineArgs function already verified this.
void printFileWO_LineNums(int argc, char *argv[])
{
    //I don't need this function anymore. 

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
            printf("%6d  ",++lineNum);
            newLineCount++;
        }
        if(c != 10)//10 is newline in ASCII
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




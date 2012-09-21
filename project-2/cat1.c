#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

typedef enum args{frmStdinWithLineNum,frmStdinWO_LineNum,frmFileWithLineNum,frmFileWO_LineNum,invalidOption}args;

const short PRINT_WITH_LINE_NUMS = 1;
const short PRINT_WITHOUT_LINE_NUMS = 0;

void printInputWithLineNums(void);
void printInputWO_LineNums(void);
void printFile(int argc, char *argv[],short printLineNums,int argStartIndex);
void printFileLineNumbers(char buffer[], int *lineNum, size_t result, short endOfFile,short lastFile,int currentFile);
args checkCmdLineArgs(int argc, char *argv[]);

void checkForMultipleFiles(int argc);//checks if there is more than one input file.
void checkForValidLastFile(int argc, char *argv[]);//checks if last file exists.

short multipleFilesExist = 0;//Assume to start out that there are not multiple files.This is used as a boolean variable.
short lastFileIsValid;//This is used as a boolean variable.
int nextToLastFile;//This will hold the index location of the next to last file in argv.


const char printLineNum[] = "-n";//Use to check if the "-n" option was passed to cat1


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
        checkForValidLastFile(argc,argv);
        checkForMultipleFiles(argc);

        if(multipleFilesExist)
            nextToLastFile = argc-2;//The location in argv of the next to last file. Used in my printFileLineNumbers function.
        else
            nextToLastFile = argc-1;//If there are not multiple files, then the nextToLastFile is just the last file.
            //I don't actually use nextToLastFile if multiple files don't exist. I just want to make sure that the variable
            //gets initialized to a value


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

//When this function is called, we know that there were fileName arguments
//passed to cat1
void printFile(int argc, char *argv[],short printLineNums,int argStartIndex)
{
    int lineNum = 0;
    const short END_OF_FILE = 1;



    int currentFile;
    for(currentFile = argStartIndex; currentFile < argc; currentFile++)
    {
        FILE *in;
        in = fopen(argv[currentFile],"r");
        if(in == NULL)
        {
            if(currentFile == argc-1)
                __fpurge(stdout);

            //An error message is printed out if the file cannot be opened.
            perror(argv[currentFile]);
        }

        else
        {   
            const int BUF_SIZE = 128;
            const int CHARS_IN_BUF = 127;
            char buffer[BUF_SIZE];
            size_t result;
            int errorFlag;
            int eofFlag;
            const int LAST_FILE = argc-1;
            
            //Set all of the locations in the buffer to null;
            memset(buffer,'\0',BUF_SIZE);

            //Copy in data into all of the spots of the buffer except for the
            //last spot, which is already '\0',which will make this buffer
            //a null terminated string. It will now print out correctly
            //using printf.
            result = fread(buffer,sizeof(char),CHARS_IN_BUF,in);
            
            //These flags will be set if "result" does not equal "CHARS_IN_BUF"
            errorFlag = ferror(in);
            eofFlag = feof(in);
                        
            //while the buffer is successfully filled with input, continue in the while loop
            while(result == CHARS_IN_BUF)
            {   
                if(printLineNums)
                {   
                    printFileLineNumbers(buffer,&lineNum,BUF_SIZE,!END_OF_FILE,currentFile == LAST_FILE,currentFile);
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
            if(eofFlag != 0)//feof returns a nonzero value if the end of file was reached
            {
                buffer[result] = '\0';//Terminates the remaing buffer input with '\0' so that it will print out correctly with printf
                if(printLineNums)
                {   
                    printFileLineNumbers(buffer,&lineNum,result,END_OF_FILE,currentFile == LAST_FILE,currentFile);
                }               
                else
                    printf("%s",buffer);

            }
            else if(errorFlag != 0)
            {
                printf("An error occured, cannot read the rest of %s.",argv[currentFile]);
            }

            //clear the error flags
            clearerr(in);

        }
        
        if(in != NULL)// "in" could be null if an invalid filename was passed as an argument.
        {
            fclose(in);//Close the file
        }
    }

}

//This function will print the line numbers for file input if the "-n" option was passed to cat1
void printFileLineNumbers(char buffer[], int *lineNum, size_t bufSize, short endOfFile,short lastFile,int currentFile)
{
    const int LAST_CHAR_IN_BUF = bufSize-1;
    if(*lineNum == 0)
    {
        printf("%6d  ",++(*lineNum));
    }   
    int j;
    for(j = 0;j < bufSize;j++)
    {
        putchar(buffer[j]);
        
        //If that last char that was printed is a '\n', then I need to enter this if statement.
        if(buffer[j] == '\n')
        {
            
            //I want to avoid printing out a new line number
            //if I am at the very last buffer location of the final
            //buffer and on the very last file.
            if(!(endOfFile && lastFile && j == LAST_CHAR_IN_BUF))
            {
                //Basically this if statement prevents the cat1 program from printing an extra
                //line number if the final file argument is for a file that doesn't exist.
                //This if statement says that if I am processing the next to last file, and the final
                //file(which is the next file to be processed) doesn't exist, and I'm at the last char
                //in this buffer, then I shouldn't print the next line number. Otherwise I will end up
                //printing a line number after the last error message is printed saying that the final 
                //file doesn't exist.
                //
                //What I described above doesn't work if there are multiple files at the end of the
                //file arguments list that don't exist. I fixed this problem by using __fpurge(stdout) on
                //line 124. There is further explanation of this in the README.md file.
                if(!(multipleFilesExist && currentFile == nextToLastFile && !lastFileIsValid && j == LAST_CHAR_IN_BUF))
                    printf("%6d  ",++(*lineNum));
            }

        }
    }

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


//This function is only called when I find out that
//the "-n" option was passed to cat1.
void checkForValidLastFile(int argc, char *argv[])
{
    int const LAST_FILE = argc-1;
    FILE *tempFile = fopen(argv[LAST_FILE],"r");
    if(tempFile == NULL)
    {
        lastFileIsValid = 0;
    }
    else
    {
        fclose(tempFile);
        lastFileIsValid = 1;
    }



}

//This function is only called when I find out that
//the "-n" option was passed to cat1.
void checkForMultipleFiles(int argc)
{
    const short YES = 1;
    int FIRST_FILE_ARG_LOCATION = 2;
    int LAST_FILE_ARG_LOCATION = argc-1;

    if(LAST_FILE_ARG_LOCATION - FIRST_FILE_ARG_LOCATION >= 1)
        multipleFilesExist = YES;


}

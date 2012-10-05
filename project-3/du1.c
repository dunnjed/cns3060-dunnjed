#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

typedef int boolean;
#define IN_START_DIRECTORY 1
#define NOT_IN_START_DIRECTORY 0
#define IS_HIDDEN 1
#define IS_NOT_HIDDEN 0

#define BUF_SIZE 128

int isHidden(char *fileName, boolean isA_Directory);
int isDirectory(struct stat *info);
void printDirContents(DIR *currentDir,char* dirPath, boolean inStartDirectory);



char* currentDirPath = ".";

int main(int argc, char *argv[])
{
    printf("\nProgram starts here:\n");
   
       
    if(argc == 1)
    {
        //then I have no arguments
        DIR* currentDir = opendir(currentDirPath);
        if(currentDir == NULL)
        {
            perror(currentDirPath);
            return -1;
        }
        else
           printDirContents(currentDir, currentDirPath, IN_START_DIRECTORY);

        closedir(currentDir);
    }
    else if(argc > 1)
    {

        int i;
        for(i = 1; i < argc; i++)
        {
            /*
            //This if statement will remove any trailing slashes that are found at the end of the given path  
            //except in the case that the root directory was passed as an argument to du1.
            if(strlen(argv[i]) > 1 && argv[i][strlen(argv[i]) - 1] == '/')
            {
                int index;
                index = strlen(argv[i]) - 1;
                while(argv[i][index] == '/')
                {
                    index--;
                }

                argv[i][index+1] = '\0';
                
            }*/
            /*
            H E L L O / / /
            [H][E][L][L][O][\0]    array has length 6
                                    strlen has length 5
            
            */
           // removeExtraSlashesInPath(argv[i]);
            


            struct stat info;

            if(stat(argv[i],&info) == -1)
                perror(argv[i]);//can't open dirItem. 
            else
            {
                if(isDirectory(&info))
                {
                    DIR* currentDir = opendir(argv[i]);
                    if(currentDir == NULL)
                    {
                        perror(argv[i]);
                        return -1;
                    }
                    else
                       printDirContents(currentDir, argv[i], IN_START_DIRECTORY);

                    closedir(currentDir);
                }
                else//It is a regular file
                {
                    char buffer[BUF_SIZE];
                    snprintf(buffer,BUF_SIZE,"%lld B",(long long)info.st_size);
                    printf("%-15s %s\n",buffer,argv[i]);
                }
            }


            
        }

    }



   return 0; 
}


int isDirectory(struct stat *info)
{
    int directory  = 0;

    switch(S_IFMT & info->st_mode)
    {
        case S_IFDIR:
            directory = 1;//The struct stat is a directory.
            break;
        default:
            directory = 0;//The struct stat is a file.
            break;

    }

    return directory;
}


int isHidden(char *fileName, boolean isA_Directory)
{   
    if(strlen(fileName) == 1 && fileName[0] == '.')// . is always hidden
        return IS_HIDDEN;
    else if(strlen(fileName) == 2 && fileName[0] == '.' && fileName[1] == '.')// .. is always hidden
        return IS_HIDDEN;
    else
        return IS_NOT_HIDDEN;
    }



//dirPath contains the path to the current directory being processed without the trailing "/"
void printDirContents(DIR *currentDIR,char* dirPath, boolean inStartDirectory)
{
    
    if(inStartDirectory)
    {

        struct stat tempInfo;

        if(stat(dirPath,&tempInfo) == -1)
            perror(dirPath);//can't open dirItem. 
        else
        {
            char buffer[BUF_SIZE];
            snprintf(buffer,BUF_SIZE,"%lld B",(long long)tempInfo.st_size);
            printf("%-15s %s\n",buffer,dirPath);
        }
        //If the dirPath is "/" and I'm in the start directory, then I don't want
        //to append another "/" to the fullDirPath in the upcoming while loop.
        //This if statement takes care of that possibility.
        if(strcmp(dirPath,"/") == 0)
            dirPath = "";
    }



    
    struct dirent* dirItem = 0;
    
    while((dirItem = readdir(currentDIR)) != NULL)
    {
        struct stat info;

        int slashLength = 1;
        char *fullDirPath = calloc(strlen(dirPath) + slashLength + strlen(dirItem->d_name) + 1,sizeof(char));
        strcpy(fullDirPath,dirPath);
        strcat(fullDirPath,"/");
        strcat(fullDirPath,dirItem->d_name);
        strcat(fullDirPath,"\0");
        //fullDirPath will contain the previous "dirPath" value and then have appended to it the
        //dirItem->d_name string, which is the newly found subdirectory or file  in the current directory.
        //For example, if I am currenlty in dir1, and dirItem->d_name is a directory called dir2, then
        //fullDirPath will now be "dir1/dir2". 

               
        if(stat(fullDirPath,&info) == -1)
            perror(dirItem->d_name);//can't open dirItem. 

        else
        {
                            
                
            if(!isHidden(dirItem->d_name,isDirectory(&info)) && isDirectory(&info))
            {
                DIR* dir = opendir(fullDirPath);
                if(dir == NULL)
                    perror(fullDirPath);
                else
                   printDirContents(dir, fullDirPath, NOT_IN_START_DIRECTORY);
                
                closedir(dir);
                
                char buffer[BUF_SIZE];
                snprintf(buffer,BUF_SIZE,"%lld B",(long long)info.st_size);
                printf("%-15s %s\n",buffer,fullDirPath);                   
            }
            else if(!isHidden(dirItem->d_name,isDirectory(&info)))
            {
                char buffer[BUF_SIZE];
                snprintf(buffer,BUF_SIZE,"%lld B",(long long)info.st_size);
                printf("%-15s %s\n",buffer,fullDirPath);

            }


            free(fullDirPath);
        }
    }



}



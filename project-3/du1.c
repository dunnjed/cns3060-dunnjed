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

int isHidden(char *fileName, boolean inStartDirectory);
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
    }





    /*
    char* dirName = (char*)get_current_dir_name();
    printf("%s\n",dirName);
    free(dirName);//dirName is malloced, you need to free dirName.  
   
    const char* currentRootDirName = "."; 
    DIR* currentDir = opendir(currentRootDirName);
    struct dirent* dir = 0;
    
    while((dir = readdir(currentDir)) != NULL)
    {
        struct stat info;

        if(stat(dir->d_name,&info) == -1)
            perror(dir->d_name);//can't open file

        else
        {
            
            printf("%-12s",dir->d_name);
            printf("%-lldB",info.st_size);

            switch(S_IFMT & info.st_mode)
            {
                case S_IFSOCK:
                    printf("socket");
                    break;
                case S_IFLNK:
                    printf("symbolic link");
                    break;
                case S_IFREG:
                    printf("regular file");
                    break;
                case S_IFBLK:
                    printf("block device");
                    break;
                case S_IFDIR:
                    printf("directory");
                    break;
                case S_IFCHR:
                    printf("character device");
                    break;
                case S_IFIFO:
                    printf("FIFO");
                    break;
                default:
                    printf("Unknown file type");
                    break;
            }

            printf("\n");
        }
    }
    
    */



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


int isHidden(char *fileName, boolean inStartDirectory)
{
    if(inStartDirectory && strlen(fileName) == 1 && fileName[0] == '.')// . is not hidden in the start directory
        return IS_NOT_HIDDEN;
    else if(!inStartDirectory && strlen(fileName) == 1 && fileName[0] == '.')// . is hidden in subdirectories
        return IS_HIDDEN;
    else if(strlen(fileName) == 2 && fileName[0] == '.' && fileName[1] == '.')// .. is always hidden
        return IS_HIDDEN;
    else if(strlen(fileName) > 1 && fileName[0] == '.')//If I'm in the start director -- THIS LINE WAS  else if(inStartDirectory && strlen(fileName) > 1 && fileName[0] == '.')
        return IS_HIDDEN;
    else
        return IS_NOT_HIDDEN;
    }



//dirPath contains the path to the current directory being processed without the trailing "/"
void printDirContents(DIR *currentDIR,char* dirPath, boolean inStartDirectory)
{
     
    
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
        //dirItem->d_name string, which is the newly found subdirectory in the current directory.
        //For example, if I am currenlty in dir1, and dirItem->d_name is a directory called dir2, then
        //fullDirPath will now be "dir1/dir2". 

               
        //If you are not in the start directory 
        if(stat(fullDirPath,&info) == -1)
            perror(dirItem->d_name);//can't open dirItem. 

        else
        {
            if(inStartDirectory)
            {
                /*
                int slashLength = 1;
                char *fullDirPath = calloc(strlen(dirPath) + slashLength + strlen(dirItem->d_name) + 1,sizeof(char));
                strcpy(fullDirPath,dirPath);
                strcat(fullDirPath,"/");
                strcat(fullDirPath,dirItem->d_name);
                strcat(fullDirPath,"\0");
                //fullDirPath will contain the previous "dirPath" value and then have appended to it the
                //dirItem->d_name string, which is the newly found subdirectory in the current directory.
                //For example, if I am currenlty in dir1, and dirItem->d_name is a directory called dir2, then
                //fullDirPath will now be "dir1/dir2".           
                
                */


                if(!isHidden(dirItem->d_name,inStartDirectory) && isDirectory(&info) && dirItem->d_name[0] != '.')
                {
                    DIR* dir = opendir(fullDirPath);
                    if(dir == NULL)
                        perror(fullDirPath);
                    else
                       printDirContents(dir, fullDirPath, NOT_IN_START_DIRECTORY);
             
                    
                    
                      
                    printf("%s\n",fullDirPath);

                }
                else if(!isHidden(dirItem->d_name,inStartDirectory))
                    printf("%s\n",dirItem->d_name);
            }
            else//NOT IN START DIRECTORY
            {
                if(!isHidden(dirItem->d_name,inStartDirectory) && isDirectory(&info))
                {
                    DIR* dir = opendir(fullDirPath);
                    if(dir == NULL)
                        perror(fullDirPath);
                    else
                       printDirContents(dir, fullDirPath, NOT_IN_START_DIRECTORY);
             
                    
                    printf("%s\n",fullDirPath);

                }
                else if(!isHidden(dirItem->d_name,inStartDirectory))
                    printf("%s\n",fullDirPath);






                /*
                if(!isHidden(dirItem->d_name,inStartDirectory))
                    printf("%s\n",fullDirPath);

                    */

            }
        }
    }



}



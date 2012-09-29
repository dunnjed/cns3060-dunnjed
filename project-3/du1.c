#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char *argv[])
{
    printf("\nProgram starts here:\n");
   
    /*
    const size_t BUF_SIZE = 256;
    char buf[BUF_SIZE];
    
    char dirNameTooLong; 
    if( (dirNameTooLong = getcwd(buf,BUF_SIZE)) != '\0')
        ;

    printf("%d\n",dirNameTooLong);
    printf("%s\n",buf);
*/
    //Get full path of the current directory.
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
            printf("%-12lld",info.st_size);

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
    
    



   return 0; 
}

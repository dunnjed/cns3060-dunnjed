#include <pthread.h>
#include <stdio.h>

void* incrementCounter(void* m);

int count;

int main(int argc, char* argv[])
{
    printf("PartB\n");
    
    pthread_t threadOne;
    pthread_t threadTwo;
    pthread_t threadThree;
    pthread_t threadFour;

    pthread_create(&threadOne,NULL,&incrementCounter,(void*)"One");
    pthread_create(&threadTwo,NULL,&incrementCounter,(void*)"Two");
    pthread_create(&threadThree,NULL,&incrementCounter,(void*)"Three");
    pthread_create(&threadFour,NULL,&incrementCounter,(void*)"Four");

    pthread_join(threadOne,NULL);
    pthread_join(threadTwo,NULL);
    pthread_join(threadThree,NULL);
    pthread_join(threadFour,NULL);

    printf("Value of count: %d\n",count);



    return 0;
}


void* incrementCounter(void* m)
{
    int i;
    for (i = 0; i < 10; ++i)
    {
        printf("t_%s; count is %d\n",(char*)m,count);
        int tempValue = count;
        printf("t_%s; count is %d, going to sleep.\n",(char*)m,count);
        sleep(1);
        printf("t_%s; tempValue is %d.\n",(char*)m,tempValue);
        tempValue = tempValue + 1;
        printf("t_%s; tempValue is now %d.\n",(char*)m,tempValue);
        printf("t_%s; count is %d before being updated.\n",(char*)m,count);
        count = tempValue;
        printf("t_%s; count is now %d after being updated.\n",(char*)m,count);

    }
    

    return NULL;
}

#include <pthread.h>
#include <stdio.h>

void* incrementCounter(void* m);

int count;

int main(int argc, char* argv[])
{
    pthread_t threadOne;
    pthread_t threadTwo;
    pthread_t threadThree;
    pthread_t threadFour;

    pthread_create(&threadOne,NULL,&incrementCounter,NULL);
    pthread_create(&threadTwo,NULL,&incrementCounter,NULL);
    pthread_create(&threadThree,NULL,&incrementCounter,NULL);
    pthread_create(&threadFour,NULL,&incrementCounter,NULL);

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
        int tempValue = count;
        //sleep(1);
        tempValue = tempValue + 1;
        count = tempValue;
    }

    return NULL;
}

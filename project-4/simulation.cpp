#include <iostream>



#define MAX_TRACK_NUM 100


int main(int argc, char *argv[])
{
    int numOfTracksEntered = 0;
    int trackNums[MAX_TRACK_NUM];    


    std::cout << "Enter your track numbers:" << std::endl;

    int trackNum = -1;
    std::cin >> trackNum;
    while(trackNum > 0)
    {
        trackNums[numOfTracksEntered++] = trackNum;
        std::cin >> trackNum;
    }

    for(int i = 0; i < numOfTracksEntered; i++)
        std::cout << trackNums[i] << std::endl;



    return 0;

}

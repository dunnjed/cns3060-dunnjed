#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>



#define MAX_NUM_OF_TRACKS 100
#define INITIAL_TRACK_POSITION 15
#define PREV_TRACK_POSITION 12

void firstComeFirstServed(int trackNums[], int numOfTracksEntered);
void shortestSeekTimeFirst(int trackNums[], int numOfTracksEntered);
void scanLook(int trackNums[], int numOfTracksEntered);

int main(int argc, char *argv[])
{
    
    int numOfTracksEntered = 0;
    int trackNums[MAX_NUM_OF_TRACKS];    


    std::cout << "Enter your track numbers:" << std::endl;

    int trackNum = -1;
    //std::cin >> trackNum;
    //int flag = 0;
    while((std::cin >> trackNum) && trackNum > 0 && numOfTracksEntered < MAX_NUM_OF_TRACKS)
    {
        trackNums[numOfTracksEntered++] = trackNum;
        //std::cout << " flag was: " << flag << std::endl;
        //std::cin >> trackNum;
    }

    //std::cout << std::endl;
    
    for(int i = 0; i < numOfTracksEntered; i++)
        std::cout << trackNums[i] << std::endl;



    if(numOfTracksEntered > 0)
    {
        firstComeFirstServed(trackNums, numOfTracksEntered);
        std::cout << std::endl;
        std::cout << std::endl;
        shortestSeekTimeFirst(trackNums, numOfTracksEntered);
        std::cout << std::endl;
        std::cout << std::endl;
        scanLook(trackNums, numOfTracksEntered);

    }




    return 0;

}

void firstComeFirstServed(int trackNums[], int numOfTracksEntered)
{
    const int fieldWidth = 30;
    int tracksTraversed = 0;
    int totalTracksTraversed = 0;
    std::cout << "First Come First Served" << std::endl;
    std::cout << std::setiosflags(std::ios::left) << std::setw(fieldWidth) << "Head Movement" << "Tracks Traversed" << std::endl;

    std::ostringstream movement;
    
    movement << "Tracks " << INITIAL_TRACK_POSITION << "-" << trackNums[0];
    tracksTraversed = std::abs(INITIAL_TRACK_POSITION - trackNums[0]);
    std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
    totalTracksTraversed += tracksTraversed;
    movement.str("");

    for(int i = 1; i < numOfTracksEntered; i++)
    {
        movement << "Tracks " << trackNums[i-1] << "-" << trackNums[i];
        tracksTraversed = std::abs(trackNums[i-1] - trackNums[i]);
        std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
        totalTracksTraversed += tracksTraversed;
        movement.str(""); 
    }
    std::cout << std::endl;
    std::cout << std::setw(fieldWidth) << "Total Tracks Traversed" << totalTracksTraversed  << std::endl;
    //3 23 65
    //3 23 65 34 21 19 10 12 32 97 16

}


void shortestSeekTimeFirst(int trackNums[], int numOfTracksEntered)
{
    const int fieldWidth = 30;

    //3 23 65 34 21 19 10 12 32 97 16
    int trackMovingTo = 0;//This will hold the track number that will be read next.
    int tracksTraversed = 0;//This is the number of tracks that were traversed to get from the current track to the next nearest track.
    int totalTracksTraversed = 0;//This will be the total number of tracks that were traversed after all the tracks have been read.

    int indexOfTrack = 0;//This value will be the index of the track that is closest to the currentTrack.
    
    std::cout << "Shortest Seek Time First" << std::endl;
    std::cout << std::setiosflags(std::ios::left) << std::setw(fieldWidth) << "Head Movement" << "Tracks Traversed" << std::endl;

    std::vector<int> tracks;//I read all of the tracks into a new vector. 
    for(int i = 0; i < numOfTracksEntered; i++)
        tracks.push_back(trackNums[i]);



    int traverseDistance = 0;//This will be updated to hold the traversal distance to the next nearest track from the current track.
    //This for loop will find the nearest track to the initial track, which is track 15.
    for(int i = 0; i < tracks.size(); i++)
    {
        if(i == 0)//This will simply initialize the traverseDistance variable to hold the distance to the first track in the tracks vector. 
        {
            traverseDistance = std::abs(INITIAL_TRACK_POSITION - tracks[i]);
            indexOfTrack = i;
        }
        else//Each subsequent iteration of the for loop will update the traverseDistance variable if the tracks[i] happens to be closer to the current track.
        {
            if(std::abs(INITIAL_TRACK_POSITION - tracks[i]) < traverseDistance)
            {
                traverseDistance = std::abs(INITIAL_TRACK_POSITION - tracks[i]);
                indexOfTrack = i;//This variable will hold the index value in the tracks vector of the closest track to the current track(that being the INITIAL_TRACK_POSITION in this case.
            }

        }



    }
    trackMovingTo = tracks[indexOfTrack];//I need to update the trackMovingTo variable to hold the value of the track that I will move to next.
    tracksTraversed = traverseDistance;//
    
    std::ostringstream movement;//Using the stringstream allows me to easily concatenate numbers into a string.
    
    movement << "Tracks " << INITIAL_TRACK_POSITION << "-" << trackMovingTo;
    std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
    totalTracksTraversed += tracksTraversed;
    movement.str("");//Clears the underlying string the stringsteam so that I can reuse it in later on.
    

    int currentTrack = trackMovingTo;//The track that I am moving to is now the current track.
    tracks.erase(tracks.begin()+indexOfTrack);//I remove the current track from the tracks vector because I have it saved in the currentTrack variable. Otherwise I would end up computing how far the currentTrack is from the currentTrack, which is unnecessary. I only want to compute how far the currentTrack is from every other track and not itself.

    while(tracks.size() > 0)
    {
        for(int i = 0; i < tracks.size(); i++)
        {
            if(i == 0)
            {
                traverseDistance = std::abs(currentTrack - tracks[i]);
                indexOfTrack = i;
            }
            else
            {
                if(std::abs(currentTrack - tracks[i]) < traverseDistance)
                {
                    traverseDistance = std::abs(currentTrack - tracks[i]);
                    indexOfTrack = i;//This variable will hold the index value in the tracks vector of the closest track to the current track.
                }

            }


        }
        trackMovingTo = tracks[indexOfTrack];//I need to update the trackMovingTo variable to hold the value of the track that I will move to next.
        tracksTraversed = traverseDistance;

        movement << "Tracks " << currentTrack << "-" << trackMovingTo;
        std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
        totalTracksTraversed += tracksTraversed;
        movement.str("");
        

        currentTrack = trackMovingTo;
        tracks.erase(tracks.begin()+indexOfTrack);




    } 

    std::cout << std::endl;
    std::cout << std::setw(fieldWidth) << "Total Tracks Traversed" << totalTracksTraversed  << std::endl;
        









}

void scanLook(int trackNums[], int numOfTracksEntered)
{
    const int fieldWidth = 30;
    int tracksTraversed = 0;
    int totalTracksTraversed = 0;


    std::vector<int> higherTracks;
    std::vector<int> lowerTracks;

    for(int i = 0; i < numOfTracksEntered; i++)
    {
       if(trackNums[i] > INITIAL_TRACK_POSITION)
           higherTracks.push_back(trackNums[i]);
       else
           lowerTracks.push_back(trackNums[i]);

    }

    std::sort(higherTracks.begin(),higherTracks.end());
    std::sort(lowerTracks.begin(),lowerTracks.end());

    

    

    std::cout << "Scan Look" << std::endl;
    std::cout << std::setiosflags(std::ios::left) << std::setw(fieldWidth) << "Head Movement" << "Tracks Traversed" << std::endl;

    std::ostringstream movement;
    
    movement << "Tracks " << INITIAL_TRACK_POSITION << "-" << higherTracks[0];
    tracksTraversed = std::abs(INITIAL_TRACK_POSITION - higherTracks[0]);
    std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
    totalTracksTraversed += tracksTraversed;
    movement.str("");

    for(int i = 1; i < higherTracks.size(); i++)
    {
        movement << "Tracks " << higherTracks[i-1] << "-" << higherTracks[i];
        tracksTraversed = std::abs(higherTracks[i-1] - higherTracks[i]);
        std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
        totalTracksTraversed += tracksTraversed;
        movement.str("");
    }

    movement << "Tracks " << higherTracks[higherTracks.size()-1] << "-" << lowerTracks[lowerTracks.size()-1];
    tracksTraversed = std::abs(higherTracks[higherTracks.size()-1] - lowerTracks[lowerTracks.size()-1]);
    std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
    totalTracksTraversed += tracksTraversed;
    movement.str("");

    for(int i = lowerTracks.size()-1; i >= 0; i--)
    {
        if(i-1 >= 0)//This keeps me from accessing an element ouside of the vector.
        {
            movement << "Tracks " << lowerTracks[i] << "-" << lowerTracks[i-1];
            tracksTraversed = std::abs(lowerTracks[i] - lowerTracks[i-1]);
            std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
            totalTracksTraversed += tracksTraversed;
            movement.str("");
        }        

    }
        
    std::cout << std::endl;
    std::cout << std::setw(fieldWidth) << "Total Tracks Traversed" << totalTracksTraversed  << std::endl;






}
/*

137 425 259 291 497 489 375 58 487 185 476 440 413 194 231 93 323 67 334 414 181 483 380 92 258 20 218 186 18 349 457 283 393 75 139 281 63 97 11 232 70 359 94 160 274 353 447 73 303 1 146 21 412 472 455 416 372 76 180 326 255 343 191 113 391 161 460 57 7 120 294 240 494 236 485 498 122 470 305 130 15 288 170 138 254 429 108 475 319 168 175 234 198 80 408 151 77 52 415 69













   */

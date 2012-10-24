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
void printStats(int currentTrack, int nextTrack, std::ostringstream &movement, int &totalTracksTraversed);


int main(int argc, char *argv[])
{
    
    int numOfTracksEntered = 0;
    int trackNums[MAX_NUM_OF_TRACKS];    

    std::cout << "Enter your track numbers:" << std::endl;

    int trackNum = -1;
    while((std::cin >> trackNum) && trackNum >= 0 && numOfTracksEntered < MAX_NUM_OF_TRACKS)
    {
        trackNums[numOfTracksEntered++] = trackNum;
    }

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
    else
    {
        std::cout << "Invalid input." << std::endl;
    }

    return 0;
}

void firstComeFirstServed(int trackNums[], int numOfTracksEntered)
{
    const int fieldWidth = 30;
    int totalTracksTraversed = 0;

    std::cout << "First Come First Served" << std::endl;
    std::cout << std::setiosflags(std::ios::left) << std::setw(fieldWidth) << "Head Movement" << "Tracks Traversed" << std::endl;

    std::ostringstream movement;
    
    printStats(INITIAL_TRACK_POSITION, trackNums[0], movement, totalTracksTraversed);

    for(int i = 1; i < numOfTracksEntered; i++)
    {
        printStats(trackNums[i-1], trackNums[i], movement, totalTracksTraversed);
    }
    std::cout << std::endl;
    std::cout << std::setw(fieldWidth) << "Total Tracks Traversed" << totalTracksTraversed  << std::endl;
}


void shortestSeekTimeFirst(int trackNums[], int numOfTracksEntered)
{
    const int fieldWidth = 30;

    int trackMovingTo = 0;//This will hold the track number that will be read next.
    int tracksTraversed = 0;//This is the number of tracks that were traversed to get from the current track to the next nearest track.
    int totalTracksTraversed = 0;//This will be the total number of tracks that were traversed after all the tracks have been read.

    int indexOfTrack = 0;//This value will be the index of the track that is closest to the currentTrack.
    
    std::cout << "Shortest Seek Time First" << std::endl;
    std::cout << std::setiosflags(std::ios::left) << std::setw(fieldWidth) << "Head Movement" << "Tracks Traversed" << std::endl;

    std::vector<int> tracks;//I read all of the tracks into a new vector. 
    for(int i = 0; i < numOfTracksEntered; i++)
        tracks.push_back(trackNums[i]);

    //This for loop will find the nearest track to the initial track, which is track 15.
    //The tracksTraversed variable will be updated to hold the traversal distance to the next nearest track from the current track.
    for(int i = 0; i < tracks.size(); i++)
    {
        if(i == 0)//This will simply initialize the traverseDistance variable to hold the distance to the first track in the tracks vector. 
        {
            tracksTraversed = std::abs(INITIAL_TRACK_POSITION - tracks[i]);
            indexOfTrack = i;
        }
        else//Each subsequent iteration of the for loop will update the traverseDistance variable if the tracks[i] happens to be closer to the current track.
        {
            if(std::abs(INITIAL_TRACK_POSITION - tracks[i]) < tracksTraversed)
            {
                tracksTraversed = std::abs(INITIAL_TRACK_POSITION - tracks[i]);
                indexOfTrack = i;//This variable will hold the index value in the tracks vector of the closest track to the current track(that being the INITIAL_TRACK_POSITION in this case.
            }
        }
    }
    trackMovingTo = tracks[indexOfTrack];//I need to update the trackMovingTo variable to hold the value of the track that I will move to next.
    tracksTraversed;// = traverseDistance;//
    
    std::ostringstream movement;//Using the stringstream allows me to easily concatenate numbers into a string.
    
    movement << "Tracks " << INITIAL_TRACK_POSITION << "-" << trackMovingTo;
    std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
    totalTracksTraversed += tracksTraversed;
    movement.str("");//Clears the underlying string of the stringsteam so that I can reuse it later on.

    tracksTraversed = 0;//I will reset this value to zero to begin the next round of iterations on the tracks vector.
    

    int currentTrack = trackMovingTo;//The track that I am moving to is now the current track.
    tracks.erase(tracks.begin()+indexOfTrack);//I remove the current track from the tracks vector because I have it saved in the currentTrack variable. Otherwise I would end up computing how far the currentTrack is from the currentTrack, which is unnecessary. I only want to compute how far the currentTrack is from every other track and not itself.

    while(tracks.size() > 0)
    {
        //The tracksTraversed variable will be updated to hold the traversal distance to the next nearest track from the current track.
        for(int i = 0; i < tracks.size(); i++)
        {
            if(i == 0)
            {
                tracksTraversed = std::abs(currentTrack - tracks[i]);
                indexOfTrack = i;
            }
            else
            {
                if(std::abs(currentTrack - tracks[i]) < tracksTraversed)
                {
                    tracksTraversed = std::abs(currentTrack - tracks[i]);
                    indexOfTrack = i;//This variable will hold the index value in the tracks vector of the closest track to the current track.
                }
            }
        }
        trackMovingTo = tracks[indexOfTrack];//I need to update the trackMovingTo variable to hold the value of the track that I will move to next.
        tracksTraversed;// = traverseDistance;

        movement << "Tracks " << currentTrack << "-" << trackMovingTo;
        std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
        totalTracksTraversed += tracksTraversed;
        movement.str("");

        tracksTraversed = 0;//I will reset this value to zero to begin the next round of iterations on the tracks vector.
        
        currentTrack = trackMovingTo;
        tracks.erase(tracks.begin()+indexOfTrack);
    } 

    std::cout << std::endl;
    std::cout << std::setw(fieldWidth) << "Total Tracks Traversed" << totalTracksTraversed  << std::endl;

}

void scanLook(int trackNums[], int numOfTracksEntered)
{
    const int fieldWidth = 30;
    int totalTracksTraversed = 0;


    std::vector<int> higherTracks;//This vector will contain all of the tracks above track 15.
    std::vector<int> lowerTracks;//This vector will contain all of the tracks below and including track 15(it will only include track 15 if it is entered again as input).

    for(int i = 0; i < numOfTracksEntered; i++)
    {
       if(trackNums[i] > INITIAL_TRACK_POSITION)
           higherTracks.push_back(trackNums[i]);
       else
           lowerTracks.push_back(trackNums[i]);

    }

    std::sort(higherTracks.begin(),higherTracks.end());
    std::sort(lowerTracks.begin(),lowerTracks.end());


    std::cout << "Scan-Look" << std::endl;
    std::cout << std::setiosflags(std::ios::left) << std::setw(fieldWidth) << "Head Movement" << "Tracks Traversed" << std::endl;

    std::ostringstream movement;
   
    //If the higherTracks vector isn't empty, then the for loop will print the stats for all the tracks higher than track 15.
    if(!higherTracks.empty())
    {
        printStats(INITIAL_TRACK_POSITION, higherTracks[0], movement, totalTracksTraversed);

        for(int i = 1; i < higherTracks.size(); i++)
        {
            printStats(higherTracks[i-1], higherTracks[i], movement, totalTracksTraversed);
        }
    }
    
    //This takes care of the traversal distance from the maximum track to the track that is closest to and below track 15.
    if(!higherTracks.empty() && !lowerTracks.empty())
        printStats(higherTracks[higherTracks.size()-1], lowerTracks[lowerTracks.size()-1], movement, totalTracksTraversed);
    
    //If the lowerTracks vector isn't empty, then the for loop will print the stats for all the tracks lower than track 15.
    if(!lowerTracks.empty())
    {
        if(higherTracks.empty())//If there were no tracks higher than 15, then I'll start at track 15 and immediately move downward to lower track numbers.
            printStats(INITIAL_TRACK_POSITION, lowerTracks[lowerTracks.size()-1], movement, totalTracksTraversed);

        for(int i = lowerTracks.size()-1; i >= 0; i--)
        {
            if(i-1 >= 0)//This keeps me from accessing an element ouside of the vector.
            {
                printStats(lowerTracks[i], lowerTracks[i-1], movement, totalTracksTraversed);
            }        
        }
    }
        
    std::cout << std::endl;
    std::cout << std::setw(fieldWidth) << "Total Tracks Traversed" << totalTracksTraversed  << std::endl;
}

void printStats(int currentTrack, int nextTrack, std::ostringstream &movement, int &totalTracksTraversed)
{
    const int fieldWidth = 30;
    int tracksTraversed = 0;

    movement << "Tracks " << currentTrack << "-" << nextTrack;
    tracksTraversed = std::abs(currentTrack - nextTrack);
    std::cout << std::setw(fieldWidth) << movement.str() << tracksTraversed << std::endl;
    totalTracksTraversed += tracksTraversed;
    movement.str("");//Clears the underlying string of the stringsteam so that I can reuse it later on.
}

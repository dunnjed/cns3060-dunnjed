Project4-Disk Scheduling
=============

Jed Dunn  

I liked that you gave us the option to write this program in any language that we wanted to. I chose C++ simply because I've 
never taken a class in C++ so I like to write programs in it whenever I get the chance so that I can continue to learn the 
language. I liked that you chose this assignment because it definitely helped me to understand more fully how these disk
scheduling algorithms work and why certain ones are better than others. You kind of get an idea of this from the slides,
but writing this program made those ideas much clearer and better to understand.


Summaries of Each Algorithm
---------------------------

###First Come First Served Algorithm###
This was by far the easieset algorithm to implement. What this algorithm does is it visits each track in the order that
they are received. This is the worst algorithm because it can end up moving all over the disk. So this algorithm causes 
the disk arm to end up traversing more tracks than the other algorithms. This algorithm's complexity is O(n).


###Shortest Seek Time First Algorithm###
This was the hardest algorithm to implement. This algorithm searches for the closest track to the current track, and then
the disk arm moves to that closest track. It then searches for the next closest track and moves to that one, and so on.
From testing my program it seems that this algorithm generally performs best. This algorithm's complexity is between O(n)
and O(n^2). I initially have to visit every track on the first iteration so that I can find which track is closest to the
initial track. After I find that out, then I can throw out this newly found closest track from my vector containing the
list of tracks. That means I have one less track to check on the next iteration. On each iteration I can remove the newly
found closest track from the vector, and therefore I have to check fewer and fewer tracks on each iteration. That is why 
it is more than O(n) but less than O(n^2) in complexity.


###Scan-Look Algorithm###
This was harder to implement than the First Come First Served Algorithm, but I thought it was quite a bit easier to implement
than the Shortest Seek Time First Algorithm. This algorithm involves visiting all of the tracks that are higher up than the
initial track. And they need to be visited in order starting with the track that is closest to 15 up to the track that is furthest
from 15. Then I backtrack and visit the track that was closest to 15 but lower than 15. Then I visit each subsequent track that
is lower than 15, starting with the one that is closest to 15 and then reading down until I get to the one that is furthest from 
track 15. I achieve this by reading all of the tracks into two separate vectors, one containing all of the tracks greater than 
15 and the other containing all of the tracks lower than 15. I then sort these two vectors and visit all the tracks in the 
appropriate order. I'm not sure of the compolexity of the sorting algorithm that the STL uses for the sort function. But visiting
all of the tracks after they are sorted is O(n) complexity.

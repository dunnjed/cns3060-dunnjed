Project6-Threads
=============

Jed Dunn  

PartA Explanation:
This program was the easiest to understand of all four programs. This program 
creates and starts each of the four threads, but it exits main without waiting
for the threads to terminate. This is why the value of "count" is 0 when it is
printed out at the end of the program.

PartB Explanation:
In program partb, I at first expected for count to be 40 once all of the threads
were done running, but after running the program the value of count was 10 instead.
After adding some printf statements to the incrementCounter() function, I was able
to understand better what was going on. It turns out that the program will first
run each thread in no particular order. For example, threadOne will run first and
it will save the value of "count" into its local variable called "tempValue". It then
sleeps and then execution moves to threadTwo (or threadThree or threadFour). Once
each of these threads has saved a local copy of "count" in its own "tempValue"
variable, then whichever thread first entered the sleep() function will then come out
of sleep and resume its execution. It will increment its own copy of "tempValue" and
then assign "count" the value of "tempValue". The next three threads will then do the
same thing. Each of the next three threads still have a value called "tempValue" that
has a value of 0, which is what count was before being incremented by threadOne. You
would think that threadTwo would then increment count to 2, but it doesn't. It simply
increments its own copy of "tempValue", which is still 0, up to the value of 1. It
then assigns count the value of 1 (it was already the value of 1 though because of 
threadOne's execution). Threads three and four will then do the exact same thing that
threadTwo did. Once they have all executed, "count" will now have the value of 1 still.
Then all the threads will go through the same exact cycle for a total of ten times.
In the end "count" will only reach a final value of 10.

PartC Explanation:
This program is different from partb in that the threads do not sleep after acquiring a local
copy of "count". This program has a problem in that there is the possibility that "count"
could end up with an incorrect value in the end. Say for example that three independent threads
assign their local copy of "tempValue" with "count" at the same time, and then increment
"tempValue" at the same time, and then update "count" with "tempValue" all at the same time.
Then "count" will end up being incremented by only 1 instead of by 3. But I tested this progam
many times and I always ended up with the correct answer of 40. This goes to show that problems
with race conditions are very hard to produce when testing your code.

PartD Explanation:
For partd, I put back the sleep() function that occurs in each of the threads and I then have to
add a mutex so that there is no data corruption when reading and writing the "count" variable.
I place this mutex lock before the place where the "count" variable is read and assigned to 
"tempValue". I unlock the mutex after "count" has been updated. This will assure that I am able to
read "count" without another thread trying to update it as I am reading it. This also assures that
multiple threads won't be trying to update "count" at the same time.




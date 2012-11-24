Project6-Threads
=============

Jed Dunn  

Start here...

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
then assigns count the value of 1 (it was alread the value of 1 though because of 
threadOne's execution). Threads three and four will then do the exact same thing that
threadTwo did. Once they have all executed, count will now have the value of 1 still.
Then all the threads will go through the same exact cycle for a total of ten times.
In the end "count" will only reach a final value of 10.

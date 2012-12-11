Project-7a
=============

Jed Dunn  

I didn't find this project too difficult to complete. I felt that I was able to
learn quite well how to register and use the signal handlers. 

One part that I was a little confused by was how to properly use the sigsuspend() 
function. Slide 42 from the Signals powerpoint slides says that there is always
the possibility that a signal could be sent before there is time to call the
sigsuspend() fucntion. If that happens, then sigsuspend() would end up waiting 
forever for a signal that actually arrived before sigsuspend() was called.
I don't feel like I needed to account for this situation in the project-7a code
because of the sleep(3) function calls that occur in my program. Because of the 
sleep(3) function, the sigsuspend() function has time to be called before it 
will receive any signals.

In my code I included a comment for each step listed in the project specification.
This will help you to easily see the code that I included for each required step.

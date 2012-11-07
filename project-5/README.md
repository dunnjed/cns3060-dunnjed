Project5-more1
=============

Jed Dunn  

To help me with the saving and restoring of the terminal settings, I was able to find a lot of 
good info from the "Understanding Unix/Linux Programming" book. In fact, the code in my 
terminalStatus() function is very similar to the code in the book. And the code in my my 
enterNonCanonicalMode() function is pretty much exactly the code that the book contains. I liked
the idea of saving a termios struct with all of the original settings and then using this
same struct to restore the terminal settings. This method is easier than trying to remember
which individual flags were changed and then trying to individually reset the flags to their
original values.

Unfortunately I had trouble getting my program to print out only the first 23 lines when 
it receives redirected input. It ends up printing all of the input at once and then printing
out the number of bytes in the input. But the command line argument option works just fine.
As do the options for entering the 'q', 'space', or 'enter' buttons. I believe I implemented
all of the other functionality as was required.

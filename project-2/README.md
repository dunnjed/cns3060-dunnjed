Project2-cat1
=============

Jed Dunn  

I think I made this project harder than it needed to be. The only problem that I am having with my 
program is when my cat1 program is passed the "-n" option along with multiple file names passed as 
arguments. If there are two or more file names at the end that don't exist, my program will print
out a final line number after the final error message, and it should not do this. 

UPDATE!!
I fixed the problem that I described above, although it seems like an unconventional way of doing it. 
In line 121 of my code, I check to see if fopen returns NULL. If it does, then I check to see if the
current file is the last file to be processed. If it is then I call __fpurge(stdout). This gets rid
of the newline number sitting in the stdout buffer. Now I no longer have an errant newline number
being printed at the end. I have to include the stdio_ext.h header to use the __fpurge function.

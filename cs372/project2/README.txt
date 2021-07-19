Clinton Hawkes
CS372-400 Networking
Program 2

************************************************************************************


COMPILING:

ftserve.c is compiled using the following command:

gcc -std=gnu99 ftserve.c -o ftserve 

ftclient.py does not need to be compiled, but it needs to be made executable using:
 
chmod +x ftclient.py

Please be sure to check that python2.7 is located at /bin/python2.7. You may do so
by using the command "whereis python2.7". If it is not located here, please 
change the first line in the ftclient.py file to reflect its location. (it should 
be here, my flip accounts had it at this location)


************************************************************************************


RUNNING PROGRAMS:

ftserve - after compiling ftserve.c using the command found above, you can
          run the program with the following sequence.

./ftserve [PORT] 

The FTP server is now running on the declared port and a client may now connect
and issue commands.


ftclient.py - I have been using Python2.7 to run the client program. The command I 
              use for starting the client is:

Command for directory listing:

ftclient.py [HOST] [PORT] [-l] [DATA PORT]

Command for file transfer:

ftclient.py [HOST] [PORT] [-g] [VALID FILENAME] [DATA PORT]


***Host must be a valid IPv4 IP address. There are no names allowed to connect
to the server. (no "localhost")***

***Files request for transfer must be .txt files***


************************************************************************************


TESTING ENVIRONMENT

All my testing used flip3 for the server and flip2 for the client. They were able to 
communicate back and forth. 

I also tried on the same server, and the programs worked as expected.


************************************************************************************


CITATAIONS:

Sources can be found at the beginning of each file. 

Main source for ftclient.py was the socket programming lectures. I used the code 
from project 1 for this as well. Other sources are found at the top of the file
by the heading.

Main source for the ftserve.c were the assignments I completed in cs344. It was 
a big help having that course behind me. My program 2 and 4 are the ones I borrowed
code from to complete this assignment. Other sources for this file can be found 
at the top of ftserve.c by the heading.

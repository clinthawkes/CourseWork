Clinton Hawkes
CS372-400 Networking
Program 1

************************************************************************************

COMPILING:

chatclient.c is compiled using the following command:

gcc -std=gnu99 chatclient.c -o chatclient

chatserve.py does not need to be compiled

************************************************************************************

RUNNING PROGRAMS:

chatclient - after compiling chatclient.c using the command found above, you can
             run the program with the following sequence.

./chatclient [HOSTNAME] [PORT] 

So if the server was running on flip3 at port 45678, I would use the following 
command to connect the client to the server.

./chatclient flip3.engr.oregonstate.edu 45678


chatserve - I have been using Python2.7 to run the server program. The command I use 
            for starting the server on port 45678 is:

python2.7 chatserve.py 45678

************************************************************************************

TESTING ENVIRONMENT

I primarily used flip3 for the server and flip2 for the client. They were able to 
communicate back and forth. 

Using the IP address of the server worked, as well as flip3.engr.oregonstate.edu for 
the hostname.

I also ran the program on my laptop using "localhost" for the hostname.


************************************************************************************

CITATAIONS:

Sources can be found at the beginning of each file. 

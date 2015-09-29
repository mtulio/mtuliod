# MTsh Shell

MTsh is a shell [in development] to connect to mtuliod TCP server.

* 
```
[mtulio@mtnote client]$ make
g++ -Wall -g -I. -I../include -c -o mtuliosh.o mtuliosh.cpp -lreadline
g++ -Wall -g -I. -I../include -c -o mtsh.o mtsh.cpp -lreadline
g++ -lreadline -o mtuliosh mtuliosh.o mtsh.o

...

[mtulio@mtnote client]$ ./mtuliosh 
MTshell# HELLO

```

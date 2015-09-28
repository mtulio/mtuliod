# MTulio Daemon - source file

* Building app, just type:
```
make clean; make
```
NOTE: The binari 'mtuliod' will be created

Then run the server and see output.
* Running server:
```
o@mtnote src]$ ./mtuliod 
 # Configuration file was found [conf/mtuliod.conf] reading...
 '-> IPADDR 		 = [0.0.0.0] 
 '-> PORT 		 = [8888] 
 '-> LOG_FILE 		 = [server.log] 
 '-> MAX_POOL_CONN 	 = [0] 
 # Starting Server on address 0:22b8 ...  [Success] 
 # Waiting for incoming connections...

...

 # Receiving connection [1] ... [OK] [Handler assigned: 4]
 # [HandlerID: 4] Closing connection by command QUIT

```

To test the server, connect to it on TCP port 8888.
* Connecting to server [and send commands: HELP, HOSTNAME, QUIT]:
```
[mtulio@mtnote mtulio-test]$ telnet 127.0.0.1 8888
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
[MTd] Hello! Welcome to MTd (MTulio Daemon)
[MTd] If you want to see all available commands. just type HELP and enjoy! ;D
[MTd]$ help
[MTd]_HELP# MTulioD HELP menu: 
	 '-> HELP	: Show this menu. 
	 '-> HOSTNAME	: Get hostname info.
	 '-> QUIT	: Close connection.
[MTd]$ hostname
[MTd]_hostname  OK# Hostname is: mtnote.mtulio.net
[MTd]$ quit
Connection closed by foreign host.

```

Enjoy! ;)


___
Roadmap:
* [OK] Create a TCP server 
* [OK] Struct the project (TCP server and its componets) 
* [OK] Read a config file 
* [--] Save server stdout to log
* [--] Create an daemon to run TCP server
* [--] Create new commands for server
* [--] Create an simple client
* [--] Creae a DB SQL to save data
* [--] Transfer files to server


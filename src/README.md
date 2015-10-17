# MTulio Daemon - source file

* Building app, just type:
```
$ make clean; make

OR to configure a RANDOM port:

$ make clean; make && cp conf/mtuliod.conf.default conf/mtuliod.conf && sed -i "s/PORT=*/PORT=$RANDOM/g" conf/mtuliod.conf
$ cat conf/mtuliod.conf
IPADDR=0.0.0.0
#RANDOM: sed -i "s/PORT=14950*/PORT=14950$RANDOM/g" conf/mtuliod.conf
PORT=14950
LOG_FILE=server.log
MAX_POOL_CONN=5
SECRET=3210
```
NOTE: The binary 'mtuliod' will be created at the same dir

Then run the server and see output.
* Running server:
```
$ ./mtuliod 
 # Configuration file was found [conf/mtuliod.conf] reading...
 '-> IPADDR 		 = [0.0.0.0] 
 '-> PORT 		 = [14950] 
 '-> LOG_FILE 		 = [server.log] 
 '-> MAX_POOL_CONN 	 = [0] 
 '-> SECRET 		 = [3210] 
 # Starting Server on address 0:3a66 ...  [Success] 
 # Waiting for incoming connections...

```

To test the server, connect to it on TCP port chose in config file.
* Connecting to server [and send commands: HELP, HOSTNAME, SETPASS, QUIT]:
```
$ telnet 172.17.1.100 `cat conf/mtuliod.conf |grep ^PORT |awk -F'=' '{print$2}'`
Trying 172.17.1.100...
Connected to 172.17.1.100.
Escape character is '^]'.
[MTd] Hello! Welcome to MTd (MTulio Daemon)
[MTd] If you want to see all available commands. just type HELP and enjoy! ;D
[MTd]$ HELP
[MTd]_HELP# MTulioD HELP menu: 
	 '-> HELP 			: Show this menu. 
	 '-> HOSTNAME 			: Get hostname info.
	 '-> SETPASS SECRET USER PASS	: Change/set system USER password.
	 '-> QUIT 			: Close connection.
[MTd]$ HOSTNAME
[MTd]_HOSTNAME  OK# Hostname is: mtuliod
[MTd]$ SETPASS 3210 user1 new@pass
[MTd]_SETPASS  ERR# cmd [SETPASS] result: User [user1] not found [252] 
[MTd]$ SETPASS 3210 user2 new@pass
[MTd]_SETPASS   OK# SETPASS result is: SUCCESS [0] 
[MTd]$ QUIT
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
* [**] Create new commands for server
* [--] Create an simple client
* [--] Create a Security session on srv-cli communication. SSL, TLS, etc...
* [--] Creae a DB SQL to save data
* [--] Transfer files to server


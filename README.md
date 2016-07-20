# C Server Daemon

MTulio Daemon is an oepn source study case of Client-Server application using TCP sockets on Unix (Linux).

___

## Building

* [1] - Building app, just type:
```
$ cd ${PROJECT_ROOT}/src
$ make clean && make
```
NOTE: The binary 'mtuliod' will be created at the same dir


* [2] - Copy configuration file located on {PROJECT_ROOT}/conf/mtuliod.conf to /etc/mtuliod/mtuliod.conf, conf/mtuliod.conf or ./mtuliod.conf :
```
$ make clean; make && cp conf/mtuliod.conf.default conf/mtuliod.conf && sed -i "s/PORT=*/PORT=$RANDOM/g" conf/mtuliod.conf
$ cat conf/mtuliod.conf
IPADDR=0.0.0.0
PORT=54321
LOG_FILE=/var/log/mtuliod/mtuliod.log
MAX_POOL_CONN=5
SECRET=3210
```

## Server side - running

* [3] - Then run the server and see output or check out on file /var/log/mtuliod/mtuliod.conf. Running server:
```
$ ./mtuliod
	*** Starting MTULIOd Server *** 
 # Configuration file was found [conf/mtuliod.conf] reading...
 '-> IPADDR 		 = [0.0.0.0] 
 '-> PORT 		 = [54321] 
 '-> LOG_FILE 		 = [/var/log/mtuliod/mtuliod.log] 
 '-> MAX_POOL_CONN 	 = [0] 
 '-> SECRET 		 = [3x10] 
 # Starting Server on address 0.0.0.0:54321 ...  [Success] 
 # Waiting for incoming connections...
 # Receiving connection [1] from IP[172.17.1.1] ... [OK] [Handler assigned: 4]
 # [HandlerID: 4] Receive message: HELP
 # [HandlerID: 4] Answer message was sent with success. Bytes=[204]
 # [HandlerID: 4] Console message was sent with success, waiting new cmds. Bytes=[7]
 # [HandlerID: 4] Receive message: HOSTNAME
 # [HandlerID: 4] Answer message was sent with success. Bytes=[41]
 # [HandlerID: 4] Console message was sent with success, waiting new cmds. Bytes=[7]
 # [HandlerID: 4] Receive message: SETPASS 3x10 marcotulio newpass
 # Running command SETPASS 
 # cmd[SETPASS] mtd_server_cmd_run_SETPASS() : [MTd]_setpass   OK# SETPASS result is: SUCCESS [0] 
 # [HandlerID: 4] Answer message was sent with success. Bytes=[52]
 # [HandlerID: 4] Console message was sent with success, waiting new cmds. Bytes=[7]
 # [HandlerID: 4] Receive message: QUIT
 # [HandlerID: 4] Closing connection by command QUIT

```

## Client side - connecting to the server

To connect to the server and send commands, connect on por 54321 TCP (as a defined on config file).

* [4] - Connecting to server using telnet [and send commands: HELP, HOSTNAME, SETPASS, QUIT]:
```
$ telnet 172.17.1.100 54321

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
[MTd]$ setpass 3x10 marcotulio newpass
[MTd]_setpass   OK# SETPASS result is: SUCCESS [0] 
[MTd]$ quit
Connection closed by foreign host.

```


Enjoy! ;)


___
Roadmap:
* [OK] Create a TCP server 
* [OK] Struct the project (TCP server and its componets) 
* [OK] Read a config file 
* [OK] Save server stdout to log
* [->] Create an daemon to run the TCP server
* [**] Create new commands for server
* [**] Create an simple client
* [--] Create a Security session on srv-cli communication. SSL, TLS, etc...
* [--] Creae a DB SQL to save data
* [--] Transfer files to server


# MTulio EngICT
# Description: MTulio Deamon
# Dependencies: MTulio LIBS (../lib)

CFLAGS := -I.
CFLAGS += -I../include
CFLAGS += -I../lib
CFLAGS += -lpthread

#OBJECTS := mtuliod.o
#OBJECTS := mtuliod_server.o
#OBJECTS += mtd_server_cmd.o
#OBJECTS += mtd_server_cmd_run.o
#OBJECTS += mtd_server_config.o
OBJECTS := ../lib/mtd_lib_strings.o
OBJECTS += ../lib/mtd_lib_file.o
OBJECTS += ../lib/mtd_lib_daemon.o

SRC=$(wildcard *.c)

########### Building Objects (OLD WAY)
#all: mtd_server_config mtd_server_cmd_run mtd_server_cmd mtuliod_server mtuliod
#all: build_lib_strings 

# Server MAIN
#mtuliod_main: mtuliod.c
#	gcc -w ${CFLAGS}  -c mtuliod.c -o mtuliod.o

# Server TCP
#mtuliod_server: mtuliod_server.c
#	gcc -w ${CFLAGS}  -c mtuliod_server.c -o mtuliod_server.o

# Server commands
#mtd_server_cmd: mtd_server_cmd.c
#	gcc -w ${CFLAGS} -c mtd_server_cmd.c -o mtd_server_cmd.o

# Server commands [run its cmds]
#mtd_server_cmd_run: mtd_server_cmd_run.c
#	gcc -w ${CFLAGS} -c mtd_server_cmd_run.c -o mtd_server_cmd_run.o

# Server config file 
#mtd_server_config: mtd_server_config.c
	#gcc -w ${CFLAGS} -c mtd_server_config.c -o mtd_server_config.o

# Main Daemon
#mtuliod:
## gcc ${CFLAGS} -w mtdLib_test.c -o mtdLib_test ${OBJECTS}
#	gcc ${CFLAGS} -w -c mtuliod.c -o mtuliod ${OBJECTS}

########### Building Program (NEW)
mtuliod: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS) ${OBJECTS}

clean: 
	rm -f *.o
	rm -f mtuliod

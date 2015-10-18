# MTulio EngICT
# Description: MTulio Deamon
# Dependencies: None

CFLAGS := -I.
CFLAGS += -I../include
CFLAGS += -lpthread

OBJECTS := mtuliod_server.o
OBJECTS += mtd_server_cmd.o
OBJECTS += mtd_server_cmd_run.o
OBJECTS += mtd_server_config.o
OBJECTS += ../lib/mtdLib_strings.o
OBJECTS += ../lib/mtdLib_file.o

all: mtd_server_config mtd_server_cmd_run mtd_server_cmd mtuliod_server mtuliod
#all: build_lib_strings 

########### Building Objects
# Server TCP
mtuliod_server: mtuliod_server.c
	gcc -w ${CFLAGS}  -c mtuliod_server.c -o mtuliod_server.o

# Server commands
mtd_server_cmd: mtd_server_cmd.c
	gcc -w ${CFLAGS} -c mtd_server_cmd.c -o mtd_server_cmd.o

# Server commands [run its cmds]
mtd_server_cmd_run: mtd_server_cmd_run.c
	gcc -w ${CFLAGS} -c mtd_server_cmd_run.c -o mtd_server_cmd_run.o

# Server config file 
mtd_server_config: mtd_server_config.c
	gcc -w ${CFLAGS} -c mtd_server_config.c -o mtd_server_config.o

# Main Daemon
mtuliod:
## gcc ${CFLAGS} -w mtdLib_test.c -o mtdLib_test ${OBJECTS}
	gcc ${CFLAGS} -w -o mtuliod ${OBJECTS}

clean: 
	rm -f *.o
	rm -f mtuliod

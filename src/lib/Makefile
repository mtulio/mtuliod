# MTulio EngICT
# Description: MTulio Deamon
# Dependencies: None

CFLAGS := -I.
CFLAGS := -I../include
CFLAGS += -lm

OBJECTS := mtdLib_strings.o
OBJECTS += mtdLib_file.o

all: build_lib_strings build_lib_file 
#all: build_lib_strings 

########### Building Libs
build_lib_strings: mtdLib_strings.c
	gcc ${CFLAGS} -c mtdLib_strings.c -o mtdLib_strings.o


build_lib_file: mtdLib_file.c
	gcc ${CFLAGS} -c mtdLib_file.c -o mtdLib_file.o

# App to test libs
build_app_testLib:
	gcc ${CFLAGS} -w mtdLib_test.c -o mtdLib_test ${OBJECTS}

clean: 
	rm -f *.o
	rm -f mtdLib_strings mtdLib_test

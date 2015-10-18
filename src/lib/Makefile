# MTulio EngICT
# Description: MTulio Deamon
# Dependencies: None

CFLAGS := -I.
CFLAGS += -I../include
CFLAGS += -lm

OBJECTS := mtd_lib_strings.o
OBJECTS += mtd_lib_file.o

all: build_lib_strings build_lib_file 
#all: build_lib_strings 

########### Building Libs
build_lib_strings: mtd_lib_strings.c
	gcc ${CFLAGS} -c mtd_lib_strings.c -o mtd_lib_strings.o


build_lib_file: mtd_lib_file.c
	gcc ${CFLAGS} -c mtd_lib_file.c -o mtd_lib_file.o

# App to test libs
build_app_testLib:
	gcc ${CFLAGS} -w mtd_lib_test.c -o mtd_lib_test ${OBJECTS}

clean: 
	rm -f *.o
	rm -f mtdLib_strings mtdLib_test

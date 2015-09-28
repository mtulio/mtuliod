# MTulio EngICT
# Description: MTulio Deamon
# Dependencies: None

## Main Makefile


all: clean build

build: build_lib build_server

build_lib:
	cd lib/; make

build_server: build_lib
	cd server/; make
	cp server/mtuliod .

clean:
	rm -f mtuliod 
	cd lib/; make clean
	cd server/; make clean

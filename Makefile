# MTulio EngICT
# Description: MTulio Deamon
# Dependencies: src directory

# Main Makefile

# Get current version
#
FILENAME_VERSION=version.txt
RELEASE=`cat $(FILENAME_VERSION)`

####################################
all: prep build

# Prep environment - version dirs
prep: clean_release
	mkdir -p release/$(RELEASE)/{bin,conf}

# Build environment 
build: 
	cd src/ && make
	mkdir -p release/$(RELEASE)
	cp src/server/mtuliod release/$(RELEASE)/bin
	cp src/conf/mtuliod.conf release/$(RELEASE)/conf
#	#cp src/scripts/scripts/mtuliod.initd release/$(RELEASE)/

# Clean env
clean: clean_release
	cd src/ && make clean

clean_release:
	rm -rf release/$(RELEASE)/*

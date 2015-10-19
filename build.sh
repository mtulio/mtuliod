#!/bin/bash

# MTuliod build script (not used yet, see Makefile)

# Set release
RELEASE=$(cat version.txt)

# Build it
make RELEASE=$RELEASE

## RELEASE DIR
# Create a tarbal from source code

# Create a RPM

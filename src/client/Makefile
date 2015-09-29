# MTulio EngICT
# Description: MTulio CLI
# Dependencies: None

CC=g++
OBJECT=${patsubst %.cpp, %.o, ${wildcard *.cpp}}
LD_FLAGS := -lreadline
CC_FLAGS := -Wall -g -I. -I../include

# Main
all: mtuliosh

########### Building Objects
# Build all
%.o: %.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< $(LD_FLAGS)

# Create binary
mtuliosh: $(OBJECT)
	$(CC) $(LD_FLAGS) -o $@ $^

########### Cleaning the home ;)
# Clean all
clean:
	rm -f *.o 
	rm -f mtuliosh
   
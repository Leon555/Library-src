CXX = gcc
INCLUDES= -I/opt/local/include
CXXFLAGS = -g -Wall -Wextra -ansi -pedantic  -DDEBUG_TEST $(INCLUDES)
MAIN= ./sort_integers.c
LINKFLAGS= -lcppunit

main:	$(MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LINKFLAGS)
	
# Default compile
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm main *.o

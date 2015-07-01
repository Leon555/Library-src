CXX = gcc
INCLUDES= -I/opt/local/include
CXXFLAGS = -g -Wall -Wextra -ansi -pedantic $(INCLUDES)
MAIN= ./ConfigReset.c
LINKFLAGS= -lcppunit

ConfigReset:	$(MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LINKFLAGS)
	
# Default compile
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm ConfigReset

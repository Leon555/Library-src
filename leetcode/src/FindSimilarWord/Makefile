CXX = g++
INCLUDES= -I/opt/local/include
CXXFLAGS = -g -Wall -Wextra -ansi -pedantic  -DDEBUG_TEST $(INCLUDES)
MAIN= ./main.cpp
OBJS = FindSimilarWord.o CExampleTest.o
LINKFLAGS= -lcppunit

main: $(OBJS) $(MAIN) 
	$(CXX) $(CXXFLAGS) -o $@  $^ $(LINKFLAGS)
	
# Default compile
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm main *.o

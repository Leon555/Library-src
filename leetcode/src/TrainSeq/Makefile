CXX = g++
INCLUDES= -I/opt/local/include
CXXFLAGS = -g $(INCLUDES)
MAIN= ./main.cpp
OBJS = sqlist.o CExampleTest.o
LINKFLAGS= -lcppunit

main:	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(MAIN) $(OBJM) $(LINKFLAGS)
	
# Default compile
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm *.o main

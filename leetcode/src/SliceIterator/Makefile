CXX = g++
INCLUDES= -I/opt/local/include
CXXFLAGS = -g $(INCLUDES)
MAIN= ./main.cpp
OBJS = SliceIterator.o CExampleTest.o
LINKFLAGS= -lcppunit

SliceIterator:	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(MAIN) $(OBJM) $(LINKFLAGS)
	
# Default compile
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

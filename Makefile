CXX=g++
CXXFLAGS= -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11
LDFLAGS=
LDLIBS= -lstdc++ -lncurses
EXECUTABLE=jencmart
SOURCES= src/main.cpp  src/menu.cpp src/game.cpp src/inOut.cpp src/map.cpp src/antHill.cpp src/ant.cpp src/path.cpp src/humanPlayer.cpp src/botPlayer.cpp src/command.cpp src/abstractPlayer.cpp src/gameWrapper.cpp
all: $(SOURCES:.cpp=.o)
	$(CXX)  $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) $(LDLIBS)
	doxygen  src/Doxyfile

compile: $(SOURCES:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) $(LDLIBS)
	doxygen  src/Doxyfile

clean:
	$(RM) $(SOURCES:.cpp=.o) $(EXECUTABLE)
	$(RM) -R doc

run:
	./$(EXECUTABLE)

doc:
	doxygen src/Doxyfile

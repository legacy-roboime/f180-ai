MAIN = nu-intel
CLIFLAGS = ./$(MAIN)
#GUIFLAGS for real robots
#GUIFLAGS = --blue=./$(MAIN) -vvpl --real
#GUIFLAGS = --blue=./$(MAIN) --yellow=./demo -vvf
GUIFLAGS = --blue "./$(MAIN) -g" --yellow "./$(MAIN) -a" -k -vv -ff
CXX = clang++
CXXFLAGS = -std=c++11
SRC := $(shell find . -name '*.cpp')
VPATH = amb

*.o: $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC)

$(MAIN): *.o
	$(CXX) $(CXXFLAGS) *.o -o $(MAIN)

gui: $(MAIN)
	roboime-next-gui $(GUIFLAGS)

cli: $(MAIN)
	roboime-next-cli $(CLIFLAGS)
clean:
	rm -f $(MAIN) *.o


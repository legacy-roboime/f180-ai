MAIN = nu-intel
CLIFLAGS = ./$(MAIN)
#GUIFLAGS for real robots
#GUIFLAGS = --blue=./$(MAIN) -vvpl --real
GUIFLAGS = --blue=./$(MAIN) --yellow=./demo -vvf
CXX = clang++-3.5 -std=c++11
#CXX = clang++ -std=c++11
#CXX = g++ -std=c++11
SRC := $(shell find -name '*.cpp')
VPATH = amb

*.o: $(SRC)
	$(CXX) -c $(SRC)

$(MAIN): *.o
	$(CXX) *.o -o $(MAIN)

gui: $(MAIN)
	roboime-next-gui $(GUIFLAGS)

cli: $(MAIN)
	roboime-next-cli $(CLIFLAGS)
clean:
	rm -f $(MAIN) *.o


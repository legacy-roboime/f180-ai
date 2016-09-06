MAIN = nu-intel
CLIFLAGS = ./$(MAIN)
GUIFLAGS = --blue=./$(MAIN) -vff
#CXX = clang++-3.5 -std=c++11
#CXX = clang++ -std=c++11
CXX = g++ -std=c++11
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


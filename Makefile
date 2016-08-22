MAIN = nu-intel
CLIFLAGS = 
GUIFLAGS = 
CXX = clang++-3.5 -std=c++11
SRC := $(shell find -name '*.cpp')
VPATH = amb

*.o: $(SRC) 
	$(CXX) -c $(SRC)

$(MAIN): *.o
	$(CXX) *.o -o $(MAIN)

gui: $(MAIN)
	roboime-next-gui $(GUIFLAGS) ./$(MAIN)

cli: $(MAIN)
	roboime-next-cli $(CLIFLAGS) ./$(MAIN) 
clean:
	rm -f $(MAIN) *.o


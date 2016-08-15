MAIN = nu-intel
FLAGS = 
CXX = clang++-3.5 -std=c++11
SRC := $(shell find -name '*.cpp')
OBJS := $(SRC:.cpp=.o)
VPATH = amb:aa

$(OBJS): $(SRC) 
	$(CXX) -c $(SRC)
	$(CXX) *.o -o $(MAIN)

gui:
	roboime-next-gui ./$(MAIN)

cli:
	roboime-next-cli ./$(MAIN) 

clean:
		rm -f $(MAIN) *.o

#TODO: Optmize makefile 

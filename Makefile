# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11 -gdwarf-3 -Wall
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder actorconnections



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o MovieNode.o ActorNode.o

actorconnections: ActorGraph.o MovieNode.o ActorNode.o DisjointSet.o util.o

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

ActorGraph.o: util.h ActorNode.h MovieNode.h ActorGraph.h

DisjointSet.o: util.h ActorNode.h MovieNode.h ActorGraph.h DisjointSet.h

ActorNode.o: ActorNode.h 

MovieNode.o: MovieNode.h

util.o: util.h

clean:
	rm -f pathfinder *.o core*


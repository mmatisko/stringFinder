CXX = clang++
RM = rm -f
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -g -O2 -pthread
LDFLAGS = -lpthread

SRC = console.cpp file.cpp filequeue.cpp filesystem.cpp main.cpp searcher.cpp
OBJ = $(subst .cpp, .o, $(SRC))

all: $(OBJ)
	$(CXX) -o stringFinder $(OBJ) $(LDFLAGS)

clean: 
	$(RM) $(OBJ)

distclean: clean
	$(RM) all

install: all ; 
	chmod +x stringFinder

console.o: console.cpp console.hpp
file.o: file.cpp file.hpp
filequeue.o: filequeue.cpp filequeue.hpp
filesystem.o: filesystem.cpp filesystem.hpp
main.o: main.cpp main.hpp 
searcher.o: searcher.cpp searcher.hpp

CXX = clang++
RM = rm -f
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -g -O2 #-stdlib=libc++
LDFLAGS = -lc++fs  #-v -lc++ -lc++abi -lc++experimental #-lstdc++fs

SRC = main.cpp file.cpp searcher.cpp filesystem.cpp console.cpp
OBJ = $(subst .cpp,.o,$(SRC))

all: tool
tool: $(OBJ)
	$(CXX) -o app $(OBJ)

main.o: main.cpp main.hpp
file.o: file.cpp file.hpp
searcher.o: searcher.cpp searcher.hpp
filesystem.o: filesystem.cpp filesystem.hpp
console.o: console.cpp console.hpp

clean: 
	$(RM) $(OBJ)

distclean: clean
	$(RM) tool

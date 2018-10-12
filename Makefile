CXX = clang++
RM = rm -f
CPPFLAGS = -std=c++14 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

SRC = main.cpp file.cpp searcher.cpp
OBJ = $(subst .cpp,.o,$(SRC))

all: tool
tool: $(OBJ)
	$(CXX) -o app $(OBJ)

main.o: main.cpp main.hpp
file.o: file.cpp file.hpp
searcher.o: searcher.cpp searcher.hpp

clean: 
	$(RM) $(OBJ)

distclean: clean
	$(RM) tool

CXX=g++
CXXFLAGS=-Wconversion -Wall -Werror -Wextra -pedantic -std=c++11
OBJ=currDay.o

all: $(OBJ)
	$(CXX) -o currDay currDay.o $(CXXFLAGS)

debug: CXXFLAGS += -g -DDEBUG
debug: clean all

clean:
	rm -Rfv *.o assemble currDay compile_commands.json
	find . -name "*.out" -type f -delete

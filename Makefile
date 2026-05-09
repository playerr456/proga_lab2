CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

all: main tests

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main.exe

tests: tests.cpp
	$(CXX) $(CXXFLAGS) tests.cpp -o tests.exe

run: main
	./main.exe

run-tests: tests
	./tests.exe

clean:
	rm -f *.exe *.o *.obj

.PHONY: all clean run run-tests

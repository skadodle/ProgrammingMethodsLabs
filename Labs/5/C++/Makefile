%.o : %.cpp
	g++ -c $< -o $@

all: program

debug: program_debug

program_debug: graph.cpp test-graph.cpp funcs.cpp
	g++ -g $^ -o $@

program: graph.o test-graph.o funcs.o
	g++ $^ -o $@

clean:
	rm -f *.o program program_debug log.txt

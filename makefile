main: validation.o file.o list.o vector.o deque.o containers.o
	g++ -march=native -O3 -o runtime runtime.cpp validation.o file.o list.o vector.o deque.o containers.o
validation:
	g++ -march=native -O3 -c validation.cpp
file:
	g++ -march=native -O3 -c file.cpp
list:
	g++ -march=native -O3 -c list.cpp
vector:
	g++ -march=native -O3 -c vector.cpp
deque:
	g++ -march=native -O3 -c deque.cpp
containers:
	g++ -march=native -O3 -c containers.cpp
clean:
	rm *.o runtime
clean-all:
	rm *.o runtime *.txt

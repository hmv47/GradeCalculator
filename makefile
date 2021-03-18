main: functions.o
	g++ -o vector vector.cpp functions.o
functions:
	g++ -c functions.cpp
clean:
	rm *.o vector *.txt

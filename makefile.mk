all:
	gcc -c library.cpp
	ar rs lib.a library.o
	gcc -c main.cpp
	gcc -o main main.cpp lib.a -pthread
clean:
	rm *.o

all:
	g++ main.cpp -o main.o
	./main.o
clean:
	rm -rf *.o
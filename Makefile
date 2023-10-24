all:
	g++ main.cpp -o main.o
clean:
	rm -rf *.o
run:
	./main.o
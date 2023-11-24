all:
	g++ main.cpp indexarLibro.cpp -o main.o
	./main.o
clean:
	rm -rf *.o
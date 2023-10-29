all:
	g++ main.cpp -o main.o
clean:
	rm -rf *.o
run:
	./main.o
GPT:
	g++ chatGPT.cpp -o GPT.o -lcurl
	./GPT.o
sus:
	g++ Sustantivos.cpp -o sus.o -lcurl
	./sus.o

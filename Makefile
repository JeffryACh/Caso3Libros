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
indexador:
	g++ indexador.cpp indexador_main.cpp -o indexador.o -std=c++11
	./indexador.o
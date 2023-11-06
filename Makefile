all:
	g++ main.cpp -o main.o
	./main.o
clean:
	rm -rf *.o
	rm -rf *.html
GPT:
	g++ chatGPT.cpp -o GPT.o -lcurl
	./GPT.o
sus:
	g++ Sustantivos.cpp -o sus.o -lcurl
	./sus.o
indexador:
	g++ indexadorLibros.cpp indexador_main.cpp PosicionDocumento.cpp -o indexador.o
	./indexador.o
http:
	g++ httpServer.cpp -o httpServer.o -lboost_system -lcpprest -lssl -lcrypto
	./httpServer.o
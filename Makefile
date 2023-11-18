all:
	g++ main.cpp -o main.o
	./main.o
clean:
	rm -rf *.o
GPT:
	g++ chatGPT.cpp -o GPT.o -lcurl
	./GPT.o
sus:
	g++ TipoDePalabra.cpp -o sus.o -lcurl -ljson-c
	./sus.o
indexador:
	g++  indexadorLibros.cpp RankingLibros.cpp indexador_main.cpp PosicionDocumento.cpp -o indexador.o
	./indexador.o
http:
	g++ httpServer.cpp -o httpServer.o -lboost_system -lcpprest -lssl -lcrypto
	./httpServer.o
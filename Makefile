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
	g++ Sustantivos.cpp -o sus.o -lcurl -ljson-c
	./sus.o
indexador:
	g++  indexadorLibros.cpp RankingLibros.cpp indexador_main.cpp PosicionDocumento.cpp -o indexador.o
	./indexador.o
indexador-tfidf:
	g++ -std=c++11 IndexadorTFIDF.cpp Documento.cpp Parrafo.cpp PosicionPalabra.cpp MainTFIDF.cpp -o indexador-tfidf.o
	./indexador-tfidf.o
http:
	g++ httpServer.cpp -o httpServer.o -lboost_system -lcpprest -lssl -lcrypto
	./httpServer.o
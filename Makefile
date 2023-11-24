all:
	g++ main.cpp indexarLibro.cpp PosicionPalabra.cpp TablaHash.cpp Documento.cpp Parrafo.cpp -o main.o
	./main.o
clean:
	rm -rf *.o
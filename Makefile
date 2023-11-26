all:
	g++ main.cpp indexarLibro.cpp PosicionPalabra.cpp TablaHash.cpp Documento.cpp Parrafo.cpp SusAndAdj.cpp -o main.o
	./main.o
clean:
	rm -rf *.o
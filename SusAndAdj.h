#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Add this line to import the fstream library
#include <algorithm>
#include <curl/curl.h>

using namespace std;

string setearPalabra(string palabra);
bool esSustantivo(string palabra);
bool esAdjetivo(string palabra);
void eliminarPalabrasRepetidas(string archivo);
bool esPalabraRepetida(string palabra, string ruta);
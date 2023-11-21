#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <fstream> // Add this line to import the fstream library
#include <algorithm>

using namespace std;

string setearPalabra(string palabra) {
    //cout << palabra << endl;
    palabra.erase(std::remove_if(palabra.begin(), palabra.end(), [](char c) { return c == '\"' || c == '[' || c == ']'; }), palabra.end());
    //cout << palabra << endl;
    return palabra;
}

bool esSustantivo(string palabra) {
    ifstream inputFile("Palabras/sus.txt"); // Open the input file stream
    if (inputFile.is_open()) {
        string sustantivo;
        while (getline(inputFile, sustantivo)) {
            transform(sustantivo.begin(), sustantivo.end(), sustantivo.begin(), ::tolower);
            transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            if (palabra == setearPalabra(sustantivo)) {
                inputFile.close(); // Close the file
                return true;
            }
        }
        inputFile.close(); // Close the file
    }
    return false;
}

bool esAdjetivo(string palabra) {
    ifstream inputFile("Palabras/adj.txt"); // Open the input file stream
    if (inputFile.is_open()) {
        string adjetivo;
        while (getline(inputFile, adjetivo)) {
            transform(adjetivo.begin(), adjetivo.end(), adjetivo.begin(), ::tolower);
            transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            if (palabra == setearPalabra(adjetivo)) {
                inputFile.close(); // Close the file
                return true;
            }
        }
        inputFile.close(); // Close the file
    }
    return false;
}
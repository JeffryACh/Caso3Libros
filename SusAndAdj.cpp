#include "SusAndAdj.h"

using namespace std;

vector<string> sustantivos;
vector<string> adjetivos;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* buffer) {
    size_t totalSize = size * nmemb;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    };
    tokens.push_back(str.substr(start, end - start));
    return tokens;
}

void SusAndAdj::cargarNSustantivos(int n){
    CURL* curl;
    CURLcode res;
    string readBuffer;
    string url = "https://random-word-form.repl.co/random/noun?count=" + to_string(n);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    sustantivos = split(readBuffer, ',');

    // Save the list of sustantivos to a file
    ofstream outputFile("Palabras/sus.txt"); // Create an output file stream
    if (outputFile.is_open()) {
        for (const string& sustantivo : sustantivos) {
            outputFile << sustantivo << endl; // Write each sustantivo to the file
        }
        outputFile.close(); // Close the file
    }
}

void SusAndAdj::cargarNAdjetivos(int n) {
    CURL* curl;
    CURLcode res;
    string readBuffer;
    string url = "https://random-word-form.repl.co/random/adjective?count=" + to_string(n);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    adjetivos = split(readBuffer, ',');

    // Save the list of adjetivos to a file
    ofstream outputFile("Palabras/adj.txt"); // Create an output file stream
    if (outputFile.is_open()) {
        for (const string& adjetivo : adjetivos) {
            outputFile << adjetivo << endl; // Write each adjetivo to the file
        }
        outputFile.close(); // Close the file
    }
}

string SusAndAdj::setearPalabra(string palabra) {
    cout << palabra << endl;
    palabra.erase(std::remove_if(palabra.begin(), palabra.end(), [](char c) { return c == '\"' || c == '[' || c == ']'; }), palabra.end());
    cout << palabra << endl;
    return palabra;
}

bool SusAndAdj::esSustantivo(string palabra) {
    ifstream inputFile("Palabras/sus.txt"); // Open the input file stream
    if (inputFile.is_open()) {
        string sustantivo;
        while (getline(inputFile, sustantivo)) {
            //cout << sustantivo << endl;
            if (palabra == setearPalabra(sustantivo)) {
                inputFile.close(); // Close the file
                return true;
            }
        }
        inputFile.close(); // Close the file
    }
    return false;
}

bool SusAndAdj::esAdjetivo(string palabra) {
    ifstream inputFile("Palabras/adj.txt"); // Open the input file stream
    if (inputFile.is_open()) {
        string adjetivo;
        while (getline(inputFile, adjetivo)) {
            if (palabra == setearPalabra(adjetivo)) {
                inputFile.close(); // Close the file
                return true;
            }
        }
        inputFile.close(); // Close the file
    }
    return false;
}
SusAndAdj::SusAndAdj() {
    // Load the list of sustantivos from a file
    ifstream inputFile("Palabras/sus.txt"); // Open the input file stream
    if (inputFile.is_open()) {
        string sustantivo;
        while (getline(inputFile, sustantivo)) {
            sustantivos.push_back(sustantivo); // Add each sustantivo to the vector
        }
        inputFile.close(); // Close the file
    }

    // Load the list of adjetivos from a file
    inputFile.open("Palabras/adj.txt"); // Open the input file stream
    if (inputFile.is_open()) {
        string adjetivo;
        while (getline(inputFile, adjetivo)) {
            adjetivos.push_back(adjetivo); // Add each adjetivo to the vector
        }
        inputFile.close(); // Close the file
    }
}

int main() {
    SusAndAdj sa;
    sa.cargarNSustantivos(20);
    sa.cargarNAdjetivos(20);
    cout << sa.esSustantivo("dog") << endl;
    cout << sa.esAdjetivo("dog") << endl;

    cout << sa.esSustantivo("cat") << endl;
    cout << sa.esAdjetivo("cat") << endl;

    cout << sa.esSustantivo("house") << endl;
    cout << sa.esAdjetivo("house") << endl;

    cout << sa.esSustantivo("beautiful") << endl;
    cout << sa.esAdjetivo("beautiful") << endl;
    return 0;
}
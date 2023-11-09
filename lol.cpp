#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
#include <json-c/json.h>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL *hnd = curl_easy_init();
    std::string readBuffer;

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://wordsapiv1.p.rapidapi.com/words/incredible/definitions");
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: 4dc6af9c3emshb073edec7c89fc1p17dabcjsncc9d69e42200");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: wordsapiv1.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(hnd);

    // Ahora puedes acceder a readBuffer para obtener la respuesta de la solicitud HTTP
    std::cout << readBuffer << std::endl;
    while (readBuffer.find("partOfSpeech") != std::string::npos) {
        std::cout << readBuffer.substr(readBuffer.find("partOfSpeech") + 15, readBuffer.find("definition") - readBuffer.find("partOfSpeech") - 18) << std::endl;
        readBuffer = readBuffer.substr(readBuffer.find("definition") + 13);
        
    }

    return 0;
}
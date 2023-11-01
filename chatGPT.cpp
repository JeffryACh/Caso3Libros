#include <iostream>
#include <string>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string prompt;

    std::cout << "Ingrese su pregunta: ";
    std::getline(std::cin, prompt);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer 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"); // Reemplaza con tu clave de API

        // Formatea la cadena de la pregunta como una cadena JSON válida
        std::string formattedPrompt = R"("prompt": ")" + prompt + R"(")";

        std::string json = R"(
        {
            "model": "gpt-3.5-turbo-instruct",
)" + formattedPrompt + R"(
            "max_tokens": 7,
            "temperature": 0
        })";

        std::string responseBuffer; // Variable adicional para almacenar la respuesta del modelo

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer); // Usar una variable adicional para almacenar la respuesta
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            std::cout << responseBuffer << std::endl; // Mostrar la respuesta almacenada en responseBuffer
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
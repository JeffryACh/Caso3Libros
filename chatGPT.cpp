#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

int main() {
    // Inicializa la biblioteca libcurl
    CURL *curl = curl_easy_init();
    cout << "Hola mundo" << endl;

    if (curl) {
        cout << "Hola mundo 2.0" << endl;
        // URL de la API de OpenAI
        const char *url = "https://api.openai.com/v1/engines/curie/completions";

        cout << "Hola mundo 3.0" << endl;

        // Tu token de autenticación de la API de OpenAI
        const char *token = "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";

        cout << "Hola mundo 4.0" << endl;

        // Datos de entrada para ChatGPT
        const char *input = "Escribe aquí tu consulta o solicitud.";

        cout << "Hola mundo 5.0" << endl;

        // Crea una cadena JSON en formato C
        std::string postFields = R"({"prompt": ")" + std::string(input) + R"("})";
        cout << "Hola mundo 6.0" << endl;

        // Establece la URL y los encabezados de autenticación
        curl_easy_setopt(curl, CURLOPT_URL, url);
        cout << "Hola mundo 7.0" << endl;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());  // Convierte std::string a const char*
        cout << "Hola mundo 8.0" << endl;
        struct curl_slist *headers = NULL;
        cout << "Hola mundo 9.0" << endl;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + std::string(token)).c_str());  // Convierte std::string a const char*
        cout << "Hola mundo 10.0" << endl;
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        cout << "Hola mundo 11.0" << endl;

        // Realiza la solicitud HTTP POST
        CURLcode res = curl_easy_perform(curl);
        cout << "Hola mundo 12.0" << endl;

        if (res != CURLE_OK) {
            cout << "Hola mundo 13.0" << endl;
            std::cerr << "Error al realizar la solicitud: " << curl_easy_strerror(res) << std::endl;
            cout << "Hola mundo 14.0" << endl;
        } else {
            cout << "Hola mundo 15.0" << endl;
            std::cout << "Respuesta: " << postFields << std::endl;
            cout << "Hola mundo 16.0" << endl;
        }
        cout << "Hola mundo 17.0" << endl;

        // Limpia los encabezados
        curl_slist_free_all(headers);
        cout << "Hola mundo 18.0" << endl;

        // Finaliza libcurl
        curl_easy_cleanup(curl);
        cout << "Hola mundo 19.0" << endl;
    }

    return 0;
}

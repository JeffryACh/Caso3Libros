#include <iostream>
#include <curl/curl.h>

int main() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        // Configura la URL de la API y la clave de autenticación
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/engines/davinci/completions");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "prompt= This is a test&max_tokens=5&temperature=1&top_p=1&n=1&stream=false&logprobs=null&stop=");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "Authorization: Bearer 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");

        // Realiza la solicitud
        res = curl_easy_perform(curl);

        // Verifica el resultado
        if (res != CURLE_OK) {
            std::cerr << "Error al realizar la solicitud: " << curl_easy_strerror(res) << std::endl;
        }

        // Limpia y finaliza
        curl_easy_cleanup(curl);
    }

    return 0;
}

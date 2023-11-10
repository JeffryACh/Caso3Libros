#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
#include <json-c/json.h>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

std::string tipoDePalabra(std::string readBuffer) {
    // Parse the JSON response
    json_object* jobj = json_tokener_parse(readBuffer.c_str());

    // Check if the JSON is valid
    if (jobj == NULL) {
        std::cerr << "Failed to parse JSON" << std::endl;
        return "otro";
    }

    // Get the "definitions" array
    json_object* jdefinitions;
    if (!json_object_object_get_ex(jobj, "definitions", &jdefinitions)) {
        std::cerr << "Failed to get definitions array" << std::endl;
        json_object_put(jobj);
        return "otro";
    }

    // Loop through the definitions
    int n = json_object_array_length(jdefinitions);
    for (int i = 0; i < n; i++) {
        json_object* jdefinition = json_object_array_get_idx(jdefinitions, i);

        // Get the "partOfSpeech" value
        json_object* jpartOfSpeech;
        if (!json_object_object_get_ex(jdefinition, "partOfSpeech", &jpartOfSpeech)) {
            std::cerr << "Failed to get partOfSpeech value" << std::endl;
            continue;
        }

        // Check the "partOfSpeech" value and return the corresponding string
        std::string partOfSpeech = json_object_get_string(jpartOfSpeech);
        if (partOfSpeech == "adjective") {
            json_object_put(jobj);
            return "adjetivo";
        } else if (partOfSpeech == "noun") {
            json_object_put(jobj);
            return "sustantivo";
        } else if (partOfSpeech == "verb") {
            json_object_put(jobj);
            return "verbo";
        }
    }

    // If we didn't find a known part of speech, return "otro"
    json_object_put(jobj);
    return "otro";
}

std::string tipoDePalabra2(std::string palabra) {
    CURL *hnd = curl_easy_init();
    std::string readBuffer;

    if (hnd) {
        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
        std::string url = "https://wordsapiv1.p.rapidapi.com/words/" + palabra + "/definitions";
        std::cout << "URL: " << url << std::endl;
        curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-RapidAPI-Key: 4dc6af9c3emshb073edec7c89fc1p17dabcjsncc9d69e42200");
        headers = curl_slist_append(headers, "X-RapidAPI-Host: wordsapiv1.p.rapidapi.com");
        curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

        CURLcode ret = curl_easy_perform(hnd);

        if (ret != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(ret) << std::endl;
        } else {
            long http_code = 0;
            curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &http_code);

            if (http_code >= 200 && http_code < 300) {
                // Parse the JSON response
                try {
                    // Replace with your JSON parsing code
                } catch (const std::exception& e) {
                    std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "HTTP request failed with status code: " << http_code << std::endl;
            }
        }

        curl_easy_cleanup(hnd);
        std::cout << "Respuesta JSON: " << readBuffer << std::endl;


        return tipoDePalabra(readBuffer);
    } else {
        std::cerr << "Error al inicializar el manipulador CURL." << std::endl;
        return "otro";
    }
}

int main() {
    try {
        std::cout << tipoDePalabra2("fighter") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
    }
    return 0;
}

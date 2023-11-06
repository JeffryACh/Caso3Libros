#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

int main() {
    http_client client(U("https://<your-region>.api.cognitive.microsoft.com/text/analytics/v3.0/languages"));

    http_request request(methods::POST);
    request.headers().add("Ocp-Apim-Subscription-Key", "<your-key>");

    // Añade tu texto aquí
    request.set_body(U("{\"documents\": [{\"id\": \"1\",\"text\": \"Hello world\"}]}"));

    client.request(request).then( {
        return response.extract_json();
    }).then( {
        std::cout << jsonValue.serialize() << std::endl;
    }).wait();

    return 0;
}

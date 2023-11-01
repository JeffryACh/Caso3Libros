#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

int main(int argc, char* argv[])
{
    auto fileStream = std::make_shared<ostream>(); // Stream para escribir datos en un archivo.

    // Abre un flujo de archivo para escribir la respuesta del servidor.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;

        // Crea un cliente http para enviar la solicitud.
        http_client client(U("http://www.bing.com"));

        // Construye la URI de la solicitud y comienza la solicitud.
        uri_builder builder(U("/search"));
        builder.append_query(U("q"), U("cpprestsdk github"));
        return client.request(methods::GET, builder.to_string());
    })

    // Maneja la llegada de los encabezados de respuesta.
    .then([=](http_response response)
    {
        printf("Recibido código de estado de respuesta:%u\n", response.status_code());

        // Escribe el cuerpo de la respuesta en el archivo.
        return response.body().read_to_end(fileStream->streambuf());
    })

    // Cierra el flujo de archivo.
    .then([=](size_t)
    {
        return fileStream->close();
    });

    // Espera a que se completen todas las operaciones de entrada/salida pendientes y maneja cualquier excepción.
    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error de excepción:%s\n", e.what());
    }

    return 0;
}
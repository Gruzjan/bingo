#include "headers/HTTPClient.hpp"
#include <emscripten/fetch.h>
#include <iostream>
#include <cstdlib>

HTTPClient::HTTPClient(std::string uri) : uri(uri) {}

void success(emscripten_fetch_t *fetch) {
    HTTPClient::HTTPResponseData = fetch->data;
    std::cerr << HTTPClient::HTTPResponseData.dump() << std::endl;
    emscripten_fetch_close(fetch);
}

void failure(emscripten_fetch_t *fetch) {
    HTTPClient::HTTPResponseData = {
        {"status", "err"}
    };
    std::cerr << HTTPClient::HTTPResponseData.dump() << std::endl;
    emscripten_fetch_close(fetch);
}


void HTTPClient::fetch(std::string method, std::string path, nlohmann::json data) {
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);

  strcpy(attr.requestMethod, method.c_str());
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

  const char * headers[] = {"Content-Type", "application/json", 0};

  std::string copy = data.dump();
  const char *newData = copy.c_str();

  attr.requestHeaders = headers;
  attr.requestData = (const char*) malloc(data.dump().size() * sizeof(char));
  strcpy((char*)attr.requestData, newData);
  attr.requestDataSize = strlen(attr.requestData);
  attr.onsuccess = success;
  attr.onerror = failure;

  emscripten_fetch(&attr, (uri + path).c_str());
}

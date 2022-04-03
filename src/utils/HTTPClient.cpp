#include "headers/HTTPClient.hpp"
#include <emscripten/fetch.h>
#include <iostream>

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

  attr.requestHeaders = headers;
  attr.requestData = data.dump().c_str();
  attr.requestDataSize = data.dump().size();
  attr.onsuccess = success;
  attr.onerror = failure;

  auto res = emscripten_fetch(&attr, (uri + path).c_str());
  std::cerr << res->data << std::endl;
}

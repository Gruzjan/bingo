#pragma once

#include <nlohmann/json.hpp>
#include <emscripten/fetch.h>

class HTTPClient {
private:
    std::string uri;
public:
    static nlohmann::json HTTPResponseData;
    HTTPClient(std::string);
    void fetch(std::string, std::string, nlohmann::json);
};
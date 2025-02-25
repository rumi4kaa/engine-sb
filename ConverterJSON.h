pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

class ConverterJSON {
public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);

private:
    const std::string configFile = "config.json";
    const std::string requestsFile = "requests.json";
    const std::string answersFile = "answers.json";
};
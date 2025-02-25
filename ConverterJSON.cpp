#include "ConverterJSON.h"

using json = nlohmann::json;

/**
 * Читает список файлов из config.json
 */
std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::ifstream file(configFile);
    if (!file.is_open()) {
        throw std::runtime_error("config file is missing");
    }

    json config;
    file >> config;
    file.close();

    if (config.empty() || !config.contains("files")) {
        throw std::runtime_error("config file is empty");
    }

    return config["files"].get<std::vector<std::string>>();
}

/**
 * Читает лимит ответов из config.json
 */
int ConverterJSON::GetResponsesLimit() {
    std::ifstream file(configFile);
    if (!file.is_open()) {
        throw std::runtime_error("config file is missing");
    }

    json config;
    file >> config;
    file.close();

    if (!config.contains("config") || !config["config"].contains("max_responses")) {
        return 5;  // Значение по умолчанию
    }

    return config["config"]["max_responses"].get<int>();
}

/**
 * Читает запросы из requests.json
 */
std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream file(requestsFile);
    if (!file.is_open()) {
        throw std::runtime_error("requests.json is missing");
    }

    json requests;
    file >> requests;
    file.close();

    if (!requests.contains("requests")) {
        throw std::runtime_error("requests.json is empty");
    }

    return requests["requests"].get<std::vector<std::string>>();
}

/**
 * Записывает результаты поиска в answers.json
 */
void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    json output;
    json results;

    for (size_t i = 0; i < answers.size(); ++i) {
        std::string requestId = "request" + std::to_string(i + 1);
        json result;
        if (answers[i].empty()) {
            result["result"] = "false";
        } else {
            result["result"] = "true";
            json relevance;
            for (const auto& [docId, rank] : answers[i]) {
                relevance.push_back({{"docid", docId}, {"rank", rank}});
            }
            result["relevance"] = relevance;
        }
        results[requestId] = result;
    }

    output["answers"] = results;
    
    std::ofstream file(answersFile);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open answers.json for writing");
    }
    
    file << output.dump(4);
    file.close();
}
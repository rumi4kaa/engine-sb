#include "SearchServer.h"
#include <sstream>
#include <set>
#include <algorithm>

/**
 * Обрабатывает поисковые запросы и возвращает список релевантных документов
 */
std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<RelativeIndex>> results;

    for (const auto& query : queries_input) {
        std::istringstream stream(query);
        std::string word;
        std::map<size_t, size_t> doc_relevance;  // doc_id -> абсолютная релевантность

        while (stream >> word) {
            auto word_entries = _index.GetWordCount(word);
            for (const auto& entry : word_entries) {
                doc_relevance[entry.doc_id] += entry.count;
            }
        }

        if (doc_relevance.empty()) {
            results.push_back({});
            continue;
        }

        size_t max_relevance = 0;
        for (const auto& [doc_id, relevance] : doc_relevance) {
            max_relevance = std::max(max_relevance, relevance);
        }

        std::vector<RelativeIndex> sorted_results;
        for (const auto& [doc_id, relevance] : doc_relevance) {
            float rank = static_cast<float>(relevance) / max_relevance;
            sorted_results.push_back({doc_id, rank});
        }

        std::sort(sorted_results.begin(), sorted_results.end(),
                  [](const RelativeIndex& a, const RelativeIndex& b) {
                      return b.rank < a.rank; // Сортировка по убыванию ранга
                  });

        results.push_back(sorted_results);
    }

    return results;
}
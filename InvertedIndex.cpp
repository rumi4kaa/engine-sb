#include "InvertedIndex.h"
#include <sstream>
#include <iostream>
#include <algorithm>

/**
 * Обновляет базу документов и строит инвертированный индекс
 */
void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    std::lock_guard<std::mutex> lock(index_mutex);  // Блокировка потока на время обновления индекса

    docs = input_docs;  // Обновляем список документов
    freq_dictionary.clear();  // Очищаем старый индекс

    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        std::istringstream stream(docs[doc_id]);
        std::string word;
        std::map<std::string, size_t> word_count;

        while (stream >> word) {
            word_count[word]++;  // Подсчёт количества вхождений слова в текущем документе
        }

        // Заполняем инвертированный индекс
        for (const auto& [word, count] : word_count) {
            freq_dictionary[word].push_back({doc_id, count});
        }
    }
}

/**
 * Возвращает список документов, где встречается слово, с указанием частоты
 */
std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::lock_guard<std::mutex> lock(index_mutex);
    if (freq_dictionary.find(word) != freq_dictionary.end()) {
        return freq_dictionary[word];
    }
    return {};  // Если слово не найдено
}
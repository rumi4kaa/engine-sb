#pragma once
#include <vector>
#include <string>
#include <map>
#include <mutex>

struct Entry {
    size_t doc_id;  // ID документа
    size_t count;   // Количество вхождений слова

    bool operator==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    void UpdateDocumentBase(const std::vector<std::string>& input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::vector<std::string> docs;  // Список текстов документов
    std::map<std::string, std::vector<Entry>> freq_dictionary;  // Инвертированный индекс
    std::mutex index_mutex;  // Защита для многопоточного обновления индекса
};
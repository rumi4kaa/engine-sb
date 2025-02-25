#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {
    try {
        ConverterJSON converter;
        
        // Читаем список документов из config.json
        std::vector<std::string> docs = converter.GetTextDocuments();
        
        // Создаём и заполняем индекс
        InvertedIndex index;
        index.UpdateDocumentBase(docs);
        
        // Загружаем поисковые запросы
        std::vector<std::string> requests = converter.GetRequests();
        
        // Выполняем поиск
        SearchServer server(index);
        std::vector<std::vector<RelativeIndex>> search_results = server.search(requests);
        
        // Записываем результаты в answers.json
        converter.putAnswers(search_results);
        
        std::cout << "Search completed. Results saved to answers.json." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
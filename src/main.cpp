#include <iostream>
#include <string>
#include <vector>
#include "converter_json.h"
#include "inverted_index.h"
#include "search_server.h"

int main(){
    std::cout << "Search Engine started" << std::endl;

    Converter_JSON cjs;
    Inverted_Index idx;
    Search_Server srv(idx);

    std::vector<std::string> docs = cjs.get_text_documents();

    idx.update_document_base(docs);

    std::vector<std::string> requests = cjs.get_requests();

    std::vector<std::vector<relative_index>> result = srv.search(requests);

    cjs.put_answers(result);

    std::cout << "Search Engine finish" << std::endl;

    return 0;
}
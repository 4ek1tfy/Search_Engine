#pragma once
#include "inverted_index.h"
#include <converter_json.h>

class Search_Server{
public:
    Search_Server(Inverted_Index& idx);

    std::vector<std::vector<relative_index>> search(const std::vector<std::string>& queries_input);

private:
    void to_words_and_search(const std::string& text, int num, std::vector<std::vector<relative_index>>& answers);

    Inverted_Index& _index;
};

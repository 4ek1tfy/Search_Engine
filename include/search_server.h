#pragma once
#include "inverted_index.h"
#include <converter_json.h>

struct relative_index
{
    size_t doc_id;
    float rank;

    bool operator == (const relative_index& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class Search_Server{
public:
    Search_Server(Inverted_Index& idx);

    std::vector<std::vector<relative_index>> search(const std::vector<std::string>& queries_input);

private:
    void to_words_and_search(const std::string& text, size_t num, std::vector<std::vector<relative_index>>& answers);

    Inverted_Index& _index;
};

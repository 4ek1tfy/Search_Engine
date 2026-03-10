#pragma once
#include "converter_json.h"
#include <map>
#include <sstream>
#include <thread>
#include <mutex>

struct Entry
{
    size_t doc_id, count;

    bool operator == (const Entry& other) const{
        return (doc_id == other.doc_id && count == other.count);
    }
};

class Inverted_Index{
public:
    Inverted_Index() = default;
    void update_document_base(const std::vector<std::string>& input_docs);

    std::vector<Entry> get_word_count(const std::string& word);
    
private:
    void to_words_and_update(const std::string& text, size_t num);
    
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};

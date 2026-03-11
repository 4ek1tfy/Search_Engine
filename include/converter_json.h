#pragma once
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cctype>

struct relative_index
{
    size_t doc_id;
    float rank;

    bool operator == (const relative_index& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class Converter_JSON{
public:
    Converter_JSON()=default;

    std::vector<std::string> get_text_documents();

    int get_responses_limit();
    
    std::vector<std::string> get_requests();

    void put_answers(std::vector<std::vector<relative_index>>answers);

private:
    std::string number_to_text(int number);
};
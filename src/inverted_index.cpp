
#include <inverted_index.h>

std::mutex mut1;

void Inverted_Index::to_words_and_update(const std::string& text, size_t num){
    std::stringstream split_to_words(text);
    std::string word;
    std::map<std::string, size_t> words;

    while(split_to_words >> word){
        {
            words[word]++;
        }
    }

    for(auto& it_word : words){ // record
        {
            std::lock_guard<std::mutex> lock(mut1);
            freq_dictionary[it_word.first].push_back({num, it_word.second});
        }
    }

    return;
};

void Inverted_Index::update_document_base(const std::vector<std::string>& input_docs){
    docs = input_docs;
    std::map<std::string, size_t> words;
    std::vector<std::thread> threads;
    freq_dictionary.clear();

    size_t num = 0;
    for(auto it : docs){
        size_t current_num = num;
        threads.push_back(std::thread([this, current_num, it](){
            this->to_words_and_update(it, current_num);
        }));  
        num++;
    }


    for(auto& thread : threads){
        thread.join();
    }

    for(auto& [word, entries] : freq_dictionary){
        std::sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b){
            return a.doc_id < b.doc_id;
        });
    }

    return;
}

std::vector<Entry> Inverted_Index::get_word_count(const std::string& word){
    auto it = freq_dictionary.find(word);
    if(it != freq_dictionary.end()){
        return it->second;
    }
    return {};
}
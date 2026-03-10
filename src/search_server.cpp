#include "search_server.h"

Search_Server::Search_Server(Inverted_Index& idx) : _index(idx){}

std::mutex mut2;
Converter_JSON C_J;

void Search_Server::to_words_and_search(const std::string& text, size_t num, std::vector<std::vector<relative_index>>& answers){
    if(text == ""){
        std::cerr << "Error text is empty";
        return;
    }
    
    std::stringstream split_to_words(text);
    std::string word;
    std::map<std::string, std::vector<Entry>> list;
    std::vector<Entry> sorted_list;
    std::pair<std::string, int> max({"", 0});

    while(split_to_words >> word){
        std::vector<Entry> entry_vec = _index.get_word_count(word);
        if(entry_vec.empty()){
            continue;
        }

        auto it = list.find(word);
        if(it == list.end()){ // Uniqueness check
            list.insert({word, entry_vec});
            if(entry_vec.size() > max.second){
                max.first = word;
                max.second = entry_vec.size();
            }
        }
    }

    if(list.empty()){
        std::lock_guard<std::mutex> lock(mut2);
        answers[num] = {};
        return;
    }


    std::map<size_t, size_t> doc_unique;

    for(auto& it_list : list){
        for(auto& it_entry : it_list.second){
            doc_unique[it_entry.doc_id] += it_entry.count;
        }
    }

    for(auto& it_entry : doc_unique){
        sorted_list.push_back({it_entry.first, it_entry.second});
    }

    int max_responses = C_J.get_responses_limit();
    int m = 0;

    if(sorted_list.empty()){
        std::cerr << "sorted_list empty" << std::endl;
        return;
    }

    std::sort(sorted_list.begin(), sorted_list.end(), 
        [](const Entry& a, const Entry& b){
        if(a.count != b.count){
            return a.count > b.count;
        }
        return a.doc_id < b.doc_id;
    });
    

    float max_absolut_relative = float(sorted_list[0].count);
    for(auto& it_sortList : sorted_list){ // fill in answers
        if(m >= max_responses){
            return;
        }
        float rank = float(it_sortList.count)/max_absolut_relative;
        {
            std::lock_guard<std::mutex> lock(mut2);
            answers[num].push_back({it_sortList.doc_id, rank});
        }
        m++;
    }
}

std::vector<std::vector<relative_index>> Search_Server::search(const std::vector<std::string>& queries_input){
    std::vector<std::vector<relative_index>> answers(queries_input.size());
    std::vector<std::thread> threads;

    size_t num = 0;
    for(auto& it : queries_input) {
        size_t current_num = num;
        threads.push_back(std::thread([this, &it, current_num, &answers]() { 
            this->to_words_and_search(it, current_num, answers);
        }));
        num++;
    }

    for(auto& thread : threads){
        thread.join();
    }

    return answers;
}
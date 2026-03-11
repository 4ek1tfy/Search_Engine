#include "converter_json.h"

std::string Converter_JSON::number_to_text(int number){
    if(number < 10){
        std::string num_text = "00" + std::to_string(number);
        return num_text;
    } else if(number < 100){
        std::string num_text = "0" + std::to_string(number);
        return num_text;
    } else {
        return std::to_string(number);
    }
}

std::vector<std::string> Converter_JSON::get_text_documents(){
    std::ifstream config_json_file("../data/config.json");


    if(!config_json_file.is_open()){
        std::cerr << "Error config file path" << std::endl;
        return {};
    }

    nlohmann::json j;

    try{
        config_json_file >> j;
    } catch(std::exception& e){
        std::cerr << "Error parsing config JSON: " << e.what() << std::endl;
        return {};
    }

    config_json_file.close();


    if(!j.contains("files")){
        std::cerr << "Error format config json" << std::endl;
        return {};
    }

    std::vector<std::string> file_paths_vec = j["files"];
    std::vector<std::string> documents;

    for(auto& it : file_paths_vec){
        if(!std::filesystem::exists(it)){
            std::cerr << "Error file path " << it << std::endl;
            documents.push_back("");
            continue;
        }
        std::stringstream buffer;
        std::ifstream file(it);
        if(!file.is_open()){
            std::cerr << "Warning: cannot open file: " << it << std::endl;
            documents.push_back("");
            continue;
        }
        buffer << file.rdbuf();
        documents.push_back(buffer.str());
    }

    return documents;
}

int Converter_JSON::get_responses_limit(){
    std::ifstream config_json_file("../data/config.json");


    if(!config_json_file.is_open()){
        std::cerr << "Error: config file not found, using default limit=5" << std::endl;
        return 5;
    }
    
    nlohmann::json j;
    try{
        config_json_file >> j;
    } catch(std::exception& e){
        std::cerr << "Error parsing config JSON: " << e.what() << std::endl;
        return 5;
    }

    config_json_file.close();

    if(!(j.contains("config") && j["config"].contains("max_responses"))){
        std::cerr << "Error format config json" << std::endl;
        return 5;
    }

    int max_responses = j["config"]["max_responses"].get<int>();

    if(max_responses > 0)
        return max_responses;

    std::cerr << "Error max_responses - config file" << std::endl;
    return 5;
}

std::vector<std::string> Converter_JSON::get_requests(){
    std::ifstream requests_json_file("../data/requests.json");

    if(!requests_json_file.is_open()){
        std::cerr << "Error requests file path" << std::endl;
        return {};
    }

    nlohmann::json j;

    try{
        requests_json_file >> j;
    } catch(std::exception& e){
        std::cerr << "Error parsing requests JSON: " << e.what() << std::endl;
        return {};
    }

    requests_json_file.close();

    if(!j.contains("requests")){
        std::cerr << "Error format requests json" << std::endl;
        return {};
    }

    std::vector<std::string> requests_vec = j["requests"];

    for(auto& it : requests_vec){
        if(it.empty()){
            std::cerr << "Request empty - requests file error" << std::endl;
        }
    }

    return requests_vec;
}

void Converter_JSON::put_answers(std::vector<std::vector<relative_index>>answers){
    nlohmann::json requests;
    if(answers.empty()){
        std::ofstream answers_json_file("../data/answers.json");
        if(!answers_json_file.is_open()){
            std::cerr << "Error answers file path" << std::endl;
            return;
        }
        std::cerr << "Answers empty" << std::endl;
        
        requests["answers"] = nlohmann::json::object();

        answers_json_file << requests << std::endl;
        answers_json_file.close();
        return;
    }

    int num = 1;
    for(auto& it_vec : answers){
        if(it_vec.empty()){
            std::string name_request = ("request" + number_to_text(num));
            nlohmann::json result;
            result["result"] = "false";
            requests[name_request] =  result;
        } else {
            std::string name_request = ("request" + number_to_text(num));
            nlohmann::json result;
            nlohmann::json relevance = nlohmann::json::array();
            result["result"] = "true";
            for(auto& it_answer : it_vec){
                relevance.push_back({
                    {"docid", it_answer.doc_id}, {"rank", it_answer.rank}  
                });
            }   
            result["relevance"] = relevance;
            requests[name_request] =  result;
        }
        num++;
    }

    nlohmann::json output_json;
    output_json["answers"] = requests;


    std::ofstream answers_json_file("../data/answers.json");
    if(!answers_json_file.is_open()){
        std::cerr << "Error answers file path" << std::endl;
        return;
    }

    answers_json_file << output_json.dump(2);
    answers_json_file.flush();
    answers_json_file.close();

    return;
}

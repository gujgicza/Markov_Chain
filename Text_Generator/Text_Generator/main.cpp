#include <iostream>
#include <map>
#include <fstream>
#include <memory>

using node = std::map<std::shared_ptr<std::string>, int>;
using markov_chain = std::map<std::shared_ptr<std::string>, std::shared_ptr<node>>;

// Settings
static int char_length = 5;
static std::string input_file_name = "test.txt";
static long text_length = 1000;

int main() {
    
    markov_chain chain;
    std::ifstream is(input_file_name);
    char c; std::string str;
    //node current_node;
    
    // Creating the Markov-chain
    for (int i = 0; i < char_length; i++) {
        is.get(c);
        str.append(&c);
    }
    auto current_node = chain[std::make_shared<std::string>(str)];
    
    while (is.get(c)) {
        //node& current_node = chain[shared_str];
        str.erase(0,1);
        str.append(&c);
        auto shared_str = std::make_shared<std::string>(str);
        ++current_node.get()->at(shared_str);
        current_node = chain[shared_str];
    }
    
    // Generating text
    auto current = chain.begin();
    for (int i = 0; i < text_length; i++) {
        std::cout << current->first.get()->data(); // << std:: endl;
        //std::cout << current->second.begin()->first.get()->data();
        //TODO
        std::shared_ptr<std::string> next_str = current->second.get()->begin()->first;
        current = chain.find(next_str);
    }
    
    return 0;
}

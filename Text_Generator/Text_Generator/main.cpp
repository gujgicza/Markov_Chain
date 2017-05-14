#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <memory>
#include <algorithm>
#include <functional>


using node = std::pair<std::shared_ptr<std::string>, std::map<std::shared_ptr<std::string>, int>>;
using markov_chain = std::set<node>;

// Settings
static int char_length = 5;
static std::string input_file_name = "alice.txt";



int main(int argc, const char * argv[]) {
    
    markov_chain chain;
    
    std::ifstream is(input_file_name);
    char c; std::string str; std::shared_ptr<std::string> shared_str;
    
    // Creating the Markov-chain
    for (int i = 0; i < char_length; i++) {
        is.get(c);
        str.append(&c);
    }
    shared_str = std::make_shared<std::string>(str);
    node current_node = std::make_pair(shared_str, std::map<std::shared_ptr<std::string>, int>());
    chain.insert(current_node);
    
    while (is.get(c)) {
        str.erase(0);
        str.append(&c);
        shared_str = std::make_shared<std::string>(str);
        ++current_node.second[shared_str];
        
        {
            std::for_each(chain.begin(), chain.end(), [&] (node& n) {
                if (n.first == shared_str)
                    current_node = n; });
            current_node = std::make_pair(shared_str, std::map<std::shared_ptr<std::string>, int>());
        
        }
            
    }
    
    // Generating text
    
    
    return 0;
}

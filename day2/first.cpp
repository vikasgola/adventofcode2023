#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

vector<string> parse_line(string line){
    string word = "";
    vector<string> tokens;
    for(auto &c: line){
        if(isalnum(c) && !isspace(c)){
            word += c;
        }else if(word.length() > 0){
            tokens.push_back(word);
            word = "";
        }
    }
    if(word.length() > 0) tokens.push_back(word);
    return tokens;
}

int process_tokens(vector<string> tokens){
    int id = stoi(tokens[1]);
    for(size_t i=2;i<tokens.size();i+=2){
        if(tokens[i+1] == "red" and stoi(tokens[i]) > 12){
            return 0;
        }else if(tokens[i+1] == "green" and stoi(tokens[i]) > 13){
            return 0;
        }else if(tokens[i+1] == "blue" and stoi(tokens[i]) > 14){
            return 0;
        }
    }
    return id;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"Usage: "<<argv[0]<<" "<<"INPUT_FILE"<<endl;
        return 0;
    }
    ifstream input(argv[1]);
    if(!input.is_open()){
        cout<<"Failed to open file "<<argv[1]<<endl;
        return 0;
    }
    int ans = 0;
    string line;
    while(getline(input, line)){
        auto tokens = parse_line(line);
        ans += process_tokens(tokens);
    }
    cout<<"Answer: "<<ans<<endl;
    return 0;
}
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

vector<string> parse_line(string line){
    string word = "";
    vector<string> tokens;
    for(auto &c: line){
        if((isalnum(c) && !isspace(c)) || c == '|'){
            word += c;
        }else if(word.length() > 0){
            tokens.push_back(word);
            word = "";
        }
    }
    if(word.length() > 0) tokens.push_back(word);
    return tokens;
}

long long process_tokens(vector<string> tokens){
    map<string, bool> exists;
    bool add = true;
    long long ans = 0;
    for(size_t i=2;i<tokens.size();i++){
        if(tokens[i] == "|"){
            add = false;
        }else if(add){
            exists[tokens[i]] = true;
        }else if(exists[tokens[i]]) ans++;
    }
    if(ans == 0) return 0;
    return 1 << (ans-1);
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
    long long ans = 0;
    string line;
    while(getline(input, line)){
        auto tokens = parse_line(line);
        ans += process_tokens(tokens);
    }
    cout<<"Answer: "<<ans<<endl;
    return 0;
}
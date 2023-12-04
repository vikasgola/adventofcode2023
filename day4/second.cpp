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
    return ans;
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
    map<long long, long long> runs;
    long long i = 0;
    while(getline(input, line)){
        if(runs.find(i) == runs.end()) runs[i] = 1;
        else runs[i]++;

        auto tokens = parse_line(line);
        auto next_runs = process_tokens(tokens);
        while(next_runs > 0){
            if(runs.find(i+next_runs) == runs.end()) runs[i+next_runs] = runs[i];
            else runs[i+next_runs] += runs[i];
            next_runs--;
        }
        ans += runs[i++];
    }
    cout<<"Answer: "<<ans<<endl;
    return 0;
}
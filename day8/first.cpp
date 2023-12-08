#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<set>

using namespace std;

vector<string> parse_line(ifstream &input){
    string line;
    getline(input, line);
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

    auto instructions = parse_line(input)[0];
    map<string, pair<string, string>> connections;

    while(!input.eof()){
        auto tokens = parse_line(input);
        if(tokens.size() == 0) continue;
        connections[tokens[0]] = {tokens[1], tokens[2]};
    }

    string start = "AAA";
    int steps = 0;
    int i_instruction = 0;
    while(start != "ZZZ"){
        start = (instructions[i_instruction] == 'L' ? connections[start].first : connections[start].second);
        i_instruction = (i_instruction+1)%instructions.size();
        steps++;
    }
    cout<<"Answer: "<<steps<<endl;
    return 0;
}
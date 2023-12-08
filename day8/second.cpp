#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<numeric>

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

bool is_end(vector<string> &locations){
    for(auto &loc: locations){
        if(loc[2] != 'Z') return false;
    }
    return true;
}

long long get_steps_to_end(string start, string instructions, map<string, pair<string, string>> &connections){
    int i_instruction = 0;
    long long steps = 0;
    while(start[2] != 'Z'){
        start = (instructions[i_instruction] == 'L' ? connections[start].first : connections[start].second);
        i_instruction = (i_instruction+1)%instructions.size();
        steps++;
    }
    return steps;
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
    vector<string> locations;

    while(!input.eof()){
        auto tokens = parse_line(input);
        if(tokens.size() == 0) continue;
        connections[tokens[0]] = {tokens[1], tokens[2]};
        if(tokens[0][2] == 'A') locations.push_back(tokens[0]);
    }

    long long ans = 1;
    for(auto &loc: locations){
        auto steps = get_steps_to_end(loc, instructions, connections);
        ans = lcm(steps, ans);
        cout<<steps<<endl;
    }
    cout<<"Answer: "<<ans<<endl;
    return 0;
}
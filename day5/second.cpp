#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<set>

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

long long next_map(vector<string> tokens, long long n){
    long long dest = stol(tokens[0]), src = stol(tokens[1]), range = stol(tokens[2]);
    if(src <= n && src+range > n){
        return dest+(n-src);
    }
    return -1;
}

long long get_location(vector<vector<string>> instructions, long long n){
    long long next_n = -1;
    for(auto &instruction: instructions){
        if(instruction[3] == "map"){
            if(next_n != -1) n = next_n;
            next_n = -1;
        }else if(next_n == -1){
            next_n = next_map(instruction, n);
        }
    }
    if(next_n != -1) n = next_n;
    return n;
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

    string line;
    vector<pair<long long, long long>> numbers;
    map<long long, bool> used;
    vector<vector<string>> instructions;

    getline(input, line);
    auto tokens = parse_line(line);
    for(size_t i=1;i<tokens.size();i+=2){
        numbers.push_back({stol(tokens[i]), stol(tokens[i+1])});
    }


    while(getline(input, line)){
        auto tokens = parse_line(line);
        if(tokens.size() > 0) instructions.push_back(tokens);
    }

    long long ans = LLONG_MAX;
    for(auto number: numbers){
        cout<<"start:"<<number.first<<endl;
        for(size_t n=number.first;n<number.second+number.first;n++){
            long long loc = get_location(instructions, n);
            ans = min(ans, loc);
            if(get_location(instructions, n+20000) == loc+20000) n += 20000;
        }
    }

    cout<<"Answer: "<<ans<<endl;
    return 0;
}
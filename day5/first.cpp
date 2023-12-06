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

long long process_tokens(vector<string> tokens, long long n){
    long long dest = stol(tokens[0]), src = stol(tokens[1]), range = stol(tokens[2]);
    if(src <= n && src+range > n){
        return dest+(n-src);
    }
    return -1;
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
    vector<long long> numbers, next_numbers;
    map<long long, bool> used;

    getline(input, line);
    auto tokens = parse_line(line);
    for(size_t i=1;i<tokens.size();i++){
        numbers.push_back(stol(tokens[i]));
        used[stol(tokens[i])] = false;
    }


    while(getline(input, line)){
        auto tokens = parse_line(line);
        if(tokens.size() == 0) continue;
        if(tokens[3] == "map"){
            for(auto n: numbers){
                if(!used[n]) next_numbers.push_back(n);
            }
            numbers = next_numbers;
            next_numbers.clear();
            used.clear();
            continue;
        }

        for(auto n: numbers){
            if(used[n]) continue;

            auto out = process_tokens(tokens, n);
            cout<<"n:"<<n<<" out:"<<out<<endl;
            if(out != -1){
                next_numbers.push_back(out);
                used[n] = true;
            }
        }
    }

    for(auto n: numbers){
        if(!used[n]) next_numbers.push_back(n);
    }
    auto ans = *min_element(next_numbers.begin(), next_numbers.end());

    cout<<"Answer: "<<ans<<endl;
    return 0;
}
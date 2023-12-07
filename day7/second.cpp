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
            if(c == 'T') c = ':';
            else if(c == 'J') c = '1';
            else if(c == 'Q') c = '<';
            else if(c == 'K') c = '=';
            else if(c == 'A') c = '>';
            word += c;
        }else if(word.length() > 0){
            tokens.push_back(word);
            word = "";
        }
    }
    if(word.length() > 0) tokens.push_back(word);
    return tokens;
}

size_t get_priority(string card){
    map<char, int> counts;
    int max_c = 0;
    char max_at;
    for(auto &c: card){
        counts[c]++;
        if(max_c < counts[c] && c != '1'){
            max_c = counts[c];
            max_at = c;
        }
    }
    if(max_at != '1'){
        counts[max_at] += counts['1'];
        counts['1'] = 0;
        // cout<<max_at<<" | "<<counts[max_at]<<endl;
    }

    vector<int> values;
    for(auto &it: counts) values.push_back(it.second);
    sort(values.begin(), values.end(), greater<int>());

    if(values[0] == 5) return 0;
    else if(values[0] == 4) return 1;
    else if(values[0] == 3 && values[1] == 2) return 2;
    else if(values[0] == 3) return 3;
    else if(values[0] == 2 and values[1] == 2) return 4;
    else if(values[0] == 2) return 5;
    else return 6;
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

    long long max_ranks = 0;
    vector<pair<string, long long>> cards[7];
    while(!input.eof()){
        auto tokens = parse_line(input);
        cards[get_priority(tokens[0])].push_back({tokens[0], stol(tokens[1])});
        max_ranks++;
    }

    long long ans = 0;
    for(auto &rank_card: cards){
        sort(rank_card.begin(), rank_card.end(), greater<pair<string, long long>>());
        for(auto r: rank_card){
            // cout<<r.first<<" | "<<max_ranks<<endl;
            ans += r.second*max_ranks--;
        }
    }

    cout<<"Answer: "<<ans<<endl;
    return 0;
}
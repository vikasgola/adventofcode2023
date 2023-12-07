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

long long get_max_ways_to_beat(long long time, long long distance){
    double lower = (time - sqrtl(time*time - 4*distance))/2.0f;
    double upper = (time + sqrtl(time*time - 4*distance))/2.0f;
    // cout<<lower<<"|"<<upper<<endl;
    // cout<<ceill(upper-1.0f) - floorl(lower+1.0f)<<endl;
    return 1+ceill(upper-1.0f) - floorl(lower+1.0f);
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
    long long ans = 1;

    auto times = parse_line(input);
    auto distances = parse_line(input);
    for(size_t i=1;i<times.size();i++){
        ans *= get_max_ways_to_beat(stol(times[i]), stol(distances[i]));
    }

    cout<<"Answer: "<<ans<<endl;
    return 0;
}
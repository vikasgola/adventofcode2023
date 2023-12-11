#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<set>

using namespace std;

vector<long long> parse_line(ifstream &input){
    string line;
    getline(input, line);
    string word = "";
    vector<long long> tokens;
    for(auto &c: line){
        if((isalnum(c) && !isspace(c)) || c == '-'){
            word += c;
        }else if(word.length() > 0){
            tokens.push_back(stol(word));
            word = "";
        }
    }
    if(word.length() > 0) tokens.push_back(stol(word));
    return tokens;
}

bool is_zero(vector<long long> temp){
    for(auto &t: temp){
        if(t != 0) return false;
    }
    return true;
}

void calculate_diff(vector<long long> &seq, vector<long long> &nseq){
    for(size_t i=1;i<seq.size();i++){
        nseq.push_back(seq[i]-seq[i-1]);
    }
    if(nseq.size() == 0) nseq.push_back(0);
}


long long get_next_element(vector<long long> &seq){
    long long diff = seq[0];
    vector<long long> nseq;
    long long sign = -1;
    while(!is_zero(seq)){
        calculate_diff(seq, nseq);
        diff += sign*nseq[0];
        sign *= -1;
        seq = nseq;
        nseq.clear();
    }
    return diff;
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

    while(!input.eof()){
        auto sequence = parse_line(input);
        if(sequence.size() == 0) continue;
        ans += get_next_element(sequence);
    }

    cout<<"Answer: "<<ans<<endl;

    return 0;
}
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

long long get_number(string line, int j, vector<bool> &index_used){
    while(isdigit(line[j])) j--;
    string number = "";
    while(isdigit(line[++j])){
        index_used[j] = true;
        number += line[j];
    }
    return stol(number);
}

long long helper(vector<string> lines, vector<vector<bool>> &index_used){
    pair<int,int> adjacents[] = {{0,-1}, {0,1}, {1,0}, {-1,0}, {-1,1}, {-1,-1}, {1,-1}, {1,1}};
    long long ans = 0;
    for(size_t i=0;i<lines.size();i++){
        for(size_t j=0;j<lines[i].length();j++){
            if(isdigit(lines[i][j]) || lines[i][j] == '.') continue;
            for(auto &adj: adjacents){
                auto p = i+adj.first, q = j+adj.second;
                if(!(p >= 0 && p < lines.size() && q >= 0 && q < lines[i].length())) continue;
                if(!isdigit(lines[p][q]) || index_used[p][q]) continue;
                ans += get_number(lines[p], q, index_used[p]);
            }
        }
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
    string line;
    vector<string> lines;
    vector<vector<bool>> index_used;
    while(getline(input, line)){
        lines.push_back(line);
        index_used.push_back(vector<bool>(line.length(), false));
    }
    long long ans = helper(lines, index_used);
    cout<<"Answer: "<<ans<<endl;
    return 0;
}
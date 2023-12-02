#include<iostream>
#include<fstream>
#include<string>
#include<cassert>
using namespace std;

const string numbers[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int is_number(string line, int t){
    for(size_t i=0;i<10;i++){
        auto number = numbers[i];
        if(strncmp(&line[t], number.c_str(), number.length()) == 0) return i;
    }
    return -1;
}

int find_first_number(string line){
    for(size_t i=0;i<line.length();i++){
        auto c = line[i];
        if(c >= '0' && c <= '9'){
            return c-'0';
        }
        int n = is_number(line, i);
        if(n != -1) return n;
    }
    return -1;
}

int find_second_number(string line){
    for(size_t i=line.length()-1;i>=0;i--){
        auto c = line[i];
        if(c >= '0' && c <= '9'){
            return c-'0';
        }
        int n = is_number(line, i);
        if(n != -1) return n;
    }
    return -1;
}

int main(){
    ifstream input("./input_second.txt");
    string line;
    int ans = 0;
    while(getline(input, line)){
        ans += find_first_number(line)*10 + find_second_number(line);
    }
    cout<<"Answer: "<<ans<<endl;
    return 0;
}
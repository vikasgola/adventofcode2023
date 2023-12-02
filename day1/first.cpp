#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(){
    ifstream input("./input_first.txt");
    string line;
    int ans = 0;
    while(getline(input, line)){
        int c1 = -1, c2 = -1;
        for(auto &c: line){
            if(c >= '0' && c <= '9'){
                if(c1 == -1) c1 = (c-'0')*10;
                else c2 = (c-'0');
            }
        }
        if(c2 == -1) c2 = c1/10;
        ans += c1+c2;
    }
    cout<<"Answer: "<<ans<<endl;
    return 0;
}
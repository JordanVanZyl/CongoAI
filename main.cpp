#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<queue>
#include<set>
#include <sstream>

using namespace std;

vector<vector<string>>vecBoardOutput(17);
vector<string>vecLine;
vector<string>vecBoardLine;

void stringTokenizer(string s, string del, vector<string>&vec)
{
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        vec.push_back(s.substr(start, end - start));
        // cout << s.substr(start, end - start) << endl;
        start = end + del.size();
        end = s.find(del, start);
    }
    vec.push_back(s.substr(start, end - start));
    
}


int main(){
    string line;
    getline(cin,line);
    stringTokenizer(line," ",vecLine);
    stringTokenizer(vecLine[0],"/",vecBoardLine);

    for(auto x:vecBoardLine){
        cout<<x<<endl;
    }

    // for(auto x:vecLine){
    //     cout<<x<<endl;
    // }

}
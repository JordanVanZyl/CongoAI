#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<queue>
#include<set>
#include <sstream>
#include <map>

using namespace std;

//For outputting in submission one
vector<vector<string>>vecBoardOutput(17);
//First vector split by spaces
vector<string>vecLine;
//Second vector splitting by / for the state of the board
vector<string>vecBoardLine;

//s=string to split, del=thing to split by in string form, vec=1D vector to store the split in
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
    vector<string>vecColStr={"a","b","c","d","e","f"};
    map<string,int>animalToOut{
        {"P",0},{"p",1},{"S",2},{"s",3},{"G",4},{"g",5},{"M",6},{"m",7},
        {"E",8},{"e",9},{"L",10},{"l",11},{"C",12},{"c",13},{"Z",14},{"z",15}
    };

    // for(auto x:vecBoardLine){
    //     cout<<x<<endl;
    // }

    // for(auto x:vecLine){
    //     cout<<x<<endl;
    // }

    for(int row=7;row>=0;row--){
        for(int col=0;col<8;col++){

        }
    }

}
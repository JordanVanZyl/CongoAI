#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<queue>
#include<set>
#include<algorithm>
#include<sstream>
#include<map>

using namespace std;

//For outputting in submission one
vector<vector<string>>vecBoardOutput(16);
//First vector split by spaces
vector<string>vecLine;
//Second vector splitting by / for the state of the board
vector<string>vecBoardLine;

vector<string>vecLines;

vector<string>vecColStr={"a","b","c","d","e","f","g"};
map<string,int>animalToOut{
    {"P",0},{"p",1},{"S",2},{"s",3},{"G",4},{"g",5},{"M",6},{"m",7},
    {"E",8},{"e",9},{"L",10},{"l",11},{"C",12},{"c",13},{"Z",14},{"z",15}
};

map<int,string>lineToOut{
    {0,"white pawn: "},{1,"black pawn: "},{2,"white superpawn: "},{3,"black superpawn: "},{4,"white giraffe: "},{5,"black giraffe: "},
    {6,"white monkey: "},{7,"black monkey: "},{8,"white elephant: "},{9,"black elephant: "},{10,"white lion: "},{11,"black lion: "},
    {12,"white crocodile: "},{13,"black crocodile: "},{14,"white zebra: "},{15,"black zebra: "}
};


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

void insertionSort(vector<string>&array) {
   int j;
   string key;
   int size=array.size();
   for(int i = 1; i<size; i++) {
      key = array[i];//take value
      j = i;
      while(j > 0 && array[j-1]>key) {
         array[j] = array[j-1];
         j--;
      }
      array[j] = key;   //insert in right place
   }
}

void printBoard(){
    string line;
    for(int numInput=0;numInput<vecLines.size();numInput++){
        vecBoardLine.clear();
        vecLine.clear();
        line=vecLines[numInput];
        stringTokenizer(line," ",vecLine);
        stringTokenizer(vecLine[0],"/",vecBoardLine);
        reverse(vecBoardLine.begin(),vecBoardLine.end());
    

        int skip,pos;
        int col,colToRead;
        for(int row=6;row>=0;row--){//FIXME: col should no correspond to the actual col we read from vecBoardLine 
            col=0;
            for(int colToRead=0;colToRead<vecBoardLine[row].size();colToRead++){

                if(isdigit(vecBoardLine[row][colToRead])){
                    skip=stoi(vecBoardLine[row].substr(colToRead,1));
                    col+=skip;
                }else{
                    pos=animalToOut[vecBoardLine[row].substr(colToRead,1)];
                    vecBoardOutput[pos].push_back(vecColStr[col]+to_string(row+1));
                    col+=1;
                }
            }
        }

        for(int i=0;i<16;i++){
            line="";
            line+=lineToOut[i];
            int elementNum=0;
            elementNum=vecBoardOutput[i].size();
            insertionSort(vecBoardOutput[i]);
            for(int j=0;j<elementNum;j++){
                line+=vecBoardOutput[i][j]+" ";
            }
            cout<<line<<endl;
        }

        if(vecLine[1]=="b"){
            cout<<"side to play: black\n";
        }else{
            cout<<"side to play: white\n";
        }

        cout<<endl;

        for(int i=0;i<16;i++){
            vecBoardOutput[i].clear();
        }
    }
    
}




int main(){
    string numInput;
    string line;

    getline(cin,numInput);
    vecLines.resize(stoi(numInput));
    for(int k=0;k<stoi(numInput);k++){
        getline(cin,line);
        vecLines[k]=line;
    }

    printBoard();

    

        

    

}
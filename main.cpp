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
//For tracking the board state
vector<vector<string>>vecBoardState(7,vector<string>(7,"-"));
//First vector split by spaces
vector<string>vecLine;
//Second vector splitting by / for the state of the board
vector<string>vecBoardLine;
//Stores all the orginal lines entered 
vector<string>vecLines;

vector<string>vecColStr={"a","b","c","d","e","f","g"};
map<string,int>animalToOut{
    {"P",0},{"p",1},{"S",2},{"s",3},{"G",4},{"g",5},{"M",6},{"m",7},
    {"E",8},{"e",9},{"L",10},{"l",11},{"C",12},{"c",13},{"Z",14},{"z",15}
};
//Converting column number to letter on the board for output
map<int,string>colToString{
        {0,"a"},{1,"b"},{2,"c"},{3,"d"},{4,"e"},{5,"f"},{6,"g"}
    };

map<int,string>lineToOut{
    {0,"white pawn: "},{1,"black pawn: "},{2,"white superpawn: "},{3,"black superpawn: "},{4,"white giraffe: "},{5,"black giraffe: "},
    {6,"white monkey: "},{7,"black monkey: "},{8,"white elephant: "},{9,"black elephant: "},{10,"white lion: "},{11,"black lion: "},
    {12,"white crocodile: "},{13,"black crocodile: "},{14,"white zebra: "},{15,"black zebra: "}
};

//s=string to split, del=thing to split by in string form, vec=1D vector to store the split in
void stringTokenizer(std::string s, std::string del, std::vector<std::string>&vec)
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

void insertionSort(std::vector<std::string>&array) {
   int j;
   std::string key;
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
    //Loop through all board lines entered
    for(int numInput=0;numInput<vecLines.size();numInput++){
        //Clear splitting vectors
        vecBoardLine.clear();
        vecLine.clear();
        //Get the line to split
        line=vecLines[numInput];
        //Split by spaces to give board, move number and colour to play
        stringTokenizer(line," ",vecLine);
        //Split by slashes to give each row for the board ordered in descending row order
        stringTokenizer(vecLine[0],"/",vecBoardLine);
        //Reverse the vector holding the board line to give the board rows in ascending order
        reverse(vecBoardLine.begin(),vecBoardLine.end());
    

        int skip,pos;
        int col,charToRead;
        for(int row=6;row>=0;row--){
            col=0;
            //Loop through each letter in the string for a board line
            for(int charToRead=0;charToRead<vecBoardLine[row].size();charToRead++){
                //Check for a skip digit
                if(isdigit(vecBoardLine[row][charToRead])){
                    //Get the number in the correct form
                    skip=stoi(vecBoardLine[row].substr(charToRead,1));
                    //Perform the column skip
                    col+=skip;
                }else{
                    //Get the value of the row in the vector that will output to console
                    pos=animalToOut[vecBoardLine[row].substr(charToRead,1)];
                    //Push the position of the piece to the correct row in the vector that will output to console
                    vecBoardOutput[pos].push_back(vecColStr[col]+to_string(row+1));
                    //Increment the column number normally
                    col+=1;
                }
            }
        }

        //Go through all the rows in the vector that will output to console
        for(int i=0;i<16;i++){
            line="";
            //Start the line with the initial required string
            line+=lineToOut[i];
            int elementNum=0;
            //Get the length of the vector line containing the piece positions
            elementNum=vecBoardOutput[i].size();
            //Sort the vector line of piece positions in ascending order
            insertionSort(vecBoardOutput[i]);
            //Add all the positions to the line
            for(int j=0;j<elementNum;j++){
                line+=vecBoardOutput[i][j]+" ";
            }
            //Output the line in console
            cout<<line<<endl;
        }

        //Output the final line of whose turn it is
        if(vecLine[1]=="b"){
            cout<<"side to play: black\n";
        }else{
            cout<<"side to play: white\n";
        }

        cout<<endl;

        //CLear the vector containing the piece positions
        for(int i=0;i<16;i++){
            vecBoardOutput[i].clear();
        }
    }
    
}

void initBoard(string line){
    //Clear splitting vectors
    vecBoardLine.clear();
    vecLine.clear();
    //Split by spaces to give board, move number and colour to play
    stringTokenizer(line," ",vecLine);
    //Split by slashes to give each row for the board ordered in descending row order
    stringTokenizer(vecLine[0],"/",vecBoardLine);
    //Reverse the vector holding the board line to give the board rows in ascending order
    reverse(vecBoardLine.begin(),vecBoardLine.end());


    int skip,pos;
    int col,charToRead;
    for(int row=6;row>=0;row--){
        col=0;
        //Loop through each letter in the string for a board line
        for(int charToRead=0;charToRead<vecBoardLine[row].size();charToRead++){
            //Check for a skip digit
            if(isdigit(vecBoardLine[row][charToRead])){
                //Get the number in the correct form
                skip=stoi(vecBoardLine[row].substr(charToRead,1));
                //Perform the column skip
                col+=skip;
            }else{
                //Update the board with the piece
                vecBoardState[row][col]=vecBoardLine[row][charToRead];
                //Increment the column number normally
                col+=1;
            }
        }
    }
    

}
void removeByValue (vector<int>&vec,int value){
	// This is the meat & potatoes
  	for(int i=0;i<vec.size();i++){
        if(vec[i]==value){
            vec.erase(vec.begin() + i);
        }
    }
}
void movesLion(string colourToMove){
    //TODO: Sort the output
    //TODO: Allow for multiple inputs and outputs
    int rowPosWL,colPosWL, rowPosBL, colPosBL;

    //Looking for uppercase L
    for(int row=0;row<7;row++){
        for(int col=0;col<7;col++){
            if(vecBoardState[row][col]=="L"){
                rowPosWL=row;
                colPosWL=col;
            }else if(vecBoardState[row][col]=="l"){
                rowPosBL=row;
                colPosBL=col;
            }      
        }
    }

    int move,newRow,newCol;
    //Lion can move 8 directions: 0:North,1:North-east,2:East,3:South-east,4:South,5:South-west,6:West,7:North-west
    //Lion can do a special river move to take enemy Lion encoded as 8
    vector<int>availableMoves={0,1,2,3,4,5,6,7};
    vector<int>vecRowColUpdate;
    map<int,vector<int>>rowColUpdate{
        {0,{1,0}},{1,{1,1}},{2,{0,1}},{3,{-1,1}},{4,{-1,0}},{5,{-1,-1}},{6,{0,-1}},{7,{1,-1}}
    };
    if(colourToMove=="w"){
        //Case 1: left most column
        if(colPosWL==2){
            //No 5,6,7
            removeByValue(availableMoves,5);
            removeByValue(availableMoves,6);
            removeByValue(availableMoves,7);
        }
        //Case 2: Right most column
        else if(colPosWL==4){
            //No 1,2,3
            removeByValue(availableMoves,1);
            removeByValue(availableMoves,2);
            removeByValue(availableMoves,3);
        }
        //Case 3: Bottom most row
        if(rowPosWL==0){
            //No 3,4,5
            removeByValue(availableMoves,3);
            removeByValue(availableMoves,4);
            removeByValue(availableMoves,5);
        }
        //Case 4: Top most row
        else if(rowPosWL==2){
            //No 0,1,7
            removeByValue(availableMoves,0);
            removeByValue(availableMoves,1);
            removeByValue(availableMoves,7);
        }
        //Case 5: Own piece blocking us
        vector<int>movesToDelete;
        for(int i=0;i<availableMoves.size();i++){
            //Use a map to give the row and col updates for a move
            move=availableMoves[i];
            vecRowColUpdate=rowColUpdate[move];
            newRow=rowPosWL+vecRowColUpdate[0];
            newCol=colPosWL+vecRowColUpdate[1];

            if(vecBoardState[newRow][newCol]=="P"||vecBoardState[newRow][newCol]=="E"||vecBoardState[newRow][newCol]=="Z"){
                movesToDelete.push_back(move);
            }
        }

        if(!movesToDelete.empty()){
            for(int i=0;i<movesToDelete[i];i++){
                removeByValue(availableMoves,movesToDelete[i]);
            }
        }
        //Case 6: Capture enemy lion across river
        //Check if the lions are on the same column
        bool openColumn=false;
        if(colPosWL==colPosBL){
            openColumn=true;
            //Check if any piece is blocking them
            for(int i=rowPosWL+1;i<rowPosBL;i++){
                if(vecBoardState[i][colPosWL]!="-"){
                    openColumn=false;
                    break;
                }
            }
            if(openColumn){
                availableMoves.push_back(8);
            }
        }
        //Check for the diagonal capture
        else if(rowPosWL==2&&rowPosBL==5){
            //Case 1: our lion at left edge of the square and enemy on the opposite edge
            if(colPosWL==2&&colPosBL==4){
                availableMoves.push_back(8);
            }
            //Case 2: reverse of case 1
            if(colPosWL==4&&colPosBL==2){
                availableMoves.push_back(8);
            }

        }
            
        

        // string outputLine;
        
        string currSquare,nextSquare;
        vector<string>vecOutputLine;
        //Translate the available moves to a square
        for(int i=0;i<availableMoves.size();i++){
            //Use a map to give the row and col updates for a move
            move=availableMoves[i];
            if(move==8){
                currSquare=colToString[colPosWL]+to_string(rowPosWL+1);
                nextSquare=colToString[colPosBL]+to_string(rowPosBL+1);  
                vecOutputLine.push_back(currSquare+nextSquare); 
            }else{
                vecRowColUpdate=rowColUpdate[move];
                newRow=rowPosWL+vecRowColUpdate[0];
                newCol=colPosWL+vecRowColUpdate[1];
                //Translate square to the correct board notation
                currSquare=colToString[colPosWL]+to_string(rowPosWL+1);
                nextSquare=colToString[newCol]+to_string(newRow+1);
                //Add the move to outputLine
                vecOutputLine.push_back(currSquare+nextSquare);
            }
            
        }
        //For sorted output
        insertionSort(vecOutputLine);
        for(int i=0;i<vecOutputLine.size();i++){
            cout<<vecOutputLine[i]<<" ";//Output all the squares we can move to
        }
        
    }else{
        //Case 1: left most column
        if(colPosBL==2){
            //No 5,6,7
            removeByValue(availableMoves,5);
            removeByValue(availableMoves,6);
            removeByValue(availableMoves,7);
        }
        //Case 2: Right most column
        else if(colPosBL==4){
            //No 1,2,3
            removeByValue(availableMoves,1);
            removeByValue(availableMoves,2);
            removeByValue(availableMoves,3);
        }
        //Case 3: Bottom most row
        if(rowPosBL==4){
            //No 3,4,5
            removeByValue(availableMoves,3);
            removeByValue(availableMoves,4);
            removeByValue(availableMoves,5);
        }
        //Case 4: Top most row
        else if(rowPosBL==6){
            //No 0,1,7
            removeByValue(availableMoves,0);
            removeByValue(availableMoves,1);
            removeByValue(availableMoves,7);
        }
        //Case 5: Own piece blocking us
        vector<int>movesToDelete;
        for(int i=0;i<availableMoves.size();i++){
            //Use a map to give the row and col updates for a move
            move=availableMoves[i];
            vecRowColUpdate=rowColUpdate[move];
            newRow=rowPosBL+vecRowColUpdate[0];
            newCol=colPosBL+vecRowColUpdate[1];

            if(vecBoardState[newRow][newCol]=="p"||vecBoardState[newRow][newCol]=="e"||vecBoardState[newRow][newCol]=="z"){
                movesToDelete.push_back(move);
            }
        }
        if(!movesToDelete.empty()){
            for(int i=0;i<movesToDelete[i];i++){
                removeByValue(availableMoves,movesToDelete[i]);
            }
        }
        
        //Case 6: Capture enemy lion across river
        //Check if the lions are on the same column
        bool openColumn=false;
        if(colPosWL==colPosBL){
            openColumn=true;
            //Check if any piece is blocking them
            for(int i=rowPosWL+1;i<rowPosBL;i++){
                if(vecBoardState[i][colPosWL]!="-"){
                    openColumn=false;
                    break;
                }
            }
            if(openColumn){
                availableMoves.push_back(8);
            }
        }
        //Check for the diagonal capture
        else if(rowPosWL==2&&rowPosBL==5){
            //Case 1: our lion at left edge of the square and enemy on the opposite edge
            if(colPosWL==2&&colPosBL==4){
                availableMoves.push_back(8);
            }
            //Case 2: reverse of case 1
            if(colPosWL==4&&colPosBL==2){
                availableMoves.push_back(8);
            }

        }
        // string outputLine;
        vector<string>vecOutputLine;
        string currSquare,nextSquare;
       
        //Translate the available moves to a square
        for(int i=0;i<availableMoves.size();i++){
            //Use a map to give the row and col updates for a move
            move=availableMoves[i];
            if(move==8){
                currSquare=colToString[colPosBL]+to_string(rowPosBL+1);
                nextSquare=colToString[colPosWL]+to_string(rowPosWL+1);  
                vecOutputLine.push_back(currSquare+nextSquare);              
            }else{
                vecRowColUpdate=rowColUpdate[move];
                newRow=rowPosBL+vecRowColUpdate[0];
                newCol=colPosBL+vecRowColUpdate[1];
                //Translate square to the correct board notation
                currSquare=colToString[colPosBL]+to_string(rowPosBL+1);
                nextSquare=colToString[newCol]+to_string(newRow+1);
                //Add the move to outputLine
                vecOutputLine.push_back(currSquare+nextSquare);
            }
            
        }    
        insertionSort(vecOutputLine);
        for(int i=0;i<vecOutputLine.size();i++){
            cout<<vecOutputLine[i]<<" ";//Output all the squares we can move to
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

    // printBoard();
    initBoard(vecLines[0]);

    cout<<endl;
    for(int row=6;row>=0;row--){
        for(int col=0;col<7;col++){
            cout<<vecBoardState[row][col]<<" ";
        }
        cout<<endl;
    }

    movesLion(vecLine[1]);
        

    

}
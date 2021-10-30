#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<queue>
#include<set>
#include<algorithm>
#include<sstream>
#include<map>
#include<list>

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
//Stores moves to make
vector<string>vecMovesToMake;

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

void resetBoard(){
    for(int row=0;row<7;row++){
        for(int col=0;col<7;col++){
            vecBoardState[row][col]="-";
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

void removeByValue(vector<int>&vec,int value){
	// This is the meat & potatoes
  	for(int i=0;i<vec.size();i++){
        if(vec[i]==value){
            vec.erase(vec.begin() + i);
        }
    }
}
void movesLion(string colourToMove){
    //TODO: Figure out why we are failing the last testcase on moodle
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
            for(int i=0;i<movesToDelete.size();i++){
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
        else if(rowPosWL==2&&rowPosBL==4){
            //Check for piece blocking in the centre of the board
            if(vecBoardState[3][3]=="-"){
                //Case 1: our lion at left edge of the square and enemy on the opposite edge
                if(colPosWL==2&&colPosBL==4){
                    availableMoves.push_back(8);
                }
                //Case 2: reverse of case 1
                if(colPosWL==4&&colPosBL==2){
                    availableMoves.push_back(8);
                }
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
        //Check for empty output
        if(!vecOutputLine.empty()){
            //For sorted output
            insertionSort(vecOutputLine);
            for(int i=0;i<vecOutputLine.size();i++){
                if(i!=vecBoardOutput.size()-1){
                    cout<<vecOutputLine[i]<<" ";//Output all the squares we can move to
                }else{
                    cout<<vecOutputLine[i]<<endl;
                }
                
            }
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
            for(int i=0;i<movesToDelete.size();i++){
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
        else if(rowPosWL==2&&rowPosBL==4){
            //Check if there is piece blocking in the centre of the board
            if(vecBoardState[3][3]=="-"){
                //Case 1: our lion at left edge of the square and enemy on the opposite edge
                if(colPosWL==2&&colPosBL==4){
                    availableMoves.push_back(8);
                }
                //Case 2: reverse of case 1
                if(colPosWL==4&&colPosBL==2){
                    availableMoves.push_back(8);
                }
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
        //Check for empty output line
        if(!vecOutputLine.empty()){
            insertionSort(vecOutputLine);
            for(int i=0;i<vecOutputLine.size();i++){
                if(i!=vecOutputLine.size()-1){
                    cout<<vecOutputLine[i]<<" ";//Output all the squares we can move to
                }else{
                    cout<<vecOutputLine[i]<<endl;
                }
                
            }
        }
     
        
    }
    if(!availableMoves.empty()){
        cout<<endl;
    }
    resetBoard();
}

void movesElephant(string colourToMove){
    // 2d vector (list of all moves they can do)(list of all legal moves the can do)
    vector < vector<int> > availablemoves1, availablemoves2, legalmoves1, legalmoves2;
    //vector of moves to delete (move 1(up) or move 8(jump down) etc.) vector of original positions
    vector<int> movesToDelete1, movesToDelete2, originalposition1, originalposition2;
    //if the first elephant is found can move onto moves for the second elephant and dontadd is dontadd illegal move to legal move vector
    bool elephant1found = false, dontadd;
    //string of original postion in board notation, board notation of where to move, list of moves is expected output
    string e1position, e2position, moveto, listmoves;
    //vector list of moves elephant 1 and elephant 2 can do
    vector<string> legalmovesstring;

    if (colourToMove == "w"){       //if white to move
    //iterate through the whole board
        for (int row = 0; row<7 ; row++){       
            for (int col = 0; col < 7; col++){
                if (vecBoardState[row][col] == "E"){        //elephant of colour found
                    //if the first elephant hasnt been found
                    if (elephant1found == false){
                        originalposition1 = {row, col};
                        vector<int> move0{row,col-1};     //left
                        availablemoves1.push_back(move0);
                        vector<int> move1{row+1,col};     //up
                        availablemoves1.push_back(move1);
                        vector<int> move2{row,col+1};     //right
                        availablemoves1.push_back(move2);
                        vector<int> move3{row-1,col};     //down
                        availablemoves1.push_back(move3);
                        vector<int> move4{row,col-2};     //jumpleft
                        availablemoves1.push_back(move4);
                        vector<int> move5{row+2,col};     //jumpup
                        availablemoves1.push_back(move5);
                        vector<int> move6{row,col+2};     //jumpright 
                        availablemoves1.push_back(move6);
                        vector<int> move7{row-2,col};     //jumpdown
                        availablemoves1.push_back(move7);
                        //available moves has been updated with ALL moves for the first elephant
                        elephant1found = true;
                    }else if(elephant1found){      //second elephants available moves
                        originalposition2 = {row, col};
                        vector<int> move0{row,col-1};     //left
                        availablemoves2.push_back(move0);
                        vector<int> move1{row+1,col};     //up
                        availablemoves2.push_back(move1);
                        vector<int> move2{row,col+1};     //right
                        availablemoves2.push_back(move2);
                        vector<int> move3{row-1,col};     //down
                        availablemoves2.push_back(move3);
                        vector<int> move4{row,col-2};     //jumpleft
                        availablemoves2.push_back(move4);
                        vector<int> move5{row+2,col};     //jumpup
                        availablemoves2.push_back(move5);
                        vector<int> move6{row,col+2};     //jumpright 
                        availablemoves2.push_back(move6);
                        vector<int> move7{row-2,col};     //jumpdown
                        availablemoves2.push_back(move7);
                        //available moves has been updated with ALL moves for the second elephant
                    }
                }     
            }
        }

        //available moves for elephants have been declared
        //now to remove all moves for legals moves
        
        //elephant 1
        if (!availablemoves1.empty()){  
            //removes moves if it moves off the board 
            for (int i = 0; i<8; i++){
                if (availablemoves1[i][0] < 0 || availablemoves1[i][0] > 6 || availablemoves1[i][1] < 0 || availablemoves1[i][1] > 6){     //if the piece moves off the board
                    movesToDelete1.push_back(i);       //deletes that row (deletes that move)
                }else if(vecBoardState[availablemoves1[i][0]][availablemoves1[i][1]] == "P" || vecBoardState[availablemoves1[i][0]][availablemoves1[i][1]] == "E" ||
                vecBoardState[availablemoves1[i][0]][availablemoves1[i][1]] == "L" || vecBoardState[availablemoves1[i][0]][availablemoves1[i][1]] == "Z"){
                    movesToDelete1.push_back(i);       //deletes that row (deletes that move)
                }
            }
        }

        //elephant 2
        if (!availablemoves2.empty()){
            //removes moves if it moves off the board
            for (int i = 0; i<8; i++){
                if (availablemoves2[i][0] < 0 || availablemoves2[i][0] > 6 || availablemoves2[i][1] < 0 || availablemoves2[i][1] > 6){     //if the piece moves off the board
                    movesToDelete2.push_back(i);       //deletes that row (deletes that move)
                }else if(vecBoardState[availablemoves2[i][0]][availablemoves2[i][1]] == "P" || vecBoardState[availablemoves2[i][0]][availablemoves2[i][1]] == "E" ||
                vecBoardState[availablemoves2[i][0]][availablemoves2[i][1]] == "L" || vecBoardState[availablemoves2[i][0]][availablemoves2[i][1]] == "Z"){
                    movesToDelete2.push_back(i);       //deletes that row (deletes that move) 
                }
            }
        }
        //remove the moves to be deleted

        //original positions of the pieces
        if(!originalposition1.empty()){
            e1position = colToString[originalposition1[1]]+to_string(originalposition1[0]+1);
        }
        if(!originalposition2.empty()){
            e2position = colToString[originalposition2[1]]+to_string(originalposition2[0]+1);
        }

        //elephant 1
        dontadd = false;
        //moves to delete will not copy moves from available moves to legal moves
        if (!movesToDelete1.empty()){
            for (int i = 0; i < 8; i++){        //iterate through all available moves
                for (int remove = 0; remove < movesToDelete1.size() ; remove++){        //iterate through moves to be deleted
                    if (i == movesToDelete1[remove]){
                        dontadd = true;
                    }
                }
                if(!dontadd){
                    legalmoves1.push_back(availablemoves1[i]);
                }
                dontadd = false;
            }
        }else{
            legalmoves1 = availablemoves1;
        }

        //elephant 2
        dontadd = false;
        //moves to delete will not copy moves from available moves to legal moves
        if (!movesToDelete2.empty()){
            for (int i = 0; i < 8; i++){        //iterate through all available moves
                for (int remove = 0; remove < movesToDelete2.size() ; remove++){        //iterate through moves to be deleted
                    if (i == movesToDelete2[remove]){
                        dontadd = true;
                    }
                }
                if (!dontadd){
                    legalmoves2.push_back(availablemoves2[i]);
                }
                dontadd = false;
            }
        }else{
            legalmoves2 = availablemoves2;
        }

        //print out availbe moves as move board
        //elephant2 first because our array 0,0 is bottom left but steve wants it to start at top left
        if (!legalmoves2.empty()){
            for (int i =0 ; i < legalmoves2.size(); i++){
                moveto = colToString[legalmoves2[i][1]]+to_string(legalmoves2[i][0]+1);
                legalmovesstring.push_back(e2position+moveto);
            }
        }

        //elephant 1
        if (!legalmoves1.empty()){
            for (int i =0 ; i < legalmoves1.size(); i++){
                moveto = colToString[legalmoves1[i][1]]+to_string(legalmoves1[i][0]+1);
                legalmovesstring.push_back(e1position+moveto);
            }
        }

        if(!legalmovesstring.empty()){
            sort(legalmovesstring.begin(), legalmovesstring.end());
            for (int i = 0; i < legalmovesstring.size(); i++){
                listmoves = listmoves + legalmovesstring[i] + " ";
            }
        }
        
        if(!listmoves.empty()){
            listmoves.pop_back();
        }
        
        cout << listmoves << endl;
    }else{      //black to move
        //iterate through the whole board
        for (int row = 0; row<7 ; row++){       
            for (int col = 0; col < 7; col++){
                if (vecBoardState[row][col] == "e"){        //elephant of colour found
                    //if the first elephant hasnt been found
                    if (elephant1found == false){
                        originalposition1 = {row, col};
                        vector<int> move0{row,col-1};     //left
                        availablemoves1.push_back(move0);
                        vector<int> move1{row+1,col};     //up
                        availablemoves1.push_back(move1);
                        vector<int> move2{row,col+1};     //right
                        availablemoves1.push_back(move2);
                        vector<int> move3{row-1,col};     //down
                        availablemoves1.push_back(move3);
                        vector<int> move4{row,col-2};     //jumpleft
                        availablemoves1.push_back(move4);
                        vector<int> move5{row+2,col};     //jumpup
                        availablemoves1.push_back(move5);
                        vector<int> move6{row,col+2};     //jumpright 
                        availablemoves1.push_back(move6);
                        vector<int> move7{row-2,col};     //jumpdown
                        availablemoves1.push_back(move7);
                        //available moves has been updated with ALL moves for the first elephant
                        elephant1found = true;
                    }else if(elephant1found){      //second elephants available moves
                        originalposition2 = {row, col};
                        vector<int> move0{row,col-1};     //left
                        availablemoves2.push_back(move0);
                        vector<int> move1{row+1,col};     //up
                        availablemoves2.push_back(move1);
                        vector<int> move2{row,col+1};     //right
                        availablemoves2.push_back(move2);
                        vector<int> move3{row-1,col};     //down
                        availablemoves2.push_back(move3);
                        vector<int> move4{row,col-2};     //jumpleft
                        availablemoves2.push_back(move4);
                        vector<int> move5{row+2,col};     //jumpup
                        availablemoves2.push_back(move5);
                        vector<int> move6{row,col+2};     //jumpright 
                        availablemoves2.push_back(move6);
                        vector<int> move7{row-2,col};     //jumpdown
                        availablemoves2.push_back(move7);
                        //available moves has been updated with ALL moves for the second elephant
                    }
                }     
            }
        }

        //available moves for elephants have been declared
        //now to remove all moves for legals moves
        
        //elephant 1
        if (!availablemoves1.empty()){  
            //removes moves if it moves off the board 
            for (int i = 0; i<8; i++){
                if (availablemoves1[i][0] < 0 || availablemoves1[i][0] > 6 || availablemoves1[i][1] < 0 || availablemoves1[i][1] > 6){     //if the piece moves off the board
                    movesToDelete1.push_back(i);       //deletes that row (deletes that move)
                }else if(vecBoardState[availablemoves1[i][0]][availablemoves1[i][1]] == "p" || vecBoardState[availablemoves1[i][0]][availablemoves1[i][1]] == "e" ||
                vecBoardState[availablemoves1[i][0]][availablemoves1[i][1]] == "l" || vecBoardState[availablemoves1[i][0]][availablemoves1[i][1]] == "z"){
                    movesToDelete1.push_back(i);       //deletes that row (deletes that move)
                }
            }
        }

        //elephant 2
        if (!availablemoves2.empty()){
            //removes moves if it moves off the board
            for (int i = 0; i<8; i++){
                if (availablemoves2[i][0] < 0 || availablemoves2[i][0] > 6 || availablemoves2[i][1] < 0 || availablemoves2[i][1] > 6){     //if the piece moves off the board
                    movesToDelete2.push_back(i);       //deletes that row (deletes that move)
                }else if(vecBoardState[availablemoves2[i][0]][availablemoves2[i][1]] == "p" || vecBoardState[availablemoves2[i][0]][availablemoves2[i][1]] == "e" ||
                vecBoardState[availablemoves2[i][0]][availablemoves2[i][1]] == "l" || vecBoardState[availablemoves2[i][0]][availablemoves2[i][1]] == "z"){
                    movesToDelete2.push_back(i);       //deletes that row (deletes that move) 
                }
            }
        }
        //remove the moves to be deleted

        //original positions of the pieces
        if(!originalposition1.empty()){
            e1position = colToString[originalposition1[1]]+to_string(originalposition1[0]+1);
        }
        if(!originalposition2.empty()){
            e2position = colToString[originalposition2[1]]+to_string(originalposition2[0]+1);
        }

        //elephant 1
        dontadd = false;
        //moves to delete will not copy moves from available moves to legal moves
        if (!movesToDelete1.empty()){
            for (int i = 0; i < 8; i++){        //iterate through all available moves
                for (int remove = 0; remove < movesToDelete1.size() ; remove++){        //iterate through moves to be deleted
                    if (i == movesToDelete1[remove]){
                        dontadd = true;
                    }
                }
                if(!dontadd){
                    legalmoves1.push_back(availablemoves1[i]);
                }
                dontadd = false;
            }
        }else{
            legalmoves1 = availablemoves1;
        }

        //elephant 2
        dontadd = false;
        //moves to delete will not copy moves from available moves to legal moves
        if (!movesToDelete2.empty()){
            for (int i = 0; i < 8; i++){        //iterate through all available moves
                for (int remove = 0; remove < movesToDelete2.size() ; remove++){        //iterate through moves to be deleted
                    if (i == movesToDelete2[remove]){
                        dontadd = true;
                    }
                }
                if (!dontadd){
                    legalmoves2.push_back(availablemoves2[i]);
                }
                dontadd = false;
            }
        }else{
            legalmoves2 = availablemoves2;
        }

        //print out availbe moves as move board
        //elephant2 first because our array 0,0 is bottom left but steve wants it to start at top left
        if (!legalmoves2.empty()){
            for (int i =0 ; i < legalmoves2.size(); i++){
                moveto = colToString[legalmoves2[i][1]]+to_string(legalmoves2[i][0]+1);
                legalmovesstring.push_back(e2position+moveto);
            }
        }

        //elephant 1
        if (!legalmoves1.empty()){
            for (int i =0 ; i < legalmoves1.size(); i++){
                moveto = colToString[legalmoves1[i][1]]+to_string(legalmoves1[i][0]+1);
                legalmovesstring.push_back(e1position+moveto);
            }
        }

        if(!legalmovesstring.empty()){
            sort(legalmovesstring.begin(), legalmovesstring.end());
            for (int i = 0; i < legalmovesstring.size(); i++){
                listmoves = listmoves + legalmovesstring[i] + " ";
            }
        }
        
        if(!listmoves.empty()){
            listmoves.pop_back();
        }
        
        cout << listmoves << endl;
    }
    resetBoard();
}

vector<string> legalpawnmoves(string colourToMove, vector<int> origin){
    vector<vector<int>> allmoves, legalmoves;
    vector<int> movesToDelete;
    int row = origin[0], col = origin[1];
    string originnotation, moveto;
    bool pawnblockedback=false, dontadd;
    vector<string> legalmovesstring;

    originnotation = colToString[col] + to_string(row+1); //eg pawn start at e5

    if(colourToMove == "w"){
        //all possible moves
        vector<int> move0 = {row+1, col-1}; //top left
        allmoves.push_back(move0);
        vector<int> move1 = {row+1, col}; // top
        allmoves.push_back(move1);
        vector<int> move3 = {row+1, col+1}; // top right
        allmoves.push_back(move3);

        //for moves to be removed
        for (int i = 0; i<3; i++){
            if (allmoves[i][0] < 0 || allmoves[i][0] > 6 || allmoves[i][1] < 0 || allmoves[i][1] > 6){     //if the piece moves off the board
                movesToDelete.push_back(i);       //deletes that row (deletes that move)
            }else if(vecBoardState[allmoves[i][0]][allmoves[i][1]] == "P" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "E" ||
            vecBoardState[allmoves[i][0]][allmoves[i][1]] == "L" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "Z"){
                movesToDelete.push_back(i);       //deletes that row (deletes that move)
            }
        }

        if(row>3){      //past the river can do extra moves
            //all possible moves if it crossed the river
            vector<int> move4 = {row-1, col}; // jump one back
            allmoves.push_back(move4);
            vector<int> move5 = {row-2, col}; //jump 2 back
            allmoves.push_back(move5);

            //for moves to be removed
            for (int i = 3; i<5; i++){
                if (allmoves[i][0] < 0 || allmoves[i][0] > 6 || allmoves[i][1] < 0 || allmoves[i][1] > 6){     //if the piece moves off the board
                    movesToDelete.push_back(i);       //deletes that row (deletes that move)
                }
                else if(i==3){
                    if(vecBoardState[allmoves[i][0]][allmoves[i][1]] == "P" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "E" ||
                    vecBoardState[allmoves[i][0]][allmoves[i][1]] == "L" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "Z" ||
                    vecBoardState[allmoves[i][0]][allmoves[i][1]] == "p" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "e" ||
                    vecBoardState[allmoves[i][0]][allmoves[i][1]] == "l" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "z"){
                        movesToDelete.push_back(i);
                        pawnblockedback = true;
                    } 
                }
                else if(i==4){
                    if(pawnblockedback){
                        movesToDelete.push_back(i);
                    }else{
                        if(vecBoardState[allmoves[i][0]][allmoves[i][1]] == "P" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "E" ||
                        vecBoardState[allmoves[i][0]][allmoves[i][1]] == "L" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "Z" ||
                        vecBoardState[allmoves[i][0]][allmoves[i][1]] == "p" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "e" ||
                        vecBoardState[allmoves[i][0]][allmoves[i][1]] == "l" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "z"){
                            movesToDelete.push_back(i);
                        }   
                    }
                }
            } 
        }
    }else if(colourToMove=="b"){
        //all possible moves
        vector<int> move0 = {row-1, col-1}; //bottom left
        allmoves.push_back(move0);
        vector<int> move1 = {row-1, col}; // bottom
        allmoves.push_back(move1);
        vector<int> move3 = {row-1, col+1}; // bottom right
        allmoves.push_back(move3);

        //for moves to be removed
        for (int i = 0; i<3; i++){
            if (allmoves[i][0] < 0 || allmoves[i][0] > 6 || allmoves[i][1] < 0 || allmoves[i][1] > 6){     //if the piece moves off the board
                movesToDelete.push_back(i);       //deletes that row (deletes that move)
            }else if(vecBoardState[allmoves[i][0]][allmoves[i][1]] == "p" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "e" ||
            vecBoardState[allmoves[i][0]][allmoves[i][1]] == "l" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "z"){
                movesToDelete.push_back(i);       //deletes that row (deletes that move)
            }
        }

        if(row<3){      //past the river can do extra moves
            //all possible moves if it crossed the river
            vector<int> move4 = {row+1, col}; // jump one back
            allmoves.push_back(move4);
            vector<int> move5 = {row+2, col}; //jump 2 back
            allmoves.push_back(move5);

            //for moves to be removed
            for (int i = 3; i<5; i++){
                if (allmoves[i][0] < 0 || allmoves[i][0] > 6 || allmoves[i][1] < 0 || allmoves[i][1] > 6){     //if the piece moves off the board
                    movesToDelete.push_back(i);       //deletes that row (deletes that move)
                }
                else if(i==3){
                    if(vecBoardState[allmoves[i][0]][allmoves[i][1]] == "P" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "E" ||
                    vecBoardState[allmoves[i][0]][allmoves[i][1]] == "L" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "Z" ||
                    vecBoardState[allmoves[i][0]][allmoves[i][1]] == "p" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "e" ||
                    vecBoardState[allmoves[i][0]][allmoves[i][1]] == "l" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "z"){
                        movesToDelete.push_back(i);
                        pawnblockedback = true;
                    } 
                }
                else if(i==4){
                    if(pawnblockedback){
                        movesToDelete.push_back(i);
                    }else{
                        if(vecBoardState[allmoves[i][0]][allmoves[i][1]] == "P" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "E" ||
                        vecBoardState[allmoves[i][0]][allmoves[i][1]] == "L" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "Z" ||
                        vecBoardState[allmoves[i][0]][allmoves[i][1]] == "p" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "e" ||
                        vecBoardState[allmoves[i][0]][allmoves[i][1]] == "l" || vecBoardState[allmoves[i][0]][allmoves[i][1]] == "z"){
                            movesToDelete.push_back(i);
                        }   
                    }
                }
            } 
        }
    }

    //create a vector containing legal moves
    dontadd = false;
    //moves to delete will not copy moves from available moves to legal moves
    if (!movesToDelete.empty()){
        for (int i = 0; i < allmoves.size(); i++){        //iterate through all available moves
            for (int remove = 0; remove < movesToDelete.size() ; remove++){        //iterate through moves to be deleted
                if (i == movesToDelete[remove]){
                    dontadd = true;
                }
            }
            if(!dontadd){
                legalmoves.push_back(allmoves[i]);
            }
            dontadd = false;
        }

    }else{
        legalmoves = allmoves;
    }
    
    //adding legal moves to the lists with cnotations
    if (!legalmoves.empty()){
        for (int i =0 ; i < legalmoves.size(); i++){
            moveto = colToString[legalmoves[i][1]]+to_string(legalmoves[i][0]+1);
            legalmovesstring.push_back(originnotation + moveto);
        }
    }

    return legalmovesstring;
}

void movesPawn(string colourToMove){
    //get colour that has to move
    vector<string> legalmovesstring, movesofcurrentpawn;
    string listmoves;
    if (colourToMove == "w"){
        //get the board state
        for(int row = 0; row<7; row++){
            for(int col = 0; col < 7; col++){
                if (vecBoardState[row][col] == "P"){        //if white moves we looking for P / else if black move we looking for p
                    movesofcurrentpawn = legalpawnmoves("w", {row,col});
                    //add the moves of this pawn to the vector of all the legal moves possible
                    legalmovesstring.insert(legalmovesstring.end(), movesofcurrentpawn.begin(), movesofcurrentpawn.end());
                }
            }
        }
    }else if(colourToMove == "b"){
        //get the board state
        for(int row = 0; row<7; row++){
            for(int col = 0; col < 7; col++){
                if (vecBoardState[row][col] == "p"){        //if white moves we looking for P / else if black move we looking for p
                    movesofcurrentpawn = legalpawnmoves("b", {row,col});
                    //add the moves of this pawn to the vector of all the legal moves possible
                    legalmovesstring.insert(legalmovesstring.end(), movesofcurrentpawn.begin(), movesofcurrentpawn.end());
                }
            }
        }
    }
    
    if(!legalmovesstring.empty()){
        sort(legalmovesstring.begin(), legalmovesstring.end());
        for (int i = 0; i < legalmovesstring.size(); i++){
            listmoves = listmoves + legalmovesstring[i] + " ";
        }
    }
        
    if(!listmoves.empty()){
        listmoves.pop_back();
    }
        
    cout << listmoves << endl;
    resetBoard();
}

void movesZebra(string colourToMove){
    //TODO: No Zebra on the board
    bool foundZebra=false;
    int posRowZ,posColZ,newPosRowZ,newPosColZ,move;
    vector<int>availableMoves={0,1,2,3,4,5,6,7};
    vector<int>vecRowColUpdate;
    vector<int>movesToDelete;
    map<int,vector<int>>rowColUpdate{
        {0,{2,-1}},{1,{2,1}},{2,{1,2}},{3,{-1,2}},{4,{-2,1}},{5,{-2,-1}},{6,{-1,-2}},{7,{1,-2}}
    };
    if(colourToMove=="w"){
        //Find the position of the white zebra
        for(int row=0;row<7;row++){
            for(int col=0;col<7;col++){
                if(vecBoardState[row][col]=="Z"){
                    posRowZ=row;
                    posColZ=col;
                    foundZebra=true;
                }
            }
        }
        if(foundZebra){
            //Cases for movement 
            //Case 1: 1 row from top of board
            if(posRowZ>=5){
                removeByValue(availableMoves,0);
                removeByValue(availableMoves,1);
            }
            //Case 2: At the top edge of the board
            if(posRowZ==6){
                removeByValue(availableMoves,2);
                removeByValue(availableMoves,7);
            }
            //Case 3: 1 column from right most edge
            if(posColZ>=5){
                removeByValue(availableMoves,2);
                removeByValue(availableMoves,3);
            }
            //Case 4: At the right most column
            if(posColZ==6){
                removeByValue(availableMoves,1);
                removeByValue(availableMoves,4);
            }
            //Case 5: 1 row from bottom of the board
            if(posRowZ<=1){
                removeByValue(availableMoves,4);
                removeByValue(availableMoves,5);
            }
            //Case 6: At bottom row of the board
            if(posRowZ==0){
                removeByValue(availableMoves,3);
                removeByValue(availableMoves,6);
            }
            //Case 7: One column from left most edge
            if(posColZ<=1){
                removeByValue(availableMoves,6);
                removeByValue(availableMoves,7);
            }
            //Case 8: At the left most edge of the board
            if(posColZ==0){
                removeByValue(availableMoves,0);
                removeByValue(availableMoves,5);
            }
            //Case 9: Check for own pieces blocking
            for(int i=0;i<availableMoves.size();i++){
                move=availableMoves[i];
                vecRowColUpdate=rowColUpdate[move];
                newPosRowZ=posRowZ+vecRowColUpdate[0];
                newPosColZ=posColZ+vecRowColUpdate[1];
                if(vecBoardState[newPosRowZ][newPosColZ]=="P"||vecBoardState[newPosRowZ][newPosColZ]=="L"||vecBoardState[newPosRowZ][newPosColZ]=="E"){
                    movesToDelete.push_back(move);
                }
            }
            if(!movesToDelete.empty()){
                for(int i=0;i<movesToDelete.size();i++){
                    removeByValue(availableMoves,movesToDelete[i]);
                }
            }
            //Output the available moves
        }    
    }else{
        //Find the position of the black zebra
        for(int row=0;row<7;row++){
            for(int col=0;col<7;col++){
                if(vecBoardState[row][col]=="z"){
                    posRowZ=row;
                    posColZ=col;
                    foundZebra=true;
                }
            }
        }

        if(foundZebra){
            //Cases for movement 
            //Case 1: 1 row from top of board
            if(posRowZ>=5){
                removeByValue(availableMoves,0);
                removeByValue(availableMoves,1);
            }
            //Case 2: At the top edge of the board
            if(posRowZ==6){
                removeByValue(availableMoves,2);
                removeByValue(availableMoves,7);
            }
            //Case 3: 1 column from right most edge
            if(posColZ>=5){
                removeByValue(availableMoves,2);
                removeByValue(availableMoves,3);
            }
            //Case 4: At the right most column
            if(posColZ==6){
                removeByValue(availableMoves,1);
                removeByValue(availableMoves,4);
            }
            //Case 5: 1 row from bottom of the board
            if(posRowZ<=1){
                removeByValue(availableMoves,4);
                removeByValue(availableMoves,5);
            }
            //Case 6: At bottom row of the board
            if(posRowZ==0){
                removeByValue(availableMoves,3);
                removeByValue(availableMoves,6);
            }
            //Case 7: One column from left most edge
            if(posColZ<=1){
                removeByValue(availableMoves,6);
                removeByValue(availableMoves,7);
            }
            //Case 8: At the left most edge of the board
            if(posColZ==0){
                removeByValue(availableMoves,0);
                removeByValue(availableMoves,5);
            }
            //Case 9: Check for own pieces blocking
            for(int i=0;i<availableMoves.size();i++){
                move=availableMoves[i];
                vecRowColUpdate=rowColUpdate[move];
                newPosRowZ=posRowZ+vecRowColUpdate[0];
                newPosColZ=posColZ+vecRowColUpdate[1];
                if(vecBoardState[newPosRowZ][newPosColZ]=="p"||vecBoardState[newPosRowZ][newPosColZ]=="l"||vecBoardState[newPosRowZ][newPosColZ]=="e"){
                    movesToDelete.push_back(move);
                }
            }
            if(!movesToDelete.empty()){
                for(int i=0;i<movesToDelete.size();i++){
                    removeByValue(availableMoves,movesToDelete[i]);
                }
            }
            //Output available moves
        }
    }
    if(foundZebra){
        // string outputLine;
        vector<string>vecOutputLine;
        string currSquare,nextSquare;
        
        if(!availableMoves.empty()){
            //Translate the available moves to a square
            for(int i=0;i<availableMoves.size();i++){
                move=availableMoves[i];
                //Use a map to give the row and col updates for a move
                vecRowColUpdate=rowColUpdate[move];
                //Update the new row and column
                newPosRowZ=posRowZ+vecRowColUpdate[0];
                newPosColZ=posColZ+vecRowColUpdate[1];
                //Translate square to the correct board notation
                currSquare=colToString[posColZ]+to_string(posRowZ+1);
                nextSquare=colToString[newPosColZ]+to_string(newPosRowZ+1);
                //Add the move to outputLine
                vecOutputLine.push_back(currSquare+nextSquare);
            }    
            //Check for empty output line
            if(!vecOutputLine.empty()){
                insertionSort(vecOutputLine);
                for(int i=0;i<vecOutputLine.size();i++){
                    if(i!=vecOutputLine.size()-1){
                        cout<<vecOutputLine[i]<<" ";//Output all the squares we can move to
                    }else{
                        cout<<vecOutputLine[i]<<endl;
                    }
                    
                }
            }

        }
    }
    resetBoard();
}


int main(){
    string numInput;
    string line,moveToMake;

    getline(cin,numInput);
    vecLines.resize(stoi(numInput));
    vecMovesToMake.resize(stoi(numInput));
    for(int k=0;k<stoi(numInput);k++){
        getline(cin,line);
        vecLines[k]=line;
        getline(cin,moveToMake);
        vecMovesToMake[k]=line;
    }

    // printBoard();
    for(int i=0;i<vecLines.size();i++){
        initBoard(vecLines[i]);

        // cout<<endl;
        // for(int row=6;row>=0;row--){
        //     for(int col=0;col<7;col++){
        //         cout<<vecBoardState[row][col]<<" ";
        //     }
        //     cout<<endl;
        // }
        movesZebra(vecLine[1]);
    }
}
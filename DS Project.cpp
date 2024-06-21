#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cctype>
using namespace std;
//FUNCTIONS USED THROUGHOUT WHOLE PROGRAM
string Encryption(string text);
string Decryption(string text);
string createpairs(string &input);
void createkeymatrix(string key);
void findinmatrix(char letter,int &row,int &col);
string removex(string text);

//INITIALIZING THE MATRIX 5 BY 5
char keymatrix[5][5];

//PRINTING THE MATRIX
void output(){
for(int i=0;i<5;++i){
for(int j=0;j<5;++j){
cout<<keymatrix[i][j]<<" ";
}
cout<<endl;
}
}
int main(){
string key,option,input;
cout<<"KEY:"<<endl;
//creating key matrix first
getline(cin,key);
createkeymatrix(key);
output();
while(1){
cout<<"OPTION: Encryption, Decryption or New Key e/d/n:"<<endl;


getline(cin,option);
//cout<<"Input: Enter plain text: "<<endl;
//getline(cin,input);
char c=option[0];
//asking from the user if he will put e (encryption) will be done
if(c=='e'){
	cout<<"Enter Plain Text:"<<endl;
	getline(cin,input);
input=createpairs(input);
cout<<input<<endl;
cout<<Encryption(input)<<endl;
}
//if he will put d (decryption) will be done
else if(c=='d'){
	cout<<"Enter Plain Text:"<<endl;
getline(cin,input);
cout<<removex(Decryption(input))<<endl;
}
// if he wants a new key in program
else if(c=='n'){
cout<<"NEW KEY:"<<endl;
getline(cin,key);
createkeymatrix(key);
}
else
cout<<"INVALID OPTION:"<<endl;
}
}

int mod(int a,int b){
 int r=a%b;
 return r < 0?r+b:r;
}


void replace(string &text,int pos,char from,char to){
if(text[pos]==from)
text[pos] = to;
if(text[pos+1]==from)
text[pos + 1] = to;
}

void findinmatrix(char letter,int &row,int &col){
   for(int r=0;r<5;++r)
   for(int c=0;c<5;++c)
   if(letter==keymatrix[r][c]){
    row=r;
    col=c;
    return;
   }
}

string Encryption(string text){
    string output="";
    int row1,col1,row2,col2;
    int size=text.length();
    for(int pos=0;pos<size;pos+=2){
    replace(text,pos,'j','i');
   
   //get position of pairs in matrix
    findinmatrix(text[pos],row1,col1);
    findinmatrix(text[pos+1],row2,col2);
   
   
    //same row->shift to right mod 5
    if(row1==row2){
    output+=keymatrix[row1][mod(col1+1,5)];
    output+=keymatrix[row2][mod(col2+1,5)];
   
}
//same col->shift down  mod 5
else if(col1==col2){
    output+=keymatrix[mod(row1+1,5)][col1];
    output+=keymatrix[mod(row2+1,5)][col2];
}

//diagonal->swap coloums
else{
output+=keymatrix[row1][col2];
output+=keymatrix[row2][col1];
}

}

return output;
}

string Decryption(string text){
    string output="";
    int row1,col1,row2,col2;
    int size=text.length();
    for(int pos=0;pos<size;pos+=2){
   
   
    findinmatrix(text[pos],row1,col1);
    findinmatrix(text[pos+1],row2,col2);
   
   
    //same row->shift to right mod 5
    if(row1==row2){
    output+=keymatrix[row1][mod(col1-1,5)];
    output+=keymatrix[row2][mod(col2-1,5)];
   
}
//same col->shift down  mod 5
else if(col1==col2){
output+=keymatrix[mod(row1-1,5)][col1];
    output+=keymatrix[mod(row2-1,5)][col2];
}

//diagonal->swap coloums
else{
output+=keymatrix[row1][col2];
output+=keymatrix[row2][col1];
}

}

return output;
}

string removex(string text){
    string orignal="";
    orignal+=text[0];
    int size=text.length();
   
   
    //start at 1 and stop at size-1 since we access i-1 and i+1
    //we do this because an X will never be 0th index
    for(int i=1;i<size-1;++i){
    if(!(text[i]=='x'&& text[i-1]==text[i+1]))
    orignal+=text[i];
}

//last letter is missed

orignal+=text[size-1];
    return orignal;
}


bool found(char c, vector<char> used){
return find(used.begin(),used.end(),c)!=used.end();
}

void createkeymatrix(string key){
vector<char> used;  //stores used letters
used.push_back('j');

int size=key.length();
int count=0;
char fillletter='a';

for(int row=0;row<5;++row)
 for(int col=0;col<5;++col)
  if(count<size){                 //INSERT KEY STAGE
char letter=key[count];
if(!found(letter,used)){
keymatrix[row][col]=letter;
used.push_back(letter);
}
else
--col;              //LAG BACK
++count;          //TRY NEXT LETTER
}
else{
if(!found(fillletter,used))
keymatrix[row][col]=fillletter;
else
--col;            
++fillletter;
}
}
string createpairs(string &input){
// Initialize a new string with a space
string newstring="";
// Get the length of the input string
int size=input.length();

// Loop through the characters of the input string
for(int i=1;i<size;++i){
// Check if the previous character is not a space
if(!isspace(input[i-1])){
// Add the previous character to the new string
newstring+=input[i-1];
// If the previous and current characters are the same, add an 'X' to the new string
if(input[i-1]==input[i])
newstring+='x';
}
}
// Add the last character of the input string to the new string
newstring+=input[size-1];
// If the length of the new string is odd, add an extra 'X' to make it even
if((newstring.length()&1)==1)
newstring+='x';
return newstring;
}

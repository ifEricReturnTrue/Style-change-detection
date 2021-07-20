//
//  main.cpp
//  summer research
//
//  Created by Eric Zheng on 2021-07-15.
//

#include<iostream>
#include<fstream>
#include<sstream>
#include <vector>

using namespace std;

void sentenceByString (ifstream &myFile);
void sentenceByVec (ifstream &myFile);
void outputVec();
void processParagraph(char line[]);

char out[1000000];
int pos = 0;

int main() {
    
    ifstream myFile;
    int fileNum = 100;
    
    char line[10000];
    
    
    
    for (fileNum = 1; fileNum < 2401; fileNum++){
        //Open a file, define input and output file names
        stringstream fileName, outputName;
        fileName << "problem-" << fileNum << ".txt";
        outputName << "sentence-problem-" << fileNum << ".txt" ;
        string myFileName = fileName.str();
        string fileOutputName = outputName.str();
        
        myFile.open(myFileName);
        
        //Check if file open
        if (myFile.is_open()) {
            
            while (!myFile.eof()) {
                
                //Take the chars until the first change line char is found (paragraph)
                myFile.getline(line, 10000, '\n');
                //Process the line
                processParagraph(line);
                
                //put an extra line change char to have different paragraphs seperated
                out[pos] = '\n';
                pos++;
                
            }
            
        }
        
        //output to the files
        ofstream outputFile(fileOutputName);
        
        outputFile << out;
                
        myFile.close();
        outputFile.close();
        
        pos = 0;
        
        //clear the string for next loop
        for (int i = 0; i < 100000; i++){
            out[i] = '\0';
        }
    
    }
    return 0;
}

void processParagraph(char line[]){
    
    //pre defining flags and some variables
    char currentChar, lastChar, nextChar;
    
    bool nextCharNewLine = false;
    
    bool waitForLetter = false;
    
    bool otherCharMeet = false;
    
    currentChar = line[0];
    nextChar = line[1];
    
    int i = 0;
    
    for (i = 0; line[i]!='\0'; i++, pos++){
        
        lastChar = currentChar;
        currentChar = line[i];
        //if next char exists, we take the next one
        if (line[i]!='\0') nextChar = line[i+1];
        
        //if after next character we need a new line, we process here and then skip this loop
        if (nextCharNewLine){
            out[pos] = line[i];
            pos++;
            out[pos] = '\n';
            nextCharNewLine = false;
            waitForLetter = true;
            continue;
        }
        
        //if we are waiting for letters(emoji case), we process here
        if (waitForLetter){
            if ((currentChar >= 'A')&&(currentChar <= 'Z')){
                waitForLetter = false;
                otherCharMeet = false;
            }else if ((currentChar >= 'a')&&(currentChar <= 'z')){
                waitForLetter = false;
                otherCharMeet = false;
            }else if ((currentChar == '(') && (otherCharMeet == false)){
                waitForLetter = false;
            }else{
                pos--;
                if (currentChar != ' ') otherCharMeet = true;
                continue;
            }
        }
        
        //if we found these chars, we need to see if it is a real end of sentence
        if ((currentChar == '.')||
            (currentChar == '!')||
            (currentChar == '?')){
            
            //last char is a letter, next char is a space, the last condition is taking care of 'e.g. ' case
            if ((lastChar >= 'a')&&(lastChar <= 'z')&&(nextChar==' ')&&(line[i-2] != '.')){
                out[pos] = line[i];
                pos++;
                out[pos] = '\n';
                waitForLetter = true;
            }else if ((lastChar >= 'A')&&(lastChar <= 'Z')&&(nextChar==' ')&&(line[i-2] != '.')){
                out[pos] = line[i];
                pos++;
                out[pos] = '\n';
                waitForLetter = true;
            }
            
            //a punctuation after bracktet should be end of sentence
            else if (lastChar == ')'){
                out[pos] = line[i];
                pos++;
                out[pos] = '\n';
                waitForLetter = true;
            }
            
            
            //if punctuation inside a bracket
            else if (nextChar==')'){
                //if the one after is the end of paragraph, must change line
                if (line[i+2] == '\0'){
                    nextCharNewLine = true;
                    out[pos] = line[i];
                    
                //if we have a space following braket we keep looking
                }else if (line[i+2] == ' '){
                    //first check end of line character
                    if (line[i+3] == '\0'){
                        nextCharNewLine = true;
                        out[pos] = line[i];
                    //Otherwise we check if this is a capital letter, only a capital letter should be new line
                    }else if ((line[i+3] >= 'A')&&(line[i+3] <= 'Z')){
                        nextCharNewLine = true;
                        out[pos] = line[i];
                    //otherwise no new line
                    }else{
                        out[pos] = line[i];
                    }
                }else{
                    out[pos] = line[i];
                }
            }
            
            //Whenever next char is end of line, we should put a new line
            else if (nextChar=='\0'){
                out[pos] = line[i];
                pos++;
                out[pos] = '\n';
                waitForLetter = true;
            }else if (nextChar=='\0'){
                out[pos] = line[i];
                pos++;
                out[pos] = '\n';
                waitForLetter = true;
            }
            
            
            
            //if the punctuation has spaces around it. we check is there is a capital letter following
            //ie: What ? Ok. -> new line
            //ie: This is a . dot. -> no new line
            else if ((lastChar == ' ')&&(nextChar==' ')){
                if((line[i+2] > 'A')&&(line[i+2] < 'Z')){
                    out[pos] = line[i];
                    pos++;
                    out[pos] = '\n';
                    waitForLetter = true;
                }else{
                    out[pos] = line[i];
                }
            }
            
            //... case handling
            else if ((lastChar == '.')&&(nextChar==' ')){
                out[pos] = line[i];
                pos++;
                out[pos] = '\n';
                waitForLetter = true;
            }
            
            //otherwise no new line
            else{
                out[pos] = line[i];
            }
                
            
        }else{
            //Whenever next char is end of line, we should put a new line
            if (nextChar == '\0'){
                out[pos] = line[i];
                pos++;
                out[pos] = '\n';
                waitForLetter = true;
            //Otherwise no new line
            }else{
                out[pos] = line[i];
            }
        }
        
    }
    
}


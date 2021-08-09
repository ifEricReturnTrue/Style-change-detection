//
//  main.cpp
//  URL cleaning
//
//  Created by Eric Zheng on 2021-08-07.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string URLKey = "http";

int main(int argc, const char * argv[]) {
    
    ifstream myFile;
    
    int fileNum = 1;
    
    for (fileNum = 1; fileNum < 11201; fileNum++){
        
        stringstream fileName;
        fileName << "sentence-problem-" << fileNum << ".txt";
        string oneFile;
        stringstream outputName;
        outputName << "sentence-problem-URLCleaned-" << fileNum << ".txt";
        
        myFile.open(fileName.str());
        
        if (myFile.is_open()) {
                    
            while (!myFile.eof()) {
                
                stringstream lineSS;
                
                string tempStr;
                char line[10000];
                
                myFile.getline(line, 10000, '\n');
                
                lineSS << line;
                
                while (!lineSS.eof()){
                    lineSS >> tempStr;
                    if (tempStr.size() > 10){
                        string strNeed;
                        bool URLFound = false;
                        for (int i = 0; i < tempStr.size()-URLKey.size(); i++){
                            string subString = tempStr.substr(i, URLKey.size());
                            if (subString == URLKey){
                                URLFound = true;
                                
                                tempStr[i] = 'U';
                                tempStr[i+1] = 'R';
                                tempStr[i+2] = 'L';
                                
                                strNeed = tempStr.substr(0, i+3);
                                
                                oneFile = oneFile + strNeed;
                                oneFile = oneFile + " ";
                                
                                //cout << fileNum << endl;
                                break;
                            }
                        }
                        
                        if(URLFound==false){
                            oneFile = oneFile + tempStr;
                            oneFile = oneFile + " ";
                        }
                        
                    }else{
                        oneFile = oneFile + tempStr;
                        oneFile = oneFile + " ";
                    }
                    
                }
                lineSS.clear();
                oneFile = oneFile + "\n";
                                
            }
            myFile.clear();
        }
        
        myFile.close();
        
        
        ofstream outputFile(outputName.str());
        
        outputFile << oneFile;
        
        outputFile.close();
        
    }
}

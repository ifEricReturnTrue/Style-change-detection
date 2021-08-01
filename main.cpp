//
//  main.cpp
//  featureCalculation
//
//  Created by Eric Zheng on 2021-07-28.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> sentenceLengths;

int main(int argc, const char * argv[]) {
    
    ifstream myFile;
    
    int fileNum = 1;
    
    for (fileNum = 1; fileNum < 11201; fileNum++){
        
        stringstream fileName;
        fileName << "sentence-problem-" << fileNum << ".txt";
        
        myFile.open(fileName.str());
        
        if (myFile.is_open()) {
                    
            while (!myFile.eof()) {
                
                stringstream lineSS;
                string tempStr;
                int strCount = 0;
                char line[10000];
                
                myFile.getline(line, 10000, '\n');
                
                if (line[0] == '\0') continue;
                
                lineSS << line;
                
                while (!lineSS.eof()){
                    lineSS >> tempStr;
                    if ((tempStr == "!") ||
                        (tempStr == "?") ||
                        (tempStr == ".") ||
                        (tempStr == ";") ||
                        (tempStr == ":") ||
                        (tempStr[0] == '\n')||
                        (tempStr[0] == '\0')||
                        (tempStr == " ") ||
                        (tempStr == "(") ||
                        (tempStr == ")") ||
                        (tempStr == "{") ||
                        (tempStr == "}") ||
                        (tempStr == "")){
                        continue;
                    }
                    strCount++;
                }
                
                if (strCount!=0) sentenceLengths.push_back(strCount);
                
            }
            
            myFile.clear();
                    
        }
        
        myFile.close();
    }
    
    ofstream outputFile("SentenceAnalysis.txt");
    string s;
    
    
    outputFile << "Total Number of Sentences: " << sentenceLengths.size() << endl;
    
    sort(sentenceLengths.begin(), sentenceLengths.end());
    
    outputFile << "Shortest Sentence Length is: " << sentenceLengths[0] << endl;
    outputFile << "Longest Sentence Length is: " <<sentenceLengths[sentenceLengths.size()-1] << endl;
    outputFile << "Mean Value of the Length: " <<sentenceLengths[int(sentenceLengths.size()/2)] << endl;
    
    double sum = 0;
    for (int i = 0; i < sentenceLengths.size(); i++){
        sum = sum + sentenceLengths[i];
    }
    
    outputFile << "Average Length: " << sum/sentenceLengths.size() << endl;
    
    int currentLength = sentenceLengths[0];
    int nextLength = sentenceLengths[1];
    int count = 1;
    int maxCount = 0, maxLen = 0;
    
    for (int i = 1; i < sentenceLengths.size()-1; i++){
        if (currentLength == nextLength){
            count++;
            currentLength = nextLength;
            nextLength = sentenceLengths[i+1];
        }else{
            outputFile << "Length " << currentLength << " has " << count << " counts." << endl;
            if (count > maxCount){
                maxCount = count;
                maxLen = currentLength;
            }
            count = 1;
            currentLength = nextLength;
            nextLength = sentenceLengths[i+1];
        }
    }
    
    if (sentenceLengths[sentenceLengths.size()-2] == sentenceLengths[sentenceLengths.size()-1]){
        count++;
        outputFile << "Length " << sentenceLengths[sentenceLengths.size()-2] << " has "
             << count << " counts." << endl;
        if (count > maxCount){
            maxCount = count;
            maxLen = currentLength;
        }
    }else{
        outputFile << "Length " << sentenceLengths[sentenceLengths.size()-2] << " has "
             << count << " counts." << endl;
        if (count > maxCount) {
            maxCount = count;
            maxLen = currentLength;
        }
        outputFile << "Length " << sentenceLengths[sentenceLengths.size()-1] << " has 1 counts." << endl;
    }
    
    outputFile << "The Length of " << maxLen << " has the most amount of samples: " << maxCount;
    outputFile.close();
    
    return 0;
    
}

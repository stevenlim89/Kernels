#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

typedef pair< vector<char>, int> Pair;

vector<int> vectorAdd(vector<int> v1, vector<int> v2){
    vector<int> sum(784, 0);
    for(int i = 0; i < 784; i++){
        sum[i] = v1[i] + v2[i];
    }
    return sum;
}

vector<int> vectorMul(vector<int> v1, int scalar){
    vector<int> mul(784, 0);
    for(int i = 0; i < 784; i++){
        mul[i] = v1[i] * scalar;
    }
    return mul;
}

int labelSet(int target, int currLabel){
    if(currLabel == target){
        return 1;
    }
    else{
        return -1;
    } 
}

vector< vector<char> > getSubstrings(vector<char> charVec, int length){
   vector< vector<char> > subStringMatrix;
   
   vector<char> buffer;

   for(int i = 0; i <= charVec.size() - length; i++){
        for(int j = 0; j < length; j++){
            buffer.push_back(charVec[i+j]);
        }
        if(find(subStringMatrix.begin(), subStringMatrix.end(), buffer) == subStringMatrix.end()){
            subStringMatrix.push_back(buffer);
        }
        buffer.clear();
   } 

   return subStringMatrix;
} 

int compareSubstrings(vector< vector<char> > v1, vector< vector<char> > v2){
    int count = 0;

    for(int i = 0; i < v1.size(); i++){
        if(find(v2.begin(), v2.end(), v1[i]) != v2.end()){
            count++;
        }
    }

    return count;
}

vector<int> perceptron(vector< pair< vector<char>, int> > matrix, int length){
    vector<int> changeTracker;
    int label = 0; 
    long long int w = 0;

    changeTracker.push_back(1);

    int counter = 0;

    vector< vector<char> > sub1;
    vector< vector<char> > sub2;

    for(int i = 1; i < matrix.size(); i++){
        sub1 = getSubstrings(matrix[i].first, length);
        for(int j = 0; j < matrix.size(); j++){
            if(changeTracker[j] == 1){
                label = labelSet(matrix[i].second, matrix[j].second);      
                sub2 = getSubstrings(matrix[j].first, length);
                counter = compareSubstrings(sub1, sub2);
                w = w + (label*counter);
            }
        }

        if(w <= 0){
            changeTracker.push_back(1);
        }
        else{
            changeTracker.push_back(0);
        }

        w = 0;
        sub2.clear();
        sub1.clear();       
    }
    
    return changeTracker;
}

double pError(vector< pair< vector<char>, int> > train, vector< pair< vector<char>, int> > test, vector<int> changeTracker, int length){
    int label = 0; 
    long long int w = 0;

    int counter = 0;
    double error = 0;

    vector< vector<char> > sub1;
    vector< vector<char> > sub2;

    for(int i = 0; i < test.size(); i++){
        sub1 = getSubstrings(test[i].first, length);
        for(int j = 0; j < changeTracker.size(); j++){
            if(changeTracker[j] == 1){
                label = labelSet(test[i].second, train[j].second);      
                sub2 = getSubstrings(train[j].first, length);
                counter = compareSubstrings(sub1, sub2);
                w = w + (label*counter);
            }
        }

        if(w <= 0){
            error++;
        }

        w = 0;
        sub2.clear();
        sub1.clear();       
    }
    
    return error/(double)test.size();
}

vector< pair< vector<char>, int> > fileToMatrix(string filename){
    char delimiter = ' ';

    // Variable to hold char number from file
    char line[1000];

    char label[2];
    // Variable to hold number that used to be a char
    int number;

    pair< vector<char>, int> p;

    vector< pair< vector<char>, int> > returnVector;

    vector<char> letters;

    ifstream trainfile; 
    trainfile.open(filename);

    //check to see if the file is opened:
    if (trainfile.is_open())
    {
        while ( trainfile.getline(line, 1000) )
        {
            for(int i = 0; i < 1000; i++){
                letters.push_back(line[i]);
                if(line[i] == ' '){
                    letters.pop_back();
                    if(line[i+2] == '-'){
                        number = -1;
                    }
                    else{
                        number = 1;
                    }
                    p.first = letters;
                    p.second = number;
                    returnVector.push_back(p);
                    break;
                }
            }

            letters.clear();
        }     
    }

    trainfile.close();

    return returnVector;
}

int main() {
    string trainingFile = "hw5train.txt";
    string testFile = "hw5test.txt";

    vector< pair< vector<char>, int> > trainingVector = fileToMatrix(trainingFile);
    vector< pair< vector<char>, int> > testVector = fileToMatrix(testFile);

    int size = trainingVector.size();
    vector<int> changeTracker = perceptron(trainingVector, 4);

    double value = pError(trainingVector, testVector, changeTracker, 4);
    cout<<value<<endl;
   
    return 0;
}
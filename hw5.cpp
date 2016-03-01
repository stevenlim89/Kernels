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

vector<int> perceptron(vector< vector<int> > matrix, int passes, int target){
    vector<int> w(784, 0);
    int dot_product = 0;
    int label = 0;

    for(int p = 0; p < passes; p++){
        for(int i = 0; i < matrix.size(); i++){
            label = labelSet(target, matrix[i][784]);
            dot_product = inner_product(w.begin(), w.end(), matrix[i].begin(), 0);

            if(dot_product*label <= 0){
                w = vectorAdd(w, vectorMul(matrix[i], label)); 
            }
        }
    }
    return w;
}

vector< pair< vector<char>, int> > fileToMatrix(string filename){
    char delimiter = ' ';

    // Variable to hold char number from file
    char line[1000];

    char label[2];
    // Variable to hold number that used to be a char
    int number;

    string s;

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
    cout<<"in main"<<endl;
    //vector< pair< vector<char>, int> > testVector = fileToMatrix(testFile);

    for(int i = 0; i < trainingVector.size(); i++){
        //cout<<trainingVector[i].first[trainingVector[i].first.size()-1]<<endl;
    }
   
    return 0;
}
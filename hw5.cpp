#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <sstream>
#include "node.cpp"
#include <iomanip>

vector< vector<double> > fileToMatrix(string filename){
    char delimiter = ' ';

    // feature vector
    vector<double> feature;

    // Matrix to hold all feature vecttors
    vector< vector<double> > featureMatrix;

    // Variable to hold char number from file
    char line[4];

    // Variable to hold number that used to be a char
    double number;

    // Counter to check when to put into featureMatrix
    int count = 0;

    ifstream trainfile; 
    trainfile.open(filename);

    //check to see if the file is opened:
    if (trainfile.is_open())
    {
        //while there are still lines in the
        //file, keep reading:
        while (! trainfile.eof() )
        {
            count++;

            // Get character from file and store in variable line
            trainfile.getline(line, 256, delimiter);

            // line is a character so convert to int
            number = atof(line);

            // add to feature vector
            feature.push_back(number);

            // If counter is 5, then feature vector has been filled and you can add it to matrix
            if(count == 5){
                featureMatrix.push_back(feature);

                // reset values
                count = 0;
                feature.clear();
            } 

        }     
    }
    trainfile.close();

    return featureMatrix;
}

int main() {
    string trainingFile = "hw5train.txt";
    string testFile = "hw5test.txt";

    vector< vector<double> > trainingMatrix = fileToMatrix(trainingFile);
    vector< vector<double> > testMatrix = fileToMatrix(testFile);
   
    return 0;
}
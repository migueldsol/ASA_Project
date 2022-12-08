#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

int getValue(){
    int lines;
    cin >> lines;
    return lines;

}

int **getLinValues(int lines, int **lineValues){
    for (int counter = 0;counter < lines; counter++){
        int value;
        cin >> value;
        lineValues[counter] = new int(value); 
    }
    return lineValues;
}

int main(){
    int lines = getValue();
    int collums = getValue();
    int **lineValues = new int*[lines]; 
    lineValues = getLinValues(lines, lineValues);
    
}

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getValue(){
    int lines;
    cin >> lines;
    return lines;

}

vector<int> getLineValues(int lines){
    vector<int> newVector;
    for (int counter = 0;counter < lines; counter++){
        int value;
        cin >> value;
        newVector.push_back(value);
    }
    return newVector;
}

int lastMaxIndex(vector<int> object,int size){
    auto max = max_element(object.begin(), object.end());
    for (int i = size-1; i >= 0; i--){
        if (object[i] == *max){
            return i;
        }
    }
    return -1;
}

int verifica_quadrado(vector<int> lineValues, int lines, int indexMaxValue){
    int count = 1;
    int temp = lineValues[indexMaxValue];
    for(int i = indexMaxValue - 1; i>= 0 && count < temp; i--){
        if (lineValues[i] < temp){
            break;
        }
        count ++;
    }
    return count;
}

vector <int> retira_quadrado(vector <int> lineValues, int lines, int quadrado, int indexMaxValue){
    if(quadrado == 1){
        lineValues[indexMaxValue]--;
    }
    else{
        for (int i = indexMaxValue; i >= indexMaxValue- quadrado + 1; i--){
            lineValues[i]-=quadrado;
        }
    }
    return lineValues;
}
int verifica_fim(vector <int> lineValues, int lines){
    int count = 0;
    for (int i = 0; i < lines; i++){
        if (lineValues[i] == 0){
            count++;
        }
        else{
            break;
        }
    }
    if (count == lines){
        return 1;
    }
    return 0;
}
/*
int calcula_combinacoes(vector <int> lineValues, int lines){
    auto max = max_element(lineValues.begin(), lineValues.end());
    return calcula_combinacoes(lineValues, lines, *max);
}
*/
int calcula_combinacoes(vector<int> lineValues, int lines, int indexMaxValue){
    int quadrado = verifica_quadrado(lineValues, lines, indexMaxValue);
    int sum = 0;
    for(int i = 1; i <= quadrado; i++){
        vector <int> newLineValues;
        newLineValues.assign(lineValues.begin(),lineValues.end());
        if (verifica_fim(newLineValues,lines) == 1){
            return 1;
        }
        else{
            newLineValues = retira_quadrado(newLineValues, lines,i, indexMaxValue);
            sum += calcula_combinacoes(newLineValues, lines, lastMaxIndex(newLineValues,lines));
        }
    }
    return sum;
}

int main(){
    int lines = getValue();
    int collums = getValue();
    vector<int> lineValues = getLineValues(lines);
    printf("%d, combinações = %d\n",collums, calcula_combinacoes(lineValues,lines,lastMaxIndex(lineValues,lines)));
    return 0;
}

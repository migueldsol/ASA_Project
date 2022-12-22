#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

map <vector<int> ,unsigned long int> hash_table;

int getValue(){
    int lines;
    cin >> lines;
    return lines;

}

vector<int> getLineValues(int lines,int collums){
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

unsigned long long calcula_combinacoes(vector<int> lineValues, int lines, int indexMaxValue){
    int quadrado = verifica_quadrado(lineValues, lines, indexMaxValue);
    unsigned long long sum = 0;
    vector <int> newLineValues;
    for(int i = 1; i <= quadrado; i++){
        newLineValues.assign(lineValues.begin(),lineValues.end());
        if (hash_table.count(lineValues)){
            return hash_table.at(lineValues);
        }
        else{
            newLineValues = retira_quadrado(newLineValues, lines,i, indexMaxValue);
            sum += calcula_combinacoes(newLineValues, lines, lastMaxIndex(newLineValues,lines));
        }
    }
    hash_table.insert({lineValues,sum});
    return sum;
}

unsigned long long gere_combinacoes(){
    int lines = getValue();
    int collums = getValue();
    unsigned long long sum = 0;
    vector<int> lineValues = getLineValues(lines,collums);
    vector<int> zero;
    for (int i = 0; i < lines; i++){
        zero.push_back(0);
    }
    hash_table.insert({zero,1});
    if (*max_element(lineValues.begin(),lineValues.end()) == 0){
        return sum;
    }
    else{
        sum = calcula_combinacoes(lineValues,lines,lastMaxIndex(lineValues,lines));
    }
    return sum;
}

int main(){
    printf("%llu\n",gere_combinacoes());
    return 0;
}

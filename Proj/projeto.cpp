#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

unordered_map<string ,unsigned long int> hash_table;

int getValue(){
    int lines;
    cin >> lines;
    return lines;

}


string hashFunction(vector<int> vec) {
    string hash;
    
    int size = vec.size();
    for (int i = size-1; i >= 0; i--){
        hash += to_string(vec[i]);
    }
    return hash;
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

unsigned long int calcula_combinacoes(vector<int> lineValues, int lines, int indexMaxValue){
    int quadrado = verifica_quadrado(lineValues, lines, indexMaxValue);
    unsigned long int sum = 0;
    string hash_value = hashFunction(lineValues);
    vector <int> newLineValues;
    for(int i = 1; i <= quadrado; i++){
        newLineValues.assign(lineValues.begin(),lineValues.end());
        if (hash_table.count(hash_value)){
            return hash_table.at(hash_value);
        }
        else{
            newLineValues = retira_quadrado(newLineValues, lines,i, indexMaxValue);
            sum += calcula_combinacoes(newLineValues, lines, lastMaxIndex(newLineValues,lines));
        }
    }
    hash_table.insert({hash_value,sum});
    return sum;
}

unsigned long int gere_combinacoes(){
    int lines = getValue();
    int collums = getValue();
    unsigned long int sum = 0;
    vector<int> lineValues = getLineValues(lines,collums);
    string zero;
    for (int i = 0; i < lines; i++){
        zero += "0";
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
    printf("%ld\n",gere_combinacoes());
    return 0;
}

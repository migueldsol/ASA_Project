#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

unordered_map<unsigned long int,unsigned long int> hash_table;

int getValue(){
    int lines;
    cin >> lines;
    return lines;

}

// Define a function that takes in a vector of integers as input
// and returns an integer as the hash value
int hashFunction(vector<int> vec) {
    // Initialize the hash value to be zero
    unsigned long int hash = 0;
    
    // Iterate over the vector and add each element to the hash value
    // multiplied by a prime number
    int size = vec.size();
    for (int i = size-1; i >= 0; i--){
        hash = hash * 10 + vec[i];
    }
    return hash;
}

vector<int> getLineValues(int lines,int collums){
    vector<int> newVector;
    for (int counter = 0;counter < lines; counter++){
        int value;
        cin >> value;
        if (value < collums){
            newVector.push_back(value);
        }
        else {
            printf("error: value bigger than collums, exiting\n");
            exit(1);
        }
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
int verifica_fim(vector <int> lineValues, int lines, unordered_map<int,int> hash_table,int hash_value){
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
    if (hash_table.count(hash_value) > 0){  
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
unsigned long int calcula_combinacoes(vector<int> lineValues, int lines, int indexMaxValue){
    int quadrado = verifica_quadrado(lineValues, lines, indexMaxValue);
    unsigned long int sum = 0;
    unsigned long int hash_value = hashFunction(lineValues);
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

int main(){
    int lines = getValue();
    int collums = getValue();
    vector<int> lineValues = getLineValues(lines,collums);
    hash_table.insert({0,1});
    printf("%ld\n",calcula_combinacoes(lineValues,lines,lastMaxIndex(lineValues,lines)));
    return 0;
}

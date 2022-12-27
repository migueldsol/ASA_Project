
#include <bits/stdc++.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

unordered_map<string ,unsigned long int> hash_table;

int getValue(){
    int lines;
    cin >> lines;
    return lines;

}

// Define a function that takes in a vector of integers as input
// and returns an integer as the hash value
string hashFunction(vector<int> vec) {
    // Initialize the hash value to be zero
    string hash;
    
    // Iterate over the vector and add each element to the hash value
    // multiplied by a prime number
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
  
// A sample function whose time taken to
// be measured
  
int main()
{
    /* Time function returns the time since the 
        Epoch(jan 1 1970). Returned time is in seconds. */
    time_t start, end;
  
    /* You can call it like this : start = time(NULL);
     in both the way start contain total time in seconds 
     since the Epoch. */
    time(&start);
  
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
  
    printf("%ld\n",gere_combinacoes());
  
    // Recording end time.
    time(&end);
  
    // Calculating total time taken by the program.
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}
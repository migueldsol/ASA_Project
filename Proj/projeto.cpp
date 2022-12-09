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

int verifica_quadrado(vector<int> lineValues, int lines){
    int count = 1;
    int temp = lineValues[lines - 1];
    for(int i = lines - 2; i>= 0; i--){
        if (lineValues[i] < temp){
            break;
        }
        count ++;
    }
    return count;
}

vector <int> retira_quadrado(vector <int> lineValues, int lines, int quadrado){
    if(quadrado == 1){
        
        auto max = max_element(lineValues.begin(), lineValues.end());

        for (int i = lines-1; i >= 0; i--){
            if (lineValues[i] == *max){
                lineValues[i] -= 1;
                break;
            }
        }
    }
    else{
        for (int i = lines-1; i >= lines - quadrado; i--){
            lineValues[i]-=quadrado;
        }
    }
    return lineValues;
}
int verifica_fim(vector <int> lineValues, int lines){
    if (lineValues[0] == 0){
        return 1;
    }
    else{
        return 0;
    }
}
int calcula_combinacoes(vector<int> lineValues, int lines){
    int quadrado = verifica_quadrado(lineValues, lines);
    int sum = 0;
    for(int i = 1; i <= quadrado; i++){
        vector <int> newLineValues;
        newLineValues.assign(lineValues.begin(),lineValues.end());
        if (verifica_fim(newLineValues,lines) == 1){
            return 1;
        }
        else{
            newLineValues = retira_quadrado(newLineValues, lines,i);
            sum += calcula_combinacoes(newLineValues, lines);
        }
    }
    return quadrado;
}

int main(){
    int lines = getValue();
    int collums = getValue();
    vector<int> lineValues = getLineValues(lines);
    printf("%d : %d, combinações = %d",verifica_quadrado(lineValues,lines),collums, calcula_combinacoes(lineValues,lines));
    return 0;
}

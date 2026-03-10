#include <iostream>
using namespace std; 

int soma(int x){
    int s = 0;
    for (int i = 1; i < x+1; i++){
        s = s + i;
    }
    return s;
}

int mult (int x, int y){
    int m = 0;
    for (int i = 0; i < y; i++){
        m = m + x;
    }
    return m;
}

int fact (int x){
    int f = 1;
    for (int i = 1; i < x+1; i++){
        f = f * i;
    }
    return f;
}

int main(){
    int num_sum;
    int x,y;
    int num_fact;

    cout << "Digite o número que você quer que seja somado iterativamente: ";
    cin >> num_sum;
    cout << "A soma iterativa é: " << soma(num_sum) << "\n";

    cout << "Digite os números que você quer realizar a multiplicação iterativa: ";
    cin >> x >> y;
    cout << "A multiplicação iterativa é: " << mult(x,y) << "\n";

    cout << "Digite o número para aplicar a operação fatorial iterativa: ";
    cin >> num_fact;
    cout << "O fatorial iterativo é: " << fact(num_fact) << "\n";

    return 0;
}
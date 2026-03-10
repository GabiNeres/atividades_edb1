#include <iostream>
using namespace std; 

int soma(int x, int acc){
    if (x == 0)
        return acc;
    else
        return (soma((x-1), acc + x)); 
}

int mult (int x, int y, int acc){
    if (y == 0)
        return acc;
    else
        return (mult(x,y-1,acc+x));
}

int fact (int x, int acc){
    if (x == 0)
        return acc;
    else
        return (fact(x-1, acc*x));
}

int main(){
    int num_sum;
    int x,y;
    int num_fact;

    cout << "Digite o número que você quer que seja somado recursivamente: ";
    cin >> num_sum;
    cout << "A soma recursiva é: " << soma(num_sum,0) << "\n";

    cout << "Digite os números que você quer realizar a multiplicação recursiva: ";
    cin >> x >> y;
    cout << "A multiplicação recursiva é: " << mult(x,y,0) << "\n";

    cout << "Digite o número para aplicar a operação fatorial recursiva: ";
    cin >> num_fact;
    cout << "O fatorial recursivo é: " << fact(num_fact,1) << "\n";

    return 0;
}


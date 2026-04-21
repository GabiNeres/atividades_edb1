#include <vector>
#include <algorithm>

#include "algorithms.hpp" 

// Implementação da Busca Sequencial
int buscaSequencial(const std::vector<int>& arr, int alvo) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == alvo) {
            return i; 
        }
    }
    return -1; 
}

// Implementação da Busca Binária
int buscaBinaria(const std::vector<int>& arr, int alvo){
    int inicio = 0, fim = arr.size() - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (arr[meio] == alvo) {
            return meio; 
        } else if (arr[meio] < alvo) { 
            inicio = meio + 1; 
        } else {
            fim = meio - 1; 
        }  
    }
    return -1;
}

// Implementação do Selection Sort
void selectionSort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++){
        auto min_i = std::min_element(arr.begin() + i, arr.end());
        std::iter_swap (arr.begin()+i, min_i);
    }
}

// Função auxiliar do Quick Sort
int partition(std::vector<int>& arr, int inicio, int fim) {
    int pivo = arr[fim]; 
    int menor = inicio; 

    for (int i = inicio; i < fim; i++) {
        if (arr[i] < pivo) {
            std::swap(arr[i], arr[menor]);
            menor++;
        }
    }

    std::swap(arr[menor], arr[fim]);
    return menor;
}

// Implementação do Quick Sort
void quickSort(std::vector<int>& arr, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = partition(arr, inicio, fim);

        quickSort(arr, inicio, pivo - 1);
        quickSort(arr, pivo + 1, fim);
    }
}
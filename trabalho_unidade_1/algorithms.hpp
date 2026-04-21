#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>

// Declaração das funções de busca
int buscaSequencial(const std::vector<int>& arr, int alvo);
int buscaBinaria(const std::vector<int>& arr, int alvo);

// Declaração das funções de ordenação
void selectionSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int inicio, int fim);

#endif
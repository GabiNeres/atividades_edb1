#include <vector>
#include <algorithm>

#include "algorithms.hpp" 

// Implementação da Busca Sequencial
/**
 * @brief Realiza uma busca sequencial em um vetor de inteiros.
 *
 * Esta função percorre o vetor linearmente desde o primeiro elemento, 
 * comparando cada posição com o valor alvo.
 *
 * @param arr Vetor de inteiros onde a busca será realizada.
 * @param alvo O valor inteiro específico que deseja-se encontrar.
 * @return Retorna o índice numérico da primeira ocorrência do alvo no vetor. 
 * Caso o alvo não seja encontrado, retorna -1.
 */
int buscaSequencial(const std::vector<int>& arr, int alvo) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == alvo) {
            return i; 
        }
    }
    return -1; 
}

// Implementação da Busca Binária
/**
 * @brief Realiza uma busca binária em um vetor de inteiros previamente ordenado.
 *
 * A cada iteração, o espaço de busca é dividido pela metade, comparando o elemento 
 * alvo com o valor central da sublista.
 *
 * @param arr Vetor de inteiros (necessariamente ordenado) onde a busca será realizada.
 * @param alvo O valor inteiro específico que deseja-se encontrar.
 * @return Retorna o índice numérico da ocorrência do alvo no vetor. 
 * Caso o alvo não seja encontrado, retorna -1.
 */
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
/**
 * @brief Ordena um vetor de inteiros utilizando o algoritmo Selection Sort.
 *
 * Esta função percorre o vetor e, a cada iteração, localiza o menor elemento 
 * na porção ainda não ordenada.
 *
 * @param arr Vetor de inteiros a ser ordenado.
 */
void selectionSort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++){
        auto min_i = std::min_element(arr.begin() + i, arr.end());
        std::iter_swap (arr.begin()+i, min_i);
    }
}

// Função auxiliar do Quick Sort para partições
/**
 * @brief Particiona um subvetor para o algoritmo Quick Sort.
 *
 * Esta função auxiliar escolhe o último elemento do intervalo como pivô e 
 * reorganiza os dados. Ela utiliza dois ponteiros para garantir que 
 * todos os elementos menores que o pivô sejam movidos para a sua esquerda. 
 * Ao final do laço, o pivô é posicionado exatamente no seu local definitivo. 
 *
 * @param arr Vetor de inteiros onde as trocas ocorrerão.
 * @param inicio Índice que demarca o começo do subvetor a ser particionado.
 * @param fim Índice que demarca o final do subvetor. O elemento arr[fim] é 
 * utilizado estaticamente como o pivô da operação.
 * @return Retorna o índice inteiro da posição final e definitiva do pivô. 
 * Este índice será utilizado pelo Quick Sort para dividir o vetor nas próximas 
 * chamadas recursivas.
 */
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
/**
 * @brief Função principal e recursiva do algoritmo de ordenação Quick Sort.
 *
 * Esta função implementa a estratégia de "Divisão e Conquista". Ela utiliza a 
 * função auxiliar de particionamento para posicionar um elemento pivô em seu 
 * local definitivo e, em seguida, chama a si mesma recursivamente para ordenar 
 * o subvetor à esquerda do pivô e o subvetor à direita do pivô. 
 *
 * @param arr Vetor de inteiros onde a ordenação ocorre.
 * @param inicio Índice numérico que define o limite inferior do subvetor atual a ser ordenado.
 * @param fim Índice numérico que define o limite superior do subvetor atual a ser ordenado.
 */
void quickSort(std::vector<int>& arr, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = partition(arr, inicio, fim);

        quickSort(arr, inicio, pivo - 1);
        quickSort(arr, pivo + 1, fim);
    }
}
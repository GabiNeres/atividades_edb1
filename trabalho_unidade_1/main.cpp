#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <functional>
#include <string>
#include "algorithms.hpp"

std::vector<int> gerarVetor(int n) {
    std::vector<int> arr(n);
    std::random_device random; 
    std::mt19937 gen(random()); 

    std::uniform_int_distribution<> distrib(1, n); 

    for (int i = 0; i < n; ++i) {
        arr[i] = distrib(gen);
    }
    return arr;
}

void testarOrdenacao(const std::string& file, const std::vector<int>& tam, int rep, std::function<void(std::vector<int>&)> algoritmo) {
    std::ofstream arquivo(file);
    arquivo << "n,tempo_ms\n";
    
    std::cout << "Iniciando testes de ordenação:" << std::endl;

    for (int n : tam) {
        double tempo = 0.0;

        for (int r = 0; r < rep; ++r) {
            std::vector<int> dados = gerarVetor(n);

            auto temp_i = std::chrono::high_resolution_clock::now();

            algoritmo(dados);

            auto temp_f = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duracao = temp_f - temp_i;
            tempo += duracao.count();
        }

        double tempo_medio = tempo / rep;
        arquivo << n << "," << tempo_medio << "\n";
        
        std::cout << "Vetor com " << n << " elementos concluído. Tempo médio: " << tempo_medio << " ms\n";
    }

    arquivo.close();
    std::cout << "Experimento empírico finalizado. Dados salvos em " << file << std::endl;
}


void testarBusca(const std::string& file, 
                 const std::vector<int>& tam, 
                 int rep, 
                 bool ordenar, 
                 std::function<int(const std::vector<int>&, int)> algoritmo) {
    
    std::ofstream arquivo(file);
    arquivo << "n,tempo_ms\n"; 

    std::cout << "Iniciando testes de busca: " << std::endl;

    for (int n : tam) {
        double tempo = 0.0;

        for (int r = 0; r < rep; ++r) {
            std::vector<int> dados = gerarVetor(n);
            int alvo = -1; 

            if (ordenar) {
                std::sort(dados.begin(), dados.end()); 
            }

            auto temp_i = std::chrono::high_resolution_clock::now();

            for(int k = 0; k < 10000; k++) {
                algoritmo(dados, alvo); 
            }

            auto temp_f = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duracao = temp_f - temp_i;
            tempo += duracao.count();
        }

        double tempo_medio = tempo / rep;
        arquivo << n << "," << tempo_medio << "\n";
        
        std::cout << "Vetor com " << n << " elementos concluído. Tempo médio (10k buscas): " << tempo_medio << " ms\n";
    }

    arquivo.close();
    std::cout << "Experimento empírico finalizado. Dados salvos em " << file << std::endl;
}


int main() {
    std::vector<int> tam= {10, 50, 100, 500, 1000, 5000, 10000, 25000}; 
    
    int repeat = 20; 

    std::cout << "Testando selection sort...\n";
    testarOrdenacao("selectionsort.csv", tam, repeat, 
        [](std::vector<int>& arr) {
            selectionSort(arr);
        }
    );

    std::cout << "Testando quick sort...\n";
    testarOrdenacao("quicksort.csv", tam, repeat, 
        [](std::vector<int>& arr) {
            quickSort(arr, 0, arr.size() - 1);
        }
    );

    std::cout << "Testando busca sequencial...\n";
    testarBusca("buscaseq.csv", tam, repeat, false, buscaSequencial);

    std::cout << "Testando busca binária...\n";
    testarBusca("buscabin.csv", tam, repeat, true, buscaBinaria);
    
    return 0;
}
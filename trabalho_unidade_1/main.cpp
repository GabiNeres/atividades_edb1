#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <functional>
#include <string>
#include "algorithms.hpp"

/**
 * @brief Gera um vetor de inteiros com valores pseudoaleatórios.
 *
 * Esta função auxiliar é a base para os testes empíricos. Os elementos gerados seguem uma distribuição 
 * perfeitamente uniforme no intervalo fechado de [1, n].
 *
 * @param n O número de elementos que o vetor terá. Este valor também atua 
 * como o valor máximo dos números aleatórios gerados.
 * @return Retorna um vetor de tamanho 'n' preenchido com dados 
 * pseudoaleatórios.
 */
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

/**
 * @brief Realiza a coleta de dados empíricos em algoritmos de ordenação.
 *
 * Esta função executa testes para medir o tempo de execução de um algoritmo de ordenação 
 * sob diferentes tamanhos de entrada. Os resultados são exportados em formato .csv (n, tempo_ms)
 * para facilitar a análise.
 *
 * @param file String contendo o caminho do arquivo .csv de saída onde os dados coletados serão salvos.
 * @param tam Vetor de inteiros contendo tamanhos de n.
 * @param rep Número de repetições do experimento para um mesmo tamanho n. 
 * É utilizado para calcular uma média aritmética de tempo, diluindo variações 
 * esperadas do hardware/software.
 * @param algoritmo Objeto iterável com o algoritmo de ordenação a ser testado.
 */
void testarOrdenacao(const std::string& file, const std::vector<int>& tam, int rep, std::function<void(std::vector<int>&)> algoritmo) {
    
    std::ofstream arquivo(file);
    arquivo << "n,tempo_ms\n";
    
    std::cout << "Iniciando testes de ordenação:" << std::endl;

    for (int n : tam) {
        double tempo = 0.0;

        for (int r = 0; r < rep; ++r) {
            std::vector<int> dados = gerarVetor(n); //Gerar vetor aleatório

            auto temp_i = std::chrono::high_resolution_clock::now(); //Início da contagem do tempo de execução

            algoritmo(dados); 

            auto temp_f = std::chrono::high_resolution_clock::now(); //Final da contagem do tempo de execução

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

/**
 * @brief Realiza a coleta de dados empíricos em algoritmos de busca.
 *
 * Força o pior caso para o algoritmo ao buscar o valor -1 e amplifica o tempo 
 * realizando 10.000 buscas por repetição.
 *
 * @param file String contendo o caminho do arquivo .csv de saída onde os dados coletados serão salvos.
 * @param tam Vetor de inteiros contendo tamanhos de n.
 * @param rep Número de repetições do experimento para um mesmo tamanho n. 
 * É utilizado para calcular uma média aritmética de tempo, diluindo variações 
 * esperadas do hardware/software.
 * @param ordenar Flag booleana de verificação. Se 'true', ordena os 
 * dados antes de iniciar o cronômetro (requisito para a Busca Binária). 
 * Se 'false', os dados permanecem como estão.
 * @param algoritmo Objeto iterável com o algoritmo de busca a ser testado.
 */
void testarBusca(const std::string& file, const std::vector<int>& tam, int rep, bool ordenar, std::function<int(const std::vector<int>&, int)> algoritmo) {
    
    std::ofstream arquivo(file);
    arquivo << "n,tempo_ms\n"; 

    std::cout << "Iniciando testes de busca: " << std::endl;

    for (int n : tam) {
        double tempo = 0.0;

        for (int r = 0; r < rep; ++r) {
            std::vector<int> dados = gerarVetor(n);
            int alvo = -1; //Alvo para pior caso

            if (ordenar) {
                std::sort(dados.begin(), dados.end()); //Ordernar para a busca binária
            }

            auto temp_i = std::chrono::high_resolution_clock::now(); //Início da contagem do tempo de execução

            for(int k = 0; k < 10000; k++) {    //Repetição de 10000 para que o tempo apareça mais
                algoritmo(dados, alvo); 
            }

            auto temp_f = std::chrono::high_resolution_clock::now(); //Final da contagem do tempo de execução

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
    std::vector<int> tam= {10, 50, 100, 500, 1000, 5000, 10000, 50000}; //Tamanhos das entradas
    
    int repeat = 20; //Repetições para obter o valor médio do tempo de execução

    std::cout << "Testando selection sort...\n";
    testarOrdenacao("graficos/selectionsort.csv", tam, repeat, 
        [](std::vector<int>& arr) {
            selectionSort(arr);
        }
    );

    std::cout << "Testando quick sort...\n";
    testarOrdenacao("graficos/quicksort.csv", tam, repeat, 
        [](std::vector<int>& arr) {
            quickSort(arr, 0, arr.size() - 1);
        }
    );

    std::cout << "Testando busca sequencial...\n";
    testarBusca("graficos/buscaseq.csv", tam, repeat, false, buscaSequencial);

    std::cout << "Testando busca binária...\n";
    testarBusca("graficos/buscabin.csv", tam, repeat, true, buscaBinaria);
    
    return 0;
}
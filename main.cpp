// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094

#include <iostream>
#include <string>

#include "leitura.cpp"
#include "solucao.cpp"
#include "algoritmo.cpp"

using namespace std;

// O progama espera que o nome da instancia seja passada por linha de comando

int main(int argc, char *argv[]){
    
    string caminho = "instances/" + string(argv[1]);
    
    Instancia instancia = LerArquivo(caminho);

    Solucao solucao = AlgoritmoProposto(instancia);

    cout << "Solucao: (" << solucao.ValorSolucao().first << ", " << solucao.ValorSolucao().second << ")" << endl;

    return 0;
}
// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094

#include <iostream>
#include <string>

#include "leitura.cpp"
#include "solucao.cpp"

using namespace std;

// O progama espera que o nome da instancia seja passada por linha de comando

int main(int argc, char *argv[]){
    //string caminho = "instances/" + string(argv[1]);
    
    // Chamada e criacao de uma instancia exemplo
    string caminho = "instances/exemplo.txt";
    Instancia instancia = LerArquivo(caminho);
    
    // Criacao de uma solucao viavel para a instancia criada
    Solucao solucao1(3, &instancia);
    solucao1.AlocarPedido(0, make_pair(1, 2)); // veiculo 0 alocado ao pedido (1, 2)
    solucao1.AlocarPedido(1, make_pair(3, 4)); // veiculo 1 alocado ao pedido (3, 4)
    solucao1.AlocarPedido(2, make_pair(5, 6)); // veiculo 2 alocado ao pedido (5, 6)

    if(solucao1.isViavel()){
        cout << "Solucao Viavel" << endl;
        cout << "Z = (" << solucao1.ValorSolucao().first << ", " << solucao1.ValorSolucao().second << ")" << endl;
    }else{
        cout << "Solucao Inviavel" << endl;
    }

    // Criacao de uma solucao inviavel para a instancia criada
    Solucao solucao2(2, &instancia);
    solucao2.AlocarPedido(0, make_pair(1, 2)); // veiculo 0 alocado ao pedido (1, 2)
    solucao2.AlocarPedido(0, make_pair(3, 4)); // veiculo 0 alocado ao pedido (3, 4)
    solucao2.AlocarPedido(1, make_pair(5, 6)); // veiculo 1 alocado ao pedido (5, 6)

    if(solucao2.isViavel()){
        cout << "Solucao Viavel" << endl;
        cout << "Z = (" << solucao2.ValorSolucao().first << ", " << solucao2.ValorSolucao().second << ")" << endl;
    }else{
        cout << "Solucao Inviavel" << endl;
    }
}
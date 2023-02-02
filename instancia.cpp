// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094

#include <string>
#include "grafo.cpp"

using namespace std;

class Instancia{

private:
    
    string nome;
    Grafo * g; // grafo

    int H; // horizonte de roterizacao
    vector< pair<int, int> > pedidos;
    double capacidade; // capacidade dos veiculos


public:    
    Instancia(string nome, Grafo * g, int H, double capacidade){
        this->nome = nome;
        this->g = g;
        this->H = H;
        this->capacidade = capacidade;
    }

    string getNome(){
        return this->nome;
    }

    int getH(){
        return this->H;
    }

    void inserirPedido(int u, int v){
        this->pedidos.push_back(make_pair(u, v));
    }

    void setPedidos(vector< pair<int, int> > pedidos){
        this->pedidos = pedidos;
    }

    vector< pair<int, int> > getPedidos(){
        return this->pedidos;
    }

    Grafo * getGrafo(){
        return this->g;
    }

    double getCapacidade(){
        return this->capacidade;
    }

};
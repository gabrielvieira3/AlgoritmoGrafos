// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094

#include <vector>
#include <map>
#include "vertice.cpp"

using namespace std;

class Grafo{

private:
    vector<Vertice> vertices; // Conjunto de vértices
    
    vector<int> * ListaAdjacencia; // Lista de adjacencia

    map < pair<int, int>, double> custo; // Associa uma arersta (i, j) a um custo c_{ij}
    map < pair<int, int>, double> tempo; // Associa uma arersta (i, j) a um tempo t_{ij}

public:

    Grafo(vector<Vertice> vertices){
        this->vertices = vertices;
        ListaAdjacencia = new vector<int> [(int) vertices.size()];
    }

    void inserirAresta(int u, int v, double custo, double tempo){
        this->ListaAdjacencia[u].push_back(v);
        this->custo[make_pair(u, v)] = custo;
        this->tempo[make_pair(u, v)] = tempo;
    }

    bool verificaAresta(int u, int v){
        for (int i = 0; i < this->ListaAdjacencia[u].size(); ++i){
            if(this->ListaAdjacencia[u][i] == v){
                return true;
            }
        }
        return false;
    }

    Vertice getVertice(int u){
        return this->vertices[u];
    }

    double getCusto(int u, int v){
        return this->custo[make_pair(u, v)];
    }

    double getTempo(int u, int v){
        return this->tempo[make_pair(u, v)];
    }

    int getN(){
        return (int) vertices.size();
    }

};
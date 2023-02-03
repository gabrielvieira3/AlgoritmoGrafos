// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094

#include <vector>
#include <map>

using namespace std;

#define DEPOSITO        0
#define PONTO_COLETA    1
#define PONTO_ENTREGA   2


class Vertice{

private:
    int id;
    int tipo; // Se o vertice eh o deposito, se eh ponto de entrega ou se eh ponto de coleta
    
    // Localizacao
    double latitude;
    double longitude;

    // demanda
    double demanda;

    // Janela de tempo
    double a;
    double b;

    // Duracao servico    
    double duracao_servico;

public:
    Vertice(int id, double latitude, double longitude, double demanda, double a, double b, double duracao_servico){
        this->id = id;
        this->latitude = latitude;
        this->longitude = longitude;
        this->demanda = demanda;

        if(demanda > 0){
            this->tipo = PONTO_ENTREGA;
        }else if(demanda < 0){
            this->tipo = PONTO_COLETA;
        }else{
            this->tipo = DEPOSITO;
        }

        this->a = a;
        this->b = b;
        this->duracao_servico = duracao_servico;
    }

    int getId(){
        return this->id;
    }

    int getTipo(){
        return this->tipo;
    }
    
    double getLatitude(){
        return this->latitude;
    }

    double getLongitude(){
        return this->longitude;
    }

    double getDemanda(){
        return this->demanda;
    }

    pair< double, double > getJanelaTempo(){
        return make_pair(this->a, this->b);
    }

    double getDuracaoServico(){
        return this->duracao_servico;
    }

};

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

};
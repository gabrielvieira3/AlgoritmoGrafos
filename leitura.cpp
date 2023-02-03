// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094

#include <iostream>
#include <fstream>
#include "instancia.cpp"

using namespace std;

// Realiza a leitura da instancia dado o caminho que a mesma se encontra
Instancia LerArquivo(string caminho){
    Instancia * instancia;

    vector<Vertice> vertices;
    vector< pair<int, int> > pedidos;

    Grafo * g; 
    int H, n;
    string nome, dados;
    double capacidade;

    string read1;
    
    size_t operator_position;
    ifstream file1(caminho.c_str());

    getline (file1, read1);
    operator_position = read1.find_first_of(": ");
    nome = read1.substr(operator_position + 2);
    
    getline (file1, read1);
    getline (file1, read1);
    getline (file1, read1);
    
    getline (file1, read1);
    operator_position = read1.find_first_of(": ");
    n = stoi(read1.substr(operator_position + 2));

    getline (file1, read1);
    getline (file1, read1);

    getline (file1, read1);
    operator_position = read1.find_first_of(": ");
    H = stoi(read1.substr(operator_position + 2));

    getline (file1, read1);
    
    getline (file1, read1);
    operator_position = read1.find_first_of(": ");
    capacidade = stod(read1.substr(operator_position + 2));    

    getline (file1, read1);

    int id, u, v;
    double latitude, longitude, demanda, duracao_servico, a, b;

    for (int i = 0; i < n; ++i){
        file1 >> id >> latitude >> longitude >> demanda >> a >> b >> duracao_servico >> u >> v;
        Vertice aux(id, latitude, longitude, demanda, a, b, duracao_servico);
        vertices.push_back(aux);
        if(i > 0){
            if(u == 0){
                pedidos.push_back(make_pair(v, i));
            }else{
                pedidos.push_back(make_pair(i, u));
            }
        }
    }

    getline (file1, read1);
    getline (file1, read1);

    g = new Grafo(vertices);

    double tempo;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            file1 >> tempo;
            g->inserirAresta(i, j, tempo, tempo); // tempo proporcional ao custo
        }
    }    

    file1.close();

    instancia = new Instancia(nome, g, H, capacidade);
    instancia->setPedidos(pedidos);

    return *instancia;
}
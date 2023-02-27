// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define INF         10000000
#define MAX_N       5000
#define ITER_MAX    100

double randValorDouble(int linf, int lsup){
    #ifdef __linux__
            int inteiro = (linf + lrand48() % (lsup - linf));//Aqui quando for executar no linux.
            return (inteiro + drand48());
    #elif _WIN32
            int inteiro = (linf + rand() % (lsup - linf));//Aqui no windows
            return (inteiro + rand());
    #else
            #error "OS not supported!"
        #endif
}

/*
Algoritmo de Floyd Warshall, onde termina-se o tamanho do menor entre todos os pares de vertices
*/

double distancia[MAX_N][MAX_N];

void Floyd_Warshall(Grafo g){

    for(int u = 0; u < g.getN(); u++){
        for(int v = 0; v < g.getN(); v++){
            distancia[u][v] = INF;
        }    
    }

    for(int u = 0; u < g.getN(); u++){
        for(int v = 0; v < g.getN(); v++){
            if(g.verificaAresta(u, v)){
                distancia[u][v] = g.getTempo(u, v);
            }
        }    
    }

    for(int u = 0; u < g.getN(); u++){
        distancia[u][u] = 0;    
    }

    for (int k = 0; k < g.getN(); k++){
        for (int i = 0; i < g.getN(); i++){
            for (int j = 0; j < g.getN(); j++){
                if(distancia[i][j] > distancia[i][k] + distancia[k][j]){
                    distancia[i][j] = distancia[i][k] + distancia[k][j];
                }
            }
        }
    }

}


Solucao AlgoritmoProposto(Instancia instancia){
    
    // Armazena os pedidos em um vetor juntamente com abertura da janela de tempo da coleta e com o fechamento de janela de tempo da entrega

    vector< pair<int, int> > pedidos = instancia.getPedidos();

    vector< pair< pair<int, int>, pair<int, int> > > janela_tempo_pedidos;
    
    for (int i = 0; i < (int) pedidos.size(); ++i){
        janela_tempo_pedidos.push_back(make_pair(make_pair(instancia.getGrafo()->getVertice(pedidos[i].first).getJanelaTempo().first, instancia.getGrafo()->getVertice(pedidos[i].second).getJanelaTempo().second), pedidos[i]));
    }

    // Ordena considerando a janela de tempo

    sort(janela_tempo_pedidos.begin(), janela_tempo_pedidos.end());

    int numVeiculos = 1;  // Armazena numero de veiculos utilizado 

    Solucao melhorSolucao(INF, &instancia); // Armazena a melhor solucao encontrada

    bool SolViavel = false; // Armazena se foi possivel ou nao encontrar uma solucao viavel
    int iter = 0; // Numero de iteracoes


    while(iter < ITER_MAX){
        
        // Inicia uma nova solucao
        Solucao solucao(numVeiculos, &instancia);

        // Dados necessarios para os veiculos
        int p[numVeiculos]; // localizacao atual
        double t[numVeiculos]; // tempo da ultima entrega

        for (int i = 0; i < numVeiculos; ++i){
            p[i] = 0; // Deposito
            t[i] = 0; // Tempo inicial 0
        }

        for (int i = 0; i < (int) janela_tempo_pedidos.size(); ++i){
            int u = janela_tempo_pedidos[i].second.first; // coleta
            int v = janela_tempo_pedidos[i].second.second; // entrega
            vector<int> G;
            for (int j = 0; j < numVeiculos; ++j){
                // Verifica se o veiculo j pode atender o pedido i
                if((instancia.getGrafo()->getVertice(u).getDemanda() <= instancia.getCapacidade()) &&  (t[j] + instancia.getGrafo()->getTempo(p[j], u) <= instancia.getGrafo()->getVertice(u).getJanelaTempo().second) && (t[j] + instancia.getGrafo()->getTempo(p[j], u) + instancia.getGrafo()->getVertice(u).getDuracaoServico() + instancia.getGrafo()->getTempo(u, v) <= instancia.getGrafo()->getVertice(v).getJanelaTempo().second) && (t[j] + instancia.getGrafo()->getTempo(p[j], u) + instancia.getGrafo()->getVertice(u).getDuracaoServico() + instancia.getGrafo()->getTempo(u, v) + instancia.getGrafo()->getVertice(v).getDuracaoServico() + instancia.getGrafo()->getTempo(v, 0) <= instancia.getH())){
                    G.push_back(j);
                }
            }

            if((int)G.size() == 0){ // Caso nao tenha nenhum veiculo que possa atender
                break;
            }else{

                if(iter == 0){ // Opta por escolha gulosas na primeira iteracao
                    int g = G[0];
                    double custo = INF;                    
                    for (int j = 0; j < (int)G.size(); j++){
                        if(instancia.getGrafo()->getCusto(G[j], u) + instancia.getGrafo()->getCusto(u, v) < custo){
                            custo = instancia.getGrafo()->getCusto(G[j], u) + instancia.getGrafo()->getCusto(u, v);
                            g = G[j];
                        }
                    }

                    t[g] += instancia.getGrafo()->getTempo(p[g], u); 
                    t[g] = max(t[g], instancia.getGrafo()->getVertice(u).getJanelaTempo().first);
                    t[g] += instancia.getGrafo()->getVertice(u).getDuracaoServico() + instancia.getGrafo()->getTempo(u, v); 
                    t[g] = max(t[g], instancia.getGrafo()->getVertice(v).getJanelaTempo().first);
                    t[g] += instancia.getGrafo()->getVertice(v).getDuracaoServico();
                    p[g] = v;
                    solucao.AlocarPedido(g, make_pair(u, v));

                }else{ // Escolhas aleatorias baseadas no custo nas demais iteracoes

                    double probabilidade[(int)G.size()];
                    double custoTotal = 0;
                    for (int j = 0; j < (int)G.size(); j++){
                        custoTotal += instancia.getGrafo()->getCusto(G[j], u) + instancia.getGrafo()->getCusto(u, v);
                    }
                    double soma_p = 0.0;
                    for (int j = 0; j < (int)G.size(); j++){
                       probabilidade[j] = (custoTotal / (instancia.getGrafo()->getCusto(G[j], u) + instancia.getGrafo()->getCusto(u, v)));
                       soma_p += probabilidade[j];
                    }

                    int g = G[0];
                    double p_ = randValorDouble(0, soma_p);
                    double p_acumulada = 0;
                    for (int j = 0; j < (int)G.size(); j++){
                       if(probabilidade[j] + p_acumulada >= p_){
                            g = G[j];
                            break;
                       }
                       p_acumulada += probabilidade[j];
                    }

                    t[g] += instancia.getGrafo()->getTempo(p[g], u); 
                    t[g] = max(t[g], instancia.getGrafo()->getVertice(u).getJanelaTempo().first);
                    t[g] += instancia.getGrafo()->getVertice(u).getDuracaoServico() + instancia.getGrafo()->getTempo(u, v); 
                    t[g] = max(t[g], instancia.getGrafo()->getVertice(v).getJanelaTempo().first);
                    t[g] += instancia.getGrafo()->getVertice(v).getDuracaoServico();
                    p[g] = v;
                    solucao.AlocarPedido(g, make_pair(u, v));
                }
            }

        }

        // Armazena se ja foi possivel encontrar uma solucao otima

        SolViavel = (SolViavel || solucao.isViavel());

        // Verifica se a solucao viavel encontrada eh melhor que a melhor solucao ja encontrada

        if((solucao.isViavel() == true)  && ((solucao.ValorSolucao().first < melhorSolucao.ValorSolucao().first) || ((solucao.ValorSolucao().first == melhorSolucao.ValorSolucao().first) && (solucao.ValorSolucao().second < melhorSolucao.ValorSolucao().second)))){
            melhorSolucao = solucao;
        }

        // Incrementa o numero de iteracoes

        iter++;

        // Se alcancou o numero de iteracoes maximas e nao foi possivel encontrar uma solucao melhor, reinicia o numero de iteracoes e incrementa o numero de veiculos a ser utilizado

        if(iter == ITER_MAX && SolViavel == false){
            iter = 0;
            numVeiculos++;
        }
    }

    // Retorna a melhor solucao encontrada
    
    return melhorSolucao;
}
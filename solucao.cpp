// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094


using namespace std;

class Solucao{

private:
    Instancia * instancia;
    int numeroVeiculos;
    vector< pair<int, int> > * pedidosAtendidos;

public:
    Solucao(int numeroVeiculos, Instancia * instancia){
        this->numeroVeiculos = numeroVeiculos;
        this->pedidosAtendidos = new vector< pair<int, int> > [numeroVeiculos];
        this->instancia = instancia;
    }

    // Atribui um pedido a um veiculo
    void AlocarPedido(int veiculo, pair<int, int> pedido){
        this->pedidosAtendidos[veiculo].push_back(pedido);
    }

    // Retorna o valor da solucao
    pair<int, double> ValorSolucao(){
        pair<int, double> valor;
        valor.first = this->numeroVeiculos;
        double custo = 0;
        for (int veiculo = 0; veiculo < this->numeroVeiculos; ++veiculo){
            int localizacao_atual = 0; // todo veiculo inicia o trajeto no deposito
            for (int j = 0; j < this->pedidosAtendidos[veiculo].size(); ++j){
                custo += instancia->getGrafo()->getCusto(localizacao_atual, this->pedidosAtendidos[veiculo][j].first); // custo de ir ate o ponto de coleta
                custo += instancia->getGrafo()->getCusto(this->pedidosAtendidos[veiculo][j].first, this->pedidosAtendidos[veiculo][j].second); // custo de levar ate o ponto de entrega
                localizacao_atual = this->pedidosAtendidos[veiculo][j].second;
            }
            custo += instancia->getGrafo()->getCusto(localizacao_atual, 0); // custo de retorno ao deposito 
        }
        valor.second = custo;
        return valor;
    }

    bool isViavel(){

        // Verifica se todos os pedidos foram alocados a exatamente um veiculo
        vector< pair<int, int> > pedidos = this->instancia->getPedidos();
        for (int i = 0; i < (int) pedidos.size(); ++i){
            bool atendido = false;
            for (int veiculo = 0; veiculo < this->numeroVeiculos; ++veiculo){
                for (int j = 0; j < (int) this->pedidosAtendidos[veiculo].size(); ++j){
                    if((pedidos[i].first == this->pedidosAtendidos[veiculo][j].first) && (pedidos[i].second == this->pedidosAtendidos[veiculo][j].second) && (!atendido)){
                        atendido = true;
                    }else if((pedidos[i].first == this->pedidosAtendidos[veiculo][j].first) && (pedidos[i].second == this->pedidosAtendidos[veiculo][j].second) && (atendido)){
                        return false; // pedido alocado a mais de um veiculo
                    }
                }
            }
            if(!atendido){
                return false; // Pelo menos um pedido nao foi atendido
            }        
        }        

        for (int veiculo = 0; veiculo < this->numeroVeiculos; ++veiculo){
            int localizacao_atual = 0; // iniciando no deposito
            double tempo_veiculo = 0; // tempo inicial
            double capacidade_veiculo = 0; // capacidade do veiculo
            for (int j = 0; j < this->pedidosAtendidos[veiculo].size(); ++j){
                tempo_veiculo += this->instancia->getGrafo()->getTempo(localizacao_atual, this->pedidosAtendidos[veiculo][j].first);
                if(tempo_veiculo > this->instancia->getGrafo()->getVertice(this->pedidosAtendidos[veiculo][j].first).getJanelaTempo().second){
                    return false;
                }
                tempo_veiculo = max(tempo_veiculo, this->instancia->getGrafo()->getVertice(this->pedidosAtendidos[veiculo][j].first).getJanelaTempo().first);
                tempo_veiculo += this->instancia->getGrafo()->getVertice(this->pedidosAtendidos[veiculo][j].first).getDuracaoServico();
                tempo_veiculo += this->instancia->getGrafo()->getTempo(this->pedidosAtendidos[veiculo][j].first, this->pedidosAtendidos[veiculo][j].second);
                if(tempo_veiculo > this->instancia->getGrafo()->getVertice(this->pedidosAtendidos[veiculo][j].second).getJanelaTempo().second){
                    return false;
                }
                tempo_veiculo = max(tempo_veiculo, this->instancia->getGrafo()->getVertice(this->pedidosAtendidos[veiculo][j].second).getJanelaTempo().first);
                tempo_veiculo += this->instancia->getGrafo()->getVertice(this->pedidosAtendidos[veiculo][j].second).getDuracaoServico();
                localizacao_atual = this->pedidosAtendidos[veiculo][j].second;
                capacidade_veiculo += this->instancia->getGrafo()->getVertice(this->pedidosAtendidos[veiculo][j].first).getDemanda();
                if(capacidade_veiculo > this->instancia->getCapacidade()){
                    return false;
                }
            }
            tempo_veiculo += this->instancia->getGrafo()->getTempo(localizacao_atual, 0); // retorno ao deposito
            if(tempo_veiculo > this->instancia->getH()){
                return false;
            }
        }

        return true;
    }

};
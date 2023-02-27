// Gabriel Fernandes Silva Vieira - 201920340
// Pedro Gabriel Camargo Calisto - 201920337
// Tulio Oliveira Cruz - 202020094

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
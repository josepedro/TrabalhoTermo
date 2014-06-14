#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tdado{
    int temperatura;
    float pressao_sat;
    float vf;
    float vg;
    float uf;
    float ufg;
    float ug;
    float hf;
    float hfg;
    float hg;
    float sf;
    float sfg;
    float sg;
    struct tdado *esq;
    struct tdado *dir;
} Tdado;

typedef struct ldado{
    int temperatura;
    float pressao_sat;
    float vf;
    float vg;
    float uf;
    float ufg;
    float ug;
    float hf;
    float hfg;
    float hg;
    float sf;
    float sfg;
    float sg;
    struct ldado *pro;
} Ldado;



FILE *fileTabela;

Tdado *constroi(Tdado *raiz, int temperatura, float pressao_sat, float vf, float vg, float uf, float ufg, float ug, float hf, float hfg, float hg, float sf, float sfg, float sg){
    if(raiz != NULL){
        if(temperatura <= raiz->temperatura){
            raiz->esq = constroi(raiz->esq, temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
            //printf("\ncodigo <= raiz->codigo: %s\n",raiz->nome);
        }
        else{
            raiz->dir = constroi(raiz->dir, temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
            //printf("\nelse: %s\n",raiz->nome);
        }        
        return raiz;
    }
    else{
        raiz = (Tdado *) malloc(sizeof(Tdado));
        raiz->temperatura = temperatura;
        raiz->pressao_sat = pressao_sat;
        raiz->vf = vf;
        raiz->vg = vg;
        raiz->uf = uf;
        raiz->ufg = ufg;
        raiz->ug = ug;
        raiz->hf = hf;
        raiz->hfg = hfg;
        raiz->hg = hg;
        raiz->sf = sf;
        raiz->sfg = sfg;
        raiz->sg = sg;
        raiz->esq = NULL;
        raiz->dir = NULL;
        return raiz;
    }
}

void mostrar_valores_decrescente_temperatura(Tdado *raiz){
      if(raiz != NULL){
          mostrar_valores_decrescente_temperatura(raiz->esq);
          mostrar_valores_decrescente_temperatura(raiz->dir);
          printf("%d %f %f %f %f %f %f %f %f %f %f %f %f\n", raiz->temperatura, raiz->pressao_sat, raiz->vf, raiz->vg, raiz->uf, raiz->ufg, raiz->ug, raiz->hf, raiz->hfg, raiz->hg, raiz->sf, raiz->sfg, raiz->sg);  

      }
}

Tdado *pesquisa_temperatura(Tdado *raiz, int temperatura){
    if (raiz != NULL){
        if (temperatura < raiz->temperatura){
            pesquisa_temperatura(raiz->esq, temperatura);         
        }
        else if (temperatura > raiz->temperatura){
            pesquisa_temperatura(raiz->dir, temperatura);
        }     
        else if (temperatura == raiz->temperatura){
            return raiz;
        }
        else {
            return NULL;
        }
    }
}

Ldado *interpola_pesquisa_temperatura(Ldado *lista, int temperatura){



}

void pesquisa_temperatura_saturado(){

    Tdado *raiz = NULL;
    Ldado *lista = NULL;

    //Abrindo arquivo
    fileTabela = fopen("saturado-entrada-temperatura.txt","r");
    if (fileTabela == NULL)
    {
        printf("\n%s\n", "Arquivo nao encontrado");
    }

    //Contando quantidade de linhas no arquivo
    char caractere = getc(fileTabela);
    int linhas = 0;
    while(caractere != EOF){
        if(caractere == '\n'){
            caractere = getc(fileTabela);
            linhas++;  
        }
        else 
            caractere = getc(fileTabela);
    }

    //resetando o ponteiro do arquivo
    fclose(fileTabela);
    fileTabela = fopen("saturado-entrada-temperatura.txt","r");
    if (fileTabela == NULL)
    {
        printf("\n%s\n", "Arquivo nao encontrado");
    }

    //Construindo a arvore
    int i;
    int temperatura;
    float pressao_sat;
    float vf;
    float vg;
    float uf;
    float ufg;
    float ug;
    float hf;
    float hfg;
    float hg;
    float sf;
    float sfg;
    float sg;
    for (i = 0; i < linhas; ++i)
    {
        fscanf(fileTabela,"%d %f %f %f %f %f %f %f %f %f %f %f %f\n", &temperatura, &pressao_sat, 
            &vf, &vg, &uf, &ufg, &ug, &hf, &hfg, &hg, &sf, &sfg, &sg);
        //printf("%d %f %f %f %f %f %f %f %f %f %f %f %f\n", temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
        //Copiando os dados para as tabelas
        lista = listar_dado(lista, temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
        raiz = constroi(raiz, temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
        //printf("\n%s\t%s\t%s\t%s\t%s\n", videos_codigo[i], videos_titulo[i], videos_midia[i], videos_preco[i], videos_genero[i]);
    }

    //mostrar_valores_decrescente_temperatura(raiz);

    //Pesquisando Temperatura
    int temperatura_consulta;
    printf("\n\n\tDigite a temperatura em graus celcius: ");
    scanf("%d",&temperatura_consulta);

    Tdado *dados_consulta = pesquisa_temperatura(raiz, temperatura_consulta);
    if (dados_consulta == NULL){
        dados_consulta = interpola_pesquisa_temperatura(raiz, temperatura_consulta);
    }


    printf("\n\tDados da consulta:\n");
    printf("\t\tTemperatura: %d graus Celcius\n", dados_consulta->temperatura); 
    printf("\t\tPressao de Saturacao: %f kPa\n", dados_consulta->pressao_sat); 
    printf("\t\tVolume Especifico Saturado Liquido: %f m^3/kg\n", dados_consulta->vf); 
    printf("\t\tVolume Especifico Saturado Vapor: %f m^3/kg\n", dados_consulta->vg);
    printf("\t\tEnergia Interna Saturado Liquido: %f kJ/kg\n", dados_consulta->uf); 
    printf("\t\tEnergia Interna Evaporacao: %f kJ/kg\n", dados_consulta->ufg);
    printf("\t\tEnergia Interna Saturado Vapor: %f kJ/kg\n", dados_consulta->ug);  
    printf("\t\tEntalpia Saturado Liquido: %f kJ/kg\n", dados_consulta->hf);
    printf("\t\tEntalpia Evaporacao: %f kJ/kg\n", dados_consulta->hfg);
    printf("\t\tEntalpia Saturado Vapor: %f kJ/kg\n", dados_consulta->hg);
    printf("\t\tEntropia Saturado Liquido: %f kJ/kg . K\n", dados_consulta->sf);
    printf("\t\tEntropia Evaporacao: %f kJ/kg . K\n",dados_consulta->sfg);
    printf("\t\tEntropia Saturado Vapor: %f kJ/kg . K\n", dados_consulta->sg);

    fclose(fileTabela);

}

int main(){

    int opcao;

    while(1){
    printf("\n\n\nMenu de opcoes\n");
    printf("\t\t-__-__-__-__-__-__-__-__-__-__-__-___-___-___-___-_\n");
    printf("\t\t\t1 = Pesquisa saturado com entrada temperatura\n");
    printf("\t\t\t2 = ciclo de Brayton\n");
    printf("\t\t\t3 = buscar os dados na tabela\n");
    printf("\t\t\t4 = sair do programa\n");
    printf("\t\t_-__-__-__-__-__-__-__-__-__-__-__-___-___-___-___-_\n");
    scanf("%d",&opcao);

    pesquisa_temperatura_saturado();

    }

    

    printf("\n\n\tFIM\n\n");
    return 0;
}
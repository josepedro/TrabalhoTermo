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

Ldado *adicionar_dado_lista(Ldado *lista, int temperatura, float pressao_sat, float vf, float vg, float uf, float ufg, float ug, float hf, float hfg, float hg, float sf, float sfg, float sg){
    if (lista != NULL){
        lista->pro = adicionar_dado_lista(lista->pro, temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
    }
    else {
        lista = (Ldado *) malloc(sizeof(Ldado));
        lista->temperatura = temperatura;
        lista->pressao_sat = pressao_sat;
        lista->vf = vf;
        lista->vg = vg;
        lista->uf = uf;
        lista->ufg = ufg;
        lista->ug = ug;
        lista->hf = hf;
        lista->hfg = hfg;
        lista->hg = hg;
        lista->sf = sf;
        lista->sfg = sfg;
        lista->sg = sg;
        lista->pro = NULL;
    }
    return lista;
}

void listar_elementos(Ldado *lista){
    if (lista != NULL)
    {
        printf("%d %f %f %f %f %f %f %f %f %f %f %f %f\n", lista->temperatura, lista->pressao_sat, lista->vf, lista->vg, lista->uf, lista->ufg, lista->ug, lista->hf, lista->hfg, lista->hg, lista->sf, lista->sfg, lista->sg);
        listar_elementos(lista->pro);
    }
}

Ldado *interpola_pesquisa_temperatura(Ldado *lista, int temperatura){
    Ldado *ant, *post, *dados_consulta = NULL;
    post = lista;
    while(post != NULL){
        if (lista->temperatura < temperatura && post->temperatura > temperatura){
            dados_consulta = (Ldado *) malloc(sizeof(Ldado));
            printf("\n\t\t\ttemperatura anterior: %d temperatura posterior: %d\n", ant->temperatura, post->temperatura);
            dados_consulta->temperatura = temperatura;
            dados_consulta->pressao_sat = ((temperatura - ant->temperatura)*
                (post->pressao_sat - ant->pressao_sat)/(post->temperatura - ant->temperatura)) + ant->pressao_sat;
            dados_consulta->vf = ((temperatura - ant->temperatura)*
                (post->vf - ant->vf)/(post->temperatura - ant->temperatura)) + ant->vf;
            dados_consulta->vg = ((temperatura - ant->temperatura)*
                (post->vg - ant->vg)/(post->temperatura - ant->temperatura)) + ant->vg;
            dados_consulta->uf = ((temperatura - ant->temperatura)*
                (post->uf - ant->uf)/(post->temperatura - ant->temperatura)) + ant->uf;
            dados_consulta->ufg = ((temperatura - ant->temperatura)*
                (post->ufg - ant->ufg)/(post->temperatura - ant->temperatura)) + ant->ufg;
            dados_consulta->ug = ((temperatura - ant->temperatura)*
                (post->ug - ant->ug)/(post->temperatura - ant->temperatura)) + ant->ug;
            dados_consulta->hf = ((temperatura - ant->temperatura)*
                (post->hf - ant->hf)/(post->temperatura - ant->temperatura)) + ant->hf;
            dados_consulta->hfg = ((temperatura - ant->temperatura)*
                (post->hfg - ant->hfg)/(post->temperatura - ant->temperatura)) + ant->hfg;
            dados_consulta->hg = ((temperatura - ant->temperatura)*
                (post->hg - ant->hg)/(post->temperatura - ant->temperatura)) + ant->hg;
            dados_consulta->sf = ((temperatura - ant->temperatura)*
                (post->sf - ant->sf)/(post->temperatura - ant->temperatura)) + ant->sf;
            dados_consulta->sfg = ((temperatura - ant->temperatura)*
                (post->sfg- ant->sfg)/(post->temperatura - ant->temperatura)) + ant->sfg;
            dados_consulta->sg = ((temperatura - ant->temperatura)*
                (post->sg - ant->sg)/(post->temperatura - ant->temperatura)) + ant->sg;
            break;        
        }
        ant = post;
        post = post->pro;
    }
    return dados_consulta;
}

void mostrar_resultado_pesquisa_arvore(Tdado *dados_consulta){
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
}

void mostrar_resultado_pesquisa_lista(Ldado *dados_consulta){
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
        lista = adicionar_dado_lista(lista, temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
        raiz = constroi(raiz, temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
        //printf("\n%s\t%s\t%s\t%s\t%s\n", videos_codigo[i], videos_titulo[i], videos_midia[i], videos_preco[i], videos_genero[i]);
    }

    //mostrar_valores_decrescente_temperatura(raiz);

    //listar_elementos(lista);

    //Pesquisando Temperatura
    float temperatura_consulta;
    printf("\n\n\tDigite a temperatura em graus celcius: ");
    scanf("%f",&temperatura_consulta);

    Tdado *dados_consulta = pesquisa_temperatura(raiz, (int) temperatura_consulta);
    if (dados_consulta == NULL){
        Ldado *dados_consulta = interpola_pesquisa_temperatura(lista, temperatura_consulta);
        if (dados_consulta == NULL){
            printf("\n\t\t%s\n", "Erro na consulta. Insira uma temperatura valida");
        }
        else{
            mostrar_resultado_pesquisa_lista(dados_consulta);
        }
    }
    else{
        mostrar_resultado_pesquisa_arvore(dados_consulta);
    }


    
    fclose(fileTabela);

}

int main(){

    int opcao;
    int sair = 1; 

    while(sair){
        printf("\n\n\n\n\n\n\nMenu de opcoes\n");
        printf("\t\t-__-__-__-__-__-__-__-__-__-__-__-___-___-___-___-_\n");
        printf("\t\t\t1 = Pesquisa saturado com entrada temperatura\n");
        printf("\t\t\t2 = Sair do programa\n");
        printf("\t\t_-__-__-__-__-__-__-__-__-__-__-__-___-___-___-___-_\n");
        printf("Opcao: ");
        scanf("%d",&opcao);

        if (opcao == 1){
            pesquisa_temperatura_saturado();
        }
        else{
            sair = 0;
        }
    }

    printf("\n\n\tFIM\n\n");
    return 0;
}
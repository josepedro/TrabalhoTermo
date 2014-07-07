#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *fileTabela;

typedef struct ldado{
    float temperatura;
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


typedef struct ldadosa{
    float temperatura;
    float pressao;
    float v;
    float u;
    float h;
    float s;
    struct ldadosa *pro;
} Ldadosa;


Ldado *adicionar_dado_lista(Ldado *lista, float temperatura, float pressao_sat, float vf, float vg, float uf, float ufg, float ug, float hf, float hfg, float hg, float sf, float sfg, float sg){
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
        printf("%f %f %f %f %f %f %f %f %f %f %f %f %f\n", lista->temperatura, lista->pressao_sat, lista->vf, lista->vg, lista->uf, lista->ufg, lista->ug, lista->hf, lista->hfg, lista->hg, lista->sf, lista->sfg, lista->sg);
        listar_elementos(lista->pro);
    }
}

Ldado *interpola_pesquisa_temperatura(Ldado *lista, float temperatura){
    Ldado *ant, *post, *dados_consulta = NULL;
    post = lista;
    while(post != NULL){
        if (lista->temperatura < temperatura && post->temperatura > temperatura){
            dados_consulta = (Ldado *) malloc(sizeof(Ldado));
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

void mostrar_resultado_pesquisa_lista(Ldado *dados_consulta){
    printf("\n\tDados da consulta:\n");
    printf("\t\tTemperatura: %f graus Celcius\n", dados_consulta->temperatura); 
    printf("\t\tPressao: %f kPa\n", dados_consulta->pressao_sat); 
    printf("\t\tVolume Especifico Liquido: %f m^3/kg\n", dados_consulta->vf); 
    printf("\t\tVolume Especifico Vapor: %f m^3/kg\n", dados_consulta->vg);
    printf("\t\tEnergia Interna Liquido: %f kJ/kg\n", dados_consulta->uf); 
    printf("\t\tEnergia Interna Evaporacao: %f kJ/kg\n", dados_consulta->ufg);
    printf("\t\tEnergia Interna Vapor: %f kJ/kg\n", dados_consulta->ug);  
    printf("\t\tEntalpia Liquido: %f kJ/kg\n", dados_consulta->hf);
    printf("\t\tEntalpia Evaporacao: %f kJ/kg\n", dados_consulta->hfg);
    printf("\t\tEntalpia Vapor: %f kJ/kg\n", dados_consulta->hg);
    printf("\t\tEntropia Liquido: %f kJ/kg . K\n", dados_consulta->sf);
    printf("\t\tEntropia Evaporacao: %f kJ/kg . K\n",dados_consulta->sfg);
    printf("\t\tEntropia Vapor: %f kJ/kg . K\n", dados_consulta->sg);
}

int quantidade_linhas(FILE *fileTabela){
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
    return linhas;
}

FILE *abrir_arquivo(FILE *fileTabela, char *nome_arquivo){
    fileTabela = fopen(nome_arquivo,"r");
    if (fileTabela == NULL)
    {
        printf("\n%s\n", "Arquivo nao encontrado");
    }
    return fileTabela; 
}

FILE *resetar_tabela(FILE *fileTabela, char *nome_arquivo){
    fclose(fileTabela);
    fileTabela = abrir_arquivo(fileTabela, nome_arquivo);
    return fileTabela;
}

Ldado *extrair_dados_temperatura(FILE *fileTabela, int linhas, Ldado *lista){
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
        lista = adicionar_dado_lista(lista, (float) temperatura, pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
    }
    return lista;
}

Ldado *consultar_temperatura(Ldado *lista, float temperatura){
    if (lista != NULL){
        if (lista->temperatura == temperatura){
            return lista;
        }
        else{
            consultar_temperatura(lista->pro, temperatura);
        }
    }
    else{
        return NULL;
    }
}

void pesquisar_interpolado_temperatura(Ldado *lista, float temperatura){
    Ldado *dados_consulta = consultar_temperatura(lista, temperatura);
    if (dados_consulta == NULL){
        Ldado *dados_consulta = interpola_pesquisa_temperatura(lista, temperatura);
        if (dados_consulta == NULL){
            printf("\n\t\t%s\n", "Erro na consulta. Insira uma temperatura valida");
        }
        else{
            mostrar_resultado_pesquisa_lista(dados_consulta);
        }
    }
    else{
        mostrar_resultado_pesquisa_lista(dados_consulta);
    }
}

void pesquisar_temperatura_saturado(){

    //iniciando vairiáveis para pesquisa
    Ldado *lista = NULL;
    char *nome_arquivo = "saturado-entrada-temperatura.txt";

    //Abrindo arquivo
    fileTabela = abrir_arquivo(fileTabela, nome_arquivo);

    //Contando quantidade de linhas no arquivo
    int linhas = quantidade_linhas(fileTabela); 


    //resetando o ponteiro do arquivo
    fileTabela = resetar_tabela(fileTabela, nome_arquivo);


    //Construir lista
    lista = extrair_dados_temperatura(fileTabela, linhas, lista);

    //listar_elementos(lista);

    //Pesquisando Temperatura
    float temperatura_consulta;
    printf("\n\n\tDigite a temperatura em graus celcius: ");
    scanf("%f",&temperatura_consulta);

    //Pesquisa completa
    pesquisar_interpolado_temperatura(lista, temperatura_consulta);
    
    //fechar tabela
    fclose(fileTabela);
}

Ldado *extrair_dados_pressao(FILE *fileTabela, int linhas, Ldado *lista){
    int i;
    float temperatura;
    int pressao_sat;
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
        fscanf(fileTabela,"%d %f %f %f %f %f %f %f %f %f %f %f %f\n", &pressao_sat, &temperatura, 
            &vf, &vg, &uf, &ufg, &ug, &hf, &hfg, &hg, &sf, &sfg, &sg);
        //printf("%d %f %f %f %f %f %f %f %f %f %f %f %f\n", pressao_sat, temperatura, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
        //Copiando os dados para as tabelas
        lista = adicionar_dado_lista(lista, temperatura, (float) pressao_sat, vf, vg, uf, ufg, ug, hf, hfg, hg, sf, sfg, sg);
    }
    return lista;

}

Ldado *consultar_pressao(Ldado *lista, float pressao){
    if (lista != NULL){
        if (lista->pressao_sat == pressao){
            return lista;
        }
        else{
            consultar_temperatura(lista->pro, pressao);
        }
    }
    else{
        return NULL;
    }
}

Ldado *interpola_pesquisa_pressao(Ldado *lista, float pressao){
    Ldado *ant, *post, *dados_consulta = NULL;
    post = lista;
    while(post != NULL){
        if (lista->pressao_sat < pressao && post->pressao_sat > pressao){
            dados_consulta = (Ldado *) malloc(sizeof(Ldado));
            dados_consulta->pressao_sat = pressao;
            dados_consulta->temperatura = ((pressao - ant->pressao_sat)*
                (post->temperatura - ant->temperatura)/(post->pressao_sat - ant->pressao_sat)) + ant->temperatura;
            dados_consulta->vf = ((pressao - ant->pressao_sat)*
                (post->vf - ant->vf)/(post->pressao_sat - ant->pressao_sat)) + ant->vf;
            dados_consulta->vg = ((pressao - ant->pressao_sat)*
                (post->vg - ant->vg)/(post->pressao_sat - ant->pressao_sat)) + ant->vg;
            dados_consulta->uf = ((pressao - ant->pressao_sat)*
                (post->uf - ant->uf)/(post->pressao_sat - ant->pressao_sat)) + ant->uf;
            dados_consulta->ufg = ((pressao - ant->pressao_sat)*
                (post->ufg - ant->ufg)/(post->pressao_sat - ant->pressao_sat)) + ant->ufg;
            dados_consulta->ug = ((pressao - ant->pressao_sat)*
                (post->ug - ant->ug)/(post->pressao_sat - ant->pressao_sat)) + ant->ug;
            dados_consulta->hf = ((pressao - ant->pressao_sat)*
                (post->hf - ant->hf)/(post->pressao_sat - ant->pressao_sat)) + ant->hf;
            dados_consulta->hfg = ((pressao - ant->pressao_sat)*
                (post->hfg - ant->hfg)/(post->pressao_sat - ant->pressao_sat)) + ant->hfg;
            dados_consulta->hg = ((pressao - ant->pressao_sat)*
                (post->hg - ant->hg)/(post->pressao_sat - ant->pressao_sat)) + ant->hg;
            dados_consulta->sf = ((pressao - ant->pressao_sat)*
                (post->sf - ant->sf)/(post->pressao_sat - ant->pressao_sat)) + ant->sf;
            dados_consulta->sfg = ((pressao - ant->pressao_sat)*
                (post->sfg- ant->sfg)/(post->pressao_sat - ant->pressao_sat)) + ant->sfg;
            dados_consulta->sg = ((pressao - ant->pressao_sat)*
                (post->sg - ant->sg)/(post->pressao_sat - ant->pressao_sat)) + ant->sg;
            break;        
        }
        ant = post;
        post = post->pro;
    }
    return dados_consulta;
}

void pesquisar_interpolado_pressao(Ldado *lista, float pressao){
    Ldado *dados_consulta = consultar_pressao(lista, pressao);
    if (dados_consulta == NULL){
        Ldado *dados_consulta = interpola_pesquisa_pressao(lista, pressao);
        if (dados_consulta == NULL){
            printf("\n\t\t%s\n", "Erro na consulta. Insira uma pressao valida");
        }
        else{
            mostrar_resultado_pesquisa_lista(dados_consulta);
        }
    }
    else{
        mostrar_resultado_pesquisa_lista(dados_consulta);
    }
}

void pesquisar_pressao_saturado(){

    //iniciando vairiáveis para pesquisa
    Ldado *lista = NULL;
    char *nome_arquivo = "saturado-entrada-pressao.txt";

    //Abrindo arquivo
    fileTabela = abrir_arquivo(fileTabela, nome_arquivo);

    //Contando quantidade de linhas no arquivo
    int linhas = quantidade_linhas(fileTabela); 

    //resetando o ponteiro do arquivo
    fileTabela = resetar_tabela(fileTabela, nome_arquivo);

    //Construir lista
    lista = extrair_dados_pressao(fileTabela, linhas, lista);

    //listar_elementos(lista);

    //Pesquisando Pressao
    float pressao_consulta;
    printf("\n\n\tDigite a temperatura em kPa: ");
    scanf("%f",&pressao_consulta);

    //Pesquisa completa
    pesquisar_interpolado_pressao(lista, pressao_consulta);
    
    //fechar tabela
    fclose(fileTabela);
    
}

void listar_elementos_superaquecido(Ldadosa *lista){
    if (lista != NULL){
        printf("%f %f %f %f %f %f \n", lista->pressao, lista->temperatura, lista->v, lista->u, lista->h, lista->s);
        listar_elementos_superaquecido(lista->pro);
    }
}

Ldadosa *adicionar_dado_lista_superaquecido(Ldadosa *lista, float pressao, float temperatura, float v, float u, float h, float s){
    if (lista != NULL){
        lista->pro = adicionar_dado_lista_superaquecido(lista->pro, pressao, temperatura, v, u, h, s);
    }
    else {
        lista = (Ldadosa *) malloc(sizeof(Ldadosa));
        lista->temperatura = temperatura;
        lista->pressao = pressao;
        lista->v = v;
        lista->u = u;
        lista->h = h;
        lista->s = s;
        lista->pro = NULL;
    }
    return lista;
}

Ldadosa *extrair_dados_superaquecido(FILE *fileTabela, int linhas, Ldadosa *lista){
    int i;
    float temperatura;
    float pressao;
    float v;
    float u;
    float h;
    float s;
    for (i = 0; i < linhas; ++i)
    {
        fscanf(fileTabela,"%f %f %f %f %f %f\n", &pressao, &temperatura, &v, &u, &h, &s);
        //printf("%f %f %f %f %f %f\n", pressao, temperatura, v, u, h, s);
        lista = adicionar_dado_lista_superaquecido(lista, pressao, temperatura, v, u, h, s);
            
    }
    return lista;
}

Ldadosa *consultar_superaquecido(Ldadosa *lista, float pressao, float temperatura){
    if (lista != NULL){
        if (lista->pressao == pressao && lista->temperatura == temperatura){
            return lista;
        }
        else{
            consultar_superaquecido(lista->pro, pressao, temperatura);
        }
    }
    else{
        return NULL;
    }
}

Ldadosa *interpola_pesquisa_superaquecido(Ldadosa *lista, float pressao, float temperatura){
    Ldadosa *ant, *post, *dados_consulta = NULL;
    post = lista;
    float constante_pressao = 1;
    float constante_temperatura = 1;
    //achar constante pressao
    while(post != NULL){
        if (lista->pressao <= pressao && post->pressao >= pressao){
            constante_pressao = (pressao - ant->pressao)/(post->pressao - ant->pressao);
            break;        
        }
        ant = post;
        post = post->pro;
    }
    post = lista;
    while(post != NULL){
        if (lista->temperatura <= temperatura && post->temperatura >= temperatura){
            constante_temperatura = (temperatura - ant->temperatura)/(post->temperatura - ant->temperatura);
            break;        
        }
        ant = post;
        post = post->pro;
    }
    dados_consulta = (Ldadosa *) malloc(sizeof(Ldadosa));
    dados_consulta->pressao = pressao;
    dados_consulta->temperatura = temperatura;
    dados_consulta->v = (post->v - ant->v)*constante_temperatura*constante_pressao + ant->v;
    dados_consulta->u = (post->u - ant->u)*constante_temperatura*constante_pressao + ant->u;
    dados_consulta->h = (post->h - ant->h)*constante_temperatura*constante_pressao + ant->h;
    dados_consulta->s = (post->s - ant->s)*constante_temperatura*constante_pressao + ant->s;
    return dados_consulta;
}

void mostrar_resultado_pesquisa_superaquecido(Ldadosa *dados_consulta){
    printf("\n\tDados da consulta:\n");
    printf("\t\tPressao: %f MPa\n", dados_consulta->pressao);
    printf("\t\tTemperatura: %f graus Celcius\n", dados_consulta->temperatura); 
    printf("\t\tVolume Especifico Super-aquecido: %f m^3/kg\n", dados_consulta->v); 
    printf("\t\tEnergia Interna Super-aquecido: %f kJ/kg\n", dados_consulta->u); 
    printf("\t\tEntalpia Saturado Super-aquecido: %f kJ/kg\n", dados_consulta->h);
    printf("\t\tEntropia Saturado Super-aquecido: %f kJ/kg . K\n", dados_consulta->s);
}

void pesquisar_interpolado_superaquecido(Ldadosa *lista, float pressao, float temperatura){
    Ldadosa *dados_consulta = consultar_superaquecido(lista, pressao, temperatura);
    if (dados_consulta == NULL){
        Ldadosa *dados_consulta = interpola_pesquisa_superaquecido(lista, pressao, temperatura);
        if (dados_consulta == NULL){
            printf("\n\t\t%s\n", "Erro na consulta. Insira uma pressao valida");
        }
        else{
            mostrar_resultado_pesquisa_superaquecido(dados_consulta);
        }
    }
    else{
        mostrar_resultado_pesquisa_superaquecido(dados_consulta);
    }

}

void pesquisar_superarquecido(){

    //iniciando vairiáveis para pesquisa
    Ldadosa *lista = NULL;
    char *nome_arquivo = "superaquecido.txt";

    //Abrindo arquivo
    fileTabela = abrir_arquivo(fileTabela, nome_arquivo);

    //Contando quantidade de linhas no arquivo
    int linhas = quantidade_linhas(fileTabela);

    //resetando o ponteiro do arquivo
    fileTabela = resetar_tabela(fileTabela, nome_arquivo);

    //Construir lista
    lista = extrair_dados_superaquecido(fileTabela, linhas, lista);

    //listar
    //listar_elementos_superaquecido(lista);

    //Pesquisa
    float pressao_consulta;
    printf("\n\n\tDigite a pressao em MPa: ");
    scanf("%f",&pressao_consulta);
    float temperatura_consulta;
    printf("\tDigite a temperatura em graus celcius: ");
    scanf("%f",&temperatura_consulta);

    //Pesquisa completa
    pesquisar_interpolado_superaquecido(lista, pressao_consulta, temperatura_consulta);

}


typedef struct dadop1{
    float vg;
    float hg;
    float sg;
    struct dadop1 *pro;
} Dadop1;


Dadop1 *pesquisar_interpolado_pressao_ciclo(Ldado *lista, float pressao){
    Dadop1 *p1 = NULL;
    Ldado *dados_consulta = consultar_pressao(lista, pressao);
    if (dados_consulta == NULL){
        Ldado *dados_consulta = interpola_pesquisa_pressao(lista, pressao);
        if (dados_consulta == NULL){
            printf("\n\t\t%s\n", "Erro na consulta. Insira uma pressao valida");
        }
        else{
            p1 = (Dadop1 *) malloc(sizeof(Dadop1));
            p1->vg = dados_consulta->vg;
            p1->hg = dados_consulta->hg;
            p1->sg = dados_consulta->sg;
        }
    }
    else{
        p1 = (Dadop1 *) malloc(sizeof(Dadop1));
        p1->vg = dados_consulta->vg;
        p1->hg = dados_consulta->hg;
        p1->sg = dados_consulta->sg;
    }
    return p1;
}


Dadop1 *pesquisar_p1(float pressao){
    
    //iniciando vairiáveis para pesquisa
    Ldado *lista = NULL;
    Dadop1 *p1 = NULL;
    char *nome_arquivo = "saturado-entrada-pressao.txt";

    //Abrindo arquivo
    fileTabela = abrir_arquivo(fileTabela, nome_arquivo);

    //Contando quantidade de linhas no arquivo
    int linhas = quantidade_linhas(fileTabela); 

    //resetando o ponteiro do arquivo
    fileTabela = resetar_tabela(fileTabela, nome_arquivo);

    //Construir lista
    lista = extrair_dados_pressao(fileTabela, linhas, lista);

    //Pesquisa completa
    p1 = pesquisar_interpolado_pressao_ciclo(lista, pressao);
    
    //fechar tabela
    fclose(fileTabela);

    return p1;

}


void pesquisar_ciclo_refrigeracao(){
    //entrada: pressao_max, pressao_min, vazao massica
    //saida: propriedades em cada ponto, p1 (Vv, Hv, Sv, tabela pressao com pressao_min), p2, p3, p4

    float pressao_menor;
    printf("\n\n\tDigite a menor pressao em kPa: ");
    scanf("%f",&pressao_menor);

    Dadop1 *p1 = NULL;
    p1 = pesquisar_p1(pressao_menor);

    printf("\n\tDados de saida para P1: \n");
    printf("\n\t\tVv: %f\n",p1->vg); 
    printf("\n\t\tHv: %f\n",p1->hg);
    printf("\n\t\tSv: %f\n",p1->sg);

}

int main(){

    int opcao;
    int sair = 1; 

    while(sair){
        printf("\n\n\n\n\n\n\nMenu de opcoes\n");
        printf("\t\t-__-__-__-__-__-__-__-__-__-__-__-___-___-___-___-_\n");
        printf("\t\t\t1 = Pesquisa saturado com entrada temperatura\n");
        printf("\t\t\t2 = Pesquisa saturado com entrada pressao\n");
        printf("\t\t\t3 = Pesquisa super-aquecido\n");
        printf("\t\t\t4 = Pesquisa comprimido com entrada temperatura\n");
        printf("\t\t\t5 = Pesquisa ciclo refrigeracao\n");
        printf("\t\t\t0 = Sair do programa\n");
        printf("\t\t_-__-__-__-__-__-__-__-__-__-__-__-___-___-___-___-_\n");
        printf("Opcao: ");
        scanf("%d",&opcao);

        if (opcao == 1){
            printf("\n\t%s","Pesquisa saturado com entrada temperatura");
            pesquisar_temperatura_saturado();
        }
        else if (opcao == 2){
            printf("\n\t%s","Pesquisa saturado com entrada pressao");
            pesquisar_pressao_saturado();
        }
        else if (opcao == 3){
            printf("\n\t%s","Pesquisa super-aquecido");
            pesquisar_superarquecido();
        }
        else if (opcao == 4){
            printf("\n\t%s","Pesquisa comprimido com entrada temperatura");
            pesquisar_temperatura_saturado();
        }
        else if (opcao == 5){
            printf("\n\t%s","Pesquisa ciclo refrigeracao");
            pesquisar_ciclo_refrigeracao();
        }
        else{
            sair = 0;
        }
    }

    printf("\n\n\tFIM\n\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_REGISTRO 700


typedef struct {

    char endereco[72];
    char bairro[72];
    char cidade[72];
    char nomeEstado[72];
    char siglaEstado[2];
    char cep[8];
    char naoUsado[2];

} Endereco;

int trinta_porcento_a_mais = NUMBER_REGISTRO+(NUMBER_REGISTRO *30)/100;//688
int duas_vezes_numero_registro = NUMBER_REGISTRO*2;//635

int funcaoHash(char *cep , int numeroRegistros );

int main(int argc, char** argv)
{
    FILE* entrada;
    Endereco e;
    int tabelaHash[duas_vezes_numero_registro];
    long registro;

    entrada = fopen( "cep.dat","r+");

    if(!entrada)
    {
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", "cep.dat");
        getchar();
        return 1;
    }
    registro = 0;
    int total_colisao = 0;

    memset(&e,0,sizeof(Endereco));
    fread(&e.endereco,1,72,entrada);
    fread(&e.bairro,1,72,entrada);
    fread(&e.cidade,1,72,entrada);
    fread(&e.nomeEstado,1,72,entrada);
    fread(&e.siglaEstado,1,2,entrada);
    fread(&e.cep,1,8,entrada);
    fseek(entrada,2,SEEK_CUR);



     while(registro < NUMBER_REGISTRO)
     {

            int chaveHash = funcaoHash(e.cep,duas_vezes_numero_registro);

            if(tabelaHash[chaveHash]== 0 )
            {
                tabelaHash[chaveHash] = 1;

            }else{
                printf("................\n");
                printf("--- COLISAO--: %d\n", chaveHash);
                printf("................\n");
                total_colisao++;
            }




        memset(&e,0,sizeof(Endereco));
        fread(&e.endereco,1,72,entrada);
        fread(&e.bairro,1,72,entrada);
        fread(&e.cidade,1,72,entrada);
        fread(&e.nomeEstado,1,72,entrada);
        fread(&e.siglaEstado,1,2,entrada);
        fread(&e.cep,1,8,entrada);
        fseek(entrada,2,SEEK_CUR);
        registro++;
    }

    printf("##############\n");
    printf("## TOTAL COLISOES: %d\n", total_colisao);
    printf("##############\n");

    getchar();
    fclose(entrada);

    return 0;
}

int funcaoHash(char *cep , int numeroRegistros )
{
    int cepInt = atoi(cep);
    int resultadoHash = cepInt % numeroRegistros;
    return resultadoHash;
}

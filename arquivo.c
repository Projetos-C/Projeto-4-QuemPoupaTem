#include "functions.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
// Funções de Arquivo:
// Manipulação do Arquivo binário

Value salvar(
    Conta contas[],
    int *pos) { // Função de Salvar a lista de contatos no arquivo binário
  FILE *arq = fopen("contas.bin", "wb");
  if (arq == NULL)
    return ABRIR;

  int qtd = fwrite(contas, TOTAL, sizeof(Conta), arq);
  if (qtd == 0)
    return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), arq);
  if (qtd == 0)
    return ESCREVER;

  if (fclose(arq))
    return FECHAR;

  printf("\033[32m| > Arquivo Salvo!!\n");
  return OK;
}

Value carregar(
    Conta contas[],
    int *pos) { // Função de Carregar a lista de contatos do arquivo binário
  FILE *f = fopen("contas.bin", "rb");
  if (f == NULL)
    return ABRIR;

  int qtd = fread(contas, TOTAL, sizeof(Conta), f);
  if (qtd == 0)
    return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return LER;

  if (fclose(f))
    return FECHAR;

  printf("\033[32m| > Contas carregados!!\n");
  return OK;
}

Value salvar_extrato(
    Extrato extratos[],
    int *pos) { // Função de Salvar a lista de contatos no arquivo binário
  FILE *arq = fopen("extratos.bin", "wb");
  if (arq == NULL)
    return ABRIR;

  int qtd = fwrite(extratos, T_EXTRATO, sizeof(Extrato), arq);
  if (qtd == 0)
    return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), arq);
  if (qtd == 0)
    return ESCREVER;

  if (fclose(arq))
    return FECHAR;

  printf("\033[32m| > Extrato Salvo!!\n");
  return OK;
}

carregar_extrato(
  Extrato extratos[],
  int *pos){
    FILE *f = fopen("extrato.bin", "rb");
    if (f == NULL)
      return ABRIR;

    int qtd = fread(extratos, T_EXTRATO, sizeof(Extrato), f);
    if (qtd == 0)
      return LER;

    if (fclose(f))
      return FECHAR;

    printf("\033[32m| > Extratos carregados!!\n");

  }
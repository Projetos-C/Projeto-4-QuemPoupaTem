#include "functions.h"

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

Value carregar_extrato(Conta contas[], int *total_contas) {
    FILE *f = fopen("contas.bin", "rb");
    if (f == NULL)
        return ABRIR;

    int qtd = fread(total_contas, sizeof(int), 1, f);
    if (qtd != 1)
        return LER;

    qtd = fread(contas, sizeof(Conta), *total_contas, f);
    if (qtd != *total_contas)
        return LER;

    if (fclose(f))
        return FECHAR;

    printf("\033[32m| > Contas carregadas!!\n");
    return OK;
}


Value gerar_arquivo_texto(Conta contas[], int user, const char *nome_arquivo) {
    // Verifica se o arquivo existe
    FILE *f = fopen(nome_arquivo, "r");
    bool novo_arquivo = false; // Flag para indicar se é um novo arquivo

    // Se o arquivo não existe, abre para escrita e cria um novo arquivo
    if (f == NULL) {
        f = fopen(nome_arquivo, "w");
        novo_arquivo = true;
    }
    else {
        fclose(f); // Fecha o arquivo aberto para verificação
        f = fopen(nome_arquivo, "w"); // Abre para escrita, substituindo o conteúdo existente
    }

    if (f == NULL)
        return ABRIR;

    fprintf(f, "Extratos da conta de %s (%s)\n", contas[user].nome, contas[user].cpf);
    fprintf(f, "Tipo de conta: %s\n", contas[user].tipo_conta == 'c' ? "Comum" : "Plus");
    fprintf(f, "Saldo atual: %.2f\n", contas[user].Saldo);
    fprintf(f, "\n| Data\t\t\t\t  | Tipo\t\t\t\t| Valor\t\t| Taxa\t\t|\n");
    fprintf(f, "-------------------------------------------------------------\n");

    for (int i = 0; i < contas[user].extrato_size; i++) {
        char buffer[26];
        struct tm* tm_info;
        tm_info = localtime(&contas[user].extrato[i].data);
        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

        const char* tipo_operacao;
        switch (contas[user].extrato[i].tipo) {
            case 1: tipo_operacao = "Deposito"; break;
            case 2: tipo_operacao = "Débito"; break;
            case 3: tipo_operacao = "Transferência Recebida"; break;
            case 4: tipo_operacao = "Transferência Paga"; break;
            default: tipo_operacao = "Desconhecido"; break;
        }

        float valor_operacao = contas[user].extrato[i].valor;
        float taxa = 0.0;
        if (contas[user].extrato[i].tipo == 2) { // Se a operação for de débito
            if (contas[user].tipo_conta == 'c') { // Se for conta comum
                taxa = valor_operacao * 0.05; // Calcula a taxa de 5%
                valor_operacao += taxa; // Adiciona a taxa ao valor da operação
            } else { // Se for conta plus
                taxa = valor_operacao * 0.03; // Calcula a taxa de 3%
                valor_operacao += taxa; // Adiciona a taxa ao valor da operação
            }
        }

        fprintf(f, "| %s\t| %s\t| %.2f\t| %.2f\t|\n", buffer, tipo_operacao, valor_operacao, taxa);
    }

    if (fclose(f))
        return FECHAR;

    if (novo_arquivo)
        printf("\033[32m| > Arquivo de extratos criado!!\n");
    else
        printf("\033[32m| > Arquivo de extratos atualizado!!\n");

    return OK;
}

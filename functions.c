#include "functions.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// >>> Funções ADM:
// Relacionadas a controle de Clientes
Value novo_cliente(Conta contas[], int *pos, int *user) { // Função de Criar um novo cliente
  if (*pos >= TOTAL) {
    return MAX_CONTA;
  }
  if (*user != -1 && *user != -2) {
    return ACESSO_INVALIDO;
  }
  printf("| > Nome do Usuario: ");
  fgets(contas[*pos].nome, T_NOME, stdin);
  contas[*pos].nome[strcspn(contas[*pos].nome, "\n")] = '\0';

  int cpfCorrect = 1;
  int cont = 0;
  char cpf[T_CPF];
  do {
    cpfCorrect = 1;
    printf("| > CPF (Ex: 112345678900): ");
    scanf("%s", cpf);
    clearBuffer();
    // Remove o \n do final do cpf informado;
    if (strlen(cpf) > 11 &&
        strlen(cpf) < 11) { // Verifica se o tamanho do cpf é válido
      cpfCorrect = 0;
    }
    if (cpfCorrect) {
      for (int i = 0; cpf[i] != '\0';
           i++) { // Verifica se não há nenhum char não cpférico no número
                  // informado;
        if (!isdigit(cpf[i]) && cpf[i] != '\0') {
          cpfCorrect = 0;
          break;
        }
      }
    }

    else {
      printf("\033[34m| > CPF Inválido, tente novamente...\n");
      cpf[0] = '\0';
    }
  } while (!cpfCorrect);
  strcpy(contas[*pos].cpf, cpf);
  contas[*pos].cpf[strcspn(contas[*pos].cpf, "\n")] = '\0';

  char tipo_conta;
  int isValidType = 0;

  printf("| > Tipo conta:\n");
  printf("|\n");
  printf("|-- Comum (c):\n");
  printf("|   - Taxa de 5%% no debito\n");
  printf("|   - Limite de saldo negativo de R$1.000\n");
  printf("|\n");
  printf("|-- Plus (p):\n");
  printf("|   - Taxa de 3%% no debito\n");
  printf("|   - Limite de saldo negativo de R$5.000\n");
  printf("|\n");

  do {
    printf("\033[34m| > Escolha o tipo de conta (p/c): ");
    scanf(" %c", &tipo_conta); // Adicionando um espaço antes de %c para ignorar
                               // espaços em branco
    clearBuffer();

    if (tipo_conta == 'c' || tipo_conta == 'p') {
      contas[*pos].tipo_conta = tipo_conta;
      isValidType = 1;
    } else {
      printf("\033[31m| > Tipo de conta invalido, Tente novamente...\n");
    }
  } while (!isValidType);

  float saldo;
  int isValid =
      0; // Inicialize isValid como 0 para que o loop execute pelo menos uma vez

  do {
    printf("\033[34m| > Informe o saldo da conta: ");
    if (scanf("%f", &saldo) == 1) {
      clearBuffer();
      if (saldo >= 0) {
        printf("\033[32m| > Saldo valido!\n");
        contas[*pos].Saldo = saldo;
        printf("\033[34m");
        isValid = 1; // Atualize isValid para 1 se o saldo for válido
      } else {
        printf("\033[31m| > Saldo invalido, Tente novamente...\n");
      }
    } else {
      printf("\033[31m| > Entrada invalida, Tente novamente...\n");
      clearBuffer();
    }
  } while (!isValid); // Repita o loop enquanto isValid for 0 (saldo inválido)

  int senhaCorrect;
  char senha[SENHA];
  do {
    senhaCorrect = 1;
    printf("| > Digite sua senha: ");
    fgets(senha, SENHA, stdin);

    senha[strcspn(senha, "\n")] = '\0'; // Remove o \n do final da string

    if (strlen(senha) < 6) {
      printf("\033[34m| > Senha muito fraca, tente novamente com pelo menos 6 "
             "caracteres...\n");
      senhaCorrect = 0; // Define senhaCorrect como 0 para repetir o loop
    } else if (strlen(senha) >= SENHA) {
      printf("\033[34m| > Tamanho máximo de senha excedido, por favor, tente "
             "novamente...\n");
      senhaCorrect = 0; // Define senhaCorrect como 0 para repetir o loop
    }
  } while (!senhaCorrect);
  strcpy(contas[*pos].senha, hash(senha));

  if(*user == -2){
    *user = *pos;
  }
  *pos = *pos + 1;

  return OK;
}

Value deletar_cliente(Conta contas[], int *pos, int *user) { // Função de Deletar um cliente
    char cpf_deletar[T_CPF];
    printf("| > Número do CPF da conta a ser deletada: ");
    fgets(cpf_deletar, T_CPF, stdin);
    cpf_deletar[strcspn(cpf_deletar, "\n")] = '\0';

    int cliente_encontrado = 0; // Flag para indicar se o cliente foi encontrado

    for (int i = 0; i < *pos; i++) {
        int comparacao = strcmp(cpf_deletar, contas[i].cpf);
        if (comparacao == 0) {
            // Move todos os clientes para cima na array para sobrescrever o cliente deletado
            for (int j = i; j < *pos - 1; j++) {
                strcpy(contas[j].cpf, contas[j + 1].cpf);
                strcpy(contas[j].nome, contas[j + 1].nome);
                strcpy(contas[j].senha, contas[j + 1].senha);
                contas[j].tipo_conta = contas[j + 1].tipo_conta;
                contas[j].Saldo = contas[j + 1].Saldo;
                memcpy(contas[j].extrato, contas[j + 1].extrato, T_EXTRATO * sizeof(Extrato));
            }
            printf("\033[32m| > Conta deletada com sucesso!!\n");
            (*pos)--;
            cliente_encontrado = 1; // Cliente encontrado
            break; // Saia do loop assim que o cliente for deletado
        }
    }

    if (!cliente_encontrado) {
        printf("| > Este número de CPF não existe em seu banco.\n");
        return NAO_ENCONTRADO; // Retorna um código de erro
    }

    return OK;
}



Value listar_cliente(Conta contas[], int *pos, int *user) { // Função de Listar Clientes
  if (*pos == 0) {
    return SEM_CONTAS;
  }
  for (int i = 0; i < *pos; i++) {
    printf("|===============================\n");
    printf("| > Nome: %s  \n", contas[i].nome);

    printf("| > CPF: %s  \n", contas[i].cpf);
    switch (contas[i].tipo_conta) {
    case 'c':
      printf("| > Tipo da conta: Comum\n");
      break;
    case 'p':
      printf("| > Tipo da conta: Plus\n");
    default:
      break;
    }
    printf("| > Saldo: %.2f \n", contas[i].Saldo);
  }
  return OK;
}

// Funções Bancárias
// Operações com valores monetários
Value debito(Conta contas[], int *pos, int *user) { // Função de debitar dinheiro de uma conta
  char cpf_origem[T_CPF];
  int posicao;
  float saldo_novo;
  int validacao = 0;
  if(*user == -1){
    do{
      printf("| > CPF: ");
      scanf("%s", cpf_origem);
      clearBuffer();
      posicao = findCPF(contas, *pos, cpf_origem);
      if(posicao == -1){
        printf("\033[34m| > CPF Não Encontrado, tente novamente...\n");
      }
      else{
        validacao = 1;
      }
    }while(!validacao);

  }else{
    posicao = *user;
    validacao = 1;
  }

  if(validacao ) {
      int Senha_Correta;
      float valor;
      int tipo_conta;
      float saldo_novo;
      do{
        Senha_Correta = auth_senha(contas, *pos, &posicao);
      }while(!Senha_Correta);
      printf("| > Valor a ser debitado: ");
      scanf("%f", &valor);
      clearBuffer();
      tipo_conta = contas[posicao].tipo_conta;
      if (tipo_conta == 1) {
        valor += (valor * 0.05);
        saldo_novo = contas[posicao].Saldo - valor;
        if (saldo_novo <= -1000) {
          printf("\033[33m| > Saldo insuficiente.");
        } else {
          contas[posicao].Saldo = saldo_novo;
          printf("\033[32m| > Débito realizado.\n");
          printf("\033[34m| > Saldo atual: %.3f\n", saldo_novo);
          } 
        } 
        else {
          valor += (valor * 0.03);
          saldo_novo = contas[posicao].Saldo - valor;
        if (saldo_novo <= -5000) {
          printf("|> Saldo insuficiente.");
        } else {
          contas[posicao].Saldo = saldo_novo;
          printf("\033[32m| > Débito realizado.\n");
          printf("\033[34m| > Saldo atual: %.3f\n", saldo_novo);
      }
    }
  }
  
  return OK;
}

Value deposito(Conta contas[], int *pos, int *user) { // essa eh a funcao de transferencia!!!!!!
  char cpf_origem[T_CPF];
  int posicao;
  int validacao = 0;
  if(*user == -1){
    do{
      printf("| > CPF: ");
      scanf("%s", cpf_origem);
      clearBuffer();
      posicao = findCPF(contas, *pos, cpf_origem);
      if(posicao == -1){
        printf("\033[34m| > CPF Não Encontrado, tente novamente...\n");
      }
      else{
        validacao = 1;
      }
    }while(!validacao);

  }else{
    posicao = *user;
    validacao = 1;
  }
  if(validacao ) {
      int Senha_Correta;
      float valor;
      float saldo_novo;
            do{
        Senha_Correta = auth_senha(contas, *pos, &posicao);
      }while(!Senha_Correta);
      printf("| > Valor a ser depositado: ");
      scanf("%f", &valor);
      clearBuffer();
      contas[posicao].Saldo += valor;
      printf("\033[32m| > Deposito realizado.\n");
      printf("\033[34m| > Saldo atual: %.3f\n", contas[posicao].Saldo);
  } 
  return OK;
}


Value extrato(Conta contas[], int *pos,int *user) { // Função de gerar extrato do cliente
  printf("extrado");
  return OK;
}
Value transacao(Conta contas[], int *pos,int *user) { // Função de realizar transacao entre contas
  float valor_deposito;
  char cpf_origem[T_CPF];
  char cpf_destino[T_CPF];
  int i;
  int posOrigem;
  int posDest;
  float saldo_novo;
  int validacao = 0;
  if(*user == -1){
    do{
      printf("| > CPF de Origem: ");
      scanf("%s", cpf_origem);
      clearBuffer();
      posOrigem = findCPF(contas, *pos, cpf_origem);
      if(posOrigem == -1){
        printf("\033[34m| > CPF Não Encontrado, tente novamente...\n");
      }
      else{
        validacao = 1;
      }
    }while(!validacao);
  }
  else{
    strcpy(cpf_origem, contas[*user].cpf);
    posOrigem = *user;
    validacao = 1;
  }

  int validacaoDestino = 0;
  if (validacao) {
      int Senha_Correta;
    do{
      printf("| > CPF de destino: ");
      scanf("%s", cpf_destino);
      clearBuffer();
      cpf_destino[strcspn(cpf_destino, "\n")] = '\0'; // Remove o \n do final do cpf informado;
      posDest = findCPF(contas, *pos, cpf_destino);
      
      if(posDest == -1){
        printf("\033[34m| > CPF Não Encontrado, tente novamente...\n");
      }
      else{
        do{
        Senha_Correta = auth_senha(contas, *pos, &posOrigem);
        }while(!Senha_Correta);
        
        printf("| > Valor do depósito: ");
        scanf("%f", &valor_deposito);
        clearBuffer();
        
        saldo_novo = contas[posOrigem].Saldo - valor_deposito;
        if (contas[posOrigem].tipo_conta == 1 && saldo_novo <= -1000) {
          printf("\034[33m| > Saldo insuficiente.\n");
        }
        else if (contas[posOrigem].tipo_conta == 2 && saldo_novo <= -5000) {
          printf("\034[33m| > Saldo insuficiente.\n");
        }
        else {
          contas[posOrigem].Saldo = saldo_novo;
          contas[posDest].Saldo += valor_deposito;
          printf("\033[32m| > Depósito concluído com sucesso.\n");
          printf("\033[34m| > Saldo atual: %.2f\n", saldo_novo);
        }
        validacaoDestino = 1;
        
      }
    }while(!validacaoDestino);
  }
  return OK;
}

// Funções auxiliares:
// Suporte
void tratarRes(Value err){
    if (err == MAX_CONTAS) {
        printf("\033[31m| ERRO - Máximo de contas atingido.\n");
    } else if (err == CRIAR) {
        printf("\033[31m| ERRO - Não foi possível criar o arquivo.\n");
    } else if (err == SEM_CONTAS) {
        printf("\033[31m| ERRO - Não existem contas salvas.\n");
    } else if (err == ABRIR) {
        printf("\033[31m| ERRO - Não foi possível abrir o arquivo.\n");
    } else if (err == FECHAR) {
        printf("\033[31m| ERRO - Não foi possível fechar o arquivo.\n");
    } else if (err == ESCREVER) {
        printf("\033[31m| ERRO - Não foi possível escrever em seu arquivo.\n");
    } else if (err == LER) {
        printf("\033[31m| ERRO - Não foi possível ler o seu arquivo.\n");
      else if (err == AUTENTICACAO) {
        printf("\033[31m| ERRO - Não foi possível autenticar os seus dados.\n");
      else if (err == ACESSO_INVALIDO) {
        printf("\033[31m| ERRO - Não foi possível validar o seu acesso.\n");
      else if (err == MAX_EXTRATO) {
        printf("\033[31m| ERRO - Tamanho do extrato excedido.\n");
    } else if (err == OK) {
        // Fazer nada em caso de sucesso 
    } 
    else{
        printf("\033[31m| ERRO - Erro de Sistema Desconhecido.\n");
    }
    
}

void clearBuffer() { // Função de Limpeza de Buffer
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
};

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




int findCPF(Conta contas[], int pos, const char *cpf) {
  for (int i = 0; i < pos; i++) {
    if (strcmp(cpf, contas[i].cpf) == 0) {
      return i; // Retorna o índice da conta quando o CPF for encontrado
    }
  }
  return -1; // Retorna -1 se o CPF não for encontrado
}

Value saveExtrato(Conta contas[], int *user, int tipo, float valor) {
  if (contas[*user].extrato_size >= T_EXTRATO) { // Verifica o limite do Extrato
      return MAX_EXTRATO;
  }

  time_t data = time(NULL); // Salva a data de agora

  Extrato nova_operacao; // Cria uma operação com os valores recebidos
  nova_operacao.tipo = tipo;
  nova_operacao.valor = valor;
  nova_operacao.data = data;
  
  // Adiciona a nova operação ao extrato
  contas[*user].extrato[contas[*user].extrato_size] = nova_operacao;
  contas[*user].extrato_size++;
  return OK;
}


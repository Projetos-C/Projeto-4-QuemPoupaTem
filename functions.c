#include "functions.h"

// >>> Funções ADM:
// Relacionadas a controle de Clientes
Value novo_cliente(Conta contas[], int *pos, int *user) { // Função de Criar um novo cliente
  if (*pos >= TOTAL) {
    return MAX_CONTAS;
  }
  if (*user != -1 && *user != -2) {
    return ACESSO_INVALIDO;
  }
  printf("| > Nome do Usuario: ");
  fgets(contas[*pos].nome, T_NOME, stdin);
  contas[*pos].nome[strcspn(contas[*pos].nome, "\n")] = '\0';

  int cpf_correto = 1;
  int cont = 0;
  char cpf[T_CPF];
  do {
    cpf_correto = 1;
    printf("| > CPF (Ex: 112345678900): ");
    scanf("%s", cpf);
    clearBuffer();
    // Remove o \n do final do cpf informado;
    if (strlen(cpf) > 11 &&
        strlen(cpf) < 11) { // Verifica se o tamanho do cpf é válido
      cpf_correto = 0;
    }
    if (cpf_correto) {
      for (int i = 0; cpf[i] != '\0';
           i++) { // Verifica se não há nenhum char não cpférico no número
                  // informado;
        if (!isdigit(cpf[i]) && cpf[i] != '\0') {
          cpf_correto = 0;
          break;
        }
      }
    }
    else {
      printf("\033[34m| > CPF Inválido, tente novamente...\n");
      cpf[0] = '\0';
    }

    if(findCPF(contas, *pos, cpf) != -1){
      printf("\033[34m| > CPF já em Uso, tente novamente...\n");
      cpf[0] = '\0';
    }
  } while (!cpf_correto);
  strcpy(contas[*pos].cpf, cpf);
  contas[*pos].cpf[strcspn(contas[*pos].cpf, "\n")] = '\0';

  char tipo_conta;
  int is_valid_type = 0;

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
      is_valid_type = 1;
    } else {
      printf("\033[31m| > Tipo de conta invalido, Tente novamente...\n");
    }
  } while (!is_valid_type);

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

  int senha_correta;
  char senha[SENHA];
  do {
    senha_correta = 1;
    printf("| > Digite sua senha: ");
    fgets(senha, SENHA, stdin);

    senha[strcspn(senha, "\n")] = '\0'; // Remove o \n do final da string

    if (strlen(senha) < 6) {
      printf("\033[34m| > Senha muito fraca, tente novamente com pelo menos 6 "
             "caracteres...\n");
      senha_correta = 0; // Define senha_correta como 0 para repetir o loop
    } else if (strlen(senha) >= SENHA) {
      printf("\033[34m| > Tamanho máximo de senha excedido, por favor, tente "
             "novamente...\n");
      senha_correta = 0; // Define senha_correta como 0 para repetir o loop
    }
  } while (!senha_correta);
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

  float valor;
  if(validacao ) {
      int senha_correta;
      int tipo_conta;
      float valor_taxa;
      float saldo_novo;
      do{
        senha_correta = auth_senha(contas, *pos, &posicao);
      }while(!senha_correta);
      printf("| > Valor a ser debitado: ");
      scanf("%f", &valor);
      clearBuffer();
      tipo_conta = contas[posicao].tipo_conta;
      if (tipo_conta == 1) {
        valor_taxa = valor * 0.05;
        saldo_novo = contas[posicao].Saldo - valor_taxa;
        if (saldo_novo <= -1000) {
          printf("\033[33m| > Saldo insuficiente.");
        } else {
          contas[posicao].Saldo = saldo_novo;
          printf("\033[32m| > Débito realizado.\n");
          printf("\033[34m| > Saldo atual: R$ %.2f\n", saldo_novo);
          } 
        } 
        else {
        valor_taxa = valor * 0.03;
        saldo_novo = contas[posicao].Saldo - valor_taxa;
        if (saldo_novo <= -5000) {
          printf("|> Saldo insuficiente.");
        } else {
          contas[posicao].Saldo = saldo_novo;
          printf("\033[32m| > Débito realizado.\n");
          printf("\033[34m| > Saldo atual: R$ %.2f\n", saldo_novo);
      }
    }
  }

  saveExtrato(contas, &*user, 2, valor);
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
  float valor;
  if(validacao ) {
      int senha_correta;
      float saldo_novo;
            do{
        senha_correta = auth_senha(contas, *pos, &posicao);
      }while(!senha_correta);
      printf("| > Valor a ser depositado: ");
      scanf("%f", &valor);
      clearBuffer();
      contas[posicao].Saldo += valor;
      printf("\033[32m| > Deposito realizado.\n");
      printf("\033[34m| > Saldo atual: R$ %.2f\n", contas[posicao].Saldo);
  } 
  saveExtrato(contas, &*user, 1, valor);

  return OK;

}

Value transacao(Conta contas[], int *pos,int *user) { // Função de realizar transacao entre contas
  float valor;
  char cpf_origem[T_CPF];
  char cpf_destino[T_CPF];
  int i;
  int pos_origem;
  int pos_dest;
  float saldo_novo;
  int validacao = 0;
  if(*user == -1){
    do{
      printf("| > CPF de Origem: ");
      scanf("%s", cpf_origem);
      clearBuffer();
      pos_origem = findCPF(contas, *pos, cpf_origem);
      if(pos_origem == -1){
        printf("\033[34m| > CPF Não Encontrado, tente novamente...\n");
      }
      else{
        validacao = 1;
      }
    }while(!validacao);
  }
  else{
    strcpy(cpf_origem, contas[*user].cpf);
    pos_origem = *user;
    validacao = 1;
  }

  int validacaoDestino = 0;
  if (validacao) {
      int senha_correta;
    do{
      printf("| > CPF de destino: ");
      scanf("%s", cpf_destino);
      clearBuffer();
      cpf_destino[strcspn(cpf_destino, "\n")] = '\0'; // Remove o \n do final do cpf informado;
      pos_dest = findCPF(contas, *pos, cpf_destino);
      
      if(pos_dest == -1 || strcmp(cpf_destino, cpf_origem) == 0){
        printf("\033[34m| > CPF Inválido, tente novamente...\n");
      }
      else{
        do{
        senha_correta = auth_senha(contas, *pos, &pos_origem);
        }while(!senha_correta);
        
        printf("| > Valor do depósito: ");
        scanf("%f", &valor);
        clearBuffer();
        
        saldo_novo = contas[pos_origem].Saldo - valor;
        if (contas[pos_origem].tipo_conta == 1 && saldo_novo <= -1000) {
          printf("\034[33m| > Saldo insuficiente.\n");
        }
        else if (contas[pos_origem].tipo_conta == 2 && saldo_novo <= -5000) {
          printf("\034[33m| > Saldo insuficiente.\n");
        }
        else {
          contas[pos_origem].Saldo = saldo_novo;
          contas[pos_dest].Saldo += valor;
          printf("\033[32m| > Depósito concluído com sucesso.\n");
          printf("\033[34m| > Saldo atual: R$ %.2f\n", saldo_novo);
        }
        validacaoDestino = 1;
        
      }
    }while(!validacaoDestino);
  } 
  saveExtrato(contas, &pos_origem, 4, valor);
  saveExtrato(contas, &pos_dest, 3, valor);
  return OK;
}

Value extrato(Conta contas[], int *pos, int *user) { // Função de gerar extrato do cliente
  if (*pos == 0) {
    return SEM_CONTAS;
  }

  char cpf_origem[T_CPF];
  int posicao;
  float saldo_novo;
  int validacao = 0;
  int senha_correta;
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
  }
  else{
    posicao = *user;
  }
  do{
    senha_correta = auth_senha(contas, *pos, &*user);
    }while(!senha_correta);
  
  if(contas[posicao].extrato_size == 0){
    return SEM_EXTRATOS;
  }


  Extrato* extrato = contas[posicao].extrato;
  int size = contas[posicao].extrato_size;
  char* tipo;
  for (int i = 0; i < size; i++) {
    printf("|===============================\n");
    const char* tipo_operacao;
    switch (extrato[i].tipo) {
      case 1: tipo_operacao = "Deposito              "; break;
      case 2: tipo_operacao = "Débito                "; break;
      case 3: tipo_operacao = "Transferência Recebida"; break;
      case 4: tipo_operacao = "Transferência Paga    "; break;
      default: tipo_operacao = "Desconhecido         "; break;
    }

    printf("| > Operação: %s\n", tipo_operacao);

    printf("| > Valor: R$%.2f  \n", extrato[i].valor);

    if(extrato[i].tipo == 2){
      if(contas[posicao].tipo_conta == 1){
        printf("| > Tarifa: R$%.2f\n", extrato[i].valor * 0.05);
        printf("|===============================\n");
      }
      else{
        printf("| > Tarifa: R$%.2f\n", extrato[i].valor * 0.03);
        printf("|===============================\n");
      }
    }
    else{
      printf("| > Tarifa: R$0,00\n");
      printf("|===============================\n");
    }
    
    struct tm* tm_info;
    char buffer[26];
    tm_info = localtime(&extrato[i].data);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    
  }
  char opc;
  printf("| > Deseja Salvar Extrato em um Arquivo? (y/n) ");
  scanf("%c", &opc);
  if(opc == 'y'){
    char file_name[100];
    printf("| > Nome do Arquivo: ");
    scanf("%99s", file_name);  
    gerar_arquivo_texto(contas, posicao, file_name);
  }

  return OK;

}


// Funções auxiliares:
// Suporte

void clearBuffer() { // Função de Limpeza de Buffer
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
};

Value saveExtrato(Conta contas[], int *user, int tipo, float valor) {
  time_t data_utc = time(NULL); // Salva a data de agora em UTC
  struct tm *data_local = localtime(&data_utc);
  data_local->tm_hour -= 3;
  mktime(data_local);
  mover_extrato(contas, &*user); // Verifica se precisa mover o extrato
  
  Extrato nova_operacao; // Cria uma operação com os valores recebidos
  nova_operacao.tipo = tipo;
  nova_operacao.valor = valor;
  nova_operacao.data = mktime(data_local);
  
  // Adiciona a nova operação ao extrato
  contas[*user].extrato[contas[*user].extrato_size] = nova_operacao;
  contas[*user].extrato_size++;
  return OK;
}


Value mover_extrato(Conta contas[], int *user) {
    if (contas[*user].extrato_size >= T_EXTRATO) {
        // Remover o primeiro extrato e mover todos os outros uma posição para cima
        for (int i = 1; i < contas[*user].extrato_size; i++) {
            contas[*user].extrato[i - 1] = contas[*user].extrato[i];
        }
        // Decrementar o tamanho do extrato
        contas[*user].extrato_size--;
    }
    return OK;
}
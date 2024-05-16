#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"





// >>> Funções ADM:
// Relacionadas a controle de Clientes
Value novo_cliente(Conta contas[], int *pos, int *user){  // Função de Criar um novo cliente
    if(*pos >= TOTAL){
        return MAX_CONTA;
    }
    if(*user != -1 && *user != -2){
        return ACESSO_INVALIDO;
    }
    printf("| > Nome do Usuario: ");
    fgets(contas[*pos].nome, T_NOME, stdin);
    contas[*pos].nome[strcspn(contas[*pos].nome, "\n")] = '\0';


    int cpfCorrect = 1;
    int cont = 0;
    char cpf[T_CPF];
    do{
        cpfCorrect = 1;
        printf("| > CPF (Ex: 112345678900): ");
        fgets(cpf, T_CPF, stdin);

        cpf[strcspn(cpf, "\n")] = '\0'; // Remove o \n do final do cpf informado;
        if(strlen(cpf) > 11 && strlen(cpf) < 11){ // Verifica se o tamanho do cpf é válido
            cpfCorrect = 0;
        }
        if(cpfCorrect){
            for (int i = 0; cpf[i] != '\0'; i++) { // Verifica se não há nenhum char não cpférico no número informado;
                if (!isdigit(cpf[i]) && cpf[i] != '\0') {
                    cpfCorrect = 0;
                    break;
                }
            }
        }

        else{
            printf("\033[34m| > CPF Inválido, tente novamente...\n");
            cpf[0] = '\0';
        }
    }while(!cpfCorrect);
    strcpy(contas[*pos].cpf, cpf);
    contas[*pos].cpf[strcspn(contas[*pos].cpf, "\n")] = '\0';



    char tipo_conta;
    int isValidType = 0;

    printf("| > Tipo conta:\n");
    printf("| -- Comum (c):\n");
    printf("|   - Taxa de 5%% no debito\n");
    printf("|   - Limite de saldo negativo de R$1.000\n");
    printf("| -- Plus (p):\n");
    printf("|   - Taxa de 3%% no debito\n");
    printf("|   - Limite de saldo negativo de R$5.000\n");

    do {
        printf("\033[34m| > Escolha o tipo de conta (p/c): ");
        scanf(" %c", &tipo_conta); // Adicionando um espaço antes de %c para ignorar espaços em branco
        clearBuffer();
        
        if (tipo_conta == 'c' || tipo_conta == 'p') {
            contas[*pos].tipo_conta = tipo_conta;
            isValidType = 1;
        } else {
            printf("\033[31m| > Tipo de conta invalido, Tente novamente...\n");
        }
    } while (!isValidType);

    


    float saldo;
    int isValid = 0; // Inicialize isValid como 0 para que o loop execute pelo menos uma vez

    do {
        printf("\033[34m| > Informe o saldo da conta: ");
        if (scanf("%f", &saldo) == 1) {
            clearBuffer();
            if (saldo >= 0) {
                printf("\033[32m| > Saldo valido!\n");
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
            printf("\033[34m| > Senha muito fraca, tente novamente com pelo menos 6 caracteres...\n");
            senhaCorrect = 0; // Define senhaCorrect como 0 para repetir o loop
        } else if (strlen(senha) >= SENHA) {
            printf("\033[34m| > Tamanho máximo de senha excedido, por favor, tente novamente...\n");
            senhaCorrect = 0; // Define senhaCorrect como 0 para repetir o loop
        }
    } while (!senhaCorrect);
    contas[*pos].senha = hash(senha);
    *user = *pos;
    *pos = *pos + 1;

    return OK;
}

Value deletar_cliente(Conta contas[], int *pos, int *user) {  // Função de Deletar um cliente
     printf("delete");
     return OK;
}
Value listar_cliente(Conta contas[], int *pos, int *user) {  // Função de Listar Clientes
    printf("%d posições", *pos);
    if (*pos == 0) {
        return SEM_CONTAS;
    }
    for (int i = 0; i < *pos; i++) {

        printf("|===============================\n");
        printf("| > Nome: %s  \n", contas[i].nome);
        
        printf("| > CPF: %s  \n", contas[i].cpf);
        switch (contas[i].tipo_conta)
        {
        case 'c':
          printf("| > Tipo da conta: Comum");
          break;
        case 'p':
          printf("| > Tipo da conta: Plus");
        default:
          break;
        }
    }
    return OK;
}


// Funções Bancárias
// Operações com valores monetários
Value debito(Conta contas[], int *pos, int *user){   // Função de debitar dinheiro de uma conta
     printf("debito");
     return OK;
}        
Value deposito(Conta contas[], int *pos, int *user){ // Função de depositar um valor em uma conta
     printf("deposito");
     return OK;
}       
Value extrato(Conta contas[], int *pos, int *user){  // Função de gerar extrato do cliente
     printf("extrado");
     return OK;
}    
Value transacao(Conta contas[], int *pos, int *user) {  // Função de realizar transacao entre contas
     printf("transacao");
     return OK;
}    


// Funções auxiliares:
// Suporte
void tratarRes(Value err) {}; // Tratamento de Erros das funções de tipo Value

void clearBuffer(){ // Função de Limpeza de Buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};


// Funções de Arquivo:
// Manipulação do Arquivo binário
Value salvar(Conta contas[], int *pos){  // Função de Salvar a lista de contatos no arquivo binário
   FILE *arq = fopen("contas.bin", "wb");
    if(arq == NULL)
        return ABRIR;
    
    int qtd = fwrite(contas, TOTAL, sizeof(Conta), arq);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), arq);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(arq))
        return FECHAR;

    printf("\033[32m| > Arquivo Salvo!!\n");
    return OK;
}           
Value carregar(Conta contatos[], int *pos){ // Função de Carregar a lista de contatos do arquivo binário 
    FILE *f = fopen("contas.bin", "rb");
    if(f == NULL)
    return ABRIR;

    int qtd = fread(contatos, TOTAL, sizeof(Conta), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
       return LER;

    if(fclose(f))
        return FECHAR;

    printf("\033[32m| > Contas carregados!!\n");
    return OK;

}        

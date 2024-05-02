#define TOTAL 1000
#define T_NOME 300
#define T_CPF 11 
#define SENHA 100


typedef struct {
    char nome[T_NOME];
    char cpf[T_CPF];
    int tipo_conta;
    float Saldo;
    char senha[SENHA];

} Conta;

typedef enum {OK, MAX_CONTAS, SEM_CONTAS, ABRIR, FECHAR, ESCREVER, LER, CRIAR} Value;

typedef Value (*func)(Conta[], int*);
Value novo_cliente(Conta contatos[], int *pos);     // Função de Criar um novo cliente
Value deletar_cliente(Conta contatos[], int *pos);   // Função de Deletar um cliente
Value listar_cliente(Conta contatos[], int *pos);    // Função de Listar os clientes
Value debito(Conta contatos[], int *pos);    // Função de debitar dinheiro de uma conta
Value deposito(Conta contatos[], int *pos);  // Função de depositar um valor em uma conta
Value extrato(Conta contatos[], int *pos); // Função de gerar extrato do cliente
Value transacao(Conta contatos[], int *pos); // Função de realizar transacao entre contas

void clearBuffer(); // Função de Limpeza de Buffer
void tratarRes(Value err); // Tratamento de Erros das funções de tipo Value

// \033[0m -> Cor Padrão de texto
// \033[34m -> Cor azul  - Utilizado no menu
// \033[32m -> Cor Verde - Utilizado para mensagens de sucesso de funções
// \033[31m -> Cor Vermelha - Utilizado para mensagens de erro
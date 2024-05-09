#define TOTAL 1000
#define T_NOME 100
#define T_CPF 12 
#define SENHA 100
#define T_EXTRATO 100

typedef struct {
    int tipo; // 1 = Deposito / 2 = Débito / 3 = Transferência Receber / 4 = Trasnferência Pagar
    int data;
    float valor;

} Extrato;

typedef struct {
    char cpf[T_CPF];
    char nome[T_NOME];
    char senha[SENHA];
    int tipo_conta; // 1 = Comum / 2 = Plus
    Extrato extrato[T_EXTRATO]; 
    float Saldo;
} Conta;

typedef enum { OK, ABRIR, FECHAR, ESCREVER, LER, CRIAR, MAX_CONTATO, SEM_CONTATO, AUTENTICACAO } Value;

typedef Value (*func)(Conta[], int*);

Value novo_cliente(Conta contas[], int *pos, int *user){};     // Função de Criar um novo cliente
Value deletar_cliente(Conta contas[], int *pos, int *user) {}; // Função de Deletar um cliente
Value listar_cliente(Conta contas[], int *pos, int *user) {};  // Função de Listar os clientes
Value debito(Conta contas[], int *pos, int *user) {};          // Função de debitar dinheiro de uma conta
Value deposito(Conta contas[], int *pos, int *user) {};        // Função de depositar um valor em uma conta
Value extrato(Conta contas[], int *pos, int *user) {};         // Função de gerar extrato do cliente
Value transacao(Conta contas[], int *pos, int *user) {};       // Função de realizar transacao entre contas
Value salvar(Conta contas[], int *pos, int *user);             // Função de Salvar a lista de contatos no arquivo binário
Value carregar(Conta contas[], int *pos, int *user);           // Função de Carregar a lista de contatos do arquivo binário
Value hash(char senha[], int *pos);
Value hash_compare(char hash[], char senha[], int *pos);

//Funções auxiliares

int menu_login(Conta contas[], int *pos);   // Menu de Login
void menu_adm(Conta contas[], int *pos);            // Menu de Administrador
void menu_usuario(Conta contas[], int *pos);        // Menu de Usuário
void clear_buffer();        // Limpeza de Buffer
void tratarRes(Value err);  // Tratamento de Erros
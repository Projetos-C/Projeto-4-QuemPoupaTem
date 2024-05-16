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

typedef struct { // Estrutura das contas
    char cpf[T_CPF];
    char nome[T_NOME];
    const char* senha;
    int tipo_conta; // 1 = Comum / 2 = Plus
    Extrato extrato[T_EXTRATO]; 
    float Saldo;
} Conta;

typedef enum { OK, ABRIR, FECHAR, ESCREVER, LER, CRIAR, MAX_CONTA, SEM_CONTAS, AUTENTICACAO, ACESSO_INVALIDO } Value; // Tipoes de respostas em funções

typedef int (*menu)(); // Forma simplificada de chamar funções do tipo menu
typedef Value (*func)(Conta[], int*, int*); // Forma simplificada de chamar as funções principais
typedef Value (*arc)(Conta[], int*); // Forma simplificada de chamar funções relacionada ao tratamento de arquivos


// Clientes 
Value novo_cliente(Conta contas[], int *pos, int *user);    // Função de Criar um novo cliente
Value deletar_cliente(Conta contas[], int *pos, int *user); // Função de Deletar um cliente
Value listar_cliente(Conta contas[], int *pos, int *user);  // Função de Listar os clientes


// Operações Bancárias
Value debito(Conta contas[], int *pos, int *user);          // Função de debitar dinheiro de uma conta
Value deposito(Conta contas[], int *pos, int *user);        // Função de depositar um valor em uma conta
Value extrato(Conta contas[], int *pos, int *user);         // Função de gerar extrato do cliente
Value transacao(Conta contas[], int *pos, int *user);       // Função de realizar transacao entre contas


// Arquivo
Value salvar(Conta contas[], int *pos);                     // Função de Salvar a lista de contatos no arquivo binário
Value carregar(Conta contas[], int *pos);                   // Função de Carregar a lista de contatos do arquivo binário


// Menus 
int menu_login();      // Menu de Login
int menu_adm();        // Menu de Administrador
int menu_user();       // Menu de Usuário Comum


// Funções de Autenticação
Value login(Conta contas[], int *pos, int *user); 

char* hash(const char* senha); // Cria um hash da senha
int compareHash(const char* senha, const char* hash);  // Verifica uma senha e um hash


//Funções auxiliares
void clearBuffer();        // Limpeza de Buffer
void tratarRes(Value err);  // Tratamento de Erros
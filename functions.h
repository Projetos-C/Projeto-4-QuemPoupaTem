#define TOTAL 1000
#define T_NOME 100
#define T_CPF 12 
#define SENHA 100
#define T_EXTRATO 100

typedef struct {
    int tipo; // 1 = Deposito / 2 = Débito / 3 = Transferência Receber / 4 = Trasnferência Pagar
    int data;
    float valor;

} Extrato

typedef struct {
    char cpf[T_CPF];
    char nome[T_NOME];
    char senha[SENHA];
    int tipo_conta; // 1 = Comum / 2 = Plus
    Extrato extrato[T_EXTRATO]; 
    float Saldo;
} Conta;
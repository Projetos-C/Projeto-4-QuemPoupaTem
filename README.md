# *Projeto 4* (Ciência da computação | 2º ciclo) - 2024
## Banco Quem Poupa Tem ##
Quem Poupa Tem é um sistema bancário desenvolvido em linguagem C pelos alunos de Desenvolvimento de Algoritmos da FEI. E possui funcionalidades voltadas tanto para administradores quanto para usuários. O projeto oferece uma série de operações bancárias, como débito, depósito, transferência e geração de extratos em arquivos de texto. Além disso, o sistema implementa criptografia de senhas para garantir maior segurança aos usuários.
## Funcionalidades ##
### Funções do administrador: ###
1. Cadastrar novos clientes | Permite que o administrador adicione novos clientes ao sistema.
2. Deletar clientes | Permite que o administrador remova clientes do sistema.
3. Listagem de Clientes | Exibe uma lista de todos os clientes cadastrados no sistema de forma organizada e eficiente.

### Funções do usuário ###
1. Débito | Permite que o usuário debite dinheiro de sua conta, aplicando taxas específicas de acordo com o tipo de conta.
2. Depósito | Permite que o usuário deposite dinheiro em sua conta.
3. Transferência | Permite a transferência de dinheiro entre contas.
4. Extrato | Gera e exibe o extrato de transações do usuário.

## Estrutura do programa ##
![image](https://github.com/Projetos-C/Projeto-4-QuemPoupaTem/assets/141969539/7f707a46-dfef-4009-8401-5f87370b9840)

## Segurança ##
Por se tratar de um banco, as senhas dos usuários são criptografadas visando a segurança das informações. O projeto utiliza uma função de hash para armazenar as senhas de forma segura. 

## Acesso de administrador ##
Atualmente, o programa possui um administrador único com credenciais específicas. Para acessar o banco como Administrador, siga os seguintes passos:

1. Executar o Programa: Inicie o programa compilado.
2. Selecionar Função de Login: Escolha a opção de login no menu.
3. Inserir Credenciais: <br> <br>
**Login:** Digite Admin ou admin. <br>
**Senha:** Digite Admin24. <br><br>

Após inserir essas credenciais, você estará logado como administrador e terá acesso a todas as funcionalidades do programa.

## Como compilar e rodar o código ##

Para rodar esta sistema de banco em seu computador, será necessario a instalação do [GCC](https://gcc.gnu.org/install/index.html) *(GNU Compiler Collection)* para compilar o seu código, que irá criar um executável responsável pelo funcionamento do programa. <br> <br>
Com o GCC instalado, basta colar o seguinte comando em seu terminal:<br><br>
`gcc *.c -o quem-poupa-tem` <br> <br>

Com o executável já criado, basta colar o seguinte comando em seu terminal: <br><br>
`./quem-poupa-tem`

E assim, você terá acesso ao banco **Quem Poupa Tem**, faça bom proveito! <br><br>


**Integrantes:**
- Arthur Leal Mussio - 22.223.017-9
- Artur Chaves Paiva - 22.223.023-7
- Giovanni Antonio Moreira - 22.223.010-4



https://excalidraw.com/#json=SCOnKm4TAslswQYAzXkVZ,zltjQTQynkcTP9g95Y0JsQ

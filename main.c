#include <stdio.h>
#include "functions.h"



int main(){

    func functions[] = {novo_cliente, deletar_cliente, listar_cliente, debito, deposito, extrato, transacao};




    Conta contas[TOTAL];
    int pos = 0;

    //------------------TRATAMENTO DE ERROS-------------------//

    //---------------------------------------------------------//

    int opcao;   

    do{
        printf("\n\033[34m|==============================|\n");
        printf("|- - - - Quem Poupa Tem - - - -|\n");
        printf("| 1 - Novo Cliente             |\n");
        printf("| 2 - Deletar Cliente          |\n");
        printf("| 3 - Listar Cliente           |\n");
        printf("| 4 - Debito                   |\n");
        printf("| 5 - Deposito                 |\n");
        printf("| 6 - Extrato                  |\n");
        printf("| 7 - Transacao                |\n");
        printf("| 0 - Sair                     |\n");
        printf("|==============================|\n");
        printf("| > Escolha uma opcao: ");
        scanf("%d", &opcao);
        clearBuffer();

 opcao--;
        if(opcao <= 6 && opcao >= 0 ){ // Condição para quando o usuário utilizar uma função
            Value erro = functions[opcao](contas, &pos); // Chama a Função Respectiva a opção escolhida
            tratarRes(erro); // Tratamento do Erro recebido da função;
            printf("\033[34m| Pressione Enter para continuar |\n");
            printf("| ============================== |\n");
            clearBuffer();
        }
        else if(opcao == -1){ // Condição para o usuário sair
            
            printf("| > Deseja Salvar Alterações? (y/n). "); // Pergunta se o usuário deseja salvar o arquivo antes de encerrar
            char Opc;
            scanf("%c", &Opc);
            clearBuffer();

            if(Opc == 'y'){ // Caso Queira Salvar as Alterações
                Value res = functions[3](contas, &pos); // Salva o Arquivo Binário Antes de Encerrar
                tratarRes(res); // Tratamento do valor recebido da função;
                if(res == OK){ // Salvar funcionou corretamente, encerrando normalmente
                    printf("\033[34m| > Encerrando...\n");
                }
                else{ // Função Salvar apresentou algum erro, pergunta ao usuário se deseja sair assim mesmo ou se deseja voltar para o menu
                    do{ 
                        printf("\033[34m| > Encerrar assim mesmo? o arquivo não foi salvo (y/n). ");
                        scanf("%c", &Opc);
                        clearBuffer();
                        if(Opc == 'n'){ // Cancela o encerramento, Retorna para o menu.
                            printf("| > Retornando para menu...\n");
                            opcao = 1;
                        }
                        else if(Opc == 'y'){ // Encerra o programa sem salvar mesmo.
                            printf("| > Encerrando...\n");
                        }
                        else{
                            printf("| > Opção Inválida, tente novamente...");
                        }
                    }while(Opc != 'n' && Opc != 'y' ); // Repete o processo se o usuário digitar uma opção inválida
                }
            }
            else if(Opc == 'n'){ // Apenas encerra o programa sem salvar alterações
                    printf("| > Encerrando...\n");
            }
            else{ // Retorna para o menu se o usuário digitar uma opção inválida
                printf("| > Opção inválida, Retornando para menu...\n");
                opcao = 1;
            }
        }
        else{ // Condição caso o usuário escolha uma opção inválida
            printf("| > Opcao inválida, Tente Novamente...\n");
        }
            
    } while(opcao != -1);
}

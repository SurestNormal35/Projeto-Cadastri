#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

//estrutura do cadastro
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Cadastro
{
    int ocupado;
    char nome[128];
    char origem[128], saida;
    int quantidade;
    time_t data;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//inicializa os cadastros
struct Cadastro cadastro[99];



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//declaração de variaveis globais
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////variavel pro switch case
    int escolha;

    //usar para todos os prompts de sim ou nao
    char sim_nao[10];
    int verificador;
    int continuar = 1;

    //usado para ser o contador do for
    int i;

    //variaveis temporarias para guardar dados no instante em que sao digitados
    char nome[128];
    char origem[128];
    int quantidade;
    int ocupado = 0;
    time_t data;

    //pra achar um espaço livre la no cadastro
    int achou;

    //número total de espaços ocupados
    int total_cadastrados = 0;

    //pra converter o número que representa a data em uma string
    int data_lida;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//declaração de funções
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//inicializa o arquvio de cadastro
void inicializar_arquivo_cadastro()
{
    //tenta abrir o arquivo só pra ver se ele existe
    FILE *caminho_arquivo_pessoas = fopen("cadastro.txt", "r");

    //não conseguiu, cria um
    if(caminho_arquivo_pessoas == NULL)
    {
        caminho_arquivo_pessoas = fopen("cadastro.txt","w");

        if(caminho_arquivo_pessoas == NULL)
        {
            printf("Erro ao criar arquivo!");
            exit(EXIT_FAILURE);
        }
        else
        {
            //primeira linha do cadastro sempre será o número de pessoas cadastradas
            fprintf(caminho_arquivo_pessoas, "%d\n", total_cadastrados);

            fclose(caminho_arquivo_pessoas);
        }

    }
    else
    {
        //fecha o arquivo
        fclose(caminho_arquivo_pessoas);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//lê dados salvos
void carregar_dados_salvos()
{
    //tenta abrir
    FILE *caminho_arquivo_pessoas = fopen("cadastro.txt", "r");

    //se n abrir mostra erro
    if(caminho_arquivo_pessoas == NULL)
    {
        printf("Erro ao abrir arquivo!");
        exit(EXIT_FAILURE);
    }
    else
    {
        //lê os dados do arquivo e os armazena no cadastro
        fscanf(caminho_arquivo_pessoas, "%d\n",&total_cadastrados);

        for(i=0;i<total_cadastrados;i++)
        {
            fscanf(caminho_arquivo_pessoas, " %127[^\n]", &cadastro[i].nome);
            fscanf(caminho_arquivo_pessoas, " %127[^\n]", &cadastro[i].origem);
            fscanf(caminho_arquivo_pessoas, "%d", &cadastro[i].quantidade);
            fscanf(caminho_arquivo_pessoas, "%d", &data_lida);

            cadastro[i].data = data_lida;

            cadastro[i].ocupado = 1;
        }
    }

    //fecha o arquivo
    fclose(caminho_arquivo_pessoas);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//salva os dados do programa
void salvar_dados()
{
    //tenta abrir
    FILE *caminho_arquivo_pessoas = fopen("cadastro.txt", "w");

    //erro se n abrir
    if(caminho_arquivo_pessoas == NULL)
    {
        printf("Erro ao salvar dados!");
        exit(EXIT_FAILURE);
    }
    else
    {
        //verifica o total de cadastros no total
        total_cadastrados = 0;

        for(i=0;i<99;i++)
        {
            if(cadastro[i].ocupado == 1)
            {
                total_cadastrados++;
            }
        }


        //salva os dados do cadastro no arquivo
        fprintf(caminho_arquivo_pessoas, "%d\n", total_cadastrados);

        for(i=0;i<99;i++)
        {
            if(cadastro[i].ocupado == 1)
            {
                fprintf(caminho_arquivo_pessoas, "%s\n", cadastro[i].nome);
                fprintf(caminho_arquivo_pessoas, "%s\n", cadastro[i].origem);
                fprintf(caminho_arquivo_pessoas, "%d\n", cadastro[i].quantidade);
                fprintf(caminho_arquivo_pessoas, "%d\n", cadastro[i].data);
            }

        }

    }

    //fecha o arquivo
    fclose(caminho_arquivo_pessoas);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//limpa lixo de memória
void limpa_lixo()
{
    //quando o programa inicializa, as variaveis ficam com lixo de memória
    //essa função troca o lixo de memória por 0 (desocupado)
    //para depois, na hora de ler os dados, carregar certinho
    for(i=0;i<99;i++)
    {
        cadastro[i].ocupado = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//menu principal
void tela_principal()
{
        printf("\nFERRAMENTA CONTROLE DE DOAÇÕES\n");

        printf("\n-----MENU-----\n");
        printf("1.Cadastro de produtos");
        printf("\n2.Estoque de produtos");
        printf("\n3.Sair\n");
        scanf("%d", &escolha);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//tela do cadastro depois que escolhe case 1 do switch
void tela_cadastro_opcoes()
{
    do
    {
        verificador = 1;

        system("cls");
        printf("\n-----MENU DE CADASTRO-----\n");
        printf("1. Cadastrar um produto");
        printf("\n2. Remover um produto");
        printf("\n3. Voltar\n");
        scanf("%d", &escolha);

        if(escolha==1)
        {
            verificador = 0;
        }
        if(escolha==3)
        {
            verificador=0;
            system("cls");
        }

    }while(verificador==1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//tela para cadastro
void tela_cadastro_cadastrar()
{
    if(escolha == 1)
    {
                    do
                    {
                        //roda todos os espaços até achar um livre
                        for(i=0;i<99;i++)
                        {
                            if(cadastro[i].ocupado==0)
                            {
                                achou = i;
                                break;
                            }
                        }
                        if(i==99)
                        {
                            printf("Estoque cheio!");
                        }
                        else
                        {
                            system("cls");
                            verificador = 1;
                            continuar = 1;

                            printf("Digite o nome do produto: ");
                            scanf(" %127[^\n]", nome);

                            printf("Digite a origem do produto: ");
                            scanf(" %127[^\n]", origem);

                            do
                            {
                                verificador = 1;

                                printf("Digite a quantidade de unidades do produto: ");
                                scanf("%d",&quantidade);

                                if(quantidade < 1)
                                {
                                    printf("Número inválido!");
                                    printf("\nDigite apenas numeros positivos\n");
                                }
                                else
                                {
                                    verificador = 0;
                                }

                            }while(verificador == 1);

                            //copia os dados das variaveis temporarias para o cadastro
                            strcpy(cadastro[achou].nome, nome);
                            strcpy(cadastro[achou].origem, origem);
                            cadastro[achou].quantidade = quantidade;
                            time(&cadastro[achou].data);
                            cadastro[achou].ocupado = 1;

                            printf("\nProduto registrado com sucesso!");

                                //laço de repetiçao para verificar resposta de sim ou nao
                                do
                                {
                                    printf("\nDeseja adicionar outro produto? [s/n]\n");
                                    scanf("%9s", &sim_nao);

                                    if(strcmp(sim_nao,"n") == 0)
                                    {
                                        system("cls");
                                        verificador=0;
                                        continuar=0;
                                    }
                                    else if(strcmp(sim_nao,"s") == 0)
                                    {
                                        system("cls");
                                        verificador=0;
                                    }
                                    else
                                    {
                                        printf("Opção inválida!");
                                    }
                                }while(verificador == 1);
                        }


                    }while(continuar == 1);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//menu de saida (opçao 3 do swtich case)
int tela_sair()
    {
        do
        {
            system("cls");
            verificador = 1;

            printf("Tem certeza? [s/n]\n");
            scanf("%9s", sim_nao);

            if(strcmp(sim_nao,"s") == 0)
            {
                verificador = 0;
                return 0;
                system("cls");
            }
            else if(strcmp(sim_nao,"n") == 0)
            {
                verificador = 0;
                system("cls");
                return 1;
            }
            else
            {
                printf("Opção inválida!\n");
                system("pause");
            }

        }while(verificador == 1);

    }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PROGRAMA PRINCIPAL

int main()
{
    //troca localização para portugues brasileiro
    setlocale(LC_ALL, "Portuguese");
    system("chcp 1252 > null");

    //variavel que determina se o programa esta rodando
    int online = 1;

    limpa_lixo();

    inicializar_arquivo_cadastro();

    carregar_dados_salvos();

    do
    {
        tela_principal();

        switch(escolha)
        {
            case 1:
                tela_cadastro_opcoes();

                tela_cadastro_cadastrar();
            break;

            case 2:


            break;

            case 3:
                salvar_dados();

                int tela_sair();

                online = tela_sair();

            break;

            default:
            system("cls");
            printf("\nOpção inválida\n");
        }

        }while(online == 1);

    return 0;
}

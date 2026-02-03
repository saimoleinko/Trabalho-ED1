#include "funcoes.h"


Produto* busca_pelo_codigo(int x, Estoque *ptr){
    
    if(ptr->produto == NULL) return NULL;

    if(ptr->produto->codigo == x) {
        return ptr->produto;}
    
    if (ptr->prox == NULL){
        return NULL;
    }
    else{
    return busca_pelo_codigo(x, ptr->prox);
    }
    }

Produto* criar_struct(Estoque *primeiro)
{
    int i;
    Produto *ptr = (Produto*)malloc(sizeof(Produto));

    if (ptr == NULL) {printf("Erro de alocacao da memoria\n");
        return NULL;}

    else{
        printf("Digite o codigo unico:\n--> ");
        scanf("%d", &ptr -> codigo); //limpar buffer??
            Produto *k = busca_pelo_codigo(ptr->codigo, primeiro);

            if (k != NULL){ //se o codigo ja estiver armazenado no estoque, este caso vai acrescentar mais produtos
                printf("Produto ja existente no sitema.\nQuantos deseja acrescentar?\n--> ");
                scanf("%d", &i);
                k-> quantidade += i;
                printf("Produto incrementado com sucesso!\n");
                free(k);
                return NULL;
            }

        getchar();
        printf("Nome do produto:\n--> ");
        scanf("%50[^\n]", ptr -> nome);
        printf("Quantos desse produto voce gostaria de armazenar?\n--> ");
        scanf("%d", &ptr -> quantidade);
        printf("Qual o preco do produto?\n--> "); //recursao infinita ao retornar apos terceiro caso
        scanf("%f", &ptr -> preco);
        getchar();
        printf("\n");
        return ptr;}
}

Estoque* busca_recursiva(Estoque *ptr){  //alertando ser tipo produto

    if (ptr->prox == NULL) return ptr;

    else return busca_recursiva(ptr->prox);
}




Estoque* busca_recursiva_especifica(Estoque *ptr, int i){

    if (!ptr) return NULL;

    if (ptr->produto && ptr->produto->codigo == i) return ptr;

    return busca_recursiva_especifica(ptr,i);
    
}


/*Estoque* busca_recursiva_anterior_especifica(int j, int i, int k, Estoque *ptr, Estoque *ptr1){ //int i sempre ser zero ao chamar
    if (ptr->produto->codigo == j){
        if (k == 0) return ptr1;
        else return ptr;
    }
    i ++;
    if (i>1) return busca_recursiva_anterior_especifica(j,i,k, ptr->prox,ptr1->prox);
    else return busca_recursiva_anterior_especifica(j,i,k, ptr->prox, ptr1);
}*/



Estoque* criar_estoque()
{

    Estoque *ptr = (Estoque*)malloc(sizeof(Estoque));

    if (ptr == NULL) {printf("Erro ao criar estoque\n");
    return NULL;}

    else {
        ptr-> produto = NULL;
        ptr-> prev = NULL;
        ptr-> prox = NULL;
        return ptr; //linkar esta funcao com o cadastrar_produto
    }
}

void cadastrar_produto(Estoque *ptr){                 //o *head deve ser no inicio o ptr -> prox = NULL do criar_estoque e *novo 
    int quantidade;
    printf("Quantos produtos serao cadastrados?\n--> ");
    scanf("%d", &quantidade);
    for (int i = 0; i < quantidade; i++){             //deve ser o ptr -> produto = NULL

    if (i !=0) printf("::Proximo produto::\n");

    if (ptr-> produto == NULL){
    ptr-> produto = criar_struct(ptr);}

    else{
        Estoque *novo = criar_estoque();           //criar mais um node e acrescentar produto ao estoque

        if (novo == NULL) return; //caso falhe, retornara null e assim a funcao cadastrar_produto acaba
        novo -> produto = criar_struct(ptr);  

            if (novo ->produto == NULL){ //caso o produto a ser acrescentado ja exista entao eh incrementado a esse produto e o novo estoque
                free(novo);
                continue;}             

        Estoque *maisum = busca_recursiva(ptr);     //achar o ultimo valor do estoque e associar a um ponteiro
        maisum->prox = novo; 
        novo->prev = maisum;                  //associar a nova struct de estoque(com o produto) com o final do estoque
    }                              
}
}

void exibir_lista_de_estoque(Estoque *ptr){

    if(!ptr){criar_estoque();
        printf("Estoque vazio\n");
        return;}

    if (ptr-> produto == NULL)
    {printf("Estoque vazio\n");
        return;
    }

    while(ptr!=NULL){
        Produto *ptr2 = ptr->produto;
        printf("Produto: %s\n", ptr2->nome);
        printf("Quantidade: %d\n", ptr2->quantidade);
        printf("Preco: R$%.2f\n", ptr2-> preco);
        printf("Codigo: %d\n\n\n", ptr2-> codigo);
        ptr = ptr->prox;
        }
    }


void editar_dados_do_produto(Estoque *ptr)
{
    int i, j;
    printf("Digite o cogido do produto\n");
    scanf("%d", &i);
    Produto* n = busca_pelo_codigo(i, ptr);

    if (n==NULL){
        printf("Produto nao encontrado\n");
        editar_dados_do_produto(ptr);
    }

    while(1)
    {
    printf("O que voce gostaria de editar?\n::[1] -- Nome\n::[2] -- Quantidade\n::[3] -- Codigo\n::[4] -- Preco\n"); 
    scanf("%d", &j);
    getchar();
    if (j == 1){            //fazer case defaut
        printf("Digite o novo nome\n-->");
        /*
        char s[50];
        char c;
        scanf("%s", novo_nome);
        printf("Gostaria de mudar %s para %s?\nS/N", ptr->nome, novo_nome);
        scanf(" %c", c);
        if(c == 'S') novo->nome = novo_nome;
        */
        scanf("%50[^\n]", n->nome);
        printf("\n");
        return;
    }

    if(j == 2){;
        printf("Digite a nova quantidade\n-->");
        scanf("%d", &n->quantidade);
        printf("\n");
        return;
    }

    if(j == 3){
        printf("Digite o novo codigo\n-->");
        scanf("%d", &n->codigo);
        printf("\n");
        return;
    }

    if(j == 4){
        printf("Digite o novo preco\n-->");
        scanf("%f", &n->preco);
        printf("\n");
        return;
    }

    else {printf("Numero invalido\n");
    }
}
}


/*Estoque* remocao(Estoque *ptr, Estoque *novo){
    if(novo->prev && novo->prox) {novo->prev->prox = novo->prox;
        novo->prox->prev = novo->prev;
        ptr = novo->prev;}
    if(novo->prox) ptr = novo->prox;
    else {free(novo);
        return NULL;}
    free(novo);
    return ptr;}
*/
Estoque* remocao(Estoque *ptr, Estoque *novo){ //novo eh a struct que sera apagada da lista
    Estoque *head = ptr; //armazenando o valor da cabeca
    while(1)
    {
        if(ptr == novo){

            if(novo->prev != NULL && novo->prox != NULL) //se ele esta no meio entao linke o anterior com o sucessor -final

            {novo->prev->prox = novo->prox;
            novo->prox->prev = novo->prev;}

            else{ 
                
                if(novo->prox != NULL){ //se esta no comeco a cabeca eh o proximo -final
                    head = ptr->prox;}

                else{

                    if (novo->prev != NULL){ busca_recursiva(head)->prev = NULL; } //se esta no final o anterior ao ultimo nao existe --final
                        

                    else{ 
                        free(novo); //se ele esta no comeco e nenhum vem apos ele entao ele libera ambos os ponteiros e retorna a nova cabeca
                        return NULL;}

            }
        }
            free(novo);
            return head;
        
    }
        else{
            ptr = ptr->prox;
            continue;
        }
    }
}

Estoque* retirar_produtos(Estoque *ptr)
{
    int codigo,quantos;
    char c;
    Estoque *head = ptr;
    printf("Quantos produtos voce gostaria de remover?\n");
    scanf("%d",&quantos);
    for(int i = 0; i<quantos; i++){
    while(1){
    printf("Digite o codigo do produto:\n");
    scanf("%d", &codigo);
    Estoque *no = busca_recursiva_especifica(ptr ,codigo);
    if (no == NULL) {
        printf("Produto nao encontrado.\n");
        continue;
    }
    break;}
    printf("Produto: %s\n", no->produto->nome);
    printf("Quantidade: %d\n", no->produto->quantidade);
    printf("Preco: R$%.2f\n", no->produto->preco);
    printf("Codigo: %d\n", no->produto->codigo);
    printf("Deseja remover este produto? (S/N)\n");
    scanf(" %c", &c);
    if (c == 'S' || c == 's') {
        head = remocao(ptr, no);
        printf("Produto removido com sucesso!\n");
    }
}
    return head;
}


/*
void retirar_produtos(Estoque *ptr)
{
    int quantidade, x;
    char c;
    printf("Quantos produtos voce deseja retirar?\n"); //se nao houver nenhum produto em estoque tem que dizer que nao pode ser retirado nada
    scanf("%d", &quantidade);
    for(int i = 0; i<quantidade; i++)
    {
        printf("Digite o codigo do produto\n");
        scanf("%d", &x);
        Produto *P = busca_pelo_codigo(x, ptr);
        if (!P){
            printf("Produto nao encontrado\n");
            continue;
        }
        printf("Produto: %s\n", P->nome);
        printf("Quantidade: %d\n", P->quantidade);
        printf("Preco: R$%.2f\n", P-> preco);
        printf("Codigo: %d\n", P-> codigo);
        printf("Gostaria de deletar?\nS/N\n");
        scanf(" %c", &c);
        if (c == 'S' || c == 's'){ //uso de lista dupla para apagar o atual
            Estoque *novo = busca_recursiva_anterior_especifica(ptr,x);
            remocao(ptr,novo);
*/

            /*
            Estoque *novo = busca_recursiva_anterior_especifica(ptr, x);
            if (novo->prev== NULL) {
                if (novo->prox == NULL){
                free(ptr);
                printf("Nenhum item restante no estoque\n");
                return NULL;}
                else ptr = novo->prox;
                continue;
            }
            Estoque *nov1 = novo->prev;
            Estoque *nov2 = novo->prox;
            nov1->prox = nov2->prox; //lembrar de checar se a lista tambem funciona caso acrescentemos no inicio ou no final -- nao feito
            printf("teste2\n"); //perguntar se isto nao apaga os ponteiros anteriores mas so o ponteiro atual
            free(novo);
            printf("Produto deletado com sucesso!\n");
            return ptr;
            
        }
        else{
            printf("Ainda desejaria deletar algum produto?\nS/N"); 
            scanf(" %c", &c);
            if(c == 'S') return retirar_produtos(ptr);
            else return;
        }
    }
}
*/

/*int main(){
    Estoque *ptr = criar_estoque(); //este deve estar na main e devera conversar com as funcoes subsequentes
    cadastrar_produto(ptr); //este sempre tem que verificar caso ptr nao exista
    printf("testando");
    exibir_lista_de_estoque(ptr);
    ptr = retirar_produtos(ptr);
    printf("oioi");
    exibir_lista_de_estoque(ptr); //este sempre vai devolver a nova cabeca ou NULL
    
    return 0;
}*/


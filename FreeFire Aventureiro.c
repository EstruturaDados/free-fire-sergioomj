#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];  // "arma", "municao", "cura", "ferramenta", etc.
    int quantidade;
} Item;

// Constantes do sistema
#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// Variáveis globais
Item mochila[MAX_ITENS];
int totalItens = 0;

//  funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();          // NOVA FUNÇÃO: Busca sequencial por nome
void exibirMenu();
void limparBuffer();

int main() {
    printf("***-***-***-***-***-***-***-***-***-***-***-***\n");
    printf("    DESAFIO CODIGO DA ILHA - EDICAO FREE FIRE\n");
    printf("***-***-***-***-***-***-***-***-***-***-***-***\n");
    printf("Sistema de Gerenciamento de Mochila - NIVEL AVENTUREIRO\n");
    printf(" Sistema com Busca Sequencial \n\n");
    
    int opcao;
    
    do {
        exibirMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer do teclado
        
        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();  // NOVA OPÇÃO: Buscar item específico
                break;
            case 5:
                printf("\nSaindo do sistema... Boa sorte na partida!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        printf("\nPressione Enter para continuar...");
        getchar(); // Pausa para o usuário ver o resultado
        
    } while(opcao != 5);
    
    return 0;
}

void exibirMenu() {
    printf("\n***-***-***-***-***-***-***-***-***-***-***-***\n");
    printf("               MENU PRINCIPAL\n");
    printf("               [NIVEL AVENTUREIRO]\n");
    printf("***-***-***-***-***-***-***-***-***-***-***-***\n");
    printf("1. Coletar item (Cadastrar)\n");
    printf("2. Descartar item (Remover)\n");
    printf("3. Verificar mochila (Listar todos)\n");
    printf("4. Procurar item especifico (Buscar) \n");  // NOVA OPÇÃO
    printf("5. Sair do sistema\n");
    printf("***-***-***-***-***-***-***-***-***-***-***-***\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n[ALERTA] Mochila cheia! Capacidade maxima: %d itens\n", MAX_ITENS);
        printf("Descartar algum item antes de coletar novos.\n");
        return;
    }
    
    printf("\n=== COLETAR NOVO ITEM ===\n");
    
    // Cria novo item
    Item novoItem;
    
    // Ler nome do item
    printf("Nome do item (ex: M4A1, Bandagem, Pochete): ");
    fgets(novoItem.nome, MAX_NOME, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // Remove o \n
    
    // Verificar se item já existe (usando busca sequencial!)
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, novoItem.nome) == 0) {  // Busca sequencial
            printf("\n[INFO] Item '%s' ja existe na mochila!\n", novoItem.nome);
            printf("Deseja aumentar a quantidade? (S/N): ");
            char resposta;
            scanf("%c", &resposta);
            limparBuffer();
            
            if (resposta == 'S' || resposta == 's') {
                printf("Quantidade adicional: ");
                int adicional;
                scanf("%d", &adicional);
                limparBuffer();
                mochila[i].quantidade += adicional;
                printf("\n[SUCESSO] Quantidade atualizada: %s x%d\n", 
                       mochila[i].nome, mochila[i].quantidade);
            }
            return;
        }
    }
    
    // Ler tipo do item
    printf("Tipo (arma/municao/cura/ferramenta/escudo): ");
    fgets(novoItem.tipo, MAX_TIPO, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';
    
    // Ler quantidade
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();
    
    // Validar quantidade
    if (novoItem.quantidade <= 0) {
        printf("\n[ERRO] Quantidade deve ser maior que zero!\n");
        return;
    }
    
    // Adicionar à mochila
    mochila[totalItens] = novoItem;
    totalItens++;
    
    printf("\n[SUCESSO] Item '%s' coletado com sucesso!\n", novoItem.nome);
    printf("Itens na mochila: %d/%d\n", totalItens, MAX_ITENS);
}

void removerItem() {
    if (totalItens == 0) {
        printf("\n[INFO] Mochila vazia! Nada para descartar.\n");
        return;
    }
    
    printf("\n*-*-* DESCARTAR ITEM *-*-*\n");
    printf("Itens na mochila:\n");
    listarItens();
    
    char nomeRemover[MAX_NOME];
    printf("\nNome do item a descartar: ");
    fgets(nomeRemover, MAX_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';
    
    //BUSCA SEQUENCIAL para encontrar o item
    int posicao = -1;  // Flag: -1 indica "não encontrado"
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {  // Comparação exata
            posicao = i;  // Item encontrado na posição i
            break;        // Para a busca, pois encontramos
        }
    }
    
    if (posicao == -1) {  // Verificação da flag
        printf("\n[ERRO] Item '%s' nao encontrado na mochila!\n", nomeRemover);
        return;
    }
    
    // Confirmar remoção
    printf("\nConfirmar descarte de '%s' (Tipo: %s, Quantidade: %d)? (S/N): ",
           mochila[posicao].nome, mochila[posicao].tipo, mochila[posicao].quantidade);
    char confirmacao;
    scanf("%c", &confirmacao);
    limparBuffer();
    
    if (confirmacao == 'S' || confirmacao == 's') {
        // Remover item movendo os itens seguintes
        for (int i = posicao; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        
        printf("\n[SUCESSO] Item descartado com sucesso!\n");
        printf("Itens restantes: %d/%d\n", totalItens, MAX_ITENS);
    } else {
        printf("\n[INFO] Operacao cancelada.\n");
    }
}

void listarItens() {
    if (totalItens == 0) {
        printf("\n[INFO] Mochila vazia! Nenhum item coletado.\n");
        return;
    }
    
    printf("\n*-*-* CONTEUDO DA MOCHILA *-*-*\n");
    printf("Total de itens: %d/%d\n\n", totalItens, MAX_ITENS);
    printf("%-5s %-30s %-20s %-10s\n", "No.", "NOME", "TIPO", "QUANTIDADE");
    printf("-------------------------------------------------------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("%-5d %-30s %-20s %-10d\n", 
               i + 1, 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
}

//NOVA FUNÇÃO: Busca sequencial por nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n[INFO] Mochila vazia! Nenhum item para buscar.\n");
        return;
    }
    
    printf("\n=== 🔍 PROCURAR ITEM ===\n");
    printf("Digite o nome exato do item que deseja encontrar:\n");
    
    char nomeBusca[MAX_NOME];
    printf("Nome do item: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';  // Remove newline
    
    //IMPLEMENTAÇÃO DE BUSCA SEQUENCIAL
    int encontrado = 0;  // Flag: 0 = não encontrado, 1 = encontrado
    int posicao = -1;    // Posição onde o item foi encontrado
    
    // Percorre todos os itens da mochila
    for (int i = 0; i < totalItens; i++) {
        // Comparação exata de strings usando strcmp
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;    // Atualiza flag
            posicao = i;       // Guarda a posição
            break;             // Para a busca (já encontrou)
        }
    }
    
    printf("\n");
    printf("*-*-* RESULTADO DA BUSCA *-*-*\n");
    
    if (encontrado) {
        //ITEM ENCONTRADO - Exibe detalhes completos
        printf("ITEM ENCONTRADO!\n\n");
        printf("DETALHES DO ITEM:\n");
        printf("──────────────────────────────────────────────\n");
        printf("Nome:       %s\n", mochila[posicao].nome);
        printf("Tipo:       %s\n", mochila[posicao].tipo);
        printf("Quantidade: %d unidades\n", mochila[posicao].quantidade);
        printf("Posição:    %d de %d itens na mochila\n", 
               posicao + 1, totalItens);
        printf("──────────────────────────────────────────────\n");
    } else {
        // ITEM NÃO ENCONTRADO - "Mensagem amigável"
        printf("ITEM NÃO ENCONTRADO!\n\n");
        printf("O item '%s' não está na sua mochila.\n", nomeBusca);
        printf("\nDicas:\n");
        printf("• Verifique se digitou o nome corretamente\n");
        printf("• Use a opção 3 para ver todos os itens disponíveis\n");
        printf("• Lembre-se que a busca é pelo nome exato\n");
    }
    
    printf("\n");
    printf("ESTATÍSTICAS DA BUSCA:\n");
    printf("Itens na mochila: %d\n", totalItens);
    printf("Busca realizada: %s\n", (encontrado ? "Sucesso" : "Sem resultados"));
}
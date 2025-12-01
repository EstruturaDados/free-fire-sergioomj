#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== ESTRUTURAS ====================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ==================== CONSTANTES ====================
#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

// ==================== VARIÁVEIS GLOBAIS ====================
Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;
int comparacoes = 0;  // Contador global de comparações
int ordenadoPorNome = 0;  // Flag para verificar se está ordenado por nome

// ==================== PROTÓTIPOS DE FUNÇÕES ====================
void exibirMenu();
void limparBuffer();
void cadastrarComponentes();
void mostrarComponentes(Componente componentes[], int n);
void bubbleSortNome(Componente componentes[], int n);
void insertionSortTipo(Componente componentes[], int n);
void selectionSortPrioridade(Componente componentes[], int n);
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]);
void medirDesempenho(void (*algoritmoOrdenacao)(Componente[], int), Componente componentes[], int n, char nomeAlgoritmo[]);
void simularMontagemFinal(Componente componentes[], int n);
void buscarComponenteInterativo();

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    printf("***-***-***-***-***-***-***-***-***-***-***-***\n");
    printf("      DESAFIO FINAL - TORRE DE RESGATE\n");
    printf("***-***-***-***-***-***-***-***-***-***-***-***\n");
    printf("Última safe zone - Monte sua torre para escapar!\n");
    printf("Sistema de Organização de Componentes - NÍVEL AVANÇADO\n\n");
    
    int opcao;
    
    do {
        exibirMenu();
        printf("\nEscolha uma estratégia: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarComponentes();
                break;
            case 2:
                medirDesempenho(bubbleSortNome, torre, totalComponentes, "Bubble Sort (Nome)");
                ordenadoPorNome = 1;  // Marca como ordenado por nome
                break;
            case 3:
                medirDesempenho(insertionSortTipo, torre, totalComponentes, "Insertion Sort (Tipo)");
                ordenadoPorNome = 0;  // Já não está ordenado por nome
                break;
            case 4:
                medirDesempenho(selectionSortPrioridade, torre, totalComponentes, "Selection Sort (Prioridade)");
                ordenadoPorNome = 0;  // Já não está ordenado por nome
                break;
            case 5:
                buscarComponenteInterativo();
                break;
            case 6:
                if (totalComponentes > 0) {
                    simularMontagemFinal(torre, totalComponentes);
                } else {
                    printf("\n  Nenhum componente cadastrado! Cadastre componentes primeiro.\n");
                }
                break;
            case 7:
                printf("\nSaindo do sistema... Boa sorte na fuga!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
        
        if (opcao != 7) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
        
    } while(opcao != 7);
    
    return 0;
}

// ==================== FUNÇÕES AUXILIARES ====================
void exibirMenu() {
    printf("\n***-***-***-***-***-***-***-***-***-***-***-***\n");
    printf("              ESTRATÉGIAS DE FUGA\n");
    printf("              [NÍVEL AVANÇADO]\n");
    printf("***-***-***-***-***-***-***-***-***-***-***-***\n");
    printf("1. Coletar componentes da torre (Cadastrar)\n");
    printf("2. Ordenar por NOME (Bubble Sort)\n");
    printf("3. Ordenar por TIPO (Insertion Sort)\n");
    printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
    printf("5. Buscar componente por nome (Busca Binária)\n");
    printf("6. Simular montagem final da torre\n");
    printf("7. Sair do sistema\n");
    printf("***-***-***-***-***-***-***-***-***-***-***-***\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ==================== CADASTRO DE COMPONENTES ====================
void cadastrarComponentes() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\n[ALERTA] Capacidade máxima atingida! Máximo: %d componentes\n", MAX_COMPONENTES);
        return;
    }
    
    int quantidade;
    printf("\n=== COLETAR COMPONENTES DA TORRE ===\n");
    printf("Quantos componentes deseja cadastrar? (1-%d): ", 
           MAX_COMPONENTES - totalComponentes);
    scanf("%d", &quantidade);
    limparBuffer();
    
    if (quantidade <= 0 || quantidade > (MAX_COMPONENTES - totalComponentes)) {
        printf("\n  Quantidade inválida!\n");
        return;
    }
    
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Componente %d/%d ---\n", i + 1, quantidade);
        
        // Nome do componente
        printf("Nome do componente: ");
        fgets(torre[totalComponentes].nome, MAX_NOME, stdin);
        torre[totalComponentes].nome[strcspn(torre[totalComponentes].nome, "\n")] = '\0';
        
        // Tipo do componente
        printf("Tipo (controle/suporte/propulsao/energia): ");
        fgets(torre[totalComponentes].tipo, MAX_TIPO, stdin);
        torre[totalComponentes].tipo[strcspn(torre[totalComponentes].tipo, "\n")] = '\0';
        
        // Prioridade
        do {
            printf("Prioridade (1-10, onde 10 é mais importante): ");
            scanf("%d", &torre[totalComponentes].prioridade);
            limparBuffer();
            
            if (torre[totalComponentes].prioridade < 1 || torre[totalComponentes].prioridade > 10) {
                printf("   Prioridade deve ser entre 1 e 10!\n");
            }
        } while (torre[totalComponentes].prioridade < 1 || torre[totalComponentes].prioridade > 10);
        
        totalComponentes++;
        printf("  Componente cadastrado com sucesso!\n");
    }
    
    printf("\n  Total de componentes na torre: %d/%d\n", totalComponentes, MAX_COMPONENTES);
    ordenadoPorNome = 0;  // Reset da flag de ordenação
}

// ==================== EXIBIÇÃO DE COMPONENTES ====================
void mostrarComponentes(Componente componentes[], int n) {
    if (n == 0) {
        printf("\n[INFO] Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n  COMPONENTES DA TORRE (%d itens):\n", n);
    printf("┌─────┬──────────────────────────────┬────────────────────┬────────────┐\n");
    printf("│ No. │ Nome                         │ Tipo               │ Prioridade │\n");
    printf("├─────┼──────────────────────────────┼────────────────────┼────────────┤\n");
    
    for (int i = 0; i < n; i++) {
        printf("│ %3d │ %-28s │ %-18s │ %10d │\n", 
               i + 1, 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    
    printf("└─────┴──────────────────────────────┴────────────────────┴────────────┘\n");
}

// ==================== ALGORITMOS DE ORDENAÇÃO ====================

// Bubble Sort para ordenar por NOME
void bubbleSortNome(Componente componentes[], int n) {
    comparacoes = 0;  // Reset contador
    int trocou;
    Componente temp;
    
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes
                temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocou = 1;
            }
        }
        // Se não houve trocas, o array já está ordenado
        if (!trocou) break;
    }
}

// Insertion Sort para ordenar por TIPO
void insertionSortTipo(Componente componentes[], int n) {
    comparacoes = 0;  // Reset contador
    Componente chave;
    int j;
    
    for (int i = 1; i < n; i++) {
        chave = componentes[i];
        j = i - 1;
        
        // Move elementos maiores que a chave para a direita
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

// Selection Sort para ordenar por PRIORIDADE (decrescente)
void selectionSortPrioridade(Componente componentes[], int n) {
    comparacoes = 0;  // Reset contador
    int maxIdx;
    Componente temp;
    
    for (int i = 0; i < n - 1; i++) {
        maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (componentes[j].prioridade > componentes[maxIdx].prioridade) {
                maxIdx = j;
            }
        }
        // Troca o elemento de maior prioridade com o primeiro não ordenado
        if (maxIdx != i) {
            temp = componentes[i];
            componentes[i] = componentes[maxIdx];
            componentes[maxIdx] = temp;
        }
    }
}

// ==================== BUSCA BINÁRIA ====================
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]) {
    comparacoes = 0;  // Reset contador
    int esquerda = 0;
    int direita = n - 1;
    int meio;
    
    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        comparacoes++;
        
        int comparacao = strcmp(componentes[meio].nome, nome);
        
        if (comparacao == 0) {
            return meio;  // Componente encontrado
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1;  // Componente não encontrado
}

// ==================== BUSCA INTERATIVA ====================
void buscarComponenteInterativo() {
    if (totalComponentes == 0) {
        printf("\n  Nenhum componente cadastrado! Cadastre componentes primeiro.\n");
        return;
    }
    
    printf("\n===   BUSCA BINÁRIA POR COMPONENTE ===\n");
    
    if (!ordenadoPorNome) {
        printf("   ATENÇÃO: Para usar busca binária, os componentes devem estar ordenados por NOME!\n");
        printf("Deseja ordenar agora? (S/N): ");
        char resposta;
        scanf("%c", &resposta);
        limparBuffer();
        
        if (resposta == 'S' || resposta == 's') {
            medirDesempenho(bubbleSortNome, torre, totalComponentes, "Bubble Sort (Nome)");
            ordenadoPorNome = 1;
        } else {
            printf("\nOperação cancelada. Use a opção 2 para ordenar primeiro.\n");
            return;
        }
    }
    
    char nomeBusca[MAX_NOME];
    printf("\nDigite o nome EXATO do componente que deseja buscar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    printf("\nExecutando busca binária por: '%s'\n", nomeBusca);
    
    // Executa a busca binária
    int resultado = buscaBinariaPorNome(torre, totalComponentes, nomeBusca);
    
    printf("\n┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                    RESULTADO DA BUSCA                      │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    
    if (resultado != -1) {
        printf("│    COMPONENTE ENCONTRADO!                                  │\n");
        printf("├─────────────────────────────────────────────────────────────┤\n");
        printf("│ Nome:       %-44s │\n", torre[resultado].nome);
        printf("│ Tipo:       %-44s │\n", torre[resultado].tipo);
        printf("│ Prioridade: %-44d │\n", torre[resultado].prioridade);
        printf("│ Posição:    %d de %d componentes                    │\n", resultado + 1, totalComponentes);
    } else {
        printf("│     COMPONENTE NÃO ENCONTRADO!                              │\n");
        printf("├─────────────────────────────────────────────────────────────┤\n");
        printf("│ O componente '%s' não está na torre.              │\n", nomeBusca);
        printf("│ Verifique se digitou o nome corretamente.                  │\n");
    }
    
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ Estatísticas da busca:                                    │\n");
    printf("│ • Comparações realizadas: %-31d │\n", comparacoes);
    printf("│ • Complexidade: O(log n)                                   │\n");
    printf("│ • Eficiência: %-45s │\n", 
           (totalComponentes <= 10) ? "Muito alta" : "Alta");
    printf("└─────────────────────────────────────────────────────────────┘\n");
    
    // Sugere buscar componente-chave se não encontrou
    if (resultado == -1) {
        printf("\n   DICA: Componentes-chave comuns para montagem da torre:\n");
        printf("  • 'chip central'     • 'propulsor principal'  • 'gerador'\n");
        printf("  • 'console controle' • 'escudo energia'       • 'sensor'\n");
    }
}

// ==================== MEDIÇÃO DE DESEMPENHO ====================
void medirDesempenho(void (*algoritmoOrdenacao)(Componente[], int), 
                     Componente componentes[], int n, char nomeAlgoritmo[]) {
    if (n == 0) {
        printf("\n Nenhum componente para ordenar! Cadastre componentes primeiro.\n");
        return;
    }
    
    printf("\n EXECUTANDO %s \n", nomeAlgoritmo);
    printf("Componentes antes da ordenação:\n");
    mostrarComponentes(componentes, n);
    
    // Faz uma cópia para não modificar o original durante medição
    Componente copia[MAX_COMPONENTES];
    memcpy(copia, componentes, sizeof(Componente) * n);
    
    // Medição do tempo
    clock_t inicio = clock();
    algoritmoOrdenacao(copia, n);
    clock_t fim = clock();
    
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    // Copia de volta para o array original
    memcpy(componentes, copia, sizeof(Componente) * n);
    
    printf("\n RESULTADOS DA ORDENAÇÃO:\n");
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│ %-60s │\n", nomeAlgoritmo);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ Número de comparações: %-36d │\n", comparacoes);
    printf("│ Tempo de execução:    %-10.6f segundos               │\n", tempo);
    
    // Informa sobre a eficiência teórica
    if (strstr(nomeAlgoritmo, "Bubble") != NULL || 
        strstr(nomeAlgoritmo, "Insertion") != NULL || 
        strstr(nomeAlgoritmo, "Selection") != NULL) {
        printf("│ Eficiência teórica:   O(n²)                                │\n");
    }
    
    printf("└─────────────────────────────────────────────────────────────┘\n");
    
    printf("\n Componentes após a ordenação:\n");
    mostrarComponentes(componentes, n);
}

// ==================== SIMULAÇÃO DE MONTAGEM ====================
void simularMontagemFinal(Componente componentes[], int n) {
    printf("\n INICIANDO MONTAGEM DA TORRE DE RESGATE \n");
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│ FASE FINAL - ÚLTIMA SAFE ZONE                              │\n");
    printf("└─────────────────────────────────────────────────────────────┘\n\n");
    
    // Pergunta ao jogador qual é o componente-chave
    char componenteChaveNome[MAX_NOME];
    printf("Antes de montar, identifique o COMPONENTE-CHAVE da sua torre.\n");
    printf("Digite o nome do componente mais importante: ");
    fgets(componenteChaveNome, MAX_NOME, stdin);
    componenteChaveNome[strcspn(componenteChaveNome, "\n")] = '\0';
    
    // Procura o componente-chave (busca linear)
    int componenteChave = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(componentes[i].nome, componenteChaveNome) == 0) {
            componenteChave = i;
            break;
        }
    }
    
    if (componenteChave != -1) {
        printf("\n COMPONENTE-CHAVE IDENTIFICADO: '%s'\n", componenteChaveNome);
        printf("   Tipo: %s | Prioridade: %d/10\n", 
               componentes[componenteChave].tipo, 
               componentes[componenteChave].prioridade);
        printf("   Status: [██████████] 100%% - PRONTO PARA ATIVAÇÃO\n\n");
    } else {
        printf("\n COMPONENTE-CHAVE NÃO ENCONTRADO: '%s'\n", componenteChaveNome);
        printf("   Status: [░░░░░░░░░░] 0%% - COMPONENTE AUSENTE\n");
        printf("   Verifique se o nome está correto ou cadastre este componente.\n\n");
    }
    
    // Pergunta como o jogador quer ver os componentes
    printf("\nComo deseja visualizar os componentes para montagem?\n");
    printf("1. Ordenados por PRIORIDADE (recomendado para montagem)\n");
    printf("2. Ordenados por NOME (organização alfabética)\n");
    printf("3. Ordenados por TIPO (agrupamento funcional)\n");
    printf("4. Manter ordem atual\n");
    printf("Escolha: ");
    
    int opcaoVisualizacao;
    scanf("%d", &opcaoVisualizacao);
    limparBuffer();
    
    // Cria uma cópia para ordenação visual
    Componente visualizacao[MAX_COMPONENTES];
    memcpy(visualizacao, componentes, sizeof(Componente) * n);
    
    // Aplica a ordenação escolhida (apenas para visualização)
    switch(opcaoVisualizacao) {
        case 1:
            selectionSortPrioridade(visualizacao, n);
            printf("\n COMPONENTES ORDENADOS POR PRIORIDADE (montagem ideal):\n");
            break;
        case 2:
            bubbleSortNome(visualizacao, n);
            printf("\n COMPONENTES ORDENADOS POR NOME (organização alfabética):\n");
            break;
        case 3:
            insertionSortTipo(visualizacao, n);
            printf("\n COMPONENTES ORDENADOS POR TIPO (agrupamento funcional):\n");
            break;
        default:
            printf("\n COMPONENTES NA ORDEM ATUAL:\n");
    }
    
    mostrarComponentes(visualizacao, n);
    
    // Calcula estatísticas PARA DECISÃO DO RESULTADO
    int prioridadeTotal = 0;
    int tiposDiferentes = 0;
    char tiposVistos[MAX_COMPONENTES][MAX_TIPO];
    int prioridadeMaxima = 0;
    char componenteMaisImportante[MAX_NOME] = "";
    
    for (int i = 0; i < n; i++) {
        prioridadeTotal += componentes[i].prioridade;
        
        // Encontra componente com maior prioridade
        if (componentes[i].prioridade > prioridadeMaxima) {
            prioridadeMaxima = componentes[i].prioridade;
            strcpy(componenteMaisImportante, componentes[i].nome);
        }
        
        // Conta tipos diferentes
        int tipoNovo = 1;
        for (int j = 0; j < tiposDiferentes; j++) {
            if (strcmp(componentes[i].tipo, tiposVistos[j]) == 0) {
                tipoNovo = 0;
                break;
            }
        }
        if (tipoNovo) {
            strcpy(tiposVistos[tiposDiferentes], componentes[i].tipo);
            tiposDiferentes++;
        }
    }
    
    double prioridadeMedia = (n > 0) ? (double)prioridadeTotal / n : 0;
    
    printf("\n ESTATÍSTICAS DA TORRE:\n");
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│ Total de componentes:    %-34d │\n", n);
    printf("│ Tipos diferentes:        %-34d │\n", tiposDiferentes);
    printf("│ Prioridade média:        %-10.2f/10                    │\n", prioridadeMedia);
    printf("│ Componente mais importante: %-30s │\n", componenteMaisImportante);
    printf("│ Componente-chave escolhido: %-30s │\n", componenteChaveNome);
    
    // DECIDE O RESULTADO BASEADO EM CRITÉRIOS CLAROS
    int sucesso = 1; // Assume sucesso inicialmente
    int criteriosFalhos = 0;
    
    // Critério 1: Componente-chave deve estar presente
    if (componenteChave == -1) {
        sucesso = 0;
        criteriosFalhos++;
    }
    
    // Critério 2: Mínimo de componentes
    if (n < 3) {
        sucesso = 0;
        criteriosFalhos++;
    }
    
    // Critério 3: Prioridade média mínima
    if (prioridadeMedia < 4.0) {
        sucesso = 0;
        criteriosFalhos++;
    }
    
    // Critério 4: Diversidade de tipos
    if (tiposDiferentes < 2) {
        sucesso = 0;
        criteriosFalhos++;
    }
    
    // Exibe status do componente-chave
    if (componenteChave != -1) {
        printf("│ Status do componente-chave: %-30s │\n", "PRESENTE ");
    } else {
        printf("│ Status do componente-chave: %-30s │\n", "AUSENTE ");
    }
    
    // Calcula chance de fuga
    double chanceFuga = 0.0;
    if (sucesso) {
        chanceFuga = 70.0 + (prioridadeMedia * 3); // Base 70% + bônus por prioridade
        if (chanceFuga > 95.0) chanceFuga = 95.0;
    } else {
        // Mesmo falhando, pode ter alguma chance baseada na qualidade
        chanceFuga = 10.0 + (prioridadeMedia * 5); 
        if (chanceFuga > 40.0) chanceFuga = 40.0;
        chanceFuga -= (criteriosFalhos * 10); // Penalidade por critérios falhos
        if (chanceFuga < 5.0) chanceFuga = 5.0;
    }
    
    printf("│ Chance de fuga estimada:    %-30.0f%% │\n", chanceFuga);
    printf("└─────────────────────────────────────────────────────────────┘\n");
    
    // Resultado final
    printf("\n RODANDO SIMULAÇÃO DE MONTAGEM...\n");
    
    // Pausa dramática
    for (int i = 3; i > 0; i--) {
        printf("%d... ", i);
        fflush(stdout);
        // Pausa simples
        for (int j = 0; j < 100000000; j++); // Loop de espera
    }
    printf("\n\n");
    
    if (sucesso) {
        printf(" PARABÉNS! TORRE MONTADA COM SUCESSO!\n");
        printf("┌─────────────────────────────────────────────────────────────┐\n");
        printf("│ SEQUÊNCIA DE FUGA INICIADA...                               │\n");
        printf("│ 1. Componentes verificados       [ok]                       │\n");
        printf("│ 2. Sistema de energia ativado    [ok]                       │\n");
        printf("│ 3. Propulsão carregada           [ok]                       │\n");
        printf("│ 4. Sequência de ignição          [ok]                       │\n");
        printf("│                                               IGNIÇÃO! 🚀  │\n");
        printf("└─────────────────────────────────────────────────────────────┘\n");
        
        // Mostra dicas para melhorar a chance
        printf("\n DICAS PARA MELHORAR SUA FUGA:\n");
        if (prioridadeMedia < 7.0) {
            printf("• Use componentes com maior prioridade (7+)\n");
        }
        if (tiposDiferentes < 3) {
            printf("• Adicione mais tipos diferentes de componentes\n");
        }
        if (n < 5) {
            printf("• Colete mais componentes (recomendado: 5+)\n");
        }
        
        printf("\nVocê escapou da ilha com sucesso! VITÓRIA! \n");
    } else {
        printf(" FALHA NA MONTAGEM DA TORRE!\n");
        printf("┌─────────────────────────────────────────────────────────────┐\n");
        printf("│ ERROS DETECTADOS:                                           │\n");
        
        // Mostra os motivos específicos da falha
        if (componenteChave == -1) {
            printf("│ • Componente-chave '%s' ausente                  │\n", componenteChaveNome);
        }
        if (n < 3) {
            printf("│ • Muito poucos componentes (%d/3 mínimos)           │\n", n);
        }
        if (prioridadeMedia < 4.0) {
            printf("│ • Prioridade média muito baixa (%.1f/10)           │\n", prioridadeMedia);
        }
        if (tiposDiferentes < 2) {
            printf("│ • Baixa diversidade de tipos (%d/2 mínimos)         │\n", tiposDiferentes);
        }
        
        printf("│                                                 FALHA!   │\n");
        printf("└─────────────────────────────────────────────────────────────┘\n");
        
        printf("\n💡 COMO MELHORAR NA PRÓXIMA TENTATIVA:\n");
        if (componenteChave == -1) {
            printf("1. Certifique-se de cadastrar o componente-chave '%s'\n", componenteChaveNome);
        }
        if (n < 3) {
            printf("2. Colete pelo menos 3 componentes\n");
        }
        if (prioridadeMedia < 4.0) {
            printf("3. Use componentes com prioridade mais alta (4+)\n");
        }
        if (tiposDiferentes < 2) {
            printf("4. Adicione diferentes tipos (controle, energia, propulsão, etc.)\n");
        }
        
        printf("\nA torre desmoronou... GAME OVER \n");
    }
}
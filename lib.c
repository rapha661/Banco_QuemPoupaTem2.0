#include "lib.h"
#include <stdio.h>
#include <string.h>

void menu(int *opcao, int *cont) {

  // Exibe o menu e recebe um inteiro do usuário.
  if (*cont == 0) { // Se for a primeira vez que o usuário entrar no programa, ele recebe o menu inicial.
    printf("Bem vindo ao banco QuemPoupaTem!\n");
    printf("Escolha uma das opções abaixo:\n");
    printf("1. Novo cliente\n");
    printf("2. Apagar cliente\n");
    printf("3. Listar clientes\n");
    printf("4. Débito\n");
    printf("5. Depósito\n");
    printf("6. Extrato\n");
    printf("7. Transferência entre contas\n");
    printf("0. Sair\n");
    printf("Opção: ");
    scanf("%d", opcao);
    printf("\n");
    *cont += 1;
  }
  else { // Caso o menu se repetir, não exibirá a mensagem "Bem vindo ao banco QuemPoupaTem!".
    printf("Escolha uma das opções abaixo:\n");
    printf("1. Novo cliente\n");
    printf("2. Apagar cliente\n");
    printf("3. Listar clientes\n");
    printf("4. Débito\n");
    printf("5. Depósito\n");
    printf("6. Extrato\n");
    printf("7. Transferência entre contas\n");
    printf("0. Sair\n");
    printf("Opção: ");
    scanf("%d", opcao);
    printf("\n");

    *cont += 1;
  }
  
}

void novo_cliente(lista_clientes *lc) {

  cliente cliente;
  char nome[101];
  char cpf[50];
  char tipo_conta[50];
  float saldo;
  char senha[101];

  int tamanho_cpf = 0;
  int tamanho_tipo_conta = 0;

  printf("\n\tDigite o nome do cliente: ");
  scanf("%s", nome);
  printf("\n");

  printf("\tDigite CPF: ");
  scanf("%s", cpf);
  printf("\n");

  printf("\tDigite o tipo de conta (c para comum ou p para plus): ");
  scanf("%s", tipo_conta);
  printf("\n");

  printf("\tDigite o saldo inicial da conta: ");
  scanf("%f", &saldo);
  printf("\n");

  printf("\tDigite a senha da conta: ");
  scanf("%s", senha);
  printf("\n");

  tamanho_cpf = strlen(cpf); // Verifica o comprimento da string cpf.
  tamanho_tipo_conta = strlen(tipo_conta); // Verifica o comprimento da string tipo_conta.

  if (tamanho_cpf != 11 || tamanho_tipo_conta != 1 || strcmp(tipo_conta, "c") != 0 && strcmp(tipo_conta, "p") != 0) { // Se o comprimento das strings do cpf e do tipo de conta estiverem errados e o tipo de conta for diferente de c ou p, para a função novo_cliente após exibir uma mensagem.
    printf("\tCPF e/ou tipo de conta inválidos.\n\n");
  }
  else { // Caso contrário, os dados são adicionados no struct cliente com as informações do cliente.
  strcpy(cliente.nome, nome);
  strcpy(cliente.cpf, cpf);
  strcpy(cliente.tipo_conta, tipo_conta);
  cliente.saldo = saldo;
  strcpy(cliente.senha, senha);

  lc->cliente[lc->qtnd] = cliente; // Adiciona o struct cliente preenchido no struct lista_clientes.
  lc->qtnd += 1; // Atualiza a quantidade de clientes dentro do lista_clientes para apontar para a última posição do array.
  printf("\tDados cadastrados com sucesso!\n\n");
  }
  
}

void apaga_extrato(lista_clientes *lc, int pos) {

  // Recebe o struct com todos os clientes e a posição do cliente na lista a ser apagado.
  cliente c = lc->cliente[pos];

  for (; pos < lc->cliente[pos].qtnd; pos++) {
    // Para cada posição da lista de struct dados_extrato, ele substitui as informações de operação e valor da posição atual pelas informações da próxima posição.
    strcpy(c.extrato[c.qtnd].operacao, lc->cliente[pos + 1].extrato[lc->cliente[pos + 1].qtnd].operacao);
    c.extrato[c.qtnd].valor = lc->cliente[pos + 1].extrato[lc->cliente[pos + 1].qtnd].valor;
  }
  
}

void apagar_cliente(lista_clientes *lc) {

  char cpf_apagado[50];
  int x = 0;
  int find = 0;

  printf("CPF a ser apagado: ");
  scanf("%s", cpf_apagado);
  
  for (; x < lc->qtnd; x++) {
    // Laço que itera sobre o cpf de cada cliente dentro do struct lista_cliente para verificar se existe o cpf no sistema.
    if (strcmp(lc->cliente[x].cpf, cpf_apagado) == 0) {
      // Se existir, valor de find é alterado e para o laço.
      find = 1;
      break;
    }
  }

  if (find == 1) { // Se o cpf existir, apaga o cliente. Senão, exibe uma mensagem de erro.
    for (; x < lc->qtnd; x++) {
      // Com a posição encontrada pelo laço anterior, o loop começa a copiar as informações do cliente da próxima posição para a posição atual.
      strcpy(lc->cliente[x].nome, lc->cliente[x + 1].nome);
      strcpy(lc->cliente[x].cpf, lc->cliente[x + 1].cpf);
      strcpy(lc->cliente[x].tipo_conta, lc->cliente[x + 1].tipo_conta);
      lc->cliente[x].saldo = lc->cliente[x + 1].saldo;
      strcpy(lc->cliente[x].senha, lc->cliente[x + 1].senha);
      apaga_extrato(lc, x);
    }
    lc->qtnd -= 1; // Decrementa 1 na quantidade do struct lista_cliente para apontar para o último cliente.
    lc->cliente->qtnd -= 1; // Decrementa 1 na quantidade dentro do struct cliente para apontar para os dados da ultíma operação feita.
    printf("\tCliente apagado com sucesso!\n\n"); // Exibi mensagem que deu certo.
  }
  else {
    printf("\tCPF incorreto!\n\n"); // Exibi mensagem de erro.
  }
  
}

void listar_clientes(lista_clientes *lc) {

  for (int x = 0; x < lc->qtnd; x++) {
    // Loop que itera sobre os dados dos clientes dentro do lista_clientes e imprime as informações deles na tela.
    printf("\n\tCliente %d\n", x);
    printf("\t\tNome: %s\n", lc->cliente[x].nome);
    printf("\t\tCPF: %s\n", lc->cliente[x].cpf);
    printf("\t\tTipo de conta: %s\n", lc->cliente[x].tipo_conta);
    printf("\t\tSaldo: R$%.2f\n", lc->cliente[x].saldo);
    printf("\t\tSenha: %s\n\n", lc->cliente[x].senha);
  }
  
}

void debito(lista_clientes *lc) {

  char cpf_debito[12];
  char senha_debito[101];
  float debito;
  int find_cpf = 0;
  int find_senha = 0;
  int saldo = 0;
  int x = 0;

  printf("\tCPF do cliente: ");
  scanf("%s", cpf_debito);
  printf("\n");

  printf("\tSenha do cliente: ");
  scanf("%s", senha_debito);
  printf("\n");

  printf("\n\tValor do débito: ");
  scanf("%f", &debito);
  printf("\n");

  for (; x < lc->qtnd; x++) {
    // Laço que itera sobre os cpfs da lista_clientes e verifica se o cpf existe no sistema.
    if (strcmp(lc->cliente[x].cpf, cpf_debito) == 0 && strcmp(lc->cliente[x].senha, senha_debito) == 0) {
      find_cpf = 1;
      find_senha = 1;
      break;
    }
  }

  if (find_cpf == 1 && find_senha == 1) {
    if (strcmp(lc->cliente[x].tipo_conta, "c") == 0 && lc->cliente[x].saldo - debito * 1.05 >= -1000) {
      // Se o cpf existir, a conta for comum e o saldo depois do debito for maior que -1000 realizará o débito
      lc->cliente[x].saldo -= debito * 1.05;
      strcpy(lc->cliente[x].extrato[lc->cliente[x].qtnd].operacao, "Débito"); // String "Débito" adicionada na variável operacao do extrato.
      lc->cliente[x].extrato[lc->cliente[x].qtnd].valor = -debito * 1.05; // Adiciona o valor do deposito na variável valor do extrato
      lc->cliente[x].qtnd += 1; // Aumenta em 1 

      printf("\n\tDébito de R$%.2f realizado com sucesso!\n\n", debito);
    }
    else if (strcmp(lc->cliente[x].tipo_conta, "p") == 0 && lc->cliente[x].saldo - debito * 1.03 >= -5000) {
      // Se o cpf existir, a conta for plus e o saldo depois do debito for maior que -5000 realizará o débito
      lc->cliente[x].saldo -= debito * 1.03;
      strcpy(lc->cliente[x].extrato[lc->cliente[x].qtnd].operacao, "Débito");
      lc->cliente[x].extrato[lc->cliente[x].qtnd].valor = -debito * 1.03;
      lc->cliente[x].qtnd += 1;
      printf("\n\tDébito de R$%.2f realizado com sucesso!\n\n", debito);
    }
    else {
      printf("\tSaldo insuficiente!\n\n");
    }
  }
  else {
    printf("\tDados incorretos\n\n");
  }
  
}

void deposito(lista_clientes *lc) {

  char cpf_deposito[12];
  float deposito;
  int find_cpf = 0;
  int x = 0;

  printf("\tCPF do cliente: ");
  scanf("%s", cpf_deposito);
  printf("\n");

  printf("\tValor do depósito: ");
  scanf("%f", &deposito);
  printf("\n");

  for (; x < lc->qtnd; x++) {
    // Laço que itera sobre os cpfs de cada clientes dentro do lista_clientes e verifica se o cpf existe no sistema.
    if (strcmp(lc->cliente[x].cpf, cpf_deposito) == 0) {
      find_cpf = 1;
      break;
    }
  }
  if (find_cpf == 1) {
    // Se existir, realiza o depósito. Senão, exibe mensagem de erro.
    lc->cliente[x].saldo += deposito; // Deposita o valor no saldo da conta do cliente.
    strcpy(lc->cliente[x].extrato[lc->cliente[x].qtnd].operacao, "Depósito"); // Copia a string "Depósito"para a variável operacao no dados_extrato.
    lc->cliente[x].extrato[lc->cliente[x].qtnd].valor = deposito; // Adiciona o valor do depósito na variável valor dentro do dados_extrato.
    lc->cliente[x].qtnd += 1; // Aumenta a quantidade para apontar para a última operação feita pelo cliente.
    printf("\tDepósito de %.2f realizado com sucesso\n\n", deposito);
  }
  else {
    printf("\n\tCPF incorreto!\n");
  }
  
}

void cria_arquivo(char *nome, FILE *f, char cpf[12]) {

  f = fopen(nome, "w"); // Cria um arquivo com nome específico.
  fprintf(f, "Extrato CPF: %s\n", cpf); // A primeira linha será exibindo de que cpf é aquele extrato.
  fclose(f); // Fecha o arquivo.
  
}

int menu2() {

  // Função para exibir as opções de extrato que o usuário possui.
  int opcao;
  printf("\t1. Extrato normal\n");
  printf("\t2. Extrato apenas das despesas\n");
  printf("\t3. Extrato apenas dos lucros\n");
  printf("\tOpcão: ");
  scanf("%d", &opcao);
  printf("\n");
  return opcao; // Retorna a opção escolhida.
  
}

void extrato(lista_clientes *lc) {

  char cpf_extrato[30];
  char cpf[12];
  char senha[101];
  int find_cpf_senha = 0;
  int x = 0;

  printf("\n\tInsira o CPF: ");
  scanf("%s", cpf);

  printf("\n\tInsira sua Senha: ");
  scanf("%s", senha);

  for (; x < lc->qtnd; x++) {
    // Laço que itera sobre os cpfs e senhas dos clientes e verifica se o cpf e a senha existe no sistema.
    if (strcmp(lc->cliente[x].cpf, cpf) == 0 && strcmp(lc->cliente[x].senha, senha) == 0) {
      find_cpf_senha = 1;
      break;
    }
  }
  if (find_cpf_senha == 1) {
    // Se existir, continua a função. Senão, exibe mensagem de erro.
    sprintf(cpf_extrato, "extrato_%s.txt", cpf); // Atribui à string cpf_extrato a string formatada junto com o cpf recido de usuário.
    FILE *f; // Cria o ponteiro do arquivo.
    cria_arquivo(cpf_extrato, f, cpf); // Cria o arquivo com o nome que está na variável cpf_extrato.
    
    switch(menu2()) {
      case 1:
        // Caso o usuário escolha a opção 1, imprimirá no arquivo o extrato normal
          f = fopen(cpf_extrato, "a"); // Abre o arquivo no modo "a".
          for (int op = 0; op < lc->cliente[x].qtnd; op++) {
            if (strcmp(lc->cliente[x].extrato[op].operacao, "Débito") == 0) {
              // Se a operação feita foi débito, imprimirá de um jeito específico de modo que apareça data, operação e valor nessa ordem.
              fprintf(f, "-/-/-         %s                %.2f\n", lc->cliente[x].extrato[op].operacao, lc->cliente[x].extrato[op].valor);
            }
            else if (strcmp(lc->cliente[x].extrato[op].operacao, "Depósito") == 0) {
              // Se a operação feita foi depósito, imprimirá de um jeito específico de modo que apareça data, operação e valor nessa ordem.
              fprintf(f, "-/-/-         %s              %.2f\n", lc->cliente[x].extrato[op].operacao, lc->cliente[x].extrato[op].valor);
            }
            else if (strcmp(lc->cliente[x].extrato[op].operacao, "Transferência") == 0) {
              // Se a operação feita foi transferência, imprimirá de um jeito específico de modo que apareça data, operação e valor nessa ordem.
              fprintf(f, "-/-/-         %s         %.2f\n", lc->cliente[x].extrato[op].operacao, lc->cliente[x].extrato[op].valor);
            }
          }
          fclose(f);
          break;
      
      case 2:
        // Se o usuário escolher a opção 2, o extrato exibirá somente os gastos da conta.
          f = fopen(cpf_extrato, "a");
          for (int op = 0; op < lc->cliente[x].qtnd; op++) {
            if (strcmp(lc->cliente[x].extrato[op].operacao, "Débito") == 0) {
              fprintf(f, "-/-/-         %s                %.2f\n", lc->cliente[x].extrato[op].operacao, lc->cliente[x].extrato[op].valor);
            }
            else if (strcmp(lc->cliente[x].extrato[op].operacao, "Transferência") == 0 && lc->cliente[x].extrato[op].valor < 0) {
              fprintf(f, "-/-/-         %s         %.2f\n", lc->cliente[x].extrato[op].operacao, lc->cliente[x].extrato[op].valor);
            }
          }
          fclose(f);
          break;
      case 3:
        // Se o usuário escolheu a opção 3, o extrato exibirá apenas os ganhos.
        f = fopen(cpf_extrato, "a");
        for (int op = 0; op < lc->cliente[x].qtnd; op++) {
          if (strcmp(lc->cliente[x].extrato[op].operacao, "Depósito") == 0) {
            fprintf(f, "-/-/-         %s              %.2f\n", lc->cliente[x].extrato[op].operacao, lc->cliente[x].extrato[op].valor);
          }
          else if (strcmp(lc->cliente[x].extrato[op].operacao, "Transferência") == 0 && lc->cliente[x].extrato[op].valor > 0) {
            fprintf(f, "-/-/-         %s         %.2f\n", lc->cliente[x].extrato[op].operacao, lc->cliente[x].extrato[op].valor);
          }
        }
        fclose(f);
        break;
    }
  }
  else {
    printf("\n\tCliente não encontrado.\n");
  }
  
}

void transf(lista_clientes *lc) {

  char cpf_origem[12];
  char cpf_destino[12];
  char senha_origem[101];
  int find_cpfsenha_origem = 0;
  int find_cpf_destino = 0;
  int pos_origem = 0;
  int pos_destino = 0;
  float transf;

  printf("\n\tCPF de origem: ");
  scanf("%s", cpf_origem);

  printf("\n\tCPF de destino: ");
  scanf("%s", cpf_destino);

  printf("\n\tSenha de origem: ");
  scanf("%s", senha_origem);

  for (; pos_origem < lc->qtnd; pos_origem++) {
    // Laço que itera sobre os cpfs e senhas dos clientes dentro do lista_clientes e verifica se o cpf e a senha existem no sistema.
    if (strcmp(lc->cliente[pos_origem].cpf, cpf_origem) == 0 && strcmp(lc->cliente[pos_origem].senha, senha_origem) == 0) {
      find_cpfsenha_origem = 1;
      break;
    }
  }
  for (; pos_destino < lc->qtnd; pos_destino++) {
    // Laço que itera sobre os cpfs dos clientes dentro do lista_clientes e verifica se o cpf existe no sistema.
    if (strcmp(lc->cliente[pos_destino].cpf, cpf_destino) == 0) {
      find_cpf_destino = 1;
      break;
    }
  }

  if (find_cpfsenha_origem == 1 && find_cpf_destino == 1) {
    // Se existir, continua com o funcionamento da função. Senão, exibe mensagem de erro.
    printf("\n\tValor da transferência: ");
    scanf("%f", &transf);

    if (strcmp(lc->cliente[pos_origem].tipo_conta, "c") == 0 && lc->cliente[pos_origem].saldo - transf * 1.05 >= -1000) {
      // Se o tipo de conta do cliente de origem for comum e o saldo pós transferência for maior ou igual a -1000, então fará a transferência.
      lc->cliente[pos_origem].saldo -= transf * 1.05; // Tira o valor mais 5% de taxa da conta do cliente de origem.
      strcpy(lc->cliente[pos_origem].extrato[lc->cliente[pos_origem].qtnd].operacao, "Transferência"); // String operacao agora é "Tranferência".
      lc->cliente[pos_origem].extrato[lc->cliente[pos_origem].qtnd].valor = -transf * 1.05; // Variável valor agora é o -valor da transferência + 5% de taxa.
      lc->cliente[pos_origem].qtnd += 1; // Aumenta a quantidade para apontar para a última operação.

      lc->cliente[pos_destino].saldo += transf; // Adiciona o valor na conta do cliente de destino.
      strcpy(lc->cliente[pos_destino].extrato[lc->cliente[pos_destino].qtnd].operacao, "Transferência"); // String operacao agora é "Tranferência".
      lc->cliente[pos_destino].extrato[lc->cliente[pos_destino].qtnd].valor = transf; // // Variável valor agora é o valor recebido.
      lc->cliente[pos_destino].qtnd += 1; // Aumenta a quantidade para apontar para a última operação.
    }

    else if (strcmp(lc->cliente[pos_origem].tipo_conta, "p") == 0 && lc->cliente[pos_origem].saldo - transf * 1.03 >= -5000) {
      // Se o tipo de conta do cliente de origem for plus e o saldo pós transferência for maior ou igual a -5000, então fará a transferência.
    lc->cliente[pos_origem].saldo -= transf * 1.03;
    strcpy(lc->cliente[pos_origem].extrato[lc->cliente[pos_origem].qtnd].operacao, "Transferência");
    lc->cliente[pos_origem].extrato[lc->cliente[pos_origem].qtnd].valor = -transf * 1.03;
    lc->cliente[pos_origem].qtnd += 1;

    lc->cliente[pos_destino].saldo += transf;
    strcpy(lc->cliente[pos_destino].extrato[lc->cliente[pos_destino].qtnd].operacao, "Transferência");
    lc->cliente[pos_destino].extrato[lc->cliente[pos_destino].qtnd].valor = transf;
    lc->cliente[pos_destino].qtnd += 1;
    }

    else {
      printf("\n\tSaldo insuficiente!");
    }
    
    printf("\n\tTranferência realizada com sucesso!\n");
  }
  else {
    printf("\n\tDados incorretos!");
  }
  
}

void salva_bin(lista_clientes *lc) {

  FILE *f = fopen("dados_clientes", "wb"); // Abre o arquivo no modo "escrita em binário"
  if (f == NULL) { // Se o arquivo não existir, para a função.
    return;
  }
  else {
    fwrite(lc, sizeof(lista_clientes), 1, f); // Escreve os dados dos clientes presentes no struct lista_clientes no arquivo.
    fclose(f); // Fecha o arquivo.
  }
  
}

void le_bin(lista_clientes *lc) {
  
  FILE *f = fopen("dados_clientes", "rb"); // Abre o arquivo no modo "leitura em binário"
  if (f == NULL) { // Se o arquivo não existir, para a função.
    return;
  }
  else {
    fread(lc, sizeof(lista_clientes), 1, f); // Lê os dados dos clientes presentes no struct lista_clientes no arquivo.
    fclose(f); // Fecha o arquivo.
  }
  
}

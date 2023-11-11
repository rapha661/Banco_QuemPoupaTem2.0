#include <stdio.h>
#include "lib.h"
// Feito por Nathan Gabriel da Fonseca Leite RA: 221230287 e Raphael Garavati Erbert RA: 221230147

int main() {
  int opcao;
  int cont = 0;
  lista_clientes lc;
  lc.qtnd = 0;
  le_bin(&lc); // Atualiza o struct lista_clientes com o conteúdo do arquivo dados_clientes.

  do {
    menu(&opcao, &cont);
    while (opcao > 9 || opcao < 0) {
      menu(&opcao, &cont);
    }
  switch(opcao) {
    case 1:
      novo_cliente(&lc);
      // salva_bin(&lc);
      break;
    case 2:
      apagar_cliente(&lc);
      // salva_bin(&lc);
      break;
    case 3:
      listar_clientes(&lc);
      // salva_bin(&lc);
      break;
    case 4:
      debito(&lc);
      // salva_bin(&lc);
      break;
    case 5:
      deposito(&lc);
      // salva_bin(&lc);
      break;
    case 6:
      extrato(&lc);
      // salva_bin(&lc);
      break;
    case 7:
      transf(&lc);
      // salva_bin(&lc);
      break;
    case 0:
      salva_bin(&lc);
      break;
    }
  } while (opcao != 0);
  
    return 0;
  
}
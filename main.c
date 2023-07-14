// Incluindo bibliotecas necessária para o programa
#include <stdio.h>
#include <stdlib.h>

// Struct de livro
typedef struct livr{
  int id;
  char titulo[55];
  char autor[35];
  int data_devol;
  struct lista_pes *posse;
}Livro;

// Struct da lista encadeada dos livros
typedef struct lista_livro{
  struct livr dados;
  struct lista_livro *prox;
}ElemL;

// Struct de pessoa
typedef struct pess{
  int id;
  char nome[20];
  char sobrenome[35];
  int qtd_livros;
  struct livr *livros;
}Pessoa;

// Struct de lista encadeada de pessoas
typedef struct lista_pes{
  struct pess dados;
  struct lista_pes *prox;
}ElemP;

// Declarando protótipos das funções
void cadastrarPessoa(ElemP **head_pes, int *qtd_pessoas);
void removerPessoa(ElemP **head_pes, int *qtd_pessoas, int *exemp_alugados);
void mostrarPessoas(ElemP **head_pes);
void atualizarPessoasSalvas(ElemP **head_pes, int qtd_pessoas, FILE *arq);
void lerPessoasSalvas(ElemP **head_pes, int *qtd_pessoas,FILE *arq, int *exemp_alugados);
void cadastrarLivro(ElemL **head_liv, int *qtd_livros);
void lerLivrosSalvos(ElemL **head_liv, int *qtd_livros, FILE *arq);
void atualizarLivrosSalvos(ElemL **head_liv, int qtd_livros, FILE *arq);
void removerLivro(ElemL **head_liv, int *qtd_livros);
void mostrarLivros(ElemL **head_pos);
void alugarLivro(ElemL **head_liv, ElemP **head_pes, int *exemp_alugados);
void converterItS(int cod_data, char *data);
int converterStI(char *data);
Pessoa lerPessoa();
Livro lerLivro();
void devolverLivro(ElemP **head_pes, int *exemp_alugados);
void alterarDataDevol(ElemP **head_pes);
void mostrarExemplares(ElemP **head_pes);
int crescente(const void *n1, const void *n2);
int decrescente(const void *n1, const void *n2);
void ordenarExemplares(ElemP **head_pes, int exemp_alugados);

int main(){
  FILE *ps_txt, *ls_txt;
  // Abrindo/criando os arquivos de salvamento
  ps_txt = fopen("pessoas_salvas.txt", "a+");
  ls_txt = fopen("livros_salvos.txt", "a+");
  // Texto do menu principal
  const char INST[] = "\nO que deseja fazer?\nDigite:\n\t(1) para cadastrar um novo indivíduo\n\t(0) para remover um indíviduo cadastrado\n\t(p) para mostrar todas as pessoas cadastradas\n\t(b) para cadastrar um novo livro\n\t(m) para mostrar todos os livros cadastrados\n\t(z) para remover um livro\n\t(a) para alugar um livro para uma determinada pessoa\n\t(d) para devolver um livro\n\t(y) para alterar a data de devolução de um exemplar\n\t(c) para mostrar os detalhes dos livros que uma determinada pessoa alugou\n\t(t) para mostrar todos os exemplares alugados ordenadamente conforme a data de devolução\n\t(s) para salvar suas ações\n\t(x) para salvar suas ações e sair do programa\n\t(q) para somente sair do programa\nEntrada: ";
  char acao;
  int qtd_pessoas, qtd_livros, exemp_alugados;
  Pessoa aux;
  Livro aux2;
  // Lendo as informações dos arquivos e salvando-as em listas
  ElemP **head_pes = (ElemP**) malloc(sizeof(ElemP*)), *noP;
  ElemL **head_liv = (ElemL**) malloc(sizeof(ElemL*)), *noL;
  lerPessoasSalvas(head_pes, &qtd_pessoas, ps_txt, &exemp_alugados);
  lerLivrosSalvos(head_liv, &qtd_livros, ls_txt);
  while(1){
    // Menu principal para o usuário do programa selecionar as ações
    printf(INST);
    scanf(" %c", &acao);
    switch(acao){
      // Cadastrar um indivíduo
      case '1':
        cadastrarPessoa(head_pes, &qtd_pessoas);
        break;
      // Remover de um indivíduo
      case '0': case 'o': case 'O':
        removerPessoa(head_pes, &qtd_pessoas, &exemp_alugados);
        break;
      case 'b': case 'B':
        cadastrarLivro(head_liv, &qtd_livros);
        break;
      // Mostrar todos os indivíduos cadastrados
      case 'p': case 'P':
        printf("\nHá %d pessoas cadastradas!\n\n", qtd_pessoas);
        noP = *head_pes;
        while(noP != NULL){
          aux = noP -> dados;
          printf("%s %s <%d> pegou %d livros emprestado.\n", aux.nome, aux.sobrenome, aux.id, aux.qtd_livros);
          noP = noP -> prox;
        }
        break;
      // Mostrar livros cadastrados
      case 'm': case 'M':
        printf("\nHá %d livros cadastrados e %d exemplares alugados!\n\n", qtd_livros, exemp_alugados);
        noL = *head_liv;
        while(noL != NULL){
          aux2 = noL -> dados;
          printf("Título: %s\nAutor: %s\nID: %d\n\n", aux2.titulo, aux2.autor, aux2.id);
          noL = noL -> prox;
        }
        putchar('\n');
        break;
      // Remover Livro
      case 'z': case 'Z':
        removerLivro(head_liv, &qtd_livros);
        break;
      // Alugar livro
      case 'a': case 'A':
        alugarLivro(head_liv, head_pes, &exemp_alugados);
        break;
      // Devolver livro
      case 'd': case 'D':
        devolverLivro(head_pes, &exemp_alugados);
        break;
      // Alterar data de devolução
      case 'y': case 'Y':
        alterarDataDevol(head_pes);
        break;
      // Mostrar detalhes dos livro de uma determinada pessoa
      case 'c': case 'C':
        mostrarExemplares(head_pes);
        break;
      // Mostra os exemplares em ordem
      case 't': case 'T':
        ordenarExemplares(head_pes, exemp_alugados);
        break;
      // Salvar as ações
      case 's': case 'S':
        atualizarPessoasSalvas(head_pes, qtd_pessoas, ps_txt);
        atualizarLivrosSalvos(head_liv, qtd_livros, ls_txt);
        break;
      // Sair do programa e salvar
      case 'x': case 'X':
        atualizarPessoasSalvas(head_pes, qtd_pessoas, ps_txt);
        atualizarLivrosSalvos(head_liv, qtd_livros, ls_txt);
        exit(0);
      // Sair do programa somente
      case 'q': case 'Q':
        exit(0);
    }
  }

  return 0;
}

// Ler dados de um pessoa do teclado
Pessoa lerPessoa(){
  Pessoa pes;
  printf("Digite o ID dessa pessoa: ");
  scanf(" %d", &pes.id);
  printf("Digite o nome dessa pessoa: ");
  scanf(" %[^\n]s", pes.nome);
  printf("Digite o sobrenome dessa pessoa: ");
  scanf(" %[^\n]s", pes.sobrenome);
  pes.qtd_livros = 0;
  pes.livros = NULL;
  return pes;
}
// Cadastrar a pessoa
void cadastrarPessoa(ElemP **head_pes, int *qtd_pessoas){
  Pessoa pes = lerPessoa();
  ElemP *no = (ElemP*) malloc(sizeof(ElemP));
  no -> dados = pes;
  no -> prox = (*head_pes);
  *head_pes = no;
  (*qtd_pessoas)++;
}
// Mostrar na tela as pessoas para que o usuário saiba como selecionar cada uma
void mostrarPessoas(ElemP **head_pes){
  int ct = 0;
  ElemP *no = (*head_pes);
  puts("\n");
  while(no != NULL){
    printf("(%d) -> %s %s <%d>\n", ct++, no -> dados.nome, no -> dados.sobrenome, no -> dados.id);
    no = no -> prox;
  }
}
// Remover pessoa
void removerPessoa(ElemP **head_pes, int *qtd_pessoas, int *exemp_alugados){
  int ct = 0, pos;
  if((*head_pes) == NULL){
    printf("\nNão há nenhuma pessoa cadastrada!\n");
    return;
  }
  printf("Digite o número referente a quem você deseja remover: ");
  mostrarPessoas(head_pes);
  printf("\n(-1) para todas\n\nEntrada: ");
  scanf(" %d", &pos);
  ElemP *atual = (*head_pes), *ant;
  if(pos == -1){
    while(atual != NULL){
      ant = atual;
      atual = atual -> prox;
      free(ant);
    }
    free(atual);
    free(head_pes);
    (*qtd_pessoas) = 0;
    return;
  }
  while(atual != NULL && ct < pos){
    ant = atual;
    atual = atual -> prox;
    ct++;
  }
  if(atual == (*head_pes)){
    *head_pes = atual -> prox;
  }else{
    ant -> prox = atual -> prox;
  }
  (*qtd_pessoas)--;
  *exemp_alugados -= atual -> dados.qtd_livros;
  free(atual);
}
// Salvar as informações das pessoas no arquivo pessoas_salvas.txt
void atualizarPessoasSalvas(ElemP **head_pes, int qtd_pessoas, FILE *arq){
  ElemP *no = *head_pes;
  Pessoa aux;
  int ind;
  fclose(arq);
  arq = fopen("pessoas_salvas.txt", "w");
  fprintf(arq, "%d\n\n", qtd_pessoas);
  while(no != NULL){
    aux = no -> dados;
    fprintf(arq, "%d\n%s\n%s\n%d\n", aux.id, aux.nome, aux.sobrenome, aux.qtd_livros);
    for(ind = 0; ind < aux.qtd_livros; ind++){
      fputc('\n', arq);
      fprintf(arq, " %d\n", aux.livros[ind].id);
      fprintf(arq, " %s\n", aux.livros[ind].titulo);
      fprintf(arq, " %s\n", aux.livros[ind].autor);
      fprintf(arq, " %d\n", aux.livros[ind].data_devol);
    }
    fputc('\n', arq);
    no = no -> prox;
  }
}
// Ler informações do arquivo pessoas_salvas.txt e salvar em uma lista encadeada
void lerPessoasSalvas(ElemP **head_pes, int *qtd_pessoas,FILE *arq, int *exemp_alugados){
  int ind, aux;
  *exemp_alugados = 0;
  aux = fscanf(arq, " %d", qtd_pessoas);
  if(aux == EOF || (*qtd_pessoas) == 0){
    *head_pes = NULL;
    *qtd_pessoas = 0;
    return;
  }
  ElemP *no1, *no2;
  for(ind = 0; ind < (*qtd_pessoas); ind++){
    no1 = (ElemP*) malloc(sizeof(ElemP));
    fscanf(arq, " %d", &(no1 -> dados.id));
    fscanf(arq, " %[^\n]s", no1 -> dados.nome);
    fscanf(arq, " %[^\n]s", no1 -> dados.sobrenome);
    fscanf(arq, " %d", &(no1 -> dados.qtd_livros));
    if(no1 -> dados.qtd_livros == 0){
      no1 -> dados.livros = NULL;
    }else{
      *exemp_alugados += no1 -> dados.qtd_livros;
      no1 -> dados.livros = (Livro*) malloc(sizeof(Livro) * (no1 -> dados.qtd_livros));
      for(aux = 0; aux < no1 -> dados.qtd_livros; aux++){
        fscanf(arq, " %d", &no1 -> dados.livros[aux].id);
        fscanf(arq, " %[^\n]s", no1 -> dados.livros[aux].titulo);
        fscanf(arq, " %[^\n]s", no1 -> dados.livros[aux].autor);
        fscanf(arq, " %d", &no1 -> dados.livros[aux].data_devol);
        no1 -> dados.livros[aux].posse = no1;
      }
    }
    if(ind == 0){
      *head_pes = no1;
    }else{
      no2 -> prox = no1;
    }
    no2 = no1;
  }
  no1 -> prox = NULL;
}
// Ler informações de um livro do teclado
Livro lerLivro(){
  Livro liv;
  printf("Digite um ID para o livro: ");
  scanf(" %d", &liv.id);
  printf("Digite o título do livro: ");
  scanf(" %[^\n]s", liv.titulo);
  printf("Digite o autor do livro: ");
  scanf(" %[^\n]s", liv.autor);
  liv.data_devol = 0;
  return liv;
}
// Cadastrar livro
void cadastrarLivro(ElemL **head_liv, int *qtd_livros){
  Livro liv = lerLivro();
  ElemL *no = (ElemL*) malloc(sizeof(ElemL));
  no -> dados = liv;
  no -> prox = (*head_liv);
  *head_liv = no;
  (*qtd_livros)++;
}
// Ler livros salvos no arquivo livros_salvos.txt e armazenar em uma lista encadeada
void lerLivrosSalvos(ElemL **head_liv, int *qtd_livros, FILE *arq){
  int ind, aux;
  aux = fscanf(arq, " %d", qtd_livros);
  if(aux == EOF || (*qtd_livros) == 0){
    *head_liv = NULL;
    *qtd_livros = 0;
    return;
  }
  ElemL *no1, *no2;
  for(ind = 0; ind < (*qtd_livros); ind++){
    no1 = (ElemL*) malloc(sizeof(ElemL));
    fscanf(arq, " %d", &(no1 -> dados.id));
    fscanf(arq, " %[^\n]s", no1 -> dados.titulo);
    fscanf(arq, " %[^\n]s", no1 -> dados.autor);
    fscanf(arq, " %d", &(no1 -> dados.data_devol));
    no1 -> dados.posse = NULL;
    if(ind == 0){
      *head_liv = no1;
    }else{
      no2 -> prox = no1;
    }
    no2 = no1;
  }
  no1 -> prox = NULL;
}
// Salvar as informações dos livros no arquivo livros_salvos.txt
void atualizarLivrosSalvos(ElemL **head_liv, int qtd_livros, FILE *arq){
  ElemL *no = *head_liv;
  Livro aux;
  int ind;
  fclose(arq);
  arq = fopen("livros_salvos.txt", "w");
  fprintf(arq, "%d\n\n", qtd_livros);
  while(no != NULL){
    aux = no -> dados;
    fprintf(arq, "%d\n%s\n%s\n%d\n", aux.id, aux.titulo, aux.autor, aux.data_devol);
    fputc('\n', arq);
    no = no -> prox;
  }
}
// Mostrar livros na tela para que o usuário saiba como selecionar cada
void mostrarLivros(ElemL **head_liv){
  int ct = 0;
  ElemL *no = (*head_liv);
  puts("\n");
  while(no != NULL){
    printf("(%d) -> %s (%s) <%d>\n", ct++, no -> dados.titulo, no -> dados.autor, no -> dados.id);
    no = no -> prox;
  }
}
// Remover livro cadastrado
void removerLivro(ElemL **head_liv, int *qtd_livros){
  int ct = 0, pos;
  if(*head_liv == NULL){
    printf("\nNão há nenhum livro cadastrado!\n");
    return;
  }
  printf("Digite o número referente a qual livro você deseja remover: ");
  mostrarLivros(head_liv);
  printf("\n(-1) para todos\n\nEntrada: ");
  scanf(" %d", &pos);
  ElemL *atual = (*head_liv), *ant;
  if(pos == -1){
    while(atual != NULL){
      ant = atual;
      atual = atual -> prox;
      ct++;
      free(ant);
    }
    free(atual);
    free(head_liv);
    (*qtd_livros) = 0;
    return;
  }
  while(atual != NULL && ct < pos){
    ant = atual;
    atual = atual -> prox;
    ct++;
  }
  if(atual == (*head_liv)){
    *head_liv = atual -> prox;
  }else{
    ant -> prox = atual -> prox;
  }
  (*qtd_livros)--;
  free(atual);
}
// Converter código inteiro da data no formato DD/MM/AAAA
void converterItS(int cod_data, char *data){
  char str_data[9];
  int ind;
  sprintf(str_data, "%d", cod_data);
  data[0] = str_data[6];
  data[1] = str_data[7];
  data[2] = '/';
  data[3] = str_data[4];
  data[4] = str_data[5];
  data[5] = '/';
  for(ind = 0; ind < 4; ind++){
    data[ind + 6] = str_data[ind];
  }
  data[10] = '\0';
  
}
// Converter data no formato DD/MM/AAAA para um código inteiro para facilitar ordenação
int converterStI(char *data){
  int aux;
  char str_data[9];
  for(aux = 0; aux < 4; aux++){
    str_data[aux] = data[aux + 6];
  }
  str_data[4] = data[3];
  str_data[5] = data[4];
  str_data[6] = data[0];
  str_data[7] = data[1];
  str_data[8] = '\0';
  aux = atoi(str_data);
  return aux;
}
// Alugar livro para uma pessoa cadastrada
void alugarLivro(ElemL **head_liv, ElemP **head_pes, int *exemp_alugados){
  int pos_liv, pos_pes, ind = 0, num;
  char buffer_str[11];
  if(*head_pes == NULL){
    puts("\nNão há nenhuma pessoa cadastrada!");
    return;
  }
  if(*head_liv == NULL){
    puts("\nNão há nenhum título cadastrado!");
    return;
  }
  ElemL *noL = *head_liv;
  ElemP *noP = *head_pes;
  printf("Selecione o livro que deseja ser alugado: ");
  mostrarLivros(head_liv);
  printf("Entrada: ");
  scanf(" %d", &pos_liv);
  printf("Agora selecione a pessoa que alugará o livro: ");
  mostrarPessoas(head_pes);
  printf("Entrada: ");
  scanf(" %d", &pos_pes);
  printf("Digite a data de devolução desse livro (DD/MM/AAAA): ");
  scanf(" %s", buffer_str);
  num = converterStI(buffer_str);
  for(ind = 0; ind < pos_liv; ind++){
    noL = noL -> prox;
  }
  for(ind = 0; ind < pos_pes; ind++){
    noP = noP -> prox;
  }
  noP -> dados.livros = realloc(noP -> dados.livros, (++(noP -> dados.qtd_livros)) * sizeof(Livro));
  noP -> dados.livros[noP -> dados.qtd_livros - 1] = noL -> dados;
  noP -> dados.livros[noP -> dados.qtd_livros - 1].data_devol = num;
  noP -> dados.livros[noP -> dados.qtd_livros - 1].posse = noP;
  (*exemp_alugados)++;
}
// Devolver livro que uma pessoa havia alugado
void devolverLivro(ElemP **head_pes, int *exemp_alugados){
  int pos, ind, n_livros;
  ElemP *no = *head_pes;
  if(*head_pes == NULL){
    puts("\nNão há nenhuma pessoa cadastrada!");
    return;
  }
  printf("Selecione a pessoa que devolveu: ");
  mostrarPessoas(head_pes);
  printf("Entrada: ");
  scanf(" %d", &pos);
  for(ind = 0; ind < pos; ind++){
    no = no -> prox;
  }
  if(no -> dados.qtd_livros == 0){
    printf("\nEssa pessoas não tem nenhum livro para ser devolvido!\n");
    return;
  }
  printf("Selecione o livro a ser devolvido!\n\n");
  for(ind = 0; ind < no -> dados.qtd_livros; ind++){
    printf("(%d) -> %s (%s) <%d>\n", ind, no -> dados.livros[ind].titulo, no -> dados.livros[ind].autor, no -> dados.livros[ind].id);
  }
  printf("(-1) para devolver todos\nEntrada: ");
  scanf(" %d", &pos);
  if(pos == -1){
    (*exemp_alugados) -= no -> dados.qtd_livros;
    no -> dados.qtd_livros = 0;
    free(no -> dados.livros);
    no -> dados.livros = NULL;
  }else{
    (no -> dados.qtd_livros)--;
    n_livros = no -> dados.qtd_livros;
    for(ind = pos; ind < n_livros; ind++){
      no -> dados.livros[ind] = no -> dados.livros[ind + 1];
    }
    no -> dados.livros = (Livro*) realloc(no -> dados.livros, sizeof(Livro) * n_livros);
    (*exemp_alugados)--;
  }
}
// Alterar data de devolução, seja para adiar ou encurtar o prazo.
void alterarDataDevol(ElemP **head_pes){
  int pos, ind;
  char data0[11], data1[11];
  ElemP *no = *head_pes;
  printf("Selecione a pessoa desejada: ");
  mostrarPessoas(head_pes);
  printf("Entrada: ");
  scanf(" %d", &pos);
  for(ind = 0; ind < pos; ind++){
    no = no -> prox;
  }
  if(no -> dados.qtd_livros == 0){
    printf("\nEssa pessoas não tem nenhum livro alugado!\n");
    return;
  }
  printf("Selecione o livro a ter sua data devolução alterada!\n\n");
  for(ind = 0; ind < no -> dados.qtd_livros; ind++){
    printf("(%d) -> %s (%s) <%d>\n", ind, no -> dados.livros[ind].titulo, no -> dados.livros[ind].autor, no -> dados.livros[ind].id);
  }
  printf("\nEntrada: ");
  scanf(" %d", &pos);
  converterItS(no -> dados.livros[pos].data_devol, data0);
  printf("Alterar data de %s para: ", data0);
  scanf(" %s", data1);
  no -> dados.livros[pos].data_devol = converterStI(data1);
}
// Mostrar todos os exemplares alugados por uma determinada pessoa
void mostrarExemplares(ElemP **head_pes){
  int pos, ind;
  Livro aux;
  char str_data[11];
  if(*head_pes == NULL){
    puts("\nNão há nenhuma pessoa cadastrada!");
    return;
  }
  ElemP *no = *head_pes;
  puts("Selecione a pessoa que você quer conferir os livros alugados: ");
  mostrarPessoas(head_pes);
  printf("Entrada: ");
  scanf(" %d", &pos);
  for(ind = 0; ind < pos; ind++){
    no = no -> prox;
  }
  if(no -> dados.qtd_livros == 0){
    puts("\nEsse pessoa não está alugando nenhum livro!");
    return;
  }
  printf("\n%s %s tem %d livros alugados!\n", no -> dados.nome, no -> dados.sobrenome, no -> dados.qtd_livros);
  for(ind = 0; ind < no -> dados.qtd_livros; ind++){
    aux = no -> dados.livros[ind];
    converterItS(aux.data_devol, str_data);
    printf("\nTítulo: %s\nAutor: %s\nID: %d\nData de devol.: %s\n\n", aux.titulo, aux.autor, aux.id, str_data);
  }
}
// Função para a função qsort() ordene de forma crescente
int crescente(const void *n1, const void *n2){
  return (((Livro*) n1) -> data_devol) - (((Livro*) n2) -> data_devol);
}
// Função para a função qsort() ordene de forma decrescente
int decrescente(const void *n1, const void *n2){
  return (((Livro*) n2) -> data_devol) - (((Livro*) n1) -> data_devol);
}
// Ordenar todos os exemplares alugados utilizando o método quick sort e escrevendo todos na tela
void ordenarExemplares(ElemP **head_pes, int exemp_alugados){
  char ordem, str_data[11];
  int ind, ind2 = 0;
  Livro aux;
  Livro *vetor_exemp = (Livro*) malloc(sizeof(Livro) * exemp_alugados);
  ElemP *no = *head_pes;
  printf("Qual ordem deseja que seja mostrada?\n\t(c) -> crescente\n\t(d) -> decrescente\nEntrada: ");
  scanf(" %c", &ordem);
  while(no != NULL){
    for(ind = 0; ind < no -> dados.qtd_livros; ind++){
      vetor_exemp[ind2++] = no -> dados.livros[ind];
    }
    no = no -> prox;
  }
  if(ordem == 'c' || ordem == 'C'){
    qsort(vetor_exemp, exemp_alugados, sizeof(Livro), crescente);
  }else if(ordem == 'd' || ordem == 'D'){
    qsort(vetor_exemp, exemp_alugados, sizeof(Livro), decrescente);
  }
  for(ind = 0; ind < exemp_alugados; ind++){
    aux = vetor_exemp[ind];
    converterItS(aux.data_devol, str_data);
    printf("\nPosse: %s %s\nTítulo: %s\nAutor: %s\nID: %d\nData de devol.: %s\n\n", vetor_exemp[ind].posse -> dados.nome, vetor_exemp[ind].posse -> dados.sobrenome, vetor_exemp[ind].titulo, aux.autor, aux.id, str_data);
    
  }
}
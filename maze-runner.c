#include <stdio.h>
#define MAX 100

/* variáveis globais */

int filai [MAX], filaj [MAX];
int p, q, u, v;
int pilha_caminhos_i [MAX], pilha_caminhos_j [MAX], pilha_respostas_i [MAX], pilha_respostas_j [MAX];
int t, s, w, z;

/* funções de fila */
/* serão criadas 2 filas; uma para a coordenada i da matriz, e outra para a j */

void criafilai (void){
  p= 0; u= 0;
}

void criafilaj (void){
  q = 0; v = 0;
}

int filavaziai (void){
  return p >= u;
}

int filavaziaj (void){
  return q >= v;
}

int tiradafilai (){
  int y = filai [p];
  p++;
  return y;
}

int tiradafilaj (){
  int y = filaj [q];
  q++;
  return y;
}

void colocanafilai (int y){
  filai [u++] = y;
}

void colocanafilaj (int y){
  filaj [v++] = y;
}

/* funções de pilha */
/* serão criadas 4 pilhas; duas para um conjunto caminhos (coordenadas i e j),
que possui "todos" os menores caminhos possíveis, e duas para o conjunto respostas
(coordenadas i e j), que possui um menor caminho possível de cada vez */

void criapilha_caminhos_i (){
  t = 0;
}

void criapilha_caminhos_j (){
  s = 0;
}

void criapilha_respostas_i (){
  w = 0;
}

void criapilha_respostas_j (){
  z = 0;
}

void empilha_caminhos_i (int y){
  pilha_caminhos_i [t++] = y;
}

void empilha_caminhos_j (int y){
  pilha_caminhos_j [s++] = y;
}

void empilha_respostas_i (int y){
  pilha_respostas_i [w++] = y;
}

void empilha_respostas_j (int y){
  pilha_respostas_j [z++] = y;
}

int desempilha_caminhos_i (){
  return pilha_caminhos_i [--t];
}

int desempilha_caminhos_j (){
  return pilha_caminhos_j [--s];
}

int desempilha_respostas_i (){
  return pilha_respostas_i [--w];
}

int desempilha_respostas_j (){
  return pilha_respostas_j [--z];
}

int pilhavazia_caminhos_i (){
  return t <= 0;
}

int pilhavazia_caminhos_j (){
  return s <= 0;
}

int pilhavazia_respostas_i (){
  return w <= 0;
}

int pilhavazia_resposta_j (){
  return z <= 0;
}

int main (){

  FILE * arquivo;

  int ti, tj, si, sj, n, m, i, j, labirinto[MAX][MAX]; /* variáveis de leitura */
  int distancia[MAX][MAX], saida = 0; /* busca em largura */
  int caminho = 0, ok = 0, k, l, cont, fim = 0; /* busca em profundidade (+ saida) */
  char option;

  arquivo = fopen ("labirinto.txt", "r");

  fscanf (arquivo, "%d %d", &ti, &tj);
  /* ti e tj: coordenadas de Thomas */

  fscanf (arquivo, "%d %d", &si, &sj);
  /* si e sj: coordenadas da saída */

  fscanf (arquivo, "%d %d", &n, &m);
  /* n e m: tamanho da matriz */

  /* o labirinto é colocado na matriz labirinto[][] */
  for (i=0; i<n; i++){
    for (j=0; j<m; j++)
    fscanf (arquivo, "%d", &labirinto[i][j]);
  }

  /* BUSCA EM LARGURA */

  /* todas as casas da matriz distância recebem o valor de -1 */
  /* conforme a matriz é preenchida, o valor de -1 nas casas por onde THomas passou
  é alterado; portanto, inicializar a matriz com -1 serve para marcar se Thomas
  já passou ou não por determinada casa */

  for (i=0; i<n; i++){
    for (j=0; j<m; j++)
    distancia [i][j] = -1;
  }

  /* a casa da matriz onde Thomas se encontra recebe 0; a distância começará a ser
  calculada a partir dela */

  distancia[ti][tj] = 0;

  criafilai ();
  criafilaj ();

  /* a posição de Thomas é colocada na fila */

  colocanafilai (ti);
  colocanafilaj (tj);

  /* busca em largura é inicializada */
  /* a bandeira saida indica se a busca atingiu nas coordenadas da saída */

  while (!filavaziai () && !filavaziaj () && !saida){
    i = tiradafilai ();
    j = tiradafilaj ();

    if (i == si && j == sj) saida = 1;

    /* a última condição dos ifs indica se a busca está sendo feito em alguma das
    casas da matriz que estão nos extremos */
    /* por exemplo, se a busca está sendo feita na primeira linha da matriz, não
    é possível "olhar para cima" */

    if (labirinto[i][j+1] == 0 && distancia[i][j+1] == -1 && j != (m-1)){
      distancia[i][j+1] = distancia[i][j] +1;
      colocanafilai (i);
      colocanafilaj (j+1);
    }

    if (labirinto[i+1][j] == 0 && distancia[i+1][j] == -1 && i != (n-1)){
      distancia[i+1][j] = distancia[i][j] + 1;
      colocanafilai (i+1);
      colocanafilaj (j);
    }

    if (labirinto[i-1][j] == 0 && distancia[i-1][j] == -1 && i != 0){
      distancia[i-1][j] = distancia[i][j] + 1;
      colocanafilai (i-1);
      colocanafilaj (j);
    }

    if (labirinto[i][j-1] == 0 && distancia [i][j-1] == -1 && j != 0){
      distancia[i][j-1] = distancia[i][j] + 1;
      colocanafilai (i);
      colocanafilaj (j-1);
    }
  } /* while (!filavaziai () && !filavaziaj () && !saida) */

  /* se a fila estiver vazia e a busca não atingiu a saída, não há saídas possíveis */
  /* nesse caso, não é feita a busca em profundidade e o programa acaba */

  if (!saida){
    printf ("Não existem caminhos possíveis entre Thomas e a saída.\n");
    fim = 1;
  }

  /* no caso de existirem caminhos, a variável caminho recebe o valor do menor
  caminho entre Thomas e a saída e a busca em profundidade para descobrir todos
  os menores caminhos é realizada */

  else{
    caminho = distancia[si][sj];

    criapilha_caminhos_i ();
    criapilha_caminhos_j ();

    /* as coordenadas da saída são empilhadas; a busca é feita da saída em direção
    a Thomas */

    empilha_caminhos_i (si);
    empilha_caminhos_j (sj);

    criapilha_respostas_i ();
    criapilha_respostas_j ();
  }

  /* BUSCA EM PROFUNDIDADE */
  /* a bandeira fim indica se ainda há caminhos possíveis. Caso haja, ela continua
  valendo 0; caso contrário, ela recebe 1 e sai do laço */
  /* o contador armazena o número de respostas possíveis; começa em 1 pois o 1º
  caminho é 1 e não 0 */

  for (cont = 1; !fim; cont++){

    saida = 0;

    /* a bandeira saída indica se Thomas encontrou a saída, isto é, se ele chegou
    nas coordenadas da saída */

    while (!saida){
      i = desempilha_caminhos_i ();
      j = desempilha_caminhos_j ();

     empilha_respostas_i (i);
     empilha_respostas_j (j);

      if (i == ti && j == tj) saida = 1;

      else{
        if (distancia[i][j+1] == (distancia[i][j] - 1) && j != (m-1)){
         empilha_caminhos_i (i);
         empilha_caminhos_j (j+1);
        }

        if (distancia[i+1][j] == (distancia[i][j]-1) && i != (n-1)){
         empilha_caminhos_i (i+1);
         empilha_caminhos_j (j);
        }

        if (distancia[i-1][j] == (distancia[i][j] -1) && i != 0){
         empilha_caminhos_i (i-1);
         empilha_caminhos_j (j);
        }

        if (distancia[i][j-1] == (distancia[i][j] -1) && j != 0){
         empilha_caminhos_i (i);
         empilha_caminhos_j (j-1);
        }

      } /* else */

    } /* while (!saida) */

    printf ("\n");

    printf ("Pressione enter para visualizar o %dº caminho possível:\n", cont);
    scanf ("%c", &option);

    /* impressão dos caminhos e mapas, um por vez */

    for (i=0; i<n; i++){
      for (j=0; j<m; j++){
        ok = 0;
        for (k=0; k<=caminho && !ok; k++){
          if (pilha_respostas_i [k] == i && pilha_respostas_j [k] == j) ok = 1;
        }
        if (ok) printf ("° ");
        if (!ok) printf ("X ");
      }
      printf ("\n");
    }

    /* verifica-se se a pilha que contém os caminhos possíves está vazia */
    /* se ela estiver vazia, não há mais caminhos possíveis; caso contrário, ainda
    há caminhos possíveis */
    /* nesse caso, o programa verifica o topo das pilhas de caminhos e o topo das
    pilhas de respostas. Verifica-se à qual valor da matriz de distância essas
    coordenadas dos topos correspondem. A pilha das respostas é desempilhada até
    que esses valores sejam iguais, isto é, até chegar na bifurcação do labirinto */
    /* as coordenadas que correspondem ao mesmo valor na matriz de distâncias são
    "trocadas" nas pilhas de respostas e o programa retorna à busca em profundidade,
    imprimindo o próximo caminho após a busca ter sido realizada novamente */
    /* nota-se que as pilhas de caminhos não são alteradaa; o topo das duas é
    retirado, mas ao final é empilhado novamente (o topo é apenas avaliado) */

    if (!pilhavazia_caminhos_i () && !pilhavazia_caminhos_j ()){
      i = desempilha_caminhos_i ();
      j = desempilha_caminhos_j ();
      k = desempilha_respostas_i ();
      l = desempilha_respostas_j ();

      while (distancia[i][j] != distancia[k][l]){
        k = desempilha_respostas_i ();
        l = desempilha_respostas_j ();
      }

      empilha_caminhos_i (i);
      empilha_caminhos_j (j);
    } /* if (!pilhavazia_caminhos_i () && !pilhavazia_caminhos_j ()) */

    /* se as pilhas de caminhos estiverem vazias, não há mais caminhos possíveis
    e o programa sai do laço maior */

    if (pilhavazia_caminhos_i () && pilhavazia_caminhos_j ()){
      fim = 1;
      printf ("\n");
      printf ("Não há mais caminhos possíveis entre Thomas e a saída.\n");
      printf ("\n");
    }

  } /* for (cont = 1; !fim; cont++) */

  fclose (arquivo);

  return 0;

} /* int main () */

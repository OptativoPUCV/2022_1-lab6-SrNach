#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
int num;
  for (int i = 0 ; i < 9 ; i ++){
    for (int j = 0 ; j < 9 ; j++){

      if (n->sudo[i][j] != 0){
        num = n->sudo[i][j];

        //Fila y columna
        for (int k = 0 ; k < 9 ; k++){
          if (k != j && n->sudo[i][k] == num) return 0;
          if (i != k && n->sudo[k][j] == num) return 0;
        }

        //Submatriz
        int k = 4, p;
        for(p = 0 ; p < 9 ; p++){
          int x = 3*(k/3) + (p/3);
          int y = 3*(k%3) + (p%3);
          if ((i!=x && j!=y) && n->sudo[x][y] == num) return 0;
        }

      }
    }
  }


  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i; int j; int k = 0;
  Node * new = copy(n);

  for (i = 0 ;i < 9 ; i++){
    for (j = 0 ;j < 9 ; j++){
      if (new->sudo[i][j] == 0){
        k = 1;
      }
      if (k == 1)break;
    }
    if (k == 1)break;
  }
  //printf("%d %d",i,j);

  if (i == 9 && j == 9) return list;

  int num = 1;
  while (num <= 9){
    Node * nn = createNode();
    nn = copy(n);
    nn->sudo[i][j] = num;
    if (is_valid(nn))
      pushBack(list, nn);
    num++;
  }
  return list;
}


int is_final(Node* n){
  for (int i = 0 ; i < 9 ; i++){
    for (int j = 0 ; j < 9 ; j++){
      if (n->sudo[i][j] == 0) return 0;
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
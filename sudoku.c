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
  // Filas
  for (int i = 0 ; i < 9 ; i++){
    int nums [10] = {0};
    for (int j = 0 ; j < 9 ; j++){
      if (nums[n->sudo[i][j]] != 0) return 0;
      else if (n->sudo[i][j] != 0)
        nums[n->sudo[i][j]]++;
    }
  }
  // Columnas
  for (int i = 0 ; i < 9 ; i++){
    int nums [10] = {0};
    for (int j = 0 ; j < 9 ; j++){
      if (nums[n->sudo[j][i]] != 0) return 0;
      else if (n->sudo[j][i] != 0)
        nums[n->sudo[j][i]]++;
    }
  }
  
  // Submatrices
  for (int x = 0 ; x < 9 ; x++){
    int k = x;
    int p;
    int nums[10] = {0};
    for(p = 0 ; p < 9 ; p++){
        int i = 3*(k/3) + (p/3) ;
        int j = 3*(k%3) + (p%3) ;
        if(nums[n->sudo[i][j]] != 0)return 0;
        else if(n->sudo[i][j] != 0)
          nums[n->sudo[i][j]]++;
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
    if (is_valid(nn)) pushBack(list, nn);
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
  Stack *S = createStack();
  push(S,initial);
  
  while (first(S)){
    Node *nn = top(S);
    pop(S);
    if (is_final(nn))return nn;

    List * adjs = get_adj_nodes(nn);
    Node* nodo = first(adjs);
    while (nodo != NULL){
      push(S,nodo);
      nodo = next(adjs);
    }
    (*cont)++;
    free(nodo);
  }
  
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
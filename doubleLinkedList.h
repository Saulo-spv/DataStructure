#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <cstdlib>

// Estrutura do Nó
typedef struct Node{
    Node* ptrNext = NULL;
    Node* ptrPrev = NULL;
    int iValue;
} Node;

// Cabeçalho de Funções
Node* newNode(int);
void insertEnd(Node**, int);
void insertFront(Node**, int);
Node* searchNode(Node*, int);
void insertBefore(Node*, int);
void insertAfter(Node*, int);
void deleteNode(Node*);
void deleteFront(Node**);
void deleteEnd(Node*);
void clearList(Node**);
bool inLoop(Node*);
void showList(Node*);

#endif
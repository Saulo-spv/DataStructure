#include <iostream>
#include <cstdlib>

#include "doubleLinkedList.h"

using std:: cin;
using std:: cout;
using std:: endl;

int main(){

    Node* head1 = NULL;
    
    // Insere elementos de 0 a 9 no final da lista
    for(int c = 0; c < 10; c++){
        insertEnd(&head1, c);
    }
    
    // Insere o elemento 8 no início da lista
    insertFront(&head1, 8);
    
    // Mostra a lista após as inserções
    cout << "List after insertions:" << endl;
    showList(head1);
    
    // Teste para buscar um elemento existente
    int searchValue = 5;
    Node* foundNode = searchNode(head1, searchValue);
    if(foundNode != NULL) {
        cout << "Element " << searchValue << " found." << endl;
    } else {
        cout << "Element " << searchValue << " not found." << endl;
    }
    
    // Teste para buscar um elemento inexistente
    searchValue = 15;
    foundNode = searchNode(head1, searchValue);
    if(foundNode != NULL) {
        cout << "Element " << searchValue << " found." << endl;
    } else {
        cout << "Element " << searchValue << " not found." << endl;
    }
    
    // Insere o valor 7 antes do elemento com valor 0
    insertBefore(head1->ptrNext, 7);
    
    // Mostra a lista após a inserção
    cout << "\nList after insertion of 7 before 0:" << endl;
    showList(head1);
    
    // Insere o valor 10 no final da lista
    insertEnd(&head1, 10);
    cout << "\nList after insertion of 10 at the end:" << endl;
    showList(head1);
    
    // Deleta o primeiro elemento
    deleteFront(&head1);
    cout << "\nList after deleting front node:" << endl;
    showList(head1);
    
    // Deleta o último elemento
    deleteEnd(head1);
    cout << "\nList after deleting end node:" << endl;
    showList(head1);
    
    // Deleta o elemento com valor 5
    Node* nodeToDelete = searchNode(head1, 5);
    if (nodeToDelete != NULL) {
        deleteNode(nodeToDelete);
        cout << "\nList after deleting node with value 5:" << endl;
        showList(head1);
    }
    
    // Libera a memoria
    clearList(&head1);

    // Mostra a lista vazia
    showList(head1);

    // Criação de uma lista com loop
    Node* head = newNode(1);
    head->ptrNext = newNode(2);
    head->ptrNext->ptrNext = newNode(3);
    head->ptrNext->ptrNext->ptrNext = head->ptrNext; // Loop criado

    printf("Lista com loop: %s\n", inLoop(head) ? "Sim" : "Não");

    // Criação de uma lista sem loop
    Node* head2 = newNode(1);
    head2->ptrNext = newNode(2);
    head2->ptrNext->ptrNext = newNode(3);

    printf("Lista sem loop: %s\n", inLoop(head2) ? "Sim" : "Não");

    return 0;
}

// Inicializa um novo Nó
Node* newNode(int iValue){
    Node* temp = (Node*)malloc(sizeof(Node));
    if(temp != NULL){
        temp->iValue = iValue;
        temp->ptrNext = NULL;
        temp->ptrPrev = NULL;
        return temp;
    } else{
        return NULL;
    }
}

// Insere um elemento no final da lista
void insertEnd(Node** head, int iValue){

    Node* temp = newNode(iValue);

    // Insere o Nó no começo da lista caso seja vazia
    if((*head) == NULL){
        (*head) = temp;
    } else{
        // Itera até o fim da lista
        Node* current = (*head);
        while(current->ptrNext != NULL){
            current = current->ptrNext;
        }
        // Inserção do Nó
        current->ptrNext = temp;
        temp->ptrPrev = current;
    }
}

// Insere um elemento no começo da lista
void insertFront(Node** head, int iValue){
    Node* temp = newNode(iValue);

    // Insere o Nó no começo da lista caso seja vazia
    if((*head) == NULL){
        temp = (*head);
    } else{
        // Insere no começo caso a lista não esteja vazia
        temp->ptrNext = (*head);
        (*head)->ptrPrev = temp;
        (*head) = temp;
    }
}

// Retorna o primeiro Nó com o valor buscado
Node* searchNode(Node* head, int iValue){
    if(head == NULL){
        cout << "Empty list!" << endl;
        return NULL;
    } else{
        // percorre a lista até encontrar o valor buscado ou até chegar ao seu final
        Node* current = head;
        while(current != NULL && current->iValue != iValue){
            current = current->ptrNext;
        }
        // Retorna o Nó, caso seja encontrado
        if(current == NULL){
            cout << "Element not found" << endl;
            return NULL;
        } else{
            return current;
        }
    }
}

// Insere antes de um nó, caso ele não seja o head
void insertBefore(Node* index, int iValue){

    // verifica se a Lista é a vazia ou se tentamos inserir antes do cabeçalho
    if(index == NULL){
        cout << "Location is NULL. Impossible to insert." << endl;
        return;
    } else if(index->ptrPrev == NULL){
        cout << "Index is head of list. Use insertFront." << endl;
        return;
    } else{
        // Insere o Nó na posição desejada
        Node* node = newNode(iValue);
        node->ptrNext = index;
        node->ptrPrev = index->ptrPrev;
        index->ptrPrev->ptrNext = node;
        index->ptrPrev = node;
    }
}

// Insere depois de um nó
void insertAfter(Node* index, int iValue){
    // verifica se a Lista está vazia, ou se tentamos inserir no final da lista
    if(index == NULL){
        cout << "Location is NULL. Impossible to insert." << endl;
        return;
    }else if(index->ptrNext == NULL){
        cout << "Index is tail of list. Use insertEnd." << endl;
        return;
    } else{
        // Insere o Nó na posição desejada
        Node* node = newNode(iValue);
        node->ptrNext = index->ptrNext;
        node->ptrPrev = index;
        index->ptrNext->ptrPrev = node;
        index->ptrNext = node;
    }
}

// Delete um nó
void deleteNode(Node* node){
    if(node == NULL){
        cout << "Node is NULL. Cannot delete." << endl;
        return;
    }

    // Verifica se o nó é o primeiro ou o último da lista
    if(node->ptrNext == NULL || node->ptrNext == NULL){
        cout << "Node is head or tail. Use deleteFront or deleteEnd." << endl;
    }

    // Atualiza os ponteiros dos nós vizinhos para remover o nó 'node'
    node->ptrNext->ptrPrev = node->ptrPrev;
    node->ptrPrev->ptrNext = node->ptrNext;
    
    // Libera a memória do nó
    free(node);
}

// Deleta o nó no início da lista
void deleteFront(Node** head){
    if (*head == NULL){
        cout << "List is empty. Cannot delete front node." << endl;
        return;
    }

    // Verifica se há apenas um nó na lista
    if ((*head)->ptrNext == NULL) {
        free((*head));
        (*head) = NULL;
        return;
    }

    // Salva o endereço do nó a ser excluído
    Node* temp = *head;

    // Atualiza 'head' para apontar para o próximo nó
    *head = (*head)->ptrNext;

    // Atualiza o ponteiro 'ptrPrev' do novo primeiro nó para NULL
    if (*head != NULL){
        (*head)->ptrPrev = NULL;
    }

    // Libera a memória do nó excluído
    free(temp);
}

// Deleta o nó no final da lista
void deleteEnd(Node* head){
    if (head == NULL) {
        cout << "List is empty. Cannot delete end node." << endl;
        return;
    }

    // Verifica se há apenas um nó na lista
    if (head->ptrNext == NULL) {
        free(head);
        head = NULL;
        return;
    }

    // Encontra o penúltimo nó
    Node* current = head;
    while (current->ptrNext->ptrNext != NULL) {
        current = current->ptrNext;
    }

    // Libera a memória do último nó
    free(current->ptrNext);
    // Atualiza o ponteiro 'ptrNext' do penúltimo nó para NULL, indicando o novo último nó
    current->ptrNext = NULL;
}

// Deleta uma lista e limpa a memoria alocada
void clearList(Node** head) {
    if (*head == NULL) {
        return;
    }

    // Deleta todos os nós exceto o último
    while ((*head)->ptrNext != NULL) {
        Node* current = *head;
        *head = (*head)->ptrNext;
        (*head)->ptrPrev = NULL;
        free(current);
    }

    // Deleta o último nó
    free(*head);
    *head = NULL;
}

bool inLoop(Node* head) {
    if (head == NULL) {
        // Se a lista estiver vazia não pode haver loop
        return false;
    }

    Node* fast = head->ptrNext;
    Node* slow = head;

    while (fast != NULL && fast != slow) {
        fast = fast->ptrNext;
        if (fast != NULL) {
            fast = fast->ptrNext;
            slow = slow->ptrNext;
        }
    }

    // Se fast atingiu o final da lista, não há loop
    return (fast != NULL);
}


// Mostra a lista
void showList(Node* head){
    if(head == NULL){
        cout << "Empty list!" << endl;
    } else{
        // Imprime os valores das lista
        Node* current = head;
        while(current != NULL){
            cout << current->iValue << "   ";
            current = current->ptrNext;
        }
        cout << endl;
    }
}
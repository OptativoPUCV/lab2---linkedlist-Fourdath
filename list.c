#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list = malloc(sizeof(List));
  list -> head = NULL;
  list -> tail= NULL;
  return list;
}

void * firstList(List * list) {
    if (list == NULL || list -> head == NULL) {
        return NULL;
    }
    list -> current = list -> head;
    return list -> current -> data;   
}

void * nextList(List * list) {
  if (list == NULL || list -> current == NULL || list -> current->next == NULL) {
    return NULL;
  }
  list -> current = list -> current -> next;
  return list -> current -> data;
}

void * lastList(List * list) {
  if(list == NULL || list-> tail == NULL){
    return NULL;
  }
  list-> current = list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if(list == NULL ||list -> current == NULL|| list -> current -> prev== NULL){
    return NULL;
  }
  list->current = list->current->prev;
  return list->current->data;
    
}

void pushFront(List * list, void * data) {
  Node * nuevo_nodo = createNode(data);
  if(list->head == NULL) {
    list->head = nuevo_nodo;
    list->tail = nuevo_nodo;
    list->current = nuevo_nodo;
  }  
  else{
    nuevo_nodo->next = list->head;
    list->head->prev = nuevo_nodo;
    list->head = nuevo_nodo;

  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list->current == NULL) {
    pushBack(list, data);
  } 
  else{
    Node * nuevo_nodo = createNode(data);  
    Node * nodo_actual = list->current;
    Node * nodo_siguiente = nodo_actual->next;
    nuevo_nodo->prev = nodo_actual;
    nuevo_nodo->next = nodo_siguiente;
    if(nodo_siguiente != NULL) {
      nodo_siguiente->prev = nuevo_nodo;
    } 
    else{
      list->tail = nuevo_nodo;
    }
    nodo_actual->next = nuevo_nodo;
    list->current = nuevo_nodo;
  }
}
 

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list == NULL || list->current == NULL) {
    return NULL;
  } 

  Node* current = list->current;
  void* data = current->data;

  if (current->prev == NULL) {
    list->head = current->next;
    if (current->next != NULL) {
      current->next->prev = NULL;
    }
  } 
  else if (current->next == NULL) {
    list->tail = current->prev;
    if (current->prev != NULL) {
      current->prev->next = NULL;
    }
  } 

  else {
    current->prev->next = current->next;
    current->next->prev = current->prev;
  }
  free(current);
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
/*
  Raúl Negrón
  801-13-4680
  CCOM3034 - Fall 2014

  deque.h

  This file contains the source code for the DEQUE class definition.
  
*/

#ifndef DEQUE_H
#define DEQUE_H

typedef int ElementType;

struct Node {
  Node* next;
  Node* prev;
  ElementType data;
};

class Deque {

  private:
    Node* head;
    Node* tail;
    int count;

  public:
    Deque();
    bool empty();
    void push_front(ElementType);
    void push_back(ElementType);
    void pop_front();
    void pop_back();
    ElementType getFront();
    ElementType getBack();
    void print();

};

#endif

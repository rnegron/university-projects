/*
  Raúl Negrón
  801-13-4680
  CCOM3034 - Fall 2014

  deque.cpp

  This file contains the source code for the implementation of the
  Deque class. Deque (pronounced "deck") is shorthand for "double-ended
  queue". This data structure allows for insertion and removal of
  elements in the beginning and the end of the deque.

  This implementation consists of a doubly linked list. All functions,
  except print() are O(1) efficient.

*/


#include "deque.h"
#include <iostream>

// Constructor
Deque::Deque() {
  head = NULL;
  tail = NULL;
  count = 0;

}

// Return true if empty, false otherwise
bool Deque::empty() {
  return (count == 0) ? true : false;
}

// push_front inserts elem into the start of the deque
void Deque::push_front(ElementType elem) {

  // Create a new node for inserting at the start
  Node* temp = new Node;
  temp->data = elem;
  temp->next = NULL;
  temp->prev = NULL;

  // If the linked list is empty, the new element is now
  // the head and the tail
  if (empty()) head = tail = temp;

  else {
    // Add the node to the beginning of the list
    // and fix the links
    temp->next = head;
    head->prev = temp;
    head = temp;
  }

  // Keep track of the amount of nodes
  count++;

}

// push_back inserts elem into the end of the deque
void Deque::push_back(ElementType elem) {

  // Create a new node for inserting at the end
  Node* temp = new Node;
  temp->data = elem;
  temp->next = NULL;
  temp->prev = NULL;

  // If the linked list is empty, the new element is now
  // the head and the tail
  if (empty()) head = tail = temp;

  else {
    // Add the node to the end of the list
    // and fix the links
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
  }

  // Keep track of the amount of nodes
  count++;
}


// pop_front deletes the first node
void Deque::pop_front() {

  if (empty()) std::cout << "The Deque is empty! Try adding some elements."
                         << std::endl;

  // The deque is not empty, proceed
  else {

    Node* temp = head;

    // Reorganize the nodes
    if (head->next != NULL) {
      head = head->next;
      head->prev = NULL;

    } else {
      head = NULL;
    }

    // Keep track of the amount of nodes
    count--;

    delete temp;

  }
}

// pop_back deletes de last node
void Deque::pop_back() {

  if (empty()) std::cout << "The Deque is empty! Try adding some elements."
                         << std::endl;

  // The deque is not empty, proceed
  else {

    Node* temp = tail;

    // Reorganize the nodes
    if (tail->prev != NULL) {
      tail = tail->prev;
      tail->next = NULL;

    } else {
      tail = NULL;
    }

    // Keep track of the amount of nodes
    count--;

    delete temp;

  }
}

// getFront returns the first node's data
ElementType Deque::getFront() {

  if (empty()) {
     std::cout << "The Deque is empty! Try adding some elements and ignore "
               << "the returned -1 value." << std::endl;
     return -1;
   }

  // The deque is not empty, proceed
  else return head->data;

}

// getBack returns the last node's data
ElementType Deque::getBack() {

  if (empty()) {
   std::cout << "The Deque is empty! Try adding some elements and ignore "
             << "the returned -1 value." << std::endl;
   return -1;
 }

  // The deque is not empty, proceed
  else return tail->data;
}

// print goes through the doubly-linked list and outputs
// the respective node's data
void Deque::print() {

  if (empty()) std::cout << "The Deque is empty! Try adding some elements."
                         << std::endl;
  else {

    Node* step = new Node;
    step->next = head;
    step = step->next;

    // While step is not NULL, output the contents of step->data
    // and move step to the next node

    std::cout << "PRINTING DEQUE.... ";

    while (step) {
      std::cout << step->data << " ";
      step = step->next;
    }

    std::cout << std::endl;
  }
}

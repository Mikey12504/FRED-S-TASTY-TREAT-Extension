#ifndef TwoDLinkedList_H
#define TwoDLinkedList_H
#include "LinkedList.h"
#include "Node.h"
#include <string>
#include <vector>

class TwoDLinkedList {
public:
    TwoDLinkedList();
    ~TwoDLinkedList();
    
    // Add new linked list
    // In order to add new linkedlist to the 2D, its head will be taken
    void insert(LinkedList* LinkedList);

    // Remove the header Node of the linkedlist
    void remove(std::string id);

    // Get the first element of 2d Linked List
    LinkedList *getFirst();

    // Get an element of the LinkedList by the category of the element
    LinkedList *getByCat(std::string cat);

    // Get an food item of the linked list
    Node *getById(std::string id);

    // Add new food item to the corresponding LinkedList
    void appendNode(std::string cat, Node *node);

    // Get the next available id in the system
    int getNextId();

private:
    // Head pointer of Two-Dimensional LinkedList
    LinkedList *head;

    // // number of LinkedList in the 2D linkedlist
    int count;
};

#endif
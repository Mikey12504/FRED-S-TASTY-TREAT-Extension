#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <vector>
#define MAX_CAT_LEN 10

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  LinkedList *next;
  std::string category;

  // Add a new Node at the back
  void append(Node *node);

  // Remove the Node base on the ID
  void remove(std::string id);

  // Get Node
  Node *getFirst();
  Node *getById(std::string id);

  // Utility methods
  bool isEmpty();
  int size();
  // Get the next Id of all the Nodes in the LinkedList
  int getNextId();

  // Get all prices
  std::vector<float> getPrices();

  // Sort the LinkedList by alphabetical order
  void sortByAlpha();
  
  // Check if category is in correct format
  static bool isValidCategory(std::string cat);
private:
  // the beginning of the list
  Node *head;

  // how many nodes are there in the list?
  unsigned count;

  // the end of the list
  Node *tail;

};

#endif // LINKEDLIST_H
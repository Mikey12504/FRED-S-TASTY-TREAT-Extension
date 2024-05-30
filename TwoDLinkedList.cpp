#include "TwoDLinkedList.h"
#include "LinkedList.h"
#include "Node.h"
#include <string>
#include <vector>

TwoDLinkedList::TwoDLinkedList() : head(nullptr), count(0) {}

TwoDLinkedList::~TwoDLinkedList(){
    // Deallocate all LinkedList within the  2d Linked list 
    while (this->head != nullptr) {
        LinkedList *temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
}

void TwoDLinkedList::insert(LinkedList* list) {
    if (!this->head) {
        this->head = list;
    } else {
        LinkedList *current = this->head;
        while(current->next) {
            current = current->next;
        }
        current->next = list;
    }
    // Ensure the last one is null pointer
    list->next = nullptr;
    this->count ++;
}

// Remove the header Node of the linkedlist
void TwoDLinkedList::remove(std::string id) {
    LinkedList *current = this->head;
    // Find the Linked contain the id and remove
    while (current != nullptr) {
        current->remove(id);
        current = current->next;
    }
};

// Get the first element of 2d Linked List
LinkedList *TwoDLinkedList::getFirst() { return this->head; };

// Get element of the LinkedList by the category of the element
LinkedList *TwoDLinkedList::getByCat(std::string cat) {
    LinkedList *current = this->head;
    LinkedList *result = nullptr;

    while (current != nullptr) {
        if (current->category.compare(cat) == 0) {
            result = current;
        }
        current = current->next;
    }
    return result;
};

// Get an food item of the linked list
Node *TwoDLinkedList::getById(std::string id) {
    Node *result = nullptr;
    LinkedList *current = this->head;
    
    while (current != nullptr) {
        Node *find = current->getById(id);
        if (find) {
            result = find;
        } 
        current = current->next;
    }
    return result;
};

// Add new food item to the corresponding LinkedList
void TwoDLinkedList::appendNode(std::string cat, Node *node) {
    LinkedList *current = this->head;
    while (current) {
        if (current->category == cat) {
            current->append(node);
        }
        current = current->next;
    } 
};

// Get the next available id in the system
int TwoDLinkedList::getNextId() {
    int LargestId = 0;
    LinkedList *currentCat = this->head;

    while (currentCat != nullptr) {
        Node *current = currentCat->getFirst();
        while (current !=  nullptr) {
            // Remove the first character "F"
            std::string numStr = current->data->id.substr(1);
            // Convert to int 
            int number = std::stoi(numStr);
            if (number > LargestId) {
                LargestId = number;
            }

            current = current->next;
        }
        currentCat = currentCat->next;
    }
    // The next lagest number
    return LargestId + 1; 
};


#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct doublyLinkedNode {
    struct doublyLinkedNode *prev;
    struct doublyLinkedNode *next;
    char data[100];
} DoublyLinkedNode;

typedef struct DoublyLinkedList {
    DoublyLinkedNode *firstNode;
    DoublyLinkedNode *lastNode;
} DoublyLinkedList;

DoublyLinkedNode* createRootNode(const char* str) {
    DoublyLinkedNode *n = (DoublyLinkedNode*)malloc(sizeof(DoublyLinkedNode));
    strncpy(n->data, str, sizeof(n->data)-1);
    n->prev = NULL;
    n->next = NULL;
    return n;
}

// acts like a `push`; insert to the end of the list
void insert(DoublyLinkedList *l, const char* str) {
    DoublyLinkedNode *n = (DoublyLinkedNode*)malloc(sizeof(DoublyLinkedNode));
    strncpy(n->data, str, sizeof(n->data)-1);
    n->prev = l->lastNode;
    l->lastNode->next = n;
    l->lastNode = n;
    n->next = NULL;
}

// acts like a `pop`; remove the last element of the list
void delete(DoublyLinkedList *l) {
    if(l->lastNode == NULL) return;
    DoublyLinkedNode *to_delete = l->lastNode;
    l->lastNode = to_delete->prev;
    free(to_delete);
}

// returns true if the data inside `data` == `str``
// helper function for `find()`
bool isEquivalent(const char data[100], const char* str) {
    return strcmp(data, str) == 0;
}

// Tells you the index where the first instance of `str` was found on the list
// returns -1 if nothing was found
int find(DoublyLinkedList *l, const char* str) {
    DoublyLinkedNode *it = l->firstNode;
    int counter = 0;

    while(it != NULL) {
        if(isEquivalent(it->data, str)) return counter;
        counter++;
        it = it->next;
    }

    return -1;
}

DoublyLinkedList* createList(const char* str) {
    DoublyLinkedList *l = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    DoublyLinkedNode* root = createRootNode(str);
    l->firstNode = root;
    l->lastNode = root;
    return l;
}

int main() {
    DoublyLinkedList *lst = createList("Luis Victoria");
    insert(lst, "Second element");
    insert(lst, "Third element");
    delete(lst);
    insert(lst, "foo");

    int test_foo = find(lst, "foo"); // should be 2
    int test_bar = find(lst, "bar"); // should be -1
}

#include <stdio.h>
#include <stdlib.h>

// Struct for a Node
struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
};

// Search for a given element in the linked list
int search(struct Node* head, int element) {
    struct Node* cur = head;
    int pos = 0;

    while (cur != NULL) {
        if (cur->value == element) {
            return pos;
        }
        cur = cur->next;
        pos++;
    }
    return -1;
}

// Insert an element at the middle
void insertAtMid(struct Node** head, int element, int pos) {
    if (pos < 0) {
        printf("Invalid Position\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = element;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (pos == 0) {
        newNode->next = *head;
        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        *head = newNode;
    } else {
        struct Node* cur = *head;
        int curPos = 0;

        while (cur != NULL && curPos < pos - 1) {
            cur = cur->next;
            curPos++;
        }

        if (cur == NULL) {
            printf("Invalid Position\n");
            return;
        }

        newNode->next = cur->next;
        newNode->prev = cur;
        if (cur->next != NULL) {
            cur->next->prev = newNode;
        }
        cur->next = newNode;
    }
}

// Insert an element at the head
void insertAtHead(struct Node** head, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = element;
    newNode->next = *head;
    newNode->prev = NULL;

    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Insert an element at the end
void insertAtEnd(struct Node** head, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = element;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* cur = *head;

        while (cur->next != NULL) {
            cur = cur->next;
        }

        cur->next = newNode;
        newNode->prev = cur;
    }
}

// Delete an element at the middle
void deleteElement(struct Node** head, int element) {
    struct Node* cur = *head;

    while (cur != NULL) {
        if (cur->value == element) {
            if (cur->prev != NULL) {
                cur->prev->next = cur->next;
            } else {
                *head = cur->next;
            }
            if (cur->next != NULL) {
                cur->next->prev = cur->prev;
            }
            free(cur);
            return;
        }
        cur = cur->next;
    }

    printf("Element Not Found\n");
}

// Delete the head element
void deleteHead(struct Node** head) {
    if (*head == NULL) {
        printf("Empty linked list\n");
        return;
    }

    struct Node* h = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(h);
}

// Delete the end element
void deleteEnd(struct Node** head) {
    if (*head == NULL) {
        printf("Empty linked list\n");
        return;
    }

    struct Node* cur = *head;

    while (cur->next != NULL) {
        cur = cur->next;
    }

    if (cur->prev != NULL) {
        cur->prev->next = NULL;
    } else {
        *head = NULL;
    }

    free(cur);
}

// Print all elements
void printList(struct Node* head) {
    struct Node* cur = head;

    while (cur != NULL) {
        printf("%d", cur->value);
        // Add '<-->' between the elements
        if (cur->next != NULL) {
            printf(" <--> ");
        }
        cur = cur->next;
    }

    printf("\n");
}

// Free the memory
void freeList(struct Node* head) {
    struct Node* cur = head;

    while (cur != NULL) {
        struct Node* del = cur;
        cur = cur->next;
        free(del);
    }
}

// Print linked list and search elements
int main() {
    struct Node* head = NULL;
    struct Node* originalList = NULL;

    // Insert initial elements
    insertAtEnd(&head, 23);
    insertAtEnd(&head, 52);
    insertAtEnd(&head, 19);
    insertAtEnd(&head, 9);
    insertAtEnd(&head, 100);

    // Create a copy of the original list
    struct Node* cur = head;
    while (cur != NULL) {
        insertAtEnd(&originalList, cur->value);
        cur = cur->next;
    }

    printf("Original linked list: ");
    printList(originalList);

    // Search for an element
    int searchElement;
    printf("Searching element: ");
    scanf("%d", &searchElement);

    int pos = search(head, searchElement);
    if (pos != -1) {
        printf("Position of the searched element: %d\n", pos);
    } else {
        printf("Element Not Found\n");
    }

    // Insert an element at the middle
    int insertElement, insertPos;
    printf("Inserting element: ");
    scanf("%d", &insertElement);
    printf("Inserting position at: ");
    scanf("%d", &insertPos);

    // Create a copy of the current list
    struct Node* curHead = NULL;
    cur = head;
    while (cur != NULL) {
        insertAtEnd(&curHead, cur->value);
        cur = cur->next;
    }

    insertAtMid(&curHead, insertElement, insertPos);
    printf("Original linked list: ");
    printList(originalList);
    printf("After insertion (middle) = ");
    printList(curHead);

    // Insert an element at the head
    int insertHead;
    printf("Inserting element at the head: ");
    scanf("%d", &insertHead);

    // Create a copy of the current list
    cur = head;
    curHead = NULL;
    while (cur != NULL) {
        insertAtEnd(&curHead, cur->value);
        cur = cur->next;
    }

    insertAtHead(&curHead, insertHead);
    printf("Original linked list: ");
    printList(originalList);
    printf("After insertion (head) = ");
    printList(curHead);

    // Insert an element at the end
    int insertEnd;
    printf("Inserting element at the end: ");
    scanf("%d", &insertEnd);

    // Create a copy of the current list
    cur = head;
    curHead = NULL;
    while (cur != NULL) {
        insertAtEnd(&curHead, cur->value);
        cur = cur->next;
    }

    insertAtEnd(&curHead, insertEnd);
    printf("Original linked list: ");
    printList(originalList);
    printf("After insertion (end) = ");
    printList(curHead);

    // Delete an element (middle)
    int delValue;
    printf("Deleting element (middle): ");
    scanf("%d", &delValue);

    // Create a copy of the current list
    cur = head;
    curHead = NULL;
    while (cur != NULL) {
        insertAtEnd(&curHead, cur->value);
        cur = cur->next;
    }

    deleteElement(&curHead, delValue);
    printf("Original linked list: ");
    printList(originalList);
    printf("After deletion (middle) = ");
    printList(curHead);

    // Delete the head element
    // Create a copy of the current list
    cur = head;
    curHead = NULL;
    while (cur != NULL) {
        insertAtEnd(&curHead, cur->value);
        cur = cur->next;
    }

    deleteHead(&curHead);
    printf("Original linked list: ");
    printList(originalList);
    printf("After deletion (head) = ");
    printList(curHead);

    // Delete the end element
    // Create a copy of the current list
    cur = head;
    curHead = NULL;
    while (cur != NULL) {
        insertAtEnd(&curHead, cur->value);
        cur = cur->next;
    }

    deleteEnd(&curHead);
    printf("Original linked list: ");
    printList(originalList);
    printf("After deletion (end) = ");
    printList(curHead);

    // Free the memory
    freeList(originalList);
    freeList(curHead);

    return 0;
}

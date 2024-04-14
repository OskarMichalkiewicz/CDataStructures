#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *next;
};

typedef struct Node node;

node *create(int value) {
  node *new = malloc(sizeof(node));
  new->value = value;
  new->next = NULL;
  return new;
};
node *unshift(node **head, int value) {
  node *new = create(value);
  new->next = *head;
  *head = new;
  return new;
}
node *push(node **tail, int value) {
  node *new = create(value);
  (*tail)->next = new;
  *tail = new;
  return new;
};
int pop(node *head) {
  int ret = -1;
  if (head->next == NULL) {
    ret = head->value;
    free(head);
    return ret;
  }
  node *curr = head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }
  ret = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return ret;
}
int shift(node **head) {
  int ret = -1;
  if (*head == NULL)
    return ret;
  node *next = (*head)->next;
  ret = (*head)->value;
  free(*head);
  *head = next;
  return ret;
}
void print(node *head) {
  node *curr = head;
  while (curr != NULL) {
    printf("%d - ", curr->value);
    curr = curr->next;
  }
}

int main() {
  node *head = create(22);
  node *tail = create(11);
  head->next = tail;
  push(&tail, 420);
  push(&tail, 44);
  push(&tail, 4);
  pop(head);
  shift(&head);
  unshift(&head, 69);

  print(head);

  return 0;
}

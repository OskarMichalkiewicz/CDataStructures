#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
  struct Node *prev;
} node;

node *create(int value) {
  node *new = malloc(sizeof(node));
  new->value = value;
  new->next = NULL;
  new->prev = NULL;
  return new;
}

node *unshift(node **head, int value, int *length) {
  node *new = create(value);
  new->next = *head;
  (*head)->prev = new;
  *head = new;
  (*length)++;
  return new;
}

node *push(node **tail, int value, int *length) {
  node *new = create(value);
  (*tail)->next = new;
  new->prev = *tail;
  *tail = new;
  (*length)++;
  return new;
}

node *pop(node **tail, int *length) {
  node *ret = NULL;
  if (*tail == NULL) {
    return ret;
  }
  ret = *tail;
  *tail = (*tail)->prev;
  (*tail)->next = NULL;
  free((*tail)->next);
  (*length)--;
  return ret;
}
node *shift(node **head, int *length) {
  node *ret = NULL;
  if (*head == NULL)
    return ret;
  ret = *head;
  *head = (*head)->next;
  (*head)->prev = NULL;
  free((*head)->prev);
  (*length)--;
  return ret;
}
void print(node *head) {
  node *curr = head;
  while (curr != NULL) {
    printf("%d <-> ", curr->value);
    curr = curr->next;
  }
}
void printb(node *tail) {
  node *curr = tail;
  while (curr != NULL) {
    printf("%d <-> ", curr->value);
    curr = curr->prev;
  }
}
node *get(node **head, int idx) {
  node *curr = *head;
  for (int i = 0; i < idx; i++) {
    curr = curr->next;
  }
  return curr;
}
node *insert(node **head, node **tail, int idx, int value, int *length) {
  if (idx == 0)
    return unshift(head, value, length);
  if (idx == *length)
    return push(tail, value, length);
  if (idx > *length || idx < 0)
    return NULL;
  node *new = create(value);
  node *curr = get(head, idx);
  curr->prev->next = new;
  new->prev = curr->prev;
  curr->prev = new;
  new->next = curr;
  (*length)++;
  return new;
}
node *del(node **head, node **tail, int value, int *length) {
  if ((*head)->value == value)
    return shift(head, length);
  if ((*tail)->value == value)
    return pop(tail, length);
  node *curr = *head;
  while (curr->value != value) {
    curr = curr->next;
  };
  curr->next->prev = curr->prev;
  curr->prev->next = curr->next;
  (*length)--;
  return curr;
}

int main() {
  node *head = create(22);
  node *tail = create(11);
  int length = 2;
  head->next = tail;
  tail->prev = head;
  push(&tail, 2, &length);
  push(&tail, 420, &length);
  push(&tail, 69, &length);
  push(&tail, 3, &length);
  pop(&tail, &length);
  shift(&head, &length);
  unshift(&head, 420, &length);
  insert(&head, &tail, 2, 69, &length);
  del(&head, &tail, 69, &length);
  printf("%d \n", length);
  print(head);
  printf("\n");
  printb(tail);
  return 1;
}

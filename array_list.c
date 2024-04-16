#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct array_list {
  size_t capacity;
  int *array;
  size_t length;
} ArrayList;

void shiftUp(ArrayList *arr, int idx) {
  for (int i = arr->length; i > idx; i--) {
    arr->array[i] = arr->array[i - 1];
  }
}
void shiftDown(ArrayList *arr, int idx) {
  for (int i = idx; i < arr->length; i++) {
    arr->array[i] = arr->array[i + 1];
  }
  arr->array[arr->length] = 0;
}
void *createArray(int size) {
  ArrayList *array_list = (ArrayList *)malloc(sizeof(int));
  array_list->array = malloc(size * sizeof(int));
  array_list->capacity = size;
  array_list->length = 0;
  return array_list;
};
void resize(ArrayList *arr) {
  int *new = malloc((arr->capacity << 2) * sizeof(int));
  memcpy(new, arr->array, arr->length * sizeof(int));
  free(arr->array);
  arr->array = new;
  arr->capacity <<= 2;
}
void push(ArrayList *arr, int value) {
  if (arr->length == arr->capacity) {
    resize(arr);
    arr->capacity <<= 2;
  }
  arr->array[arr->length] = value;
  arr->length++;
}
void prepend(ArrayList *arr, int value) {
  if (arr->length == arr->capacity) {
    resize(arr);
    arr->capacity <<= 2;
  }
  if (arr->length > 0)
    shiftUp(arr, 0);
  arr->array[0] = value;
  arr->length++;
}
void insertAt(ArrayList *arr, int idx, int value) {
  if (idx < 0 || idx > arr->capacity)
    return;
  arr->length++;
  if (arr->length == arr->capacity)
    resize(arr);
  if (arr->array[idx])
    shiftUp(arr, idx);
  arr->array[idx] = value;
}
void removeAt(ArrayList *arr, int idx) {
  if (idx < 0 || idx > arr->capacity)
    return;
  shiftDown(arr, idx);
  arr->length--;
}
void removeValue(ArrayList *arr, int value) {
  for (int i = 0; i < arr->length; i++) {
    if (arr->array[i] == value)
      removeAt(arr, i);
  }
}

int main() {
  ArrayList *array_list = createArray(100);
  for (int i = 0; i < 20; i++) {
    push(array_list, i);
  }
  for (int i = 0; i < 20; i++) {
    prepend(array_list, 69);
  }
  insertAt(array_list, 3, 420);
  removeAt(array_list, 3);
  removeValue(array_list, 2);
  for (int i = 0; i < array_list->length; i++) {
    printf("%d\n", array_list->array[i]);
  }
  printf("%d\n", ((int)array_list->length));

  return 1;
}

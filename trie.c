#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 26

typedef struct node {
  char key;
  struct node *children[NUM_CHARS];
  bool isEnd;
} node;
node *create(unsigned char key) {
  node *new = malloc(sizeof(node));
  for (int i = 0; i < NUM_CHARS; i++) {
    new->children[i] = NULL;
  }
  new->key = key;
  new->isEnd = false;
  return new;
}
void freeTrienode(node *node) {
  if (node->key == '\0')
    return;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (node->children[i] != NULL) {
      freeTrienode(node->children[i]);
    } else {
      continue;
    }
  }
  free(node);
}

void insert(node *root, char *signedText) {

  unsigned char *text = (unsigned char *)signedText;
  node *temp = root;

  for (int i = 0; text[i] != '\0'; i++) {
    int idx = (int)text[i] - 'a';
    if (temp->children[idx] == NULL) {
      temp->children[idx] = create(text[i]);
    };
    temp = temp->children[idx];
  }
  temp->isEnd = true;
}

bool search(node *root, char *word) {
  node *temp = root;
  for (int i = 0; word[i] != '\0'; i++) {
    int idx = (int)word[i] - 'a';
    if (temp->children[idx] == NULL)
      return false;
    temp = temp->children[idx];
  }
  if (temp != NULL && temp->isEnd)
    return true;
  return false;
}

void print(node *root) {
  if (!root) {
    return;
  }
  if (root->key == '\0')
    printf("*");
  if (root->isEnd)
    printf("[");
  printf("%c", root->key);
  if (root->isEnd)
    printf("]");
  for (int i = 0; i < NUM_CHARS; i++) {
    if (root->children[i] != NULL) {
      if (root->key == '\0') {
        printf("\n\\");
        printf("\n `-> ");
      } else if (root->isEnd) {
        printf("\n|%*s\\ ", i, "");
        printf("\n|%*s `-> ", i, "");
      } else
        printf(" -> ");
      print(root->children[i]);
    }
  }
}

bool find(node *root, char *signedText) {
  unsigned char *text = (unsigned char *)signedText;
  int length = strlen(signedText);
  node *temp = root;
  for (int i = 0; i < length; i++) {
    if (temp->children[text[i]] == NULL) {
      return false;
    }
    temp = temp->children[text[i]];
  }
  return temp->isEnd;
}

bool deleteWord(node *root, char *word) {

  node *curr = root;
  node *lastBrnach = NULL;
  char lastBrnachChar = 'a';
  int length = strlen(word);

  for (int i = 0; i < length; i++) {
    int idx = (int)word[i] - 'a';
    if (curr->children[idx] == NULL)
      return false;
    else {
      int count = 0;
      for (int j = 0; j < NUM_CHARS; j++) {
        if (curr->children[j] != NULL)
          count++;
      }
      if (count > 1) {
        lastBrnach = curr;
        lastBrnachChar = word[i];
      }
      curr = curr->children[idx];
    }
  }

  int count = 0;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (curr->children[i] != NULL) {
      count++;
    }
  }
  if (count > 0) {
    curr->isEnd = false;
    return true;
  }
  if (lastBrnach != NULL) {
    lastBrnach->children[lastBrnachChar - 'a'] = NULL;
    return true;
  } else {
    root->children[word[0] - 'a'] = NULL;
    return true;
  }
}

int main() {
  node *root = create('\0');
  insert(root, "kin");
  insert(root, "kit");
  insert(root, "cat");
  insert(root, "cattle");
  insert(root, "hap");
  insert(root, "happy");
  insert(root, "far");
  insert(root, "fart");
  insert(root, "farse");

  printf("before deleting cat");
  printf("\n");
  printf("\n");
  print(root);
  printf("\n");
  deleteWord(root, "cat");
  printf("\n");
  printf("after deleting cat");
  printf("\n");
  printf("before deleting hap");
  printf("\n");
  printf("\n");
  print(root);
  printf("\n");
  deleteWord(root, "hap");
  printf("\n");
  printf("after deleting hap");
  printf("\n");
  printf("before deleting happy");
  printf("\n");
  print(root);
  printf("\n");
  deleteWord(root, "happy");
  printf("\n");
  printf("after deleting happy");
  printf("\n");
  printf("before deleting kin");
  printf("\n");
  print(root);
  printf("\n");
  deleteWord(root, "kin");
  printf("\n");
  printf("after deleting kin");
  printf("\n");
  printf("before deleting cattle");
  printf("\n");
  print(root);
  printf("\n");
  deleteWord(root, "cattle");
  printf("\n");
  printf("after deleting cattle");
  printf("\n");
  printf("before deleting kit");
  printf("\n");
  print(root);
  printf("\n");
  deleteWord(root, "kit");
  printf("\n");
  printf("after deleting kit");
  printf("\n");
  print(root);
  printf("\n");
  deleteWord(root, "far");
  print(root);
  printf("\n");
  deleteWord(root, "farse");
  print(root);
  printf("\n");
  free(root);

  return 0;
}

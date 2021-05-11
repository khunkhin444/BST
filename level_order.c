#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buf_size 1024

struct node {
    char *data;
    struct node *left;
    struct node *right;
};

struct node *newNode(char *input) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    (*temp).data = strdup(input);
    (*temp).left = (*temp).right = NULL;
    return temp;
}

struct node *insert(struct node *parent, char *input) {
    if(parent==NULL) {
        parent = newNode(input);
    }
    else if(strcmp(input,(*parent).data)<=0) (*parent).left = insert((*parent).left, input);
    else (*parent).right = insert((*parent).right, input);
    return parent;
}

void inorder(struct node *parent) {
    if(parent==NULL) return;
    inorder((*parent).left);
    printf("%s",(*parent).data);
    inorder((*parent).right);
}

int main() {
    char input[buf_size];
    struct node *root = NULL;
    while(fgets(input,buf_size,stdin)) {
        root = insert(root, input);
    }
    level_order(root);
}

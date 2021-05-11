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

void enqueue(struct node **queue, int *rear, struct node *temp) {
    queue[*rear] = temp;
    (*rear)++;
}

struct node *dequeue(struct node **queue, int *front) {
    (*front)++;
    return queue[*front-1];
}

void level_order(struct node *parent) {
    int front = 0;
    int rear = 0;
    struct node **queue = (struct node **)malloc(sizeof(struct node)*1024);
    struct node *temp = parent;
    while(temp) {
        printf("%s", (*temp).data);
        if((*temp).left) enqueue(queue, &rear, (*temp).left);
        if((*temp).right) enqueue(queue, &rear, (*temp).right);
        temp = dequeue(queue, &front);
    }
}

int main() {
    char input[buf_size];
    struct node *root = NULL;
    while(fgets(input,buf_size,stdin)) {
        root = insert(root, input);
    }
    level_order(root);
}

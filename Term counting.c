#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct stack {
    char *data;
    int cnt;
    struct stack *link;
};

struct node {
    char *data;
    int cnt;
    struct node *left;
    struct node *right;
};

char *getword(char *text, char *word) {
    char *ptr = text;
    char *qtr = word;
    while(*ptr && isspace(*ptr)) ptr++;
    while(*ptr && (!isspace(*ptr) && *ptr!='\n')) {
        *qtr++ = *ptr++;
    }
    *qtr = '\0';
    if(qtr-word==0) return NULL;
    else return ptr;
}

struct stack *stack_insert(struct stack *head, char *word) {
    struct stack *tmp = (struct stack*)malloc(sizeof(struct stack));
    (*tmp).link = head;
    (*tmp).data = strdup(word);
    (*tmp).cnt = 1;
    head = tmp;
    return head;
}

struct stack *stack_find(struct stack *head, char *word) {
    struct stack *tmp = head;
    while(tmp) {
        if(strcmp((*tmp).data, word)==0) return tmp;
        tmp = (*tmp).link;
    }
    return NULL;
}

struct node *newNode(char *word, int count) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    (*temp).data = strdup(word);
    (*temp).cnt = count;
    (*temp).left = (*temp).right = NULL;
    return temp;
}

struct node *node_insert(struct node *parent, char *word, int count) {
    if(parent==NULL) parent = newNode(word, count);
    else if(count<(*parent).cnt) {
        (*parent).left = node_insert((*parent).left, word, count);
    }
    else if(count == (*parent).cnt) {
        if(strcmp(word, (*parent).data)>0) (*parent).left = node_insert((*parent).left, word, count);
        else (*parent).right = node_insert((*parent).right, word, count);
    }
    else (*parent).right = node_insert((*parent).right, word, count);
    return parent;
}


void traversal(struct node *parent) {
    if(parent == NULL) return;
    traversal((*parent).right);
    printf("%s %d\n", (*parent).data, (*parent).cnt);
    traversal((*parent).left);
}

int main() {
    char line[300];
    char *c;
    char *ptr;
    char word[300];
    struct stack *head = NULL;
    struct stack *temp;
    struct node *root = NULL;
    while(fgets(line,300,stdin)) {
        c = line;
        while((c=getword(c,word))) {
            ptr = word;
            if(*ptr == 'A' || *ptr =='a') {
                if((temp=stack_find(head,word))==NULL)
                    head = stack_insert(head, word);
                else (*temp).cnt +=1;
            }
        }
    }
    while(head) {
        root = node_insert(root, (*head).data, (*head).cnt);
        temp = head;
        head = (*head).link;
        free(temp);
    }
    traversal(root);
}

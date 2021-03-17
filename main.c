/***********************************
 * DSA Zadianie 2 - BVS
 *
 * FIIT STU 2021
 * Pavol Hradsky
************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    int height;
    struct node *right;
    struct node *left;
    struct node *parent;
} NODE;

NODE* create_node(int data){
    NODE *result = NULL;
    result = (NODE*)malloc(sizeof(NODE));
    result->data = data;
    return result;
}

void update_height(NODE **new_node, NODE **head){
    NODE *tmp = *new_node;
    int tmp_height = 0;

    while(tmp != *head){
        tmp = tmp->parent;
    }
}

int insert(NODE *new_node, NODE **head){
    NODE *tmp = *head;

    new_node->right = NULL;
    new_node->left = NULL;
    new_node->parent = NULL;
    new_node->height = 0;

    int tmp_height = 0;

    if(tmp == NULL){
        *head = new_node;
        printf("%d\n", (*head)->data);
        return 0;
    }
    while(tmp != NULL){
        if(new_node->data == tmp->data){
            return 2;
        }
        if(new_node->data > tmp->data && tmp->right != NULL){
            tmp = tmp->right;
        } else if(new_node->data < tmp->data && tmp->left != NULL){
            tmp = tmp->left;
        } else if(new_node->data > tmp->data && tmp->right == NULL){
            tmp->right = new_node;
            new_node->parent = tmp;
            return 1;
        } else{
            tmp->left = new_node;
            new_node->parent = tmp;
            return 1;
        }
    }
    return 0;
}

/////////////////////////////////

int _print_t(NODE *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->data);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_t(NODE *tree)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}


////////////////////////////////

int main() {
    NODE *head = NULL;
    insert(create_node(5), &head);
    insert(create_node(10), &head);
    insert(create_node(6), &head);
    insert(create_node(8), &head);
    insert(create_node(3), &head);
    insert(create_node(4), &head);
    insert(create_node(1), &head);
    insert(create_node(11), &head);
    insert(create_node(2), &head);
    insert(create_node(0), &head);
    insert(create_node(7), &head);
    insert(create_node(9), &head);insert(create_node(1), &head);

    print_t(head);
    return 0;
}

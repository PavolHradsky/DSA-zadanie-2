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

NODE *head = NULL;

NODE* create_node(int data){
    NODE *result = NULL;
    result = (NODE*)malloc(sizeof(NODE));
    result->data = data;
    return result;
}

int update_height(NODE **new_node){
    NODE *tmp = *new_node;
    int tmp_height = tmp->height;

    do {
        if (tmp->height > tmp_height) {
            return 0;
        }
        tmp->height = tmp_height;
        printf("Height of node with number %d is %d\n", tmp->data, tmp->height);
        tmp = tmp->parent;
        tmp_height++;
    } while(tmp != NULL);
    return 1;
}

int rotate_left(NODE **node) {
    NODE *tmp = *node;
    NODE *right = tmp->right;

    int isRoot = 0;
    if (right == NULL) {
        return 0;
    }
    if (head == tmp) {
        head = right;
        isRoot = 1;
        right->parent = NULL;
    } else {
        if(tmp->data < tmp->parent->data) {
            (tmp->parent)->left = right;
        } else {
            (tmp->parent)->right = right;
        }
    }
    if(isRoot == 0) {
        right->parent = tmp->parent;
    }
    tmp->parent = right;
    tmp->right = right->left;
    right->left = tmp;

    if (tmp->right == NULL){
        if(tmp->left == NULL){
            tmp->height = 0;
        } else {
            tmp->height = tmp->left->height + 1;
        }
    } else if(tmp->left == NULL) {
        tmp->height = tmp->right->height + 1;
    }
    else if (tmp->right->height > tmp->left->height) {
        tmp->height = tmp->right->height + 1;
    } else {
        tmp->height = tmp->left->height + 1;
    }

    if (right->right == NULL) {
        right->height = right->left->height + 1;
    }
    else if (right->right->height > right->left->height) {
        right->height = right->right->height + 1;
    } else {
        right->height = right->left->height + 1;
    }

    update_height(&right);

    return 1;
}

int rotate_right(NODE **node) {
    NODE *tmp = *node;
    NODE *left = tmp->left;

    int isRoot = 0;
    if (left == NULL) {
        return 0;
    }
    if (head == tmp) {
        head = left;
        isRoot = 1;
        left->parent = NULL;
    } else {
        if(tmp->data < tmp->parent->data) {
            (tmp->parent)->left = left;
        } else {
            (tmp->parent)->right = left;
        }
    }
    if(isRoot == 0) {
        left->parent = tmp->parent;
    }
    tmp->parent = left;
    tmp->left = left->right;
    left->right = tmp;


    if (tmp->right == NULL){
        if(tmp->left == NULL){
            tmp->height = 0;
        } else {
            tmp->height = tmp->left->height + 1;
        }
    } else if(tmp->left == NULL) {
        tmp->height = tmp->right->height + 1;
    }
    else if (tmp->right->height > tmp->left->height) {
        tmp->height = tmp->right->height + 1;
    } else {
        tmp->height = tmp->left->height + 1;
    }

    if (left->left == NULL) {
        left->height = left->right->height + 1;
    }
    else if (left->right->height > left->left->height) {
        left->height = left->right->height + 1;
    } else {
        left->height = left->left->height + 1;
    }
    update_height(&left);

    return 1;
}

int align(NODE **node) {
    NODE *tmp = *node;
    int bf, bfr, bfl;

    while(tmp != NULL) {
        if(tmp->left == NULL) {
            if(tmp->right == NULL) {
                tmp = tmp->parent;
                continue;
            }
            if(tmp->right->height >= 1) {
                if(tmp->right->left != NULL && tmp->right->right == NULL) {
                    rotate_right(&(tmp->right));
                }
                rotate_left(&tmp);
            }
            tmp = tmp->parent;
            continue;
        }
        if(tmp->right == NULL) {
            if(tmp->left->height >= 1) {
                if(tmp->left->right != NULL && tmp->left->left == NULL) {
                    rotate_left(&(tmp->left));
                }
                rotate_right(&tmp);
            }
            tmp = tmp->parent;
            continue;
        }

        bf = tmp->right->height - tmp->left->height;

        if(tmp->right->right != NULL) {
            if(tmp->right->left != NULL) {
                bfr = tmp->right->right->height - tmp->right->left->height;
            } else {
                bfr = tmp->right->right->height + 1;
            }
        } else if(tmp->right->left != NULL) {
            bfr = (tmp->right->left->height + 1) * (-1);
        } else {
            bfr = 0;
        }

        if(tmp->left->right != NULL) {
            if(tmp->left->left != NULL) {
                bfl = tmp->left->right->height - tmp->left->left->height;
            } else {
                bfl = tmp->left->right->height + 1;
            }
        } else if(tmp->left->left != NULL) {
            bfl = (tmp->left->left->height + 1) * (-1);
        } else {
            bfl = 0;
        }

        if(bf < 2 && bf > -2) {
            tmp = tmp->parent;
            continue;
        }
        if(bf <= -2) {
            if(bfl > bfr) {
                rotate_left(&(tmp->left));
            }
            rotate_right(&tmp);
        } else if(bf >= 2) {
            if(bfr < bfl) {
                rotate_right(&(tmp->right));
            }
            rotate_left(&tmp);
        }
        tmp = tmp->parent;
    }

    return 0;
}

int insert(NODE *new_node){
    NODE *tmp = head;

    new_node->right = NULL;
    new_node->left = NULL;
    new_node->parent = NULL;
    new_node->height = 0;

    if(tmp == NULL){
        head = new_node;
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
            update_height(&new_node);
            align(&tmp);
            return 1;
        } else{
            tmp->left = new_node;
            new_node->parent = tmp;
            update_height(&new_node);
            align(&tmp);
            return 1;
        }
    }
    return 0;
}


///////////////////////////////// PRINTF TREE

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
//    insert(create_node(5));
//    insert(create_node(10));
//    insert(create_node(6));
//    insert(create_node(8));
//    insert(create_node(3));
//    insert(create_node(4));
//    insert(create_node(1));
//    insert(create_node(11));
//    insert(create_node(2));
//    insert(create_node(0));
//    print_t(head);
//    insert(create_node(7));
//    insert(create_node(9));
//    insert(create_node(1));
//
//    print_t(head);

//    insert(create_node(24));
//    insert(create_node(12));
//    insert(create_node(5));
//    print_t(head);
//    insert(create_node(30));
//    insert(create_node(20));
//    insert(create_node(45));
//    print_t(head);
//    insert(create_node(11));
//    insert(create_node(13));
//    insert(create_node(9));
//    print_t(head);

//    for (int i = 0; i < 17; ++i) {
//        insert(create_node(i));
//    }
//    print_t(head);

//    insert(create_node(3));
//    insert(create_node(1));
//    insert(create_node(2));
//    print_t(head);

    insert(create_node(40));
    print_t(head);
    insert(create_node(20));
    print_t(head);
    insert(create_node(10));
    print_t(head);
    insert(create_node(25));
    print_t(head);
    insert(create_node(30));
    print_t(head);
    insert(create_node(22));
    print_t(head);
    insert(create_node(50));
    print_t(head);



    return 0;
}

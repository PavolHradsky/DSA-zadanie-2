/***********************************
 * DSA Zadianie 2 - BVS
 *
 * FIIT STU 2021
 * Pavol Hradsky
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {   //vytvorenie struktury vrchola stromu
    int data;
    int height;
    struct node *right;
    struct node *left;
    struct node *parent;
} NODE;

NODE *head = NULL;  //globalna premenna, ukazujuca na root stromu

NODE* create_node(int data){    //funkcia dostane data a vytvori uzol NODE
    NODE *result = NULL;
    result = (NODE*)malloc(sizeof(NODE));
    result->data = data;
    return result;
}

int update_height(NODE **new_node){     //funkcia dostane nejaky uzol, a aktualizuje vysky vsetkych uzlov v stome nad nim
    NODE *tmp = *new_node;
    int tmp_height = tmp->height;   //tmp_height je aktualna vyska uzlu ktory som dostal

    do {    //prebehne cely strom od tmp po root, a aktualizuje vysky
        if (tmp->height > tmp_height) {     //ak je vyska uzlu vacsia vyska jeho jedneho podstromu, skonci
            return 0;
        }
        tmp->height = tmp_height;   //aktualizuje vysku
        //printf("Height of node with number %d is %d\n", tmp->data, tmp->height);
        tmp = tmp->parent;      //posunie sa na rodica
        tmp_height++;
    } while(tmp != NULL);
    return 1;
}

int rotate_left(NODE **node) {      //otacanie podstromu dolava
    NODE *tmp = *node;
    NODE *right = tmp->right;      //ulozi sa miesto tmp a jeho prave dieta, ktore sa budu vymienat

    int isRoot = 0;
    if (right == NULL) {    //zisti sa, strom ma prave dieta, ak nie, funkcia skonci
        return 0;
    }
    if (head == tmp) {  //zisti sa, ci je dany uloz root (head)
        head = right;   //head sa nastavi na right, boolean isRoot na 1 a rodic right na NULL
        isRoot = 1;
        right->parent = NULL;
    } else {    //inak, sa zisti, ci je tmp pravym alebo lavym dietatom jeho rodica a podla toho si jeho rodic nastavi dieta na right
        if(tmp->data < tmp->parent->data) {
            (tmp->parent)->left = right;
        } else {
            (tmp->parent)->right = right;
        }
    }
    if(isRoot == 0) {   //ak tmp nebol root, nastavi sa rodic right na rodica tmp
        right->parent = tmp->parent;
    }
    tmp->parent = right;    //aktualizuje sa zvysok dolezitych udajov
    tmp->right = right->left;
    right->left = tmp;

    if (tmp->right == NULL){    //aktualizuje sa vyska zmenenych uzlov podla pravidiel
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

    update_height(&right);  //aktualizuje sa vyska uzlov ku korenu

    return 1;
}

int rotate_right(NODE **node) { //otacanie podstromu dolava
    NODE *tmp = *node;
    NODE *left = tmp->left; //ulozi sa miesto tmp a jeho lave dieta, ktore sa budu vymienat

    int isRoot = 0;
    if (left == NULL) { //zisti sa, strom ma lave dieta, ak nie, funkcia skonci
        return 0;
    }
    if (head == tmp) {      //zisti sa, ci je dany uloz root (head)
        head = left;        //head sa nastavi na left, boolean isRoot na 1 a rodic left na NULL
        isRoot = 1;
        left->parent = NULL;
    } else {    //inak, sa zisti, ci je tmp pravym alebo lavym dietatom jeho rodica a podla toho si jeho rodic nastavi dieta na left
        if(tmp->data < tmp->parent->data) {
            (tmp->parent)->left = left;
        } else {
            (tmp->parent)->right = left;
        }
    }
    if(isRoot == 0) {   //ak tmp nebol root, nastavi sa rodic left na rodica tmp
        left->parent = tmp->parent;
    }
    tmp->parent = left;     //aktualizuje sa zvysok dolezitych udajov
    tmp->left = left->right;
    left->right = tmp;


    if (tmp->right == NULL){        //aktualizuje sa vyska zmenenych uzlov podla pravidiel
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
    update_height(&left);   //aktualizuje sa vyska uzlov ku korenu

    return 1;
}

int align(NODE **node) {    //funkcia zarovna strom (managuje otacania)
    NODE *tmp = *node;
    int bf, bfr, bfl;

    while(tmp != NULL) {    //pozera sa postupne na uzly az po root
        if(tmp->left == NULL) {
            if(tmp->right == NULL) {    //ak tmp nema deti, posunie sa na rodica
                tmp = tmp->parent;
                continue;
            }
            if(tmp->right->height >= 1) {   //ak nema lave dieta a prave ma vysku vacsiu alebo rovnu ako 1, otoci sa dolava
                if(tmp->right->left != NULL && tmp->right->right == NULL) {     //ak jeho prave dieta ma laveho potomka a nema praveho potomka, otoci sa najprv toto dieta do prava
                    rotate_right(&(tmp->right));
                }
                rotate_left(&tmp);
            }
            tmp = tmp->parent;
            continue;
        }
        if(tmp->right == NULL) {
            if(tmp->left->height >= 1) {    //ak nema prave dieta a lave ma vysku vacsiu alebo rovnu ako 1, otoci sa doprava
                if(tmp->left->right != NULL && tmp->left->left == NULL) {
                    rotate_left(&(tmp->left));  //ak jeho lave dieta ma praveho potomka a nema laveho potomka, otoci sa najprv toto dieta dolava
                }
                rotate_right(&tmp);
            }
            tmp = tmp->parent;
            continue;
        }   //posunie sa na rodica

        bf = tmp->right->height - tmp->left->height;    //vyrata sa bf (rozdiel vysky praveho a laveho podstromu)

        if(tmp->right->right != NULL) {     //vyrata sa aj bfr (bf praveho podstromu), dava sa pozor na to aby som nebral vysku z NULL
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

        if(tmp->left->right != NULL) {     //vyrata sa aj bfl (bf laveho podstromu), dava sa pozor na to aby som nebral vysku z NULL
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

        if(bf < 2 && bf > -2) {     //ak je bf vacsie ako -2 a mensie ako 2, posunie sa na rodica
            tmp = tmp->parent;
            continue;
        }
        if(bf <= -2) {  //ak je bf mensie alebo rovne ako -2
            if(bfl > bfr) {     //ak je bfl vacsie ako bfr, otoci sa lave dieta dolava
                rotate_left(&(tmp->left));
            }
            rotate_right(&tmp);     //otoci sa doprava
        } else if(bf >= 2) {    //ak je bf vacsie alebo rovne ako 2
            if(bfr < bfl) {     //ak je bfr mensie ako bfl, otoci sa prave dieta doprava
                rotate_right(&(tmp->right));
            }
            rotate_left(&tmp);  //otoci sa dolava
        }
        tmp = tmp->parent;  //posunie sa na rodica
    }

    return 0;
}

int insert(NODE *new_node){     //funkcia insert dostane uzol z create_node, prehlada strom a vlozi ho na spravne miesto
    NODE *tmp = head;

    new_node->right = NULL;     //nastavia sa defoultne hodnoty
    new_node->left = NULL;
    new_node->parent = NULL;
    new_node->height = 0;

    if(tmp == NULL){    //ak je to prvy prvok, head sa nastavi na tento uzol a skonci sa funkcia
        head = new_node;
        return 0;
    }
    while(tmp != NULL){     //kym nepridem na koniec stromu, porovnavam, ci je hodnota mojeho uzlu vacsia mensia alebo rovna ako hodnota tmp, potom podla toho posuvam tmp
        if(new_node->data == tmp->data){    //ak je rovna, skoncim funkciu (tato hodnota uz v strome je)
            return 2;
        }
        if(new_node->data > tmp->data && tmp->right != NULL){      //ak je vacsia a tmp ma prave dieta, posunie sa na neho
            tmp = tmp->right;
        } else if(new_node->data < tmp->data && tmp->left != NULL){     //ak je mensia a tmp ma lave dieta, posunie sa na neho
            tmp = tmp->left;
        } else if(new_node->data > tmp->data && tmp->right == NULL){    //ak je vacsia a tmp nema prave dieta, vlozi sa uzol sem
            tmp->right = new_node;  //nastavia sa hodnoty, aktualizuje sa vyska stromu a zarovna sa strom
            new_node->parent = tmp;
            update_height(&new_node);
            align(&tmp);
            return 1;
        } else{     //inak - ak je mensia a tmp nema lave dieta, vlozi sa uzol sem
            tmp->left = new_node;   //nastavia sa hodnoty, aktualizuje sa vyska stromu a zarovna sa strom
            new_node->parent = tmp;
            update_height(&new_node);
            align(&tmp);
            return 1;
        }
    }
    return 0;
}

int search(int x) {     //funkcia search dostane na vstupe cislo a vrati pocet krokov, ktore bolo treba aby ho nasla v strome
    NODE *tmp = head;
    int i = 0;
    while (tmp != NULL) {   //kym nie je na konci stromu, porovnava hodnotu x s hodnotou uzla tmp
        if(x < tmp->data) {     //ak je mensia, posunie sa dolava
            tmp = tmp->left;
        } else if(x > tmp->data) {      //ak je vacsia, posunie sa doprava
            tmp = tmp->right;
        } else {    //inak - ak je rovna, vrati i (pocet krokov)
            return i;
        }
        i++;    //zvacsi i o 1
    }
    return -1;      //ak ho nenasla, vrati -1
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

//    insert(create_node(40));
//    print_t(head);
//    insert(create_node(20));
//    print_t(head);
//    insert(create_node(10));
//    print_t(head);
//    insert(create_node(25));
//    print_t(head);
//    insert(create_node(30));
//    print_t(head);
//    insert(create_node(22));
//    print_t(head);
//    insert(create_node(50));
//    print_t(head);


    int max = 1000000;
    int toFind = 500000;
    clock_t start, end;
    double cpu_time_used;

    start = clock();    //zapne casovac

    for (int i = 0; i < max; ++i) {     //vytvori strom z max cisel (1000000)
        insert(create_node(i));
    }
    int num;
    for (int i = 0; i < toFind; ++i) {  //hlada nahodne cisla od 0 po max v strome toFind-krat (500000)
        num = (rand() % (max));
        search(num);
    }

    end = clock();      //skonci casovac
    cpu_time_used = ((double) (end - start));   //vyrata cas
    printf("finding %d times in tree size %d\n", toFind, max);      //vypise vysledok
    printf("Time: %dms\n", (int) cpu_time_used);


    return 0;
}

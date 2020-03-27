#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define Data int
#define INT

/* mirror*/

typedef struct node{
    struct node* parent;
    struct node* left;
    Data data;
    int height;
    struct node* right;
}Tree;

void SIGINV(int arg)
{
    arg ? : puts("key does not exist!");
}

void man()
{
    printf("-------MAN-------\n");
    char command[100];
    scanf(" %s", command);
    if(strcmp(command, "insert") == 0){
        puts(">Inserts a node in a tree.\n>Two options : -bst to insert in the bst & -avl to insert into the avl tree");
    }
    else if(strcmp(command, "print") == 0){
        puts(">Prints a tree.\nTwo options : -bst to print the bst & -avl to print the avl tree");
    }
    else if(strcmp(command, "min") == 0){
        puts(">Prints the smallest element in the tree");
    }
    else if(strcmp(command, "max") == 0){
        puts(">Prints the largest element in the tree");
    }
    else if(strcmp(command, "search") == 0){
        puts(">Prints the subtree of the entered key & returns NULL if the key is not found.\n>Two options : -bst to find the subtree of a key in the bst");
        puts(" & -avl to print the same in the avl tree.\nOption to be followed by the search value");
    }
    else if(strcmp(command, "predecessor") == 0){
        puts("Prints the inorder prodecessor of a key");
    }
    else if(strcmp(command, "successor") == 0){ 
        puts("Prints the inorder successor of a key");
    }
    else if(strcmp(command, "delete") == 0){
        puts("Deletes a key from the trees");
    }
    else if(strcmp(command, "exit") == 0){
        puts("Exits the program");
    }
    else{
        printf("%s : not a valid command\n", command);
    }
}

Tree* newTree(Tree* tree, Tree* parent, Tree* left, Data key, Tree* right)
{
    tree = (Tree*)malloc(sizeof(Tree));
    tree->parent = parent;
    tree->left = left;
    tree->height = 0;
    tree->right = right;
    tree->data = key;
    return tree;
}

int getHeight(Tree* tree)
{
    return tree ? tree->height : -1;
}

int max(int value1, int value2)
{
    return value1 > value2 ? value1 : value2;
}

Tree* insertIntoBst(Tree* tree, Data key)                 /*height of leaf nodes will be 0*/
{
    if(tree == NULL){
        tree = newTree(tree, NULL, NULL, key, NULL);
    }
    else if(key < tree->data){
        tree->left = insertIntoBst(tree->left, key);
    }
    else if(key > tree->data){
        tree->right = insertIntoBst(tree->right, key);
    }
    tree->height = max(getHeight(tree->right), getHeight(tree->left)) + 1;
    return tree;
}   

void fixParents(Tree* tree) 
{
    if(tree == NULL){
        return;
    }
    tree->parent = NULL;                    /*for case of root*/
    if(tree->left){
        fixParents(tree->left);
        tree->left->parent = tree;
    }
    if(tree->right){
        fixParents(tree->right);
        tree->right->parent = tree;
    }
}

void fixHeight(Tree* tree)
{
    if(tree == NULL){
        return;
    }
    if(tree->left){
        fixHeight(tree->left);
    }
    if(tree->right){
        fixHeight(tree->right);
    }
    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
    return;
}

void printInorderTraversal(Tree* tree)
{
    if(tree == NULL){
        return;
    }
    printInorderTraversal(tree->left);
    #ifdef INT
    printf("%d ", tree->data);
    #else
    printf("%c ", tree->data);
    #endif
    printInorderTraversal(tree->right);    
}

void printPreorderTraversal(Tree* tree)
{
    if(tree == NULL){
        return;
    }
    #ifdef INT
    printf("%d ", tree->data);
    #else
    printf("%c ", tree->data);
    #endif
    printPreorderTraversal(tree->left);
    printPreorderTraversal(tree->right);
}

void printPostorderTraversal(Tree* tree)
{
    if(tree == NULL){
        return;
    }
    printPostorderTraversal(tree->left);
    printPostorderTraversal(tree->right);
    #ifdef INT
    printf("%d ", tree->data);
    #else
    printf("%c ", tree->data);
    #endif
}

void printTree(Tree* tree)
{
    printf("Inorder : ");
    printInorderTraversal(tree);
    puts("");
    printf("Preorder : ");
    printPreorderTraversal(tree);
    puts("");
    printf("Postorder : ");
    printPostorderTraversal(tree);
    puts("");
}

Tree* findMinTree(Tree* tree)
{
    if(tree->left){
        return findMinTree(tree->left);
    }
    return tree;
}

Tree* findMaxTree(Tree* tree)
{
    if(tree->right){
        return findMaxTree(tree->right);
    }
    return tree;
}

Tree* findTree(Tree* tree, Data key)
{
    if(tree == NULL){
        SIGINV(0);
        return NULL;
    }
    else if(key > tree->data){
        return findTree(tree->right, key);
    }
    else if(key < tree->data){
        return findTree(tree->left, key);
    }
    else{
        return tree;
    }
}

int findHeight(Tree* tree)          //useless as height has been added
{
    return tree->height;
}

Tree* inorderPredecessorHelper(Tree* tree)          //case of node with no left child???
{
    if(tree->left){
        return findMaxTree(tree->left);
    }
    if(tree->parent == NULL){
        return NULL;
    }
    Tree* temp = tree->parent;
    while(temp->left == tree){
        tree = tree->parent;
        temp = tree->parent;
        if(temp == NULL){
            return NULL;
        }
    }
    return temp;
}

Tree* inorderPredecessor(Tree* tree, Data key)
{
    Tree* temp = findTree(tree, key);
    return inorderPredecessorHelper(temp);
}

Tree* inorderSuccessorHelper(Tree* tree)
{
    if(tree->right){
        return findMinTree(tree->right);
    }
    if(tree->parent == NULL){
        return NULL;
    }
    Tree* temp = tree->parent;
    while(temp->right == tree){         /*can it be done using recursion in the same function?*/
        tree = tree->parent;
        temp = tree->parent;
        if(temp == NULL){
            return NULL;
        }
    }
    return temp;
}

Tree* inorderSuccessor(Tree* tree, Data key)
{
    Tree* temp = findTree(tree, key);
    return inorderSuccessorHelper(temp);
}

Tree* deleteNode(Tree* root, Data key)
{
    if(root == NULL){
        SIGINV(0);
        return NULL;
    }
    if(key < root->data){
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->data){
        root->right = deleteNode(root->right, key);
    }
    else{
        Tree* hold = NULL;
        if(root->right == NULL && root->left == NULL){
            root->parent = NULL;
            free(root);
            return NULL;
        }
        if(root->right == NULL){
            hold = root->left;
            if(root->parent){
                root->parent->left = root->left;
            }
            root->parent = root->left = root->right;
            free(root);
            return hold;
        }
        if(root->left == NULL){
            hold = root->right;
            if(root->parent){
                root->parent->right = root->right;
            }
            root->parent = root->right = root->left;
            free(root);
            return hold;
        }
        /* root->right & root->left exist here*/
        hold = root->right;
        while(hold->left){
            hold = hold->left;
        }
        /*hold now has the inorder successor*/
        if(hold->right == NULL && hold->left == NULL){
            if(hold->parent->left == hold){
                hold->parent = hold->parent->left = NULL;
            }
            else{
                hold->parent = hold->parent->right = NULL;
            }
            root->data = hold->data;
            free(hold);
            return root;
        }
        if(hold->right){
            hold->parent->left = hold->right;
            hold->parent = hold->right = NULL;
            root->data = hold->data;
            free(hold);
            return root;
        }
    }
}

/* check if tree is balanced*/
void isBalancedHelper(Tree* tree, int* balanceFactor)
{
    if(tree == NULL){
        return;
    }
    int leftHeight = -1, rightHeight = -1, bFactor;
    if(tree->left){
        isBalancedHelper(tree->left, balanceFactor);
        leftHeight = tree->left->height;
    }
    if(tree->right){
        isBalancedHelper(tree->right, balanceFactor);
        rightHeight = tree->right->height;
    }
    if(*balanceFactor == 0){        /*placed here because when we return frrom recursion and a bFactor is <=1, *balanceFactor will be assigned 1*/
        return;
    }
    bFactor = rightHeight - leftHeight;
    if(abs(bFactor) > 1){
        *balanceFactor = 0;
        return;
    }
    *balanceFactor = 1;
}

int isBalanced(Tree* tree)
{
    int balanceFactor = -1;
    isBalancedHelper(tree, &balanceFactor);
    return balanceFactor;
}

/*insert into AVL Tree*/
Tree* rotateLeft(Tree* tree)
{
    Tree* hold = tree->right;
    tree->right = hold->left;
    hold->left = tree;
    return hold;
}

Tree* rotateRight(Tree* tree)
{
    Tree* hold = tree->left;
    tree->left = hold->right;
    hold->right = tree;
    return hold;
}

Tree* balanceTreeHelper(Tree* tree, int bFactor)
{
    /*have to detect whether R, L, RL or LR rotation is to be done*/
    if(bFactor > 1){
        if(tree->right->right){
            /*Do L rotation here*/
            return rotateLeft(tree);
        }
        else{
            /*Do RL rotation here*/
            tree->right = rotateRight(tree->right);
            return rotateLeft(tree);
        }
    }
    else{
        if(tree->left->left){
            /*Do R rotation here*/
            return rotateRight(tree);
        }
        else{
            /*Do LR rotation here*/
            tree->left = rotateLeft(tree->left);
            return rotateRight(tree);
        }
    }
}

Tree* balanceTree(Tree* tree)
{
    if(tree == NULL){
        return NULL;
    }
    if(tree->left){
        tree->left = balanceTree(tree->left);
    }
    fixHeight(tree);
    if(tree->right){
        tree->right = balanceTree(tree->right);
    }
    fixHeight(tree);
    int bFactor = getHeight(tree->right) - getHeight(tree->left);
    if(abs(bFactor) > 1){
        return balanceTreeHelper(tree, bFactor);
    }
    return tree;
}

Tree* insertIntoAvl(Tree* tree, Data key)
{
    tree = insertIntoBst(tree, key);
    if(isBalanced(tree)){
        return tree;
    }
    return balanceTree(tree);
}

int main()
{
    char string[100], option, command[100];
    Tree* rootBst = NULL, *temp = NULL, *rootAvl = NULL;
    Data value;
    while(1){
        printf("[Binary_Search_&_AVL_Tree@Data_Structures]$");
        scanf(" %s", string);
        if(strcmp(string, "insert") == 0){
            scanf(" %d", &value);
            rootBst = insertIntoBst(rootBst, value);
            rootAvl = insertIntoAvl(rootAvl, value);
            fixParents(rootBst);
            fixParents(rootAvl);
        }
        else if(strcmp(string, "print") == 0){
            scanf(" %s", command);
            if(strcmp(command, "-bst") == 0){
                printTree(rootBst);
            }
            else if(strcmp(command, "-avl") == 0){
                printTree(rootAvl);
            }
            else{
                printf("%s : no option found\n", string);
            }
        }
        else if(strcmp(string, "min") == 0){
            temp = findMinTree(rootBst);
            printf("%s : minimum key is ", string);
            #ifdef INT
            printf("%d ", temp->data);
            #else
            printf("%c ", temp->data);
            #endif
            puts("");
        }
        else if(strcmp(string, "max") == 0){
            temp = findMaxTree(rootBst);
            printf("%s : maximum node is ", string);
            #ifdef INT
            printf("%d ", temp->data);
            #else
            printf("%c ", temp->data);
            #endif
            puts("");
        }
        else if(strcmp(string, "search") == 0){
            scanf(" %s", command);
            if(strcmp(command, "-bst") == 0){
                scanf(" %d", &value);
                temp = findTree(rootBst, value);
                if(temp == NULL){
                    puts("Such a key does not exist in the tree");
                }
                else{
                    puts("The key's subtree is : ");
                    printTree(temp);
                }
            }
            else if(strcmp(command, "-avl") == 0){
                scanf(" %d", &value);
                temp = findTree(rootAvl, value);
                if(temp == NULL){
                    puts("Such a key does not exist in the tree");
                }
                else{
                    puts("The key's subtree is : ");
                    printTree(temp);
                }
            }
            else{
                printf("%s : no option found\n", string);
            }
        }
        else if(strcmp(string, "predecessor") == 0){
            scanf(" %s", command);
            if(strcmp(command, "-bst") == 0){
                scanf(" %d", &value);
                temp = inorderPredecessor(rootBst, value);
                puts("The predecessor's subtree is : ");
                printTree(temp);
            }
            else if(strcmp(command, "-avl") == 0){
                scanf(" %d", &value);
                temp = inorderPredecessor(rootAvl, value);
                puts("The predecessor's subtree is : ");
                printTree(temp);
            }
            else{
                printf("%s : no option found\n", string);
            }
        }
        else if(strcmp(string, "successor") == 0){
            scanf(" %s", command);
            if(strcmp(command, "-bst") == 0){
                scanf(" %d", &value);
                temp = inorderSuccessor(rootBst, value);
                puts("The successor's subtree is : ");
                printTree(temp);
            }
            else if(strcmp(command, "-avl") == 0){
                scanf(" %d", &value);
                temp = inorderSuccessor(rootAvl, value);
                puts("The successor's subtree is : ");
                printTree(temp);
            }
            else{
                printf("%s : no option found\n", string);
            }
        }
        else if(strcmp(string, "delete") == 0){
            scanf(" %d", &value);
            rootBst = deleteNode(rootBst, value);
            fixParents(rootBst);
            fixHeight(rootBst);
            rootAvl = deleteNode(rootAvl, value);
            fixParents(rootAvl);
            fixHeight(rootAvl);
        }
        else if(strcmp(string, "exit") == 0){
            break;
        }
        else if(strcmp(string, "man") == 0){
            man();
        }
        else{
            printf("%s : command not found\n", string);
            //fflush(stdin);       not working.Why?
            while(getchar() != '\n');
        }
    } 
    puts("Thank You For Using The Program!");
    return 0;  
}

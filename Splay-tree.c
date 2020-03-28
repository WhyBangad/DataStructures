#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Data int
#define INT

typedef struct node{
    struct node* parent;
    struct node* left;
    Data data;
    struct node* right;
}Tree;


/*make man like actual man using spacing (empty string of 30 of spaces etc...) later*/
void man()
{
    printf("-------MAN-------\n");
    char command[100];
    scanf(" %s", command);
    if(strcmp(command, "insert") == 0){
        puts(">Inserts a node in a tree.\n>Two options : -bst to insert in the bst & -splay to insert into the splay tree");
    }
    else if(strcmp(command, "print") == 0){
        puts(">Prints a tree.\nTwo options : -bst to print the bst & -splay to print the splay tree");
    }
    else if(strcmp(command, "search") == 0){
        puts(">Prints the subtree of the entered key & returns NULL if the key is not found.\n>Two options : -bst to find the subtree of a key in the bst");
        puts(" & -splay to print the same in the splay tree.\n>This will splay the searched value in the splay tree.\n>Option to be followed by the search value");
    }
    else if(strcmp(command, "predecessor") == 0){
        puts("Prints the inorder prodecessor of a key");
    }
    else if(strcmp(command, "successor") == 0){ 
        puts("Prints the inorder successor of a key");
    }
    else if(strcmp(command, "delete") == 0){
        puts(">Deletes a key from the trees\n>Also splays the parent in case of the splay tree");
    }
    else if(strcmp(command, "exit") == 0){
        puts("Exits the program");
    }
    else{
        printf("%s : not a valid command\n", command);
    }
}

void SIGKEY(int key)
{
    key ? puts("Key does not exit in the tree") : puts("");
}

Tree* newTree(Tree* tree, Tree* left, Data key, Tree* right)
{
    tree = (Tree*)malloc(sizeof(Tree));
    tree->left = left;
    tree->right = right;
    tree->data = key;
    return tree;
}

void fixParents(Tree* tree)
{
    if(tree == NULL){
        return;
    }
    tree->parent = NULL;
    if(tree->left){
        fixParents(tree->left);
        tree->left->parent = tree;
    }
    if(tree->right){
        fixParents(tree->right);
        tree->right->parent = tree;
    }    
}

Tree* insertIntoBST(Tree* tree, Data key)
{
    if(tree == NULL){
        return newTree(tree, NULL, key, NULL);
    }
    else if(key < tree->data){
        tree->left = insertIntoBST(tree->left, key);
    }
    else if(key > tree->data){
        tree->right = insertIntoBST(tree->right, key);
    }
    return tree;
}

/*use this for search in BST*/
Tree* findTree(Tree* tree, Data key)
{
    if(tree == NULL){
        return NULL;
    }
    if(key < tree->data){
        return findTree(tree->left, key);
    }
    if(key > tree->data){
        return findTree(tree->right, key);
    }
    return tree;
}

void printInorder(Tree* tree)
{
    if(tree == NULL){
        return;
    }
    printInorder(tree->left);
    #ifdef INT
    printf("%d ", tree->data);
    #else
    /*Some print function*/
    #endif
    printInorder(tree->right);
}

void printPreorder(Tree* tree)
{
    if(tree == NULL){
        return;
    }
    #ifdef INT
    printf("%d ", tree->data);
    #else
    /*Some print function*/
    #endif
    printPreorder(tree->left);
    printPreorder(tree->right);
}

void printPostorder(Tree* tree)
{
    if(tree == NULL){
        return;
    }
    printPostorder(tree->left);
    printPostorder(tree->right);
    #ifdef INT
    printf("%d ", tree->data);
    #else
    /*Some print function*/
    #endif
}

void printTree(Tree* tree)
{
    printf("Inorder : ");
    printInorder(tree);
    puts("");
    printf("Preorder : ");
    printPreorder(tree);
    puts("");
    printf("Postorder : ");
    printPostorder(tree);
    puts("");
}

Tree* inorderSuccessorHelper(Tree* tree)
{
    if(tree->right){
        tree = tree->right;
        while(tree->left){
            tree = tree->left;
        }
        return tree;
    }
    return NULL;
}

Tree* inorderSuccessor(Tree* tree, Data key)
{
    Tree* temp = findTree(tree, key);
    return inorderSuccessorHelper(temp);
}

Tree* inorderPredecessorHelper(Tree* tree)
{
    if(tree->left){
        tree = tree->left;
        while(tree->right){
            tree = tree->right;
        }
        return tree;
    }
    return NULL;
}

Tree* inorderPredecessor(Tree* tree, Data key)
{
    Tree* temp = findTree(tree, key);
    return inorderPredecessorHelper(temp);
}

Tree* deleteFromBST(Tree* tree, Data key)
{
    if(tree == NULL){      
        SIGKEY(1);
        return NULL;
    }
    else if(key < tree->data){
        tree->left = deleteFromBST(tree->left, key);
    }
    else if(key > tree->data){
        tree->right = deleteFromBST(tree->right, key);
    }
    /*key has been found here*/
    Tree* holder = NULL;
    if(tree->right == NULL && tree->left == NULL){
        tree->parent = NULL;
        free(tree);
        return NULL;
    }
    if(tree->left && tree->right == NULL){
        holder = tree;
        tree = tree->left;
        holder->left = holder->parent = NULL;
        free(holder);
        return tree;
    }
    if(tree->right && tree->left == NULL){
        holder = tree;
        tree = tree->right;
        holder->right = holder->parent = NULL;
        free(holder);
        return tree;
    }
    /*both right and left children exist here*/
    else{
        Tree* successor = inorderSuccessorHelper(tree);  
        tree->data = successor->data;
        tree->right = deleteFromBST(tree->right, successor->data);
        return tree;
    }
}
/*Splay functions begin*/

Tree* zig(Tree* tree)
{
    /*Right rotate*/
    Tree* hold = tree->parent;
    tree->parent = tree->parent->parent;
    hold->parent = tree;
    hold->left = tree->right;
    tree->right = hold;
    return tree;
}

Tree* zag(Tree* tree)
{
    /*Left rotate*/
    Tree* hold = tree->parent;
    tree->parent = tree->parent->parent;
    hold->parent = tree;
    hold->right = tree->left;
    tree->left = hold;
    return tree;
}

Tree* zig_zig(Tree* tree)
{
    tree->parent = zig(tree->parent);
    return zig(tree);
}

Tree* zig_zag(Tree* tree)
{
    tree = zig(tree);
    return zag(tree);
}

Tree* zag_zag(Tree* tree)
{
    tree->parent = zag(tree->parent);
    return zag(tree);
}

Tree* zag_zig(Tree* tree)
{
    tree = zag(tree);
    return zig(tree);
}

Tree* splayTree(Tree* tree)
{
    if(tree == NULL || tree->parent == NULL){
        return tree;
    }
    Tree* node = tree, *parent = tree->parent, *grandParent = tree->parent->parent;
    if(grandParent){
        if(parent->left == tree){
            if(grandParent->left == parent){         /*zig-zig case*/
                    tree = zig_zig(tree);
            }
            else{                                    /*zig-zag case*/
                    tree = zig_zag(tree);
            }
        }
        else{  
            if(grandParent->right == parent){       /*zag-zag case*/
                    tree = zag_zag(tree);
            }                             
            else{                                   /*zag-zig case*/
                    tree = zag_zig(tree);
            }
        }
    }
    else{                                           /*grandParent is NULL here*/
        if(parent->left == tree){                   /*case of zig*/
            tree = zig(tree);
        }   
        else{                                       /*case of zag*/
            tree = zag(tree);
        }
    }
    return splayTree(tree);
}

Tree* insertIntoSplayTree(Tree* tree, Data key)
{
    tree = insertIntoBST(tree, key);
    fixParents(tree);
    tree = splayTree(findTree(tree, key));
}

Tree* deleteFromSplayTree(Tree* tree, Data key)
{
    Tree* parent = NULL, *temp = NULL;
    temp = findTree(tree, key);
    if(temp == NULL){
        SIGKEY(1);
        return tree;
    }
    parent = temp->parent;
    if(parent){
        tree = deleteFromBST(tree, key);
        fixParents(tree);
        printTree(tree);
        return splayTree(parent);
    }
    /*parent is NULL implying root node*/
    return deleteFromBST(tree, key);
}

Tree* searchInSplayTree(Tree* tree, Data key)
{
    Tree* temp = findTree(tree, key);
    return splayTree(temp);
}

void driver()
{
    Tree* rootBST = NULL, *rootSplay = NULL, *temp = NULL;
    char string[100], option, command[100];
    Data value;
    while(1){
        printf("[Binary_Search_&_Splay_Tree@Data_Structures]$");
        scanf(" %s", string);
        if(strcmp(string, "insert") == 0){
            scanf(" %d", &value);
            rootBST = insertIntoBST(rootBST, value);
            fixParents(rootBST);
            rootSplay = insertIntoSplayTree(rootSplay, value);
            fixParents(rootSplay);
        }
        else if(strcmp(string, "print") == 0){
            scanf(" %s", command);
            if(strcmp(command, "-bst") == 0){
                printTree(rootBST);
            }
            else if(strcmp(command, "-splay") == 0){
                printTree(rootSplay);
            }
            else{
                printf("%s : no option found\n", string);
            }
        }
        else if(strcmp(string, "search") == 0){
            scanf(" %s", command);
            if(strcmp(command, "-bst") == 0){
                scanf(" %d", &value);
                temp = findTree(rootBST, value);
                if(temp == NULL){
                    puts("Such a key does not exist in the tree");
                }
                else{
                    puts("The key's subtree is : ");
                    printTree(temp);
                }
            }
            else if(strcmp(command, "-splay") == 0){
                scanf(" %d", &value);
                rootSplay = searchInSplayTree(rootSplay, value);
                puts("The tree now is : ");
                printTree(rootSplay);
                fixParents(rootSplay);
            }
            else{
                printf("%s : no option found\n", string);
            }
        }
        else if(strcmp(string, "predecessor") == 0){
            scanf(" %s", command);
            if(strcmp(command, "-bst") == 0){
                scanf(" %d", &value);
                temp = inorderPredecessor(rootBST, value);
                puts("The predecessor's subtree is : ");
                printTree(temp);
            }
            else if(strcmp(command, "-splay") == 0){
                scanf(" %d", &value);
                temp = inorderPredecessor(rootSplay, value);
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
                temp = inorderSuccessor(rootBST, value);
                puts("The successor's subtree is : ");
                printTree(temp);
            }
            else if(strcmp(command, "-splay") == 0){
                scanf(" %d", &value);
                temp = inorderSuccessor(rootSplay, value);
                puts("The successor's subtree is : ");
                printTree(temp);
            }
            else{
                printf("%s : no option found\n", string);
            }
        }
        else if(strcmp(string, "delete") == 0){
            scanf(" %d", &value);
            rootBST = deleteFromBST(rootBST, value);
            fixParents(rootBST);
            rootSplay = deleteFromSplayTree(rootSplay, value);
            fixParents(rootSplay);
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
}

int main()
{
    driver();
    return 0;
}
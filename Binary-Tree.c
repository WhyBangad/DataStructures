#include<stdio.h>
#include<stdlib.h>
#define Data int

typedef struct node{
    struct node* left;
    Data data;
    struct node* right;
}Tree;

Tree* newTree(Tree* left, Tree* node, Tree* right, Data value)
{
    node = (Tree*)malloc(sizeof(Tree));
    node->left = left;
    node->right = right;
    node->data = value;
    return node;
}

int searchIndex(int lo, int hi, Data* array, Data value)
{
    for(int i = lo; i <= hi; ++i){
        if(array[i] == value){
            return i;
        }
    }
    return -1;
}

Tree* treeFromPreorderHelper(int lo, int hi, Data* inorder, Data* preorder, int* preIndex)
{
    Tree* node = NULL;
    if(lo > hi){
        return NULL;
    }
    Data value = preorder[(*preIndex)++];
    int index = searchIndex(lo, hi, inorder, value);
    node = newTree(NULL, node, NULL, value);
    node->left = treeFromPreorderHelper(lo, index - 1, inorder, preorder, preIndex);
    node->right = treeFromPreorderHelper(index + 1, hi, inorder, preorder, preIndex);
    return node;
}

void treeFromPreorder(Data* inorder, Data* preorder, int size, Tree** root)
{
    int *preorderIndex;
    preorderIndex =(int*)malloc(sizeof(int));
    *preorderIndex = 0;
    *root = treeFromPreorderHelper(0, size - 1, inorder, preorder, preorderIndex);
    return;
}

Tree* treeFromPostorderHelper(int lo, int hi, Data* inorder, Data* postorder, int* postIndex)
{
    Tree* node = NULL;
    if(lo > hi){
        return NULL;
    }
    Data value = postorder[(*postIndex)--];
    int index = searchIndex(lo, hi, inorder, value);
    node = newTree(NULL, node, NULL, value);
    node->right = treeFromPostorderHelper(index + 1, hi, inorder, postorder, postIndex);
    node->left = treeFromPostorderHelper(lo, index - 1, inorder, postorder, postIndex);
    return node;
}

void treeFromPostorder(Data* inorder, Data* postorder, int size, Tree** root)
{
    int* postIndex = (int*)malloc(sizeof(int));
    *postIndex = size - 1;
    *root = treeFromPostorderHelper(0, size - 1, inorder, postorder, postIndex);
    return;
}

void printTreeInorder(Tree* node)
{
    if(node == NULL){
        return;
    }
    printTreeInorder(node->left);
    #ifdef CHAR
    printf("%c ", node->data);
    #else
    printf("%d ", node->data);
    #endif
    printTreeInorder(node->right);
}

void printTreePreorder(Tree* node)
{
    if(node == NULL){
        return;
    }
    #ifdef CHAR
    printf("%c ", node->data);
    #else
    printf("%d ", node->data);
    #endif
    printTreePreorder(node->left);
    printTreePreorder(node->right);
}

void printTreePostorder(Tree* node)
{
    if(node == NULL){
        return;
    }
    printTreePostorder(node->left);
    printTreePostorder(node->right);
    #ifdef CHAR
    printf("%c ", node->data);
    #else
    printf("%d ", node->data);
    #endif
}

void printTree(Tree* node)
{
    printf("Inorder : ");
    printTreeInorder(node);
    puts("");
    printf("Preorder : ");
    printTreePreorder(node);
    puts("");
    printf("Postorder : ");
    printTreePostorder(node);
    puts("");
}

void findMinKey(Tree* node, Data* min)
{
    if(node == NULL){
        return;
    }
    if((node->data) < (*min)){
        *min = node->data;
    }
    if(node->left){
    findMinKey(node->left, min);
    }
    if(node->right){
    findMinKey(node->right, min);
    }
}

void findMaxKey(Tree* node, Data* max)
{
    if(node == NULL){
        return;
    }
    if((node->data) > (*max)){
        *max = node->data;
    }
    if(node->left){
    findMaxKey(node->left, max);
    }
    if(node->right){
    findMaxKey(node->right, max);
    }
}

Tree* findTree(Tree* tree, Data key)
{
    if(tree == NULL || tree->data == key){
        return tree;
    }
    Tree* found = findTree(tree->left, key);
    if(!found){
        found = findTree(tree->right, key);
    }
    return found;
}

int findHeight(Tree* node)
{
    if(node == NULL){
        return 0;
    }
    int leftDepth = findHeight(node->left);
    int rightDepth = findHeight(node->right);
    if(leftDepth > rightDepth){
        return leftDepth + 1;
    }
    return rightDepth + 1;
}

Tree* mirrorTree(Tree* tree)
{
    Tree* node = NULL;
    if(tree != NULL){
        node = newTree(NULL, tree, NULL, tree->data);
        node->left = mirrorTree(tree->left);
        node->right = mirrorTree(tree->right);
    }
    return node;
}

int compareTrees(Tree* tree1, Tree* tree2)
{
    int compValue = 0, leftCompValue = 0, rightCompValue = 0;
    if(tree1 == NULL && tree2 == NULL){
        return 1;
    }
    else if(tree1 == NULL || tree2 == NULL){
        return 0;
    }
    return (tree1->data == tree2->data) & compareTrees(tree1->left, tree2->left) & compareTrees(tree1->right, tree2->right);
}

/*void deleteTree(Tree** tree)        //problem in this function
{                                       //because im trying to make a pointer in the heap point to NULL?
    Tree* temp = *tree;
    if(temp == NULL){
        return;
    }
    if(temp->left == NULL && temp->right == NULL){
        *tree = NULL;
        printf("Deleting\n");
        free(temp);
        return;
    }
    if(temp->left){
        printf("Going Left\n");
        deleteTree(&((*tree)->left));
    }
    if(temp->right){
        printf("Going Right\n");
        deleteTree(&((*tree)->right));
    }
    printf("Coming back to delete\n");
    (*tree)->left = (*tree)->right = *tree = NULL;
    free(temp);
    printf("Coming back to delete#2\n");
    return;
}*/

Tree* deleteTree(Tree* tree)
{
    if(tree == NULL){
        return NULL;
    }
    else if(tree->left == NULL && tree->right == NULL){
        free(tree);
        return NULL;
    }
    if(tree->left){
        tree->left = deleteTree(tree->left);
    }
    if(tree->right){
        tree->right = deleteTree(tree->right);
    }
    free(tree);
    return NULL;
}

Tree* inorderPredecessor(Tree* tree, Data key)      //wrong because have't considered parent        //wrong code completely and also for successor
{
    tree = findTree(tree, key);
    if(tree->left == NULL){
        return NULL;
    }
    tree = tree->left;
    while(tree->right){
        tree = tree->right;
    }
    return tree;
}

Tree* inorderSuccessor(Tree* tree, Data key)
{
    tree = findTree(tree, key);
    if(tree->right == NULL){
        return NULL;
    }
    tree = tree->right;
    while(tree->left){
        tree = tree->left;
    }
    return tree;
}

int leafNodeCount(Tree* tree)
{
    int total = 0;
    if(tree == NULL){
        return 0;
    }
    else if(tree->left == NULL && tree->right == NULL){
        return 1;
    }
    if(tree->left){
        total += leafNodeCount(tree->left);
    }
    if(tree->right){
        total += leafNodeCount(tree->right);
    }
    return total;
}

int nonLeafCount(Tree* tree)
{
    int total = 0;
    if(tree == NULL){
        return 0;
    }
    else if(tree->left == NULL && tree->right == NULL){
        return 0;
    }
    if(tree->left){
        total +=nonLeafCount(tree->left);
    }
    if(tree->right){
        total += nonLeafCount(tree->right);
    }
    return total + 1;
}

int main()
{
    Tree* root1 = NULL, *root2 = NULL, *rootMirror = NULL, *node = NULL;
    int height = 0;
    Data min = __INT32_MAX__, max = -1;
    Data inorder1[11] = {4, 8, 2, 5, 1, 9, 6, 3, 10, 7, 11};
    Data preorder1[11] = {1, 2, 4, 8, 5, 3, 6, 9, 7, 10, 11};
    Data postorder2[11] = {8, 4, 3, 2, 10, 6, 9, 11, 7, 5, 1};
    Data inorder2[11] = {4, 8, 2, 3, 1, 10, 6, 5, 9, 7, 11};
    puts("Tree1 : ");
    treeFromPreorder(inorder1, preorder1, 11, &root1);
    printTree(root1);
    puts("Tree2 : ");
    treeFromPostorder(inorder2, postorder2, 11, &root2);
    printTree(root2);
    findMinKey(root1, &min);
    printf("The minimum element in Tree1 is : %d\n", min);
    findMaxKey(root1, &max);
    printf("The maximum element Tree1 is : %d\n", max);
    printf("In Tree1 : ");
    node = findTree(root1, 3);
    if(node == NULL){
        puts("Such a key does not exist!");
    }
    else{
        printTree(node);
    }
    height = findHeight(node);
    printf("The height of the node is : %d\n", height);
    rootMirror = mirrorTree(root1);
    puts("Mirror tree of Tree1 has been created!");
    printTree(rootMirror);
    if(compareTrees(root1, root2)){
        puts("The trees have the same key values!");
    }
    else{
        puts("The trees have different key values!");
    }
    root2 = deleteTree(root2);
    puts("The tree has been deleted!");
    printTree(root2);
    puts("The inorder predecessor tree is : ");     
    printTree(inorderPredecessor(root1, 9));
    puts("The inorder sucessor tree is : ");
    printTree(inorderSuccessor(root1, 3));
    printf("The number of leaf nodes in the tree is : %d\n", leafNodeCount(root1));
    printf("The number of non leaf nodes in the tree is : %d\n", nonLeafCount(root1));
    return 0;
}
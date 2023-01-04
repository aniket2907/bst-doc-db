#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Tree_Node * root;


Tree_Node * newnode(char data)
{
    Tree_Node * a = (Tree_Node*)malloc(sizeof(Tree_Node));
    a->data=data;
    a->count=0;
    a->left=NULL;
    a->right=NULL;
    return a;
}
void tree_insert(Tree_Node** root, char data)
{
    if (*root==NULL)
    {
        *root=newnode(data);
    }
    if (data==(*root)->data)
    {
        (*root)->count++;
    }
    if (data<(*root)->data)
    {
        tree_insert(&((*root)->left), data);
    }
    if(data>((*root)->data))
    {
        tree_insert(&((*root)->right), data);
    }
    
}


Tree_Node* tree_search(Tree_Node* root, char data){
    if (root==NULL)
    {
        return NULL;
    }
    if (root->data == data)
    {
        return root;
    }
    if (data>root->data)
    {
        return tree_search(root->right, data);
    }
    if (data<root->data)
    {
        return tree_search(root->left, data);
    }
    return NULL;
    }


void tree_print_sorted(Tree_Node* root){
    if (root==NULL)
    {
        return;
    }
    tree_print_sorted(root->left);
    int i=0;
    while(i<root->count)
    {
        printf("%c", root->data);
        i++;
    }
    tree_print_sorted(root->right);
}

Tree_Node* create_bst (char data[]){

    root = NULL;
    int i = 0;
    while(data[i]!='\0')
    {
    tree_insert(&root, data[i]);
    i++;
    }
    return root;
}

void tree_delete(Tree_Node* root){
    if(root==NULL)
        return;
    tree_delete(root->left);
    tree_delete(root->right);
    free(root);
}

void main()
{
    
}
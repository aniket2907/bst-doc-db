#include "bstdb.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


typedef struct Node 
{
	char name[200];
	int word_count;
	int doc_id;
	struct Node * left;
	struct Node * right;
}Node;

Node * root;
int num_searches, num_comps, num_insertions, node_count;

int bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. 
	num_searches=0;
	num_comps=0;
	num_insertions=0;
	node_count=0;
	root=NULL;
	if(num_searches || num_comps)
	{
		return 0;
	}
	return 1;
}

Node *newnode (char *name, int word_count, int doc_id)
{
	Node * a = (Node*)malloc(sizeof(Node));
	strcpy(a->name,name);
	a->word_count=word_count;
	a->doc_id=doc_id;
	a->left=NULL;
	a->right=NULL;
	return a;
}


int tree_insert(Node **root, char * name, int word_count, int doc_id)
{
	if (*root==NULL)
	{
		*root=newnode(name,word_count,doc_id);
		node_count++;
		return doc_id;
	}
	if (doc_id==(*root)->doc_id)
	{
		doc_id++;
	}
	if(doc_id>(*root)->doc_id)
	{
		return tree_insert(&((*root)->right), name, word_count, doc_id);
	}
	if(doc_id<(*root)->doc_id)
	{
		return tree_insert(&((*root)->left), name, word_count, doc_id);
	}
	else return 1;
}


int bstdb_add ( char *name, int word_count ) {
	// This function creates a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
		// This function also generates and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	num_insertions++;
	int doc_id=time(NULL) + rand();
	//calling self-defined function
	return tree_insert(&root,name, word_count, doc_id);
}


Node * tree_search(Node * root, int doc_id)
{
	num_comps++;
	if (root==NULL)
    {
        return NULL;
    }
    if (root->doc_id==doc_id)
    {
        return root;
    }
    if (doc_id>root->doc_id)
    {
        return tree_search(root->right, doc_id);
    }
    if (doc_id<root->doc_id)
    {
        return tree_search(root->left, doc_id);
    }
    return NULL;
}


int
bstdb_get_word_count ( int doc_id ) 
{
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	num_searches++;
	if(tree_search(root, doc_id)!=NULL)
		return tree_search(root, doc_id)->word_count;
	else 
		return -1;
}

char*
bstdb_get_name ( int doc_id ) {
	num_searches++;
	if(tree_search(root, doc_id)!=NULL)
		return tree_search(root, doc_id)->name;
	else
		return 0;
}

void
bstdb_stat ( void ) {


	printf("STAT \n");
	printf("Average number of node visits per search = %f \n", (float)(num_comps/num_searches));
	printf("Number of insertions: %d \n", num_insertions);
	printf("Number of nodes in tree: %d \n",node_count);
}

void tree_delete(Node * root)
{
	//node_count++;
	if(root==NULL)
	{
		return;
	}
	tree_delete(root->left);
	tree_delete(root->right);
	free(root);
}
void
bstdb_quit ( void ) {
	tree_delete(root);
}

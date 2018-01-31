#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;

typedef struct _BiTree
{
    int data;
    struct _BiTree *lchild, *rchild, *parent;
}BiTree, *BitTree;

//Find the node with min value(recursion version)
BitTree SearchMinNode(BitTree rnode)
{
    if(rnode == NULL)
	return NULL;
    if(rnode->lchild == NULL)
	return rnode;
    else
	return SearchMinNode(rnode->lchild);
}

//Find the node with min value(loop version)
BitTree SearchMinValue(BitTree rnode)
{
    BitTree p = rnode;
    if(p == NULL || p->lchild == NULL) return p;
    while(p)
    {
	p = p->lchild;
	if(p->lchild == NULL) return p;
    }
}

//Find the node with max value(recursion version)
BitTree SearchMaxNode(BitTree rnode)
{
    if(rnode == NULL)
	return NULL;
    if(rnode->rchild == NULL)
	return rnode;
    else
	return SearchMaxNode(rnode->rchild);
}

//Find the node with max value(loop version)
BitTree SearchMaxValue(BitTree rnode)
{
    BitTree p = rnode;
    if(p == NULL || p->rchild == NULL) return p;
    while(p)
    {
	p = p->rchild;
	if(p->rchild != NULL) continue;
    }
}

//Find the node with the given value(recursion version)
BitTree NodeForKey(BitTree rnode, int key)
{
    if(!rnode)
	return NULL;
    if(key < rnode->data)
	return NodeForKey(rnode->lchild, key);
    else if(key > rnode->data)
	return NodeForKey(rnode->rchild, key);
    else
	return rnode;
}

//Find the node with the given value(loop version)
BitTree NodeForValue(BitTree rnode, int value)
{
    BitTree p = rnode;
    while(p)
    {
	if(p->data == value) return p;
	p = (value < p->data) ? p->lchild : p-> rchild;
    }
    return NULL;

}

//Insert element
void InsertNodeInto(BitTree &rnode, int data)
{
    BitTree p = (BitTree)malloc(sizeof(BiTree));
    if(!p) return;
    p->data = data;
    p->lchild = p->rchild = p->parent = NULL;
    if(!rnode)
    {
	rnode = p;
	return;
    }
    if(NodeForValue(rnode, data))
    {
	return;
    }
    BitTree pos = NULL, rootnode = rnode;
    while(rootnode)
    {
	pos = rootnode;
	rootnode = (data < rootnode->data) ? rootnode->lchild : rootnode->rchild;
    }
    if(data < pos->data)
    {
	pos->lchild = p;
	p->parent = pos;
    }
    else
    {
	pos->rchild = p;
	p->parent = pos;
    }
}

//Delete element
void DeleteElement(BitTree &rnode, int data)
{
    BitTree p = rnode;
    if(!p) return;
    if(!NodeForValue(p, data)) return;
    BitTree pos = NodeForValue(p, data);
    if(pos->lchild == NULL and pos->rchild == NULL)
    {
	if(pos->parent == NULL)
	    free(pos);
	if(pos == pos->parent->lchild)
	{
	    pos->parent->lchild = NULL;
	    free(pos);
	}
	else
	{
	    pos->parent->rchild = NULL;
	    free(pos);
	}
    }

    else if(pos->lchild == NULL and pos->rchild !=NULL)
    {
	if(pos == pos->parent->lchild)
	{
	    pos->parent->lchild = pos->rchild;
	    pos->rchild->parent = pos->parent;
	    free(pos);
	}
	else
	{
	    pos->parent->rchild = pos->rchild;
	    pos->rchild->parent = pos->parent;
	    free(pos);
	}
    }

    else if(pos->rchild == NULL and pos->lchild != NULL)
    {
	if(pos == pos->parent->rchild)
	{
	    pos->parent->rchild = pos->lchild;
	    pos->lchild->parent = pos->parent;
	    free(pos);
	}
	else
	{
	    pos->parent->lchild = pos->lchild;
	    pos->lchild->parent = pos->parent;
	    free(pos);
	}
    }

    else
    {
	if(pos->parent == NULL)
	{
	    BitTree min = SearchMinValue(pos->rchild);
	    min->lchild = pos->lchild;
	    min->rchild = pos->rchild;
	    min->parent->lchild = NULL;
	    min->parent = NULL;
	    pos->lchild->parent = min;
	    pos->rchild->parent = min;
	    free(pos);
	}
	if(pos->parent->lchild == pos)
	{
	    BitTree min = SearchMinValue(pos->rchild);
	    //BitTree max = SearchMaxValue(pos->lchild)
	    pos->parent->lchild = min;
	    min->parent->lchild = NULL;
	    min->lchild = pos->lchild;
	    min->rchild = pos->rchild;
	    min->parent = pos->parent;
	    pos->lchild->parent = pos->rchild->parent = min;
	    free(pos);
	}
	else
	{
	    BitTree max = SearchMaxValue(pos->lchild);
	    //BitTree min = SearchMaxValue(pos->rchild);
	    pos->parent->rchild = max;
	    max->parent->rchild = NULL;
	    max->rchild = pos->rchild;
	    max->lchild = pos->lchild;
	    max->parent = pos->parent;
	    pos->lchild->parent = pos->rchild->parent = max;
	    free(pos);
	}
    }
    return;
}

// PreOrder traversal(recursion version)
void PreOrder(BitTree rnode)
{
    if(!rnode)
	return;
    cout << rnode->data << " ";
    PreOrder(rnode->lchild);
    PreOrder(rnode->rchild);
}

//PreOrder traversal(loop version)
void _PreOrder(BitTree rnode)
{
    BitTree p = rnode, cur = NULL;
    if(!p)
	return;
    stack<BitTree> s;
    s.push(p);
    while(!s.empty())
    {
	cur = s.top();
	cout << cur->data << " ";
	s.pop();
	if(cur->rchild != NULL)
	    s.push(cur->rchild);
        if(cur->lchild != NULL)
	    s.push(cur->lchild);
    }
}

//InOrder traversal(recursion version)
void InOrder(BitTree rnode)
{
    if(!rnode)
	return;
    InOrder(rnode->lchild);
    cout << rnode->data << " ";
    InOrder(rnode->rchild);
}

//InOrder traversal(loop version)
void _InOrder(BitTree rnode)
{
    BitTree cur = rnode;
    if(!cur)
	return;
    stack<BitTree> s;
    while(!s.empty() || cur != NULL)
    {
	while(cur != NULL)
	{
	    s.push(cur);
	    cur = cur->lchild;
	}
	cur = s.top();
	cout << cur->data << " ";
	s.pop();
	cur = cur->rchild;
    }
}

//PostOrder traversal(recursion version)
void PostOrder(BitTree rnode)
{
    if(!rnode)
	return;
    PostOrder(rnode->lchild);
    PostOrder(rnode->rchild);
    cout << rnode->data << " ";
}

//PostOrder traversal(loop version)
void _PostOrder(BitTree rnode)
{
    if(!rnode)
	return;
    stack<pair<BitTree, bool> > s;
    pair<BitTree, bool> cur = make_pair(rnode, true);
    while(cur.first != NULL)
    {
	s.push(cur);
	cur = make_pair(cur.first->lchild, true);
    }
    if(!s.empty())
    {
	if(s.top().second == true)
	{
	    s.top().second = false;
	    cur = make_pair(s.top().first->rchild, true);
	}
	else
	{
	    cout << s.top().first->data << " ";
	    s.pop();
	}
    }
}

//PostOrder traversal(loop version)
void __PostOrder(BitTree rnode)
{
    if(!rnode)
	return;
    BitTree cur, pre = NULL;
    stack<BitTree> s;
    s.push(rnode);
    while(!s.empty())
    {
	cur = s.top();
	if((cur->lchild==NULL&&cur->rchild==NUll)||(pre != NULL&&(pre==cur->lchild||pre==cur-rchild))
	{
	    cout << cur->data << " ";
	    s.pop();
	    pre = cur;
	}
	else
	{
	    if(cur->rchild != NULL)
		s.push(cur->rchild);
	    if(cur->lchild != NULL)
		s.push(cur->lchild);
	}
    }
}

//layer traversal(loop version)
void LayerOrder(BitTree rnode)
{
    if(!rnode)
	return;
    queue<BitTree> tree;
    tree.push(rnode);
    BitTree cur = NULL;
    while(!tree.empty())
    {
	cur = tree.front();
	cout << cur->data << " ";
	tree.pop();
	if(cur->lchild != NULL)
	    tree.push(cur-lchild);
	if(cur->rchild != NULL)
	    tree.push(cur->rchild);
    }
}


//calculate the width of the tree
int GetTreeWidth(BitTree rnode)
{
    if(!rnode)
	return 0;
    int cur_width = 0, upper_width = 1, tree_width = 1;
    queue<BitTree> tree;
    tree.push(rnode);
    BitTree cur = NULL;
    while(!tree.empty())
    {
	while(upper_width != 0)
	{
	    cur = tree.front();
	    tree.pop();
	    if(cur->lchild != NULL)
		tree.push(cur->lchild);
	    if(cur->rchild != NULL)
		tree.push(cur->rchild);
	    upper_width--;
	}
	cur_width = tree.size();
	tree_width = cur_width > upper_width ? cur_width : upper_width;
	upper_width = cur_width;
    }
    return tree_width;
}

//calculate the height of the tree
int GetTreeHeight(BitTree rnode)
{
    if(!rnode)
	return 0;
    int ltree_height = GetTreeHeight(rnode->lchild);
    int rtree_height = GetTreeHeight(rnode->rchild);
    return ltree_height > rtree_height ? ltree_height+1 : rtree_height+1; 
}

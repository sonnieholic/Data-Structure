#include<iostream>
#include<cstdio>
#include <malloc.h>
#include<math.h>
#define MAX(a, b)    ( (a) > (b) ? (a) : (b) )

using namespace std;


typedef int Type;

typedef struct AVLTreeAVLTreeNode{
    Type value;                    // 关键字(键值)
    int height_count;
    struct AVLTreeAVLTreeNode *left;    // 左孩子
    struct AVLTreeAVLTreeNode *right;    // 右孩子
}AVLTreeNode, *AVLTree;

int Pheightc;
char Phbuf[6][200];
int Phx;

void pprint_tree(AVLTree tree, int level){
    if (tree == NULL){
        Phx += (pow(2, Pheightc - level) - 1);
        return;
    }
    char(*a)[200] = Phbuf;
    pprint_tree(tree->left, level + 1);
    a[level][Phx++] = tree->value;
    pprint_tree(tree->right, level + 1);

}

int height_count(AVLTreeNode *p)
{
	if(p==NULL)return 0;
	else{return ((AVLTreeNode *)(p))->height_count; }
}
/*
	打印树的函数
*/
void printTree(AVLTree tree){
    Pheightc=0;
    Phx=0;
    if (tree == NULL) return;
    char(*a)[200] = Phbuf;
    for (int i = 0; i<6; i++){
        for (int j = 0; j<200; j++){
            a[i][j] = '#';
        }
    }
    //先获取树高度
    Pheightc = height_count(tree);
    if (Pheightc > 6){
        cout << "error" << endl;
        return;
    }
    pprint_tree(tree, 0);
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 200; j++){
            if (a[i][j] =='#') cout << " ";
            else cout << (int)a[i][j];
        }
        cout << endl;
    }
}

/*
  获取AVL树的高度
 */
int avltree_height_count(AVLTree tree)
{
    return height_count(tree);
}

/*
  LL：左左对应的情况(左单旋转)。

  返回值：旋转后的根节点
 */
AVLTreeNode* LLRotation(AVLTree temp2)
{
    AVLTree temp1;

    temp1 = temp2->left;
    temp2->left = temp1->right;
    temp1->right = temp2;

    temp2->height_count = MAX( height_count(temp2->left), height_count(temp2->right)) + 1;
    temp1->height_count = MAX( height_count(temp1->left), temp2->height_count) + 1;

    return temp1;
}

/*
  RR：右右对应的情况(右单旋转)。

  返回值：旋转后的根节点
 */
 AVLTreeNode* RRRotation(AVLTree temp1)
{
    AVLTree temp2;

    temp2 = temp1->right;
    temp1->right = temp2->left;
    temp2->left = temp1;

    temp1->height_count = MAX( height_count(temp1->left), height_count(temp1->right)) + 1;
    temp2->height_count = MAX( height_count(temp2->right), temp1->height_count) + 1;

    return temp2;
}


/*
  LR：左右对应的情况(左双旋转)。

  返回值：旋转后的根节点
 */
 AVLTreeNode* LRRotation(AVLTree temp3)
{
    temp3->left = RRRotation(temp3->left);

    return LLRotation(temp3);
}

/*
  RL：右左对应的情况(右双旋转)。

  返回值：旋转后的根节点
 */
 AVLTreeNode* RLRotation(AVLTree temp1)
{
    temp1->right = LLRotation(temp1->right);

    return RRRotation(temp1);
}

/*
  将结点插入到AVL树中，并返回根节点
  返回值：
      根节点
 */
AVLTreeNode* avltree_insert(AVLTree tree, Type value)
{
    if (tree == NULL)
    {
        // 新建节点
		AVLTreeNode* p;
		p = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
		p->value = value;
		p->height_count = 0;
		p->left = NULL;
		p->right = NULL;
		tree=p;
        if (tree==NULL)
        {
            printf("ERROR!\n");
            return NULL;
        }
    }
    else if (value < tree->value) // 应该将value插入到"tree的左子树"的情况
    {
        tree->left = avltree_insert(tree->left, value);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height_count(tree->left) - height_count(tree->right) == 2)
        {
            if (value < tree->left->value)
            {
                cout<<"LL之前"<<endl;
                printTree(tree);
                tree = LLRotation(tree);
                cout<<"LL之后"<<endl;
                printTree(tree);
            }
            else
            {
                cout<<"LR之前"<<endl;
                printTree(tree);
                tree = LRRotation(tree);
                cout<<"LR之后"<<endl;
                printTree(tree);
            }
        }
    }
    else if (value > tree->value) // 应该将value插入到"tree的右子树"的情况
    {
        tree->right = avltree_insert(tree->right, value);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height_count(tree->right) - height_count(tree->left) == 2)
        {
            if (value > tree->right->value)
            {
                cout<<"RR之前"<<endl;
                printTree(tree);
                tree = RRRotation(tree);
                cout<<"RR之后"<<endl;
                printTree(tree);
            }
            else
            {
                cout<<"RL之前"<<endl;
                printTree(tree);
                tree = RLRotation(tree);
                cout<<"RL之后"<<endl;
                printTree(tree);
            }
        }
    }
    else //value == tree->value)
    {
        printf("error!\n");
    }
    tree->height_count = MAX( height_count(tree->left), height_count(tree->right)) + 1;
    return tree;
}
/*
    查找
*/
AVLTreeNode *avltree_search(AVLTree tree,Type value)
{
        if(tree->value==value)return tree;
        if(tree->value<value) return avltree_search(tree->right,value);
        if(tree->value>value) return avltree_search(tree->left,value);
}

/*
    找最大,最小节点
*/

AVLTreeNode *avltree_maximum(AVLTreeNode * T)
{
    AVLTreeNode *temp=T;
    while(temp->right!=NULL)
    {
        temp=temp->right;
    }
    return temp;
}
AVLTreeNode *avltree_minimum(AVLTreeNode * T)
{
    AVLTreeNode *temp=T;
    while(temp->left!=NULL)
    {
        temp=temp->left;
    }
    return temp;
}
/*
  删除结点(z)，返回根节点
  返回值：
      根节点
 */
AVLTreeNode* delete_AVLTreeNode(AVLTree tree, AVLTreeNode *z)
{
    // 根为空 或者 没有要删除的节点，直接返回NULL。
    if (tree==NULL || z==NULL)
        return NULL;

    if (z->value < tree->value)        // 待删除的节点在tree的左子树中
    {
        tree->left = delete_AVLTreeNode(tree->left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height_count(tree->right) - height_count(tree->left) == 2)
        {
            AVLTreeNode *r =  tree->right;
            if (height_count(r->left) > height_count(r->right))
                tree = RLRotation(tree);
            else
                tree = RRRotation(tree);
        }
    }
    else if (z->value > tree->value)// 待删除的节点在"tree的右子树"中
    {
        tree->right = delete_AVLTreeNode(tree->right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height_count(tree->left) - height_count(tree->right) == 2)
        {
            AVLTreeNode *l =  tree->left;
            if (height_count(l->right) > height_count(l->left))
                tree = LRRotation(tree);
            else
                tree = LLRotation(tree);
        }
    }
    else    // tree是对应要删除的节点。
    {
        // tree的左右孩子都非空
        if ((tree->left) && (tree->right))
        {
            if (height_count(tree->left) > height_count(tree->right))
            {
                AVLTreeNode *max = avltree_maximum(tree->left);
                tree->value = max->value;
                tree->left = delete_AVLTreeNode(tree->left, max);
            }
            else
            {
                AVLTreeNode *min = avltree_minimum(tree->right);
                tree->value = min->value;
                tree->right = delete_AVLTreeNode(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode *tmp = tree;
            tree = tree->left ? tree->left : tree->right;
            delete(tmp);
        }
    }

    return tree;
}

/*
  删除结点(value是节点值)，返回根节点
  返回值：
      根节点
 */

AVLTreeNode* avltree_delete(AVLTree tree, Type value)
{
    AVLTreeNode *z;
    if ((z = avltree_search(tree, value)) != NULL)
        tree = delete_AVLTreeNode(tree, z);
    return tree;
}

void inorder(AVLTreeNode* T)
{
    if (T == NULL)
        return;
    else
    {
        inorder(T->left);
        printf("%d ", T->value);
        inorder(T->right);
    }
}

int* search(int value,AVLTreeNode * T)
{
    if(value==T->value){cout<<value<<"在"<<&(T->value)<<endl;return &(T->value);}
    if(value>T->value)return search(value,T->right);
    if(value<T->value)return search(value,T->left);
}

int main()
{
    freopen("test.txt","r",stdin);
    freopen("ans.txt","w",stdout);
    AVLTreeNode* T=NULL;

    int arr[16];
    for(int i=0;i<=15;i++)
        scanf("%d",&arr[i]);


    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
       {
         T = avltree_insert(T,arr[i]);
       }
    cout<<"排序:"<<endl;
    inorder(T);
    cout<<endl;
    printTree(T);
    cout<<"删除元素11后"<<endl;
    T=avltree_delete(T, 11);
    inorder(T);
    cout<<endl;
    printTree(T);
    cout<<endl;
    int *temp;
    temp=search(10,T);
    cout<<temp<<"处:"<<*temp<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

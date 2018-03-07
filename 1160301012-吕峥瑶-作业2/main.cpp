/*
    最小堆优化的哈夫曼编码
*/
#include <stdio.h>
#include <stdlib.h>
#include<iostream>

#define MAX_TREE_HT 100
using namespace std;
int total=0;
int total1=0;
struct MinHeapNode {
    char data;         // 输入的字符数组中的一个字符
    unsigned freq;     // 字符出现的次数
    struct MinHeapNode *left, *right;
};//最小堆的结点
struct MinHeap {
    unsigned size;     // 最小堆元素的个数
    unsigned capacity;  //最大容量
    struct MinHeapNode **array;
};// 最小堆: 作为优先队列使用
struct node{
    char arr[95];
    int freq[95];
};
struct code{
    int *hufcode;
    int num;
};
typedef struct node Node;
typedef code Code;
typedef struct MinHeapNode * MHN;
Code str[95];//存95个字符的相应的哈夫曼编码
Node hufman;
//初始化一个最小堆节点
MHN newNode(char data, unsigned freq) {
    MHN temp = (MHN) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
};

// 创建一个容量为capacity 的最小堆
struct MinHeap* newMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    MHN *array = (MHN *)malloc(minHeap->capacity * sizeof(MHN));
    minHeap->array = array;
    return minHeap;
};

//  swap 两个堆节点
void swapMinHeapNode(MHN *a, MHN *b) {
    MHN temp = *a;
    *a = *b;
    *b = temp;
}

//得到左孩子节点下标，默认第一个节点下标为0
int getLeftIndex(int index) {
    return ((index << 1) + 1);
}

//得到右孩子节点下标，默认第一个节点下标为0
int getRightIndex(int index) {
    return ((index << 1) + 2);
}

// 调整最小堆
void adjustMinHeap(struct MinHeap* minHeap, int index) {
    int less = index;
    int left = getLeftIndex(index);
    int right = getRightIndex(index);
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[less]->freq) {
        less = left;
    }
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[less]->freq) {
        less = right;
    }

    if (less != index) {
        swapMinHeapNode(&minHeap->array[less], &minHeap->array[index]);
        adjustMinHeap(minHeap, less);
    }
}

//检测堆的大小是否为1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// 检测是否是叶子节点
int isLeaf(MHN node) {
    return !(node->left) && !(node->right);
}



//取得堆中最小的节点
MHN extractMin(struct MinHeap* minHeap) {
    MHN temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size-1];
    --minHeap->size;
    adjustMinHeap(minHeap, 0);
    return temp;
}

// 向最小堆中插入一个节点
void insertMinHeap(struct MinHeap* minHeap,MHN minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i-1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i-1) / 2];
        i = (i-1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

//构建一个最小堆
void buildMinHeap(struct MinHeap* minHeap) {
    int index = minHeap->size - 1;
    int i;
    for (i = (index - 1) / 2; i >= 0; --i) {
        adjustMinHeap(minHeap, i);
    }
}

// 创建一个容量为 size的最小堆，并插入 data[] 中的元素到最小堆
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = newMinHeap(size);
    for (int i = 0; i < size; i++) {
        minHeap->array[i] = newNode(data[i],  freq[i]);
    }
    minHeap ->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// 构建哈夫曼树
MHN buildHuffmanTree(char data[], int freq[], int size) {
    MHN left, right, top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('.', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
// 打印
void printArr(int arr[], int n,int tp)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d", arr[i]);
        str[tp].hufcode[i]=arr[i];
    }
    printf("\n");
}
// 打印哈夫曼编码
void printCodes(MHN root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr ,top + 1);
    }
    // 如果是叶子节点就打印
    if (isLeaf(root)) {
        printf("%c :", root->data);
        int tp=(int)(root->data)-32;
        str[tp].hufcode=(int *)malloc(sizeof(int)*(top));
        str[tp].num=top;
        printArr(arr, top,tp);
    }
}


// 构建哈夫曼树，并遍历打印该哈夫曼树
 MHN HuffmanCodes(char data[], int freq[], int size)
{
   //  构建哈夫曼树
    MHN root = buildHuffmanTree(data, freq, size);
   // 打印构建好的哈夫曼树
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
    return root;
}

//初始化数组
void initial(Node &hufman)
{
    for(int i=0;i<=94;i++)
    {
        hufman.arr[i]=i+32;
       // printf("%c",hufman.arr[i]);
        hufman.freq[i]=0;
    }
}
//从文件读取
void ReadFromFile(Node &hufman)
{
    char ch;
    while((scanf("%c",&ch)!=EOF))
    {
        int temp=(int)ch;
        hufman.freq[temp-32]=hufman.freq[temp-32]+1;
    }
}
//打印频率
void Print(Node &hufman)
{
        hufman.arr[8]='(';
    for(int i=0;i<=94;i++)
    {
        printf("%c : %d\n",hufman.arr[i],hufman.freq[i]);
    }
}
//把编码写入code.txt
void TFileTHuf()
{
    FILE *fp;
    FILE *fp1;
    fp=fopen("test.txt","r");
    fp1=fopen("code.txt","w");
    char ch;
    while((ch= fgetc(fp)) != EOF)
    {
        total1++;
        int tp=(int)ch-32;
        for(int i=0;i<str[tp].num;i++)
        {
             fprintf(fp1,"%d",str[tp].hufcode[i]);
             total++;
        }
    }
    fclose(fp);
    fclose(fp1);
}
//解码转回文档
void Decode(MHN root)
{
    FILE *fp3;
    FILE *fp4;
    fp4=fopen("decode.txt","w");
    fp3=fopen("code.txt","r");
    int temp;
    MHN tempnode=root;
    char ch;
    while((ch= fgetc(fp3))!= EOF)
    {
        temp=ch-'0';
        if(temp==0)tempnode=tempnode->left;
        else tempnode=tempnode->right;
        if(isLeaf(tempnode))
        {
            fprintf(fp4,"%c",tempnode->data);
            tempnode=root;
        }
    }
    fclose(fp3);
    fclose(fp4);
}
//分析过程和效率
void analyse(int total,int total1)
{
    cout<<"文本一共"<<total1<<"字符"<<endl;
    cout<<"哈夫曼编码用了"<<total<<"bit"<<endl;
    cout<<"原文本二进制编码用了"<<total1*8<<"bit"<<endl;
    double rate;
    rate=total/(total1*8.0)*100;
    cout<<"压缩率为"<<rate<<"%"<<endl;
}
int main() {
    freopen("test.txt","r",stdin);
    initial(hufman);
    ReadFromFile(hufman);
    Print(hufman);
    MHN root;
    root=HuffmanCodes(hufman.arr, hufman.freq,95);
    Decode(root);
    TFileTHuf();
    analyse(total,total1);
    fclose(stdin);
    return 0;
}

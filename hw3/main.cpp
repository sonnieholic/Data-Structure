/*
作业3
内含dijkstra堆优化
*/
#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <strings.h>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#define INT_MAX1 100000
using namespace std;
const int maxn=100000+5;
typedef pair<int,int> pii;
struct Edge{
    int to,weight;
    Edge(int to,int weight):to(to),weight(weight){}
};
vector<vector<Edge> > G(maxn);
struct Dijkstra{
    int n,m;
    bool done[maxn];
    int dist[maxn];
    int p[maxn];
    Dijkstra(int n):n(n){
        for(int i=0;i<n;i++) G[i].clear();
    }
    void AddEdge(int from,int to,int weight){
        G[from].push_back(Edge(to,weight));
    }
    void dijkstra(int s)
    {
        priority_queue<pii,vector<pii>,greater<pii> > Q;
        memset(dist,0x7f,sizeof(dist));
        memset(done,false,sizeof(done));

        dist[s]=0;
        Q.push(pii(0,s));
        while(!Q.empty())
        {
            int u=Q.top().second; Q.pop();
            if(done[u]) continue;
            done[u]=true;
            for(int i=0;i<G[u].size();i++)
            {
                Edge& e=G[u][i];
                int v=e.to ,w=e.weight;
                if(dist[v]>dist[u]+w)
                {
                    dist[v]=dist[u]+w;
                    p[v]=u;
                    Q.push(pii(dist[v],v));
                }
            }
        }
    }
};

typedef int ** Graph;
int vertexnum,edgenum;
Graph goal;
/*
图的建立
*/
Graph CreateGraph()
{
    freopen("test.txt","r",stdin);
    scanf("%d %d",&vertexnum,&edgenum);
    goal=(Graph)malloc(sizeof(int *)*(vertexnum+1));
    for(int i=1;i<=vertexnum;i++)
    {
        goal[i]=(int *)malloc(sizeof(int)*(vertexnum+1));
    }
    for(int i=1;i<=vertexnum;i++)
        for(int j=1;j<=vertexnum;j++)
            goal[i][j]=INT_MAX1;
    int x,y,z;
    for(int i=1;i<=edgenum;i++)
    {
        scanf("%d %d %d",&x,&y,&z);
        goal[x][y]=z;
    }
    cout<<"输入的图为："<<endl;
    for(int i=1;i<=vertexnum;i++)
    {for(int j=1;j<=vertexnum;j++)
            if(goal[i][j]==INT_MAX1)cout<<"∞"<<"  ";
            else cout<<goal[i][j]<<"  ";
    cout<<endl;
    }
    return goal;
}
int MinCost(int D[],bool S[])
{
    int temp=INT_MAX1;
    int w;
    for(int i=2;i<=vertexnum;i++)
        if(!S[i]&&D[i]<temp)
    {
        temp=D[i];
        w=i;
    }
    return w;
}
/*
dijkstra算法
*/
void Dijkstra(Graph C,int D[],int P[],bool S[])
{
    for(int i=2;i<=vertexnum;i++)
    {
        D[i]=C[1][i];
        S[i]=false;
        P[i]=1;
    }
    for(int i=2;i<=vertexnum;i++)
    {
        int w=MinCost(D,S);

        int sum=0;
        S[w]=true;
        for(int v=2;v<=vertexnum;v++)
            if(S[v]!=true)
        {
            sum=D[w]+C[w][v];
            if(sum<D[v]){D[v]=sum;P[v]=w;}
        }

    }
    cout<<"此时源点为1"<<endl;
    for(int i=2;i<=vertexnum;i++)
    {
        if(D[i]>=100000){cout<<"不可达"<<endl;continue;}
        cout<<"从源点到"<<i<<"的最短距离为"<<D[i]<<endl;
        cout<<"最短路径为:"<<endl;
        stack <int>path;
        int i1=i;
        path.push(i);
        while(i1!=1)
        {
            path.push(P[i1]);
            i1=P[i1];
        }
        cout<<"1";
        path.pop();
        while(!path.empty())
        {
            cout<<"->";
            cout<<path.top();
            path.pop();
        }
        cout<<endl;
    }
}
void getPath(int i ,int j,int **P1){
    if(P1[i][j]==-1) printf("->%d ",j);
    else{
        getPath(i,P1[i][j],P1);
        getPath(P1[i][j],j,P1);
    }
}
/*
以floyed为基础的操作
*/
void Floyed(Graph goal,int **D1,int **P1,int option)
{
    int A[vertexnum+1][vertexnum+1];
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            D1[i][j]=goal[i][j];

            P1[i][j]=-1;
            if(goal[i][j]==INT_MAX1)A[i][j]=0;
            else A[i][j]=1;
        }
    }
    for(int k=1;k<=vertexnum;k++)
    {
        for(int i=1;i<=vertexnum;i++)
        {
            for(int j=1;j<=vertexnum;j++)
            {
                if(D1[i][k]+D1[k][j]<D1[i][j])
                {
                    D1[i][j]=D1[i][k]+D1[k][j];
                    P1[i][j]=k;
                }
            }
        }
    }
//最短距离矩阵和最短路径矩阵
    if(option==2){
    cout<<"最短距离矩阵"<<endl;
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            if(D1[i][j]==INT_MAX1)cout<<"∞"<<"  ";
            else cout<<D1[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"最短路径矩阵"<<endl;
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            cout<<P1[i][j]<<"  ";
        }
        cout<<endl;
    }}
    if(option==3){
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            if(D1[i][j]==INT_MAX1)cout<<i<<"和"<<j<<"之间不可达"<<endl;
            else
            {
                cout<<i<<"和"<<j<<"之间最短路径长度为："<<D1[i][j]<<endl;
                cout<<i<<"和"<<j<<"之间最短路径为："<<endl;
                cout<<i;
                getPath(i,j,P1);
                cout<<endl;
            }
        }
        cout<<endl;
    }}
//到目标节点的最短长度
    if(option==4){
    cout<<"输入您要查找的目标节点"<<endl;
    int score;
    scanf("%d",&score);
    if(score>vertexnum)cout<<"输入无效";
    else
    {
        cout<<"输入的是："<<score<<endl;
        for(int i=1;i<=vertexnum;i++)
        {
            if(i==score)continue;
            if(D1[i][score]==INT_MAX1)continue;
            cout<<"顶点"<<i<<"到顶点"<<score<<"的最短路径长度是 "<<D1[i][score]<<" ,路径是："<<endl;
            cout<<i;
            getPath(i,score,P1);
            cout<<endl;
        }
    }}
//一对顶点之间的最短距离
    if(option==5){
    cout<<"输入一对顶点"<<endl;
    int temp;
    scanf("%d",&temp);
    int m,n;
    scanf("%d %d",&m,&n);
    cout<<"从"<<m<<"到"<<n<<endl;
    if(m>vertexnum||n>vertexnum)cout<<"输入无效";
    else
    {
        if(D1[m][n]==INT_MAX1){cout<<"不可达";}
        else{
        cout<<"最短距离为"<<D1[m][n]<<endl;
        cout<<"最短路径为 : ";
        cout<<m;
        getPath(m,n,P1);}
    }
    cout<<endl<<"从"<<n<<"到"<<m<<endl;
    if(m>vertexnum||n>vertexnum)cout<<"输入无效";
    else
    {
        if(D1[n][m]==INT_MAX1){cout<<"不可达";}
        else{
        cout<<"最短距离为"<<D1[n][m]<<endl;
        cout<<"最短路径为 : ";
        cout<<n;
        getPath(n,m,P1);}
    }
    }

//可达矩阵

    if(option==6){
            cout<<endl<<"可达矩阵为"<<endl;
    for (int i = 1;i <=vertexnum;i++)
    {
        for (int j = 1;j <=vertexnum;j++)
        {
            if (A[j][i])
            {
                for (int k = 1;k <=vertexnum;k++)
                {
                    A[j][k] = A[j][k]|A[i][k];//逻辑加
                }
            }
        }
    }
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            cout<<A[i][j]<<"  ";
        }
        cout<<endl;
    }
    }
}

int main()
{
    int option;
    cout<<"1.Dijkstra"<<endl;
    cout<<"2.Fliyed最短距离最短路径矩阵"<<endl;
    cout<<"3.任意两点之间最短路径和距离"<<endl;
    cout<<"4.单目标最短距离和路径"<<endl;
    cout<<"5.一对顶点到彼此的最短路径和距离"<<endl;
    cout<<"6.可达矩阵"<<endl;
    cout<<"7.Dijkstra优化"<<endl;
    scanf("%d",&option);

    goal=CreateGraph();
    int D[vertexnum+1],P[vertexnum+1];
    bool S[vertexnum+1];
    if(option==1){
    cout<<endl<<"Dijkstra"<<endl<<endl;
    Dijkstra(goal,D,P,S);}
    if(option==2||option==3||option==4||option==5||option==6){
    Graph P1,D1;
    P1=(Graph)malloc(sizeof(int *)*(vertexnum+1));
    for(int i=1;i<=vertexnum;i++)
    {
        P1[i]=(int *)malloc(sizeof(int)*(vertexnum+1));
    }
    D1=(Graph)malloc(sizeof(int *)*(vertexnum+1));
    for(int i=1;i<=vertexnum;i++)
    {
        D1[i]=(int *)malloc(sizeof(int)*(vertexnum+1));
    }
    cout<<endl<<"Floyed"<<endl<<endl;
    Floyed(goal,D1,P1,option);
    fclose(stdin);}
/*
优化的dijkstra
*/
    if(option==7){
    cout<<"dijkstra堆优化"<<endl;
    freopen("test1.txt","r",stdin);
    int n,m,u,v,w;
    cin>>n>>m;
     struct Dijkstra d(n);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        d.AddEdge(u,v,w);
    }
    d.dijkstra(1);
    for(int i=2;i<=n;i++)
    cout<<"源点1到"<<i<<"最短路径长度为"<<d.dist[i]<<endl;
    cout<<"从源点到最后一个顶点的最短路径为"<<endl;
    vector<int> ans;
    for(int i=n;i!=1;i=d.p[i]) ans.push_back(i);
    ans.push_back(1);
    for(int i=ans.size()-1;i>=0;i--) {cout<<ans[i];if(i!=0)cout<<"->";}
    fclose(stdin);}
    return 0;
}

#include<cstdio>
#include<iostream>
#include<string.h>
#include<fstream>
#include<math.h>
using namespace std;

struct polynode{
    float coef;
    int exp;
    polynode *link;
};
typedef polynode *polypointer;
polypointer a=NULL;
polypointer b=NULL;

ofstream outfile,fout;
float x0;
void Destory(polypointer head)//销毁链表函数
{
	polypointer p = head,pr = NULL;
	while (p != NULL)
	{
		pr = p;
		p = p->link;
		delete pr;
	}
	cout<<"空间已释放"<<endl;
	return;
}
void calcu(float x,polypointer ans)//带入 x0求值
{
    float p1=0;
    if(ans==NULL){cout<<0<<endl;outfile<<0<<endl;return;}
    while(ans!=NULL)
    {
        p1=p1+ans->coef*pow(x,ans->exp);
        ans=ans->link;
    }
    cout<<p1<<endl;
    outfile<<p1<<endl;
}
int Print(polypointer L)
{

    if(L==NULL){cout<<"0"<<endl;outfile<<"0"<<endl;return 1;}
    do{
        cout<<L->coef<<"x^"<<L->exp;
        outfile<<L->coef<<"x^"<<L->exp;
        if(L->link!=NULL&&L->link->coef>0){cout<<"+";outfile<<"+";}
        L=L->link;
    }while(L!=NULL&&L->link!=NULL);
    if(L!=NULL){cout<<L->coef<<"x^"<<L->exp<<endl;outfile<<L->coef<<"x^"<<L->exp<<endl;}
    else {cout<<endl;outfile<<endl;}
    return 0;
}
polypointer Insert(float coef1,int exp1,polypointer L)//插入链表，按照降幂，插入排序
{
   // int cu=2;
    if(L==NULL)
    {
      //  cout<<1<<endl;
        L=new polynode;
        L->coef=coef1;
        L->exp=exp1;
        L->link=NULL;
        return L;
    }
    else{

        int doflag=0;
        int done=0;
        polypointer temp=L;
        polypointer temp1=L;
        polypointer tem;
        tem=new polynode;
        tem->coef=coef1;
        tem->exp=exp1;
        tem->link=NULL;
        while(temp1!=NULL)
        {
            if(tem->exp==temp1->exp){temp1->coef+=tem->coef;done=1;}
            temp1=temp1->link;
            //return L;
        }
        if(done==1)return L;
        if(temp->exp<exp1)
            {
                polypointer x1;
                x1=L;
                L=tem;
                tem->link=x1;
                return L;
            }

        if(temp->link==NULL)
        {
            if(temp->exp<exp1)
            {
                polypointer x1;
                x1=L;
                L=tem;
                tem->link=x1;
            }

            else{L->link=tem;}
            doflag=1;
            return L;
        }
        while(temp->link!=NULL)
       {
            if((exp1<(temp->exp))&&(exp1>(temp->link->exp)))
            {
                polypointer x;
                x=temp->link;
                temp->link=tem;
                tem->link=x;
                doflag=1;
            }
            temp=temp->link;
        }
        if(doflag==0)
        {
            polypointer x2=L;
            while(x2->link!=NULL)
            {
                x2=x2->link;
            }
            x2->link=tem;
        }
        return L;
    }
}
polypointer trans(char expr[],polypointer m)//解读字符串中的信息，把字符串变为数字
{
    polypointer temp=m;
    int i=0;
    int pflag=0;
    int xflag=0;
    int tag=0;
    int tag1=0;
    float ans=0;
    int counte=0;
    int counte1=0;
    int exp;
    float coef;
    while(expr[i]!='#')
    {
        if(expr[i]=='+')
        {
            i++;
            tag1=0;
            xflag=0;
            coef=ans;
            temp=Insert(coef,exp,temp);
            pflag=0;
            counte=0;
            counte1=0;
            ans=0;
            continue;
        }
        else if(expr[i]=='^')
        {
            i++;
            continue;
        }
        else if(expr[i]=='x')
        {
            xflag=1;
            i++;
            tag=0;
            continue;
        }
        else if((expr[i]>='0'&&expr[i]<='9')||expr[i]=='.')
        {
            if(expr[i]=='.')
            {
                pflag=1;
                i++;
                continue;
            }
            if(xflag==0)
            {
                int tem1=expr[i]-'0';//把数字由字符转变为数字
                //cout<<"tem1:"<<tem1;
                if(pflag==0)//如果是小数点前的位数做一种处理
                {
                counte++;
                if(counte==1){ans=ans+tem1;}
                else ans=ans*10+tem1;
                }
                else{//如果是小数点后的位数，做另一种处理
                counte1++;
                ans=ans+pow(0.1,counte1)*tem1;
                //cout<<ans<<endl;
                }
            }
            else{
                if(tag1>1)
                {
                    exp=exp*10+(expr[i]-'0');
                }
                else{
                    exp=expr[i]-'0';
                    tag1=2;
                }
            }
            i++;
        }
    }
   // cout<<coef<<" "<<exp<<endl;
    coef=ans;
    temp=Insert(coef,exp,temp);
    pflag=0;
    counte=0;
    counte1=0;
    ans=0;
    return temp;
}
char op3[3];
char exp3[10];
int ReadDoubleExpr()//从文件读取运算式
{
    char expr1[100];
    char expr2[100];
    FILE *fp;
   // int contr=0;
    cout<<"请输入打开文件no."<<endl;
    int file;
    cin>>file;
    switch(file)
    {
        case 0:
            fp=fopen("exp.txt","r");
            break;
        case 1:
            fp=fopen("exp1.txt","r");
            break;
        case 2:
            fp=fopen("exp2.txt","r");
            break;
        case 3:
            fp=fopen("exp3.txt","r");
            break;
        case 4:
            fp=fopen("exp4.txt","r");
            break;
        default:
            cout<<"not found!"<<endl;
            return -1;
    }
    fgets(expr1,1024,fp);
    fgets(expr2,1024,fp);
    fgets(op3,1024,fp);
    fgets(exp3,1024,fp);
    sscanf(exp3,"%[^#]",exp3);
    sscanf(exp3,"%f",&x0);
    cout<<expr1<<endl;
    outfile<<expr1<<endl;
    cout<<expr2<<endl;
    outfile<<expr2<<endl;


    a=trans(expr1,b);
    cout<<"expr1存入链表后："<<endl;
    outfile<<"expr1存入链表后："<<endl;
    Print(a);

    b=trans(expr2,b);
    cout<<"expr2存入链表后："<<endl;
    outfile<<"expr2存入链表后："<<endl;
    Print(b);
}
polypointer Attach(float c,int e,polypointer d)//插入链表
/*
建立一个新结点，系数coef=c,指数exp=e,把它连接到d所指结点之后，并且返回这个新结点的指针
*/
{
    polypointer x;
    x=new polynode;
    x->coef=c;
    x->exp=e;
    d->link=x;
    return x;
}
char Compare(int x,int y)
{
    if(x==y)return '=';
    if(x>y) return '>';
    if(x<y) return '<';
}
polypointer PolyAdd(polypointer a,polypointer b)//加法
{
    polypointer p,q,d,c;
    float x;
    p=a;q=b;
    c=new polynode;d=c;
    d->link=NULL;
    while((p!=NULL)&&(q!=NULL))
    {
        switch(Compare(p->exp,q->exp))
        {
            case '=':
                x=p->coef+q->coef;
                if(x!=0)
                    d=Attach(x,p->exp,d);
                p=p->link;q=q->link;
                break;
            case '>':
                d=Attach(p->coef,p->exp,d);
                p=p->link;
                break;
            case '<':
                d=Attach(q->coef,q->exp,d);
                q=q->link;
                break;
        }
    }
    while(p!=NULL)
    {
        d=Attach(p->coef,p->exp,d);
        p=p->link;
    }
     while(q!=NULL)
    {
        d=Attach(q->coef,q->exp,d);
        q=q->link;
    }
    d->link=NULL;
    p=c;c=c->link;delete p;
   // Print(c);
    return c;
}
polypointer PolySub(polypointer a,polypointer b)//减法
{
    polypointer sub;
    polypointer temans;
    sub=b;
    do{
        sub->coef=-sub->coef;
        sub=sub->link;
    }while(sub!=NULL);
  // if(sub!=NULL) sub->coef=-sub->coef;
    temans=PolyAdd(a,b);
   // Print(temans);
    return temans;
}
polypointer PolyMul(polypointer a,polypointer b)//乘法
{
    polypointer p,q,c;
    p=a;q=b;
    c=NULL;
    while(q!=NULL)
    {
        p=a;
        while(p!=NULL)
        {
            c=Insert(p->coef*q->coef,p->exp+q->exp,c);
            p=p->link;
        }
        q=q->link;
    }
    return c;
}
polypointer PolyDiv(polypointer a,polypointer b)//除法
{
    polypointer p,q;
    polypointer ans=NULL;
    polypointer ans1=NULL;
    polynode uniq;
    p=a;
    q=b;
    while(p->exp>=q->exp)
    {
        polypointer ans2=NULL;
        ans=Insert(p->coef/q->coef,p->exp-q->exp,ans);
        uniq.coef=p->coef/q->coef;
        uniq.exp=p->exp-q->exp;
        uniq.link=NULL;
        ans1=PolyMul(&uniq,q);//不是ans,是除得的结果
        ans2=PolySub(p,ans1);
        if(ans2==NULL){p=ans2;break;}
        p=ans2;
       // if(p->coef==0)break;
    }
    cout<<"商式为："<<endl;
    outfile<<"商式为："<<endl;
    Print(ans);
    cout<<"带入数字"<<x0<<"后商式计算得："<<endl;
    outfile<<"带入数字"<<x0<<"后商式计算得："<<endl;
    calcu(x0,ans);
    cout<<"余式为："<<endl;
    outfile<<"余式为："<<endl;
    Print(p);
    cout<<"带入数字"<<x0<<"后余式计算得："<<endl;
    outfile<<"带入数字"<<x0<<"后余式计算得："<<endl;
    calcu(x0,p);
    return ans;
}

int main()
{
    outfile.open("ans.txt");
    int r;
    r=ReadDoubleExpr();
    if(r==-1){cout<<"未成功打开文件,请重试"<<endl;return -1;}
    polypointer ans;
    cout<<op3[0]<<endl;

    outfile<<op3[0]<<endl;
    switch(op3[0])
    {
        case '+':
            ans=PolyAdd(a,b);
            cout<<"计算结果为："<<endl;
            outfile<<"计算结果为："<<endl;
            Print(ans);
            cout<<"带入数字"<<x0<<"后计算结果为："<<endl;
            outfile<<"带入数字"<<x0<<"后计算结果为："<<endl;
            calcu(x0,ans);
            break;
        case '-':
            ans=PolySub(a,b);
            cout<<"计算结果为："<<endl;
            outfile<<"计算结果为："<<endl;
            Print(ans);
            cout<<"带入数字"<<x0<<"后计算结果为："<<endl;
            outfile<<"带入数字"<<x0<<"后计算结果为："<<endl;
            calcu(x0,ans);
            break;
        case '*':
            ans=PolyMul(a,b);
            cout<<"计算结果为："<<endl;
            outfile<<"计算结果为："<<endl;
            Print(ans);
            cout<<"带入数字"<<x0<<"后计算结果为："<<endl;
            outfile<<"带入数字"<<x0<<"后计算结果为："<<endl;
            calcu(x0,ans);
            break;
        case '/':
            ans=PolyDiv(a,b);
            break;
        default:
            cout<<"error"<<endl;
            outfile<<"error"<<endl;
            return -1;
    }
    Destory(ans);
    cout<<"已经成功写入文件"<<endl;
    outfile.close();
    return 0;
}

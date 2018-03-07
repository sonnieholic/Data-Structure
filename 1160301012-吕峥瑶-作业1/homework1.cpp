#include<iostream>
#include<cstdio>
#include<string.h>
#include<math.h>
#define max 50
using namespace std;

typedef struct {
    char data[max];
    float value[max];
    int top ;
} STACK ;
void push(char x,STACK &S)
{
    S.data[++S.top]=x;
}
char pop(STACK &S)
{
    S.top--;
    return S.data[S.top+1];
}
typedef struct {
    float data[max];
    int top ;
} STACK1 ;
STACK S;
char data1[max];
char data2[max];
char data3[max];
char* ReadExpr()//从文件中读取出输入的表达式，并且存在数组data1里。然后进一步操作
{
    cout<<"请输入一个语法正确的（中缀）表达式，在文件exp.txt中,注意："<<endl;
    cout<<"1.输入的表达式请以“#”开始和结尾"<<endl;
    cout<<"2.支持加，减，乘，除和幂级操作"<<endl;
    cout<<"3.支持浮点数,但是请把负数转化为(0-正数)"<<endl;
    cout<<"4.表达式中的符号都必须是英文符号"<<endl;
    cout<<"5.可以输入英文字母（大小写都可以）作为变量，但是后面会要求赋值"<<endl;
    cout<<"输入完成请按Y："<<endl;

    char sr=0;
    cin>>sr;
    if(sr=='Y'||sr=='y')
    {
        FILE *fp;
        int contr=0;
        fp=fopen("exp.txt","r");
    while(((data1[contr]=fgetc(fp))!=EOF))
    {
        contr++;
    }
  //  cout<<data1<<endl;
    int i=0,flag=0,j=0;
    S.top=-1;
    if(data1[1]=='-')data2[j++]='0';
    int sflag=0;
    while(flag!=2)//去掉其中的#，存入data2中
    {
        if(data1[i++]=='#'){flag++;continue;}
        else
        {
            if(data1[i-1]=='(')sflag=1;
            if(data1[i-1]=='-'&&sflag==1){data2[j++]='0';sflag=0;}
            if(data1[i-1]>='0'&&data1[i-1]<='9')sflag=0;
            if(data1[i-1]==' ')continue;
            else  {data2[j++]=data1[i-1];}
        }
    }
    data2[j]='\0';
    cout<<"您输入的表达式为："<<endl;
    cout<<data2<<endl;
    return data2;
    }
    else{
        cout<<"请输入合法字符"<<endl;
    }
    return data2;
}
char *SuffixExpr(char *exp)//将中缀表达式转化为后缀表达式
{
    cout<<"在转化为后缀表达式的过程中，每一步栈顶变化如下:"<<endl;
    S.value[0]=-2;
    S.top=-1;
    int val;
    int j=0;
    while(*exp!='\0')//遍历data2，将符号压入栈中，并且打印数字
    {
        switch(*exp)
        {
            case '+':
                val=1;//这个值用来衡量算数符号的优先级
                if(S.top==-1){push(*exp,S);S.value[S.top]=val+0.1;}//如果栈为空，直接压栈
                else{
                    if(val>=S.value[S.top]){push(*exp,S);S.value[S.top]=val+0.1;}//判断优先级，如果高于栈顶，直接压栈
                    else{
                        do{
                            data3[j++]=' ';
                            data3[j++]=S.data[S.top];
                            S.top--;
                        }while(S.value[S.top]>val&&S.top!=-1);
                        push(*exp,S);S.value[S.top]=val+0.1;
                        }//低于栈顶则从栈中弹出元素直到栈空或者满足条件，存入data3中，以备打印需要

                }
                data3[j++]=' ';//用空格将数字和符号分隔开来，方便后面处理
                break;
            case '-'://同上
                val=1;
                if(S.top==-1){push(*exp,S);S.value[S.top]=val+0.1;}
                else{
                    if(val>=S.value[S.top]){push(*exp,S);S.value[S.top]=val+0.1;}
                    else{
                        do{
                            data3[j++]=' ';
                            data3[j++]=pop(S);
                        }while(S.value[S.top]>val&&S.top!=-1);
                        push(*exp,S);S.value[S.top]=val+0.1;
                    }
                }
                data3[j++]=' ';
                break;
            case '*'://同上
                val=2;
                if(S.top==-1){push(*exp,S);S.value[S.top]=val+0.1;}
                else{
                    if(val>=S.value[S.top]){push(*exp,S);S.value[S.top]=val+0.1;}
                    else{
                        do{
                            data3[j++]=' ';
                            data3[j++]=pop(S);
                        }while(S.value[S.top]>val&&S.top!=-1);
                       push(*exp,S);S.value[S.top]=val+0.1;
                    }

                }
                data3[j++]=' ';
                break;
            case '/'://同上
                val=2;
                if(S.top==-1){push(*exp,S);S.value[S.top]=val+0.1;}
                else{
                    if(val>=S.value[S.top]){push(*exp,S);S.value[S.top]=val+0.1;}
                    else{
                        do{
                            data3[j++]=' ';
                            data3[j++]=pop(S);
                        }while(S.value[S.top]>val&&S.top!=-1);
                        push(*exp,S);S.value[S.top]=val+0.1;
                    }

                }
                data3[j++]=' ';
                break;
            case '^'://同上
                val=3;
                    if(val>=S.value[S.top]){push(*exp,S);S.value[S.top]=val+0.1;}
                    else{
                        do{
                            data3[j++]=' ';
                            data3[j++]=pop(S);
                        }while(S.value[S.top]>val&&S.top!=-1);
                push(*exp,S);S.value[S.top]=val+0.1;
                }
                data3[j++]=' ';
                break;
            case '('://优先级最高，可以直接压栈，但是压栈之后优先级最低，所以直接赋值val=-1
                val=-1;
                S.data[++S.top]='(';
                S.value[S.top]=val;
                //data3[j++]=' ';
                break;
            case ')'://不进栈，弹出栈顶直到弹出左括号为止
                do{
                            data3[j++]=' ';
                            data3[j++]=pop(S);
                        }while(S.data[S.top]!='('&&S.top!=-1);
                        S.top--;
                        break;
            default:
                data3[j++]=*exp;
                break;
        }
       cout<<S.data[S.top]<<endl;
        exp++;//指针递增
    }
    while(S.top!=-1)//如果栈中还有元素，则弹出直到栈空
    {
        if(S.data[S.top]=='('){S.top--;continue;}
        else{data3[j++]=' ';data3[j++]=S.data[S.top];S.top--;}
    }
    data3[j]='\0';
    cout<<"转为后缀表达式为："<<endl;
    cout<<data3<<endl;
    return data3;
}
void Compute(char data3[])
{
    STACK1 T;
    T.top=-1;
    float ans=0;
    int flag=0;
    int i=0;
    float z;
    int tag=0;
    int counte=0;
    int counte1=0;
    cout<<"计算过程中每一步栈顶变化为："<<endl;
    while(data3[i]!='\0')
    {
        if((data3[i]>='A'&&data3[i]<='Z')||(data3[i]>='a'&&data3[i]<='z'))
           {
                cout<<"（计算过程中检测到您输入了变量"<<data3[i]<<",请为这个变量赋值:）"<<endl;
                cin>>ans;
                flag=1;
           }
        if((data3[i]=='+')||(data3[i]=='-')||(data3[i]=='*')||(data3[i]=='/')||(data3[i]=='^'))//如果是运算符号则单独处理
        {
            float x,y;
            x=T.data[T.top];
            T.top--;
            y=T.data[T.top];
            T.top--;//弹出栈顶两个元素
            switch(data3[i])//匹配操作符进行计算，然后将结果压入栈中
            {
                case '+':
                    z=y+x;
                    T.data[++T.top]=z;
                    break;
                case '-':
                    z=y-x;
                    T.data[++T.top]=z;
                    break;
                case '*':
                    z=y*x;
                    T.data[++T.top]=z;
                    break;
                case '/':
                    z=y/x;
                    T.data[++T.top]=z;
                    break;
                case '^':
                    z=pow(y,x);
                    T.data[++T.top]=z;
                    break;
                default:
                    cout<<"ops error!"<<endl;
                    break;
            }
            flag=0;//flag置0，表明最近操作是符号
        }
        if(((data3[i]>='0')&&(data3[i]<='9'))||data3[i]=='.')//如果是组成操作数的部分则单独处理
        {
            if(data3[i]=='.')//tag判断处理的数字是小数点前的还是后的
            {
                tag=1;
            }
            else{
            int tem1=data3[i]-'0';//把数字由字符转变为数字
            if(tag==0)//如果是小数点前的位数做一种处理
            {
                counte++;
                if(counte==1)ans=ans+tem1;
                else ans=ans*10+tem1;
            }
            else{//如果是小数点后的位数，做另一种处理
                counte1++;
                ans=ans+pow(0.1,counte1)*tem1;
            }
            }
            flag=1;//flag置1，表明最近操作是数字
      //      cout<<ans<<endl;
        }
        if((data3[i]==' ')&&flag==1)//如果是空格并且最近的操作是数字而不是符号，则要将数字压栈
        {
            T.top++;
            T.data[T.top]=ans;//压栈后，该操作数处理完毕，要对ans,counte,counte1,tag置0
            tag=0;
            counte=0;
            counte1=0;
            ans=0;
        }
        i++;
        cout<<T.data[T.top]<<endl;
    }
   // cout<<T.top<<endl;
    cout<<"计算结果为"<<endl;
   cout<<T.data[0]<<endl;
}
int main()
{
    char *exp;
    exp=ReadExpr();
    SuffixExpr(exp);
    Compute(data3);
}

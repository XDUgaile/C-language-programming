#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LEN 30
#define  MAX 100

//栈的数组实现
typedef struct
{
    int data[MAX_LEN];
    int top;
}Stack;

//为栈分配空间
Stack *Createstack()
{
    Stack *p;
    p = (Stack *)malloc(sizeof(*p));
    p->top = -1;
    return p;
}

//压栈
int Push(Stack *p,int x)
{
    if (p->top == MAX_LEN - 1)
    {
    return -1;
    }
    p->top++;
    p->data[p->top] = x;
    return 0;
}

//出栈
int Pop(Stack *L,int *x)
{
    if (L->top == -1)
    {
    return -1;
    }
    //利用传出参数传出栈顶元素
    *x = L->data[L->top];
    L->top--;
    return 0;
}

//栈顶
int TOP(Stack *L,int *x)
{
    if (L->top == -1)	//如果栈顶为-1就返回-1 
    {
    return -1;
    }
    *x = L->data[L->top];	//否则就将栈顶的值赋给x 
    return 0;
}

//判断栈是否为空
int Empty(Stack *L)
{
    return (L->top == -1);
}

//定义符号的优先级
int Priority(int ope)
{
    switch(ope)
    {
    case '(':   return 0;  //左括号已经在栈内时，如果比较，其优先级最低
    case '+':
    case '-':   return 1;	//+-为同一优先级 
    case '*':
    case '/':   return 2;	//*/为同一优先级 
    default :   return -1;
    }
}

// 将两个数出栈、根据ope符号计算，然后再次入栈
void Calculation(Stack *snum,int ope)
{
    int n,n1,n2;
    Pop(snum,&n1);
    Pop(snum,&n2);
    switch(ope)
    {
        case '+':   n = n1 + n2; break;
        case '-':   n = n2 - n1; break;
        case '*':   n = n1 * n2; break;
        case '/':   n = n2 / n1; break;
    }
    Push(snum,n);
}

// 先处理除右括号外的符号
void Deal_ope(Stack *snum,Stack *sope,int ope)
{
    int old_ope;
    if (Empty(sope) || ope == '(')
    {
        Push(sope,ope);
        return ;
    }
    TOP(sope,&old_ope);
    if (Priority(ope) > Priority(old_ope))
    {
        //传入符号大于当前栈顶，则将传入符号入栈
        Push(sope,ope);
        return ;
    }
    //如果传入的符号优先级小于当前栈顶符号
    while (Priority(ope) <= Priority(old_ope))
    {
        //将当前栈顶的符号取出与数字栈中顶端的两个数字进行计算
        Pop(sope,&old_ope);
        printf("%c ",old_ope);
        Calculation(snum,old_ope);
        if (Empty(sope))
        {
            break;
        }
        //再次取出一个当前栈符号与传入符号比较，循环
        TOP(sope,&old_ope);
    }
    Push(sope,ope);
}

//单独处理右括号
void Right(Stack *snum,Stack *sope)
{
    int old_ope;
    TOP(sope,&old_ope);
    while (old_ope != '(')
    {
        //当前符号出栈然后将数字出栈两个进行计算,在括号内优先级最高
        Pop(sope,&old_ope);
        printf("%c ",old_ope);
        Calculation(snum,old_ope);
        //循环
        TOP(sope,&old_ope);
    }
    Pop(sope,&old_ope);//出现左括号时将它丢弃
}

// 打印数字栈
void Display(Stack *L)
{
    int i;
    if (L->top == -1)
    {
    return ;
    }
    for (i = 0 ; i <= L->top; i++)
    {
    printf("%d ",L->data[i]);
    }
    printf("\n");
}

//打印符号栈
void Displayope(Stack *L)
{
    int i;
    if (L->top == -1)
    {
    return ;
    }
    for (i = 0 ; i <= L->top; i++)
    {
    printf("%c ",L->data[i]);
    }
    printf("\n");
}
 
int main()
{
    char str[MAX];
    scanf("%s", str);
//    printf("%s\n",str);
    int i = 0,value = 0,flag = 0;   //数字的值
    int old_ope;
    Stack *numstack,*opestack;
    numstack = Createstack();  // 创建存放数字的栈
    opestack = Createstack();  // 创建存放运算符的栈
    printf("后缀表达式为:");
    /* 表达式字符串解析函数,然后将高优先级的符号/(*)进行计算重新入栈
       退出while大家的优先级都一样*/
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            value *= 10;        //数字的获取，注意可能不止一位
            value +=str[i]-'0';
            flag = 1;
        }
        else
        {
            if (flag)   //flag = 1说明value里面存储了数字，将其入栈
            {
                printf("%d ",value);
                Push (numstack, value);
                //flag标志清零，value存放数字的变量清零
                flag = 0;
                value = 0;
            }
            if(str[i] == ')')
            {
                Right(numstack,opestack);
            }
            else
            {
                Deal_ope(numstack,opestack,str[i]);
            }
        }
        i++;
    }
    if (flag)   //如果flag = 1.说明value里面还有数值,将其入栈
    {
        printf("%d ",value);
        Push(numstack,value);
    }
    while (!Empty(opestack))  //如果符号栈不为空，继续计算
    {
        Pop(opestack,&old_ope);
        printf("%c ",old_ope);
        Calculation(numstack,old_ope);
    }
    Pop(numstack,&value); //最终答案
    printf("\n%s = %d\n",str,value);
    return 0;
}

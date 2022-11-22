#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LEN 30
#define  MAX 100

//ջ������ʵ��
typedef struct
{
    int data[MAX_LEN];
    int top;
}Stack;

//Ϊջ����ռ�
Stack *Createstack()
{
    Stack *p;
    p = (Stack *)malloc(sizeof(*p));
    p->top = -1;
    return p;
}

//ѹջ
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

//��ջ
int Pop(Stack *L,int *x)
{
    if (L->top == -1)
    {
    return -1;
    }
    //���ô�����������ջ��Ԫ��
    *x = L->data[L->top];
    L->top--;
    return 0;
}

//ջ��
int TOP(Stack *L,int *x)
{
    if (L->top == -1)	//���ջ��Ϊ-1�ͷ���-1 
    {
    return -1;
    }
    *x = L->data[L->top];	//����ͽ�ջ����ֵ����x 
    return 0;
}

//�ж�ջ�Ƿ�Ϊ��
int Empty(Stack *L)
{
    return (L->top == -1);
}

//������ŵ����ȼ�
int Priority(int ope)
{
    switch(ope)
    {
    case '(':   return 0;  //�������Ѿ���ջ��ʱ������Ƚϣ������ȼ����
    case '+':
    case '-':   return 1;	//+-Ϊͬһ���ȼ� 
    case '*':
    case '/':   return 2;	//*/Ϊͬһ���ȼ� 
    default :   return -1;
    }
}

// ����������ջ������ope���ż��㣬Ȼ���ٴ���ջ
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

// �ȴ������������ķ���
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
        //������Ŵ��ڵ�ǰջ�����򽫴��������ջ
        Push(sope,ope);
        return ;
    }
    //�������ķ������ȼ�С�ڵ�ǰջ������
    while (Priority(ope) <= Priority(old_ope))
    {
        //����ǰջ���ķ���ȡ��������ջ�ж��˵��������ֽ��м���
        Pop(sope,&old_ope);
        printf("%c ",old_ope);
        Calculation(snum,old_ope);
        if (Empty(sope))
        {
            break;
        }
        //�ٴ�ȡ��һ����ǰջ�����봫����űȽϣ�ѭ��
        TOP(sope,&old_ope);
    }
    Push(sope,ope);
}

//��������������
void Right(Stack *snum,Stack *sope)
{
    int old_ope;
    TOP(sope,&old_ope);
    while (old_ope != '(')
    {
        //��ǰ���ų�ջȻ�����ֳ�ջ�������м���,�����������ȼ����
        Pop(sope,&old_ope);
        printf("%c ",old_ope);
        Calculation(snum,old_ope);
        //ѭ��
        TOP(sope,&old_ope);
    }
    Pop(sope,&old_ope);//����������ʱ��������
}

// ��ӡ����ջ
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

//��ӡ����ջ
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
    int i = 0,value = 0,flag = 0;   //���ֵ�ֵ
    int old_ope;
    Stack *numstack,*opestack;
    numstack = Createstack();  // ����������ֵ�ջ
    opestack = Createstack();  // ��������������ջ
    printf("��׺���ʽΪ:");
    /* ���ʽ�ַ�����������,Ȼ�󽫸����ȼ��ķ���/(*)���м���������ջ
       �˳�while��ҵ����ȼ���һ��*/
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            value *= 10;        //���ֵĻ�ȡ��ע����ܲ�ֹһλ
            value +=str[i]-'0';
            flag = 1;
        }
        else
        {
            if (flag)   //flag = 1˵��value����洢�����֣�������ջ
            {
                printf("%d ",value);
                Push (numstack, value);
                //flag��־���㣬value������ֵı�������
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
    if (flag)   //���flag = 1.˵��value���滹����ֵ,������ջ
    {
        printf("%d ",value);
        Push(numstack,value);
    }
    while (!Empty(opestack))  //�������ջ��Ϊ�գ���������
    {
        Pop(opestack,&old_ope);
        printf("%c ",old_ope);
        Calculation(numstack,old_ope);
    }
    Pop(numstack,&value); //���մ�
    printf("\n%s = %d\n",str,value);
    return 0;
}

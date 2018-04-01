#include "./public.h"
#include "./list.h"

char *myGets(char *src, int size)
{
    char *dest = src;
    for(; dest<src+size-1; )
    {
        *dest = getchar();
        if(*src == '\n')
            continue;
        if(*dest == '\n')
            break;
        dest++;
    }
    if(*dest != '\n')
        while(getchar() != '\n');
    *dest = '\0';
    return src;
}

int initTime(Times *times)
{
    printf("输入年份:");
    scanf("%d",&times->year);
    getchar();
    if(1 > times->year)
        return 0;
    printf("输入月份:");
    scanf("%d",&times->month);
    getchar();
    if(0 > times->month || 12 < times->month)
        return 0;
    printf("输入日期:");
    scanf("%d",&times->day);
    getchar();
    if(0 > times->day || 31 < times->day)
        return 0;
    return 1;
}

void setTime(Times *times)
{
    while(!initTime(times))
        printf("\n时间输入错误，请重新输入\n");
    return;
}

void putTime(Times times)
{
    printf("\t%d年%d月%d号",times.year,times.month,times.day);
    return;
}

int putInt()
{
    int num = 0;
    scanf("%d",&num);
    getchar();
    return num;
}
int setID()
{
    printf("彩票ID：");
    int ID = putInt();
    return ID;
}
int setAccount()
{

    printf("账户：");
    int account = putInt();
    return account;
}
int setPwd()
{
    printf("密码：");
    int pwd = putInt();
    return pwd;
}

int setNum()
{
    printf("购买数量：");
    int num = putInt();
    return num;

}
char * setName(char *str)
{
    printf("用户名:");
    return myGets(str,SIZE);
}
int setMoney()
{
    printf("设置金额:");
    int money = putInt();
    return money;
}
char myGetc()   //只获取一个字符
{
    char ch= getchar();
    while(getchar()!='\n')
    ;
    return ch;
}
void anyKey()   //在清屏前暂停显示
{
    printf("\n按任意键继续..\n");
    if('\n' == getchar())
        return;
    else
    {
        getchar();
        return;
    }
}

void printState(bool a,int b)   //彩票的几种状态的打印方式
{
    if(a == false){
        if(0 == b)
            printf("false");
        else
            printf("$:%d",b);
    }
    else
        printf("true ");
    return;
}


#include "./interfaceUI.h"

void adminUI()
{   printf("\033[47;31m\033[5m");
    printf("************************\n");
    printf("\t1.彩票发布\t\n");
    printf("\t2.删除彩票\t\n");
    printf("\t3.查询信息\t\n");
    printf("\t4.彩票排序\t\n");
    printf("\t5.彩票开奖\t\n");
    printf("\t0.退　出\t\n");
    printf("************************\n");
    printf("\033[0m");
    printf("input choice:");
    return;
}



void userUI()
{
    printf("***************************\n");
    printf("\t1.个人信息\n");
    printf("\t2.购彩记录\n");
    printf("\t3.显示彩票信息\n");
    printf("\t4.选购彩票\n");
    printf("\t5.账户充值\n");
    printf("\t6.用户注销\n");
    printf("\t0.退出\n");
    printf("**************************\n");
    printf("input choice:");
    return;
}

int loginUI()
{
    printf("*********************");
    printf("\t1.注册\n");
    printf("\t2.登录\n");
    printf("*********************\n");
    printf("input choice:");
    return 0;
}
void initUI()
{
    printf("*******************************\n\n");
    printf("\t项目名称:彩票管理系统\n\n");
    printf("\t作者:项琼楼\n\n");
    printf("\t版本号：SH-1\n\n");
    printf("\t发布时间：2018/3/26\n\n");
    printf("*******************************\n\n");
    return;
}


#ifndef _LIST_H_
#define _LIST_H_


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

// bool 类型宏定义
#define bool int
#define false 0
#define true 1
#define SIZE 32

typedef struct Times
{
    int year;
    int month;
    int day;
}Times;
typedef struct lotInfo
{
    int ID;         //ID
    char type[32]; //类型
    float price;    //单价
    int num;        //数量
    bool state[2];     //状态
    struct Times star; //发布时间
    struct Times last;   //开奖时间
}lotInfo;

typedef struct lotNode
{
    struct lotInfo data;//数据域

    struct lotNode *pNext;//指针域
}lotNode;

typedef struct userInfo
{
    int account;    //账户
    char name[SIZE];
    int pwd;   //密码
    float balance;  //余额
}userInfo;

typedef struct userNode
{
    struct userInfo data;//

    struct userNode *pNext;//
}userNode;

typedef struct buyInfo
{
    int account;    //账户
    int ID;         //编号
    char type[SIZE]; //类型
    int num;        //数量
    bool state[2];     //状态
}buyInfo;

typedef struct buyNode
{
    struct buyInfo data;

    struct buyNode *pNext;
}buyNode;

#define LOT_INFO_LEN sizeof(struct lotInfo)

#define LOT_NODE_LEN sizeof(struct lotNode)

#define USER_INFO_LEN sizeof(struct userInfo)

#define USER_NODE_LEN sizeof(struct userNode)

#define BUY_INFO_LEN sizeof(struct buyInfo)

#define BUY_NODE_LEN sizeof(struct buyNode)

userNode *makeUserNode();
buyNode *makeBuyNode();
int checkZH(userNode *phUser,int account);
void initUserInfo(userNode *phUser,userInfo *temp);
int initBuyInfo(lotNode *phLot,buyNode *pBuy,userNode *pUser);
int addUser(userNode * pHead);
int buyLottery(buyNode *phBuy,lotNode *phLot,userNode *pUser);
userNode *loginCheck(userNode *phUser);
userNode *reloadNode(userNode *pUser);
void showUserInfo(userNode *temp);
void showBuyInfo(buyNode *temp);
void showLotInfo(lotInfo temp);
void printLotInfo(lotNode *phLot);
void buyHistory(userNode *pUser,buyNode *phBuy);
int Rechage(userInfo *balance);
int delUser(userNode *phUser,userNode *pUser);


int userInfoWriteToFile(userNode *phUser);
userNode *userInfoReadFromFile();
int buyInfoWriteToFile(buyNode *phBuy);
buyNode *buyInfoReadFromFile();
lotNode *makeLotNode();
lotNode *lotInfoReadFromFile();
int lotInfoWriteToFile(lotNode *pHead);
#endif

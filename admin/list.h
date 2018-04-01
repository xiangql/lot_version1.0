#ifndef _LIST_H_
#define _LIST_H_


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

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
    char type[SIZE]; //类型
    float price;    //单价
    int num;        //数量
    bool state[2];     //状态，利用数组，存储中奖状态和中奖金额
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


lotNode *makeLotNode();
int checkID(lotNode *pHead,int ID);
void initLotInfo(lotNode *pHead,lotInfo *temp);
int addLottery(lotNode *pHead);
int deleteLot(lotNode *pHead);
void showLotInfo(lotInfo temp);
int searchID(lotNode *pHead);
void swapNode(lotInfo *temp,lotInfo *loop);
int sortID(lotNode *phLot);
int numRange(lotNode *phLot);
int getWinID(lotNode *phLot,int money);
void update(int ID,int money,userNode *phUser,buyNode *phBuy);
void showWinLotInfo(lotNode *phLot);

int lotInfoWriteToFile(lotNode *pHead);
lotNode *lotInfoReadFromFile();
int userInfoWriteToFile(userNode *phUser);
userNode *userInfoReadFromFile();
int buyInfoWriteToFile(buyNode *phBuy);
buyNode *buyInfoReadFromFile();
userNode *makeUserNode();
buyNode *makeBuyNode();

#endif

#include "test.h"

void showUser(userNode *phUser)
{
    userNode *temp = phUser->pNext;
    while(NULL != temp){
        printf("账 户：%d\n",temp->data.account);
        printf("用户名：%s\n",temp->data.name);
        printf("余 额：%.2f\n",temp->data.balance);
        temp = temp->pNext;
    }
    return;
}

void showBuy(buyNode *phBuy)
{
    buyNode *temp = phBuy->pNext;
    while(NULL != temp){
        printf("ID:%d ",temp->data.ID);
        printf("type:%s ",temp->data.type);
        printf("num:%d",temp->data.num);
        printState(temp->data.state[0],temp->data.state[1]);
        printf("\n");
        temp = temp->pNext;
    }
    return;
}

void showLot(lotNode *phLot)
{
    lotNode *temp = phLot->pNext;
    while(NULL != temp){
        printf("ID:%d type:%s price:%.2f num:%d state:",
                temp->data.ID,
                temp->data.type,
                temp->data.price,
                temp->data.num);
        printState(temp->data.state[0],temp->data.state[1]);
        putTime(temp->data.star);
        putTime(temp->data.last);
        printf("\n");
        temp = temp->pNext;
    }
    return;
}




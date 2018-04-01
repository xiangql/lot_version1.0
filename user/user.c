#include "./user.h"
#include "./test.h" //程序调试函数库

userNode* userLogin(userNode *phUser)//只有登录成功返回用户节点，其他都返回空
{
    system("clear");
    loginUI();
    char ch = myGetc();
    if('1' == ch){  //判断写入文件是否成功，保证程序的不正常退出不会造成数据丢失
        if(addUser(phUser) && userInfoWriteToFile(phUser))
            printf("注册成功,请登录系统\n");
        else
            printf("注册失败，请重新注册\n");
    }
    else if('2' == ch){
        userNode *pUser = loginCheck(phUser);
        if(NULL != pUser){
            printf("登录成功\n");
            anyKey();
            return pUser;
        }
        else
            printf("登录失败，请重新登录\n");
    }
    else
        printf("input error!\n");
    anyKey();
    return NULL;
}

int userFunc(userNode *phUser,userNode *pUser)
{
    system("clear");
    userUI();
    char ch = myGetc();
    buyNode *phBuy = buyInfoReadFromFile();//读取购买文件
    lotNode *phLot = lotInfoReadFromFile();
    reloadNode(pUser);
    switch(ch){
        case '1':
        {
            showUserInfo(pUser);
            break;
        }
        case '2':
        {
            buyHistory(pUser,phBuy);
            break;
        }
        case '3':
        {
            printLotInfo(phLot);
            break;
        }
        case '4':
        {   //更新彩票链表中的被采购数量--购买链表的数据增加--用户链表的余额
            if(buyLottery(phBuy,phLot,pUser) && buyInfoWriteToFile(phBuy) &&lotInfoWriteToFile(phLot))
                printf("此次购买成功");
            else
                printf("此次购买失败，请重新购买!");
            userInfoWriteToFile(phUser);
            break;
        }
        case '5':
        {
            if(Rechage(&pUser->data) &&  userInfoWriteToFile(phUser))
                printf("\n充值成功 ");
            break;
        }
        case '6':
        {
            if(delUser(phUser,pUser) && userInfoWriteToFile(phUser))
                printf("注销成功!");
            else
                printf("注销用户失败!");
            anyKey();
            return 0;
        }
        case '0':
        {
            return 0;
        }
    }
    anyKey();
    return 1;
}


int main(void)
{
    initUI();
    anyKey();
    int sign = 0;
    while(1){
        userNode *phUser = userInfoReadFromFile();
        userNode *pUser = userLogin(phUser);
        if(NULL != pUser){
        //登录成功
            while(userFunc(phUser,pUser))
               ;
        }
    }

    return 0;
}


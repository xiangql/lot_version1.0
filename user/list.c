#include "./list.h"
#include "./public.h"

//****************添加用户并初始化---保证账户的唯一性***************
int checkZH(userNode *phUser,int account)
{
    userNode *temp = phUser->pNext;
    while(NULL != temp){
        if(account == temp->data.account)
            return 0;  //账户重名 返回 0
        temp = temp->pNext;
    }
    if(NULL == temp)
        return 1;    //此账户唯一 返回 1
    return 1;
}
void initUserInfo(userNode *phUser,userInfo *temp)
{
    printf("\n============用户信息添加===============\n");
    temp->account = setAccount();//需要检查账户的唯一性
    if(!checkZH(phUser,temp->account)){
        printf("次账户已存在，请重新录入\n");
        sleep(1);
        initUserInfo(phUser,temp);
        return;
    }
    setName(temp->name);
    temp->pwd = setPwd();
    printf("初始余额为零，请注意充值\n");
    temp->balance = 0;  //初始化账户余额为0
    return;
}
int addUser(userNode * pHead)
{
    if(NULL == pHead){
        printf("\n\t%s:the link is empty!\n",__func__);
        return 0;
    }

    userNode *newNode = makeUserNode();
    initUserInfo(pHead,&newNode->data);

    newNode->pNext = pHead->pNext;
    pHead->pNext = newNode;
    newNode = NULL;
    return 1;
}

//*******根据ID购买彩票,并初始化购买信息　－刷新用户－彩票－购买信息,注意已开奖彩票是无法购买的
int initBuyInfo(lotNode *phLot,buyNode *pBuy,userNode *pUser)
{
     int ID = 0;
     int num = 0;
     int total = 0;
     if(NULL == phLot || NULL == phLot->pNext){
        printf("\n\t%s:the link is empty!\n",__func__);
        return -1;
    }
    lotNode *temp = phLot->pNext;
    ID = setID();
    num = setNum();
    while(NULL != temp){
        if(ID == temp->data.ID && temp->data.state[0] == true){
            total = num * temp->data.price;//对账户余额判断及更新
            if(total > pUser->data.balance){
                printf("\n余额不足，请先充值\n");
                return 0;
            }
            pBuy->data.ID = ID;
            pBuy->data.num = num;//
            temp->data.num += num;//彩票购买数量增加
            pBuy->data.account = pUser->data.account;
            strcpy(pBuy->data.type,temp->data.type);
            pBuy->data.state[0] = temp->data.state[0];
            pUser->data.balance -= total;//扣除费用
            break;
        }
        temp = temp->pNext;
    }
    if(NULL == temp){
        printf("此ID彩票不存在\n");
        return 0;
    }
    return 1;
}
int buyLottery(buyNode *phBuy,lotNode *phLot,userNode *pUser)
{
    if(NULL == phLot || NULL == phLot->pNext){
        printf("\n\t%s:the link is empty!\n",__func__);
        return -1;
    }
    if(NULL == phBuy){
        printf("\n\t%s:the link is empty!\n",__func__);
        return -2;
    }

    buyNode *newNode = makeBuyNode();
    if(!initBuyInfo(phLot,newNode,pUser))
        return 0;
    newNode->pNext = phBuy->pNext;
    phBuy->pNext = newNode;
    newNode = NULL;
    return 1;
}

//******************检查用户登录**********************************
userNode *loginCheck(userNode *phUser)
{

//******************刷新当前用户信息,以防用户数据已更改*************
     if(NULL == phUser || NULL == phUser->pNext){
        printf("\n\t%s:the link is empty!\n",__func__);
        return NULL;
    }

    int account = 0;
    int pwd = 0;
    account = setAccount();
    pwd = setPwd();

    userNode *temp = phUser->pNext;
    while(NULL != temp){
        if(account == temp->data.account && pwd == temp->data.pwd){
            return temp;   //登录成功返回当前用户节点
        }
        temp = temp->pNext;
    }
    if(NULL == temp){
        return temp;//登录失败返回NULL
    }
    return temp;
}
userNode *reloadNode(userNode *pUser)
{
    userNode *phUser = userInfoReadFromFile();
    userNode *temp = phUser->pNext;
    while(NULL != temp){
        if(pUser->data.account == temp->data.account)
            pUser->data.balance = temp->data.balance;
            temp = temp->pNext;
    }
    return pUser;
}

//****************打印当前用户的信息，注意账户余额可能以改变，需刷新
void showUserInfo(userNode *temp)
{
    printf("账 户：%d\n",temp->data.account);
    printf("用户名：%s\n",temp->data.name);
    printf("余 额：%.2f\n",temp->data.balance);
    return;
}

//***************打印彩民的购买信息*************************
void showBuyInfo(buyNode *temp)
{
    printf("%d\t",temp->data.ID);
    printf("%s\t",temp->data.type);
    printf("%d\t",temp->data.num);
    printState(temp->data.state[0],temp->data.state[1]);
    printf("\n");
    return;
}
void buyHistory(userNode *pUser,buyNode *phBuy)
{
    if(NULL == phBuy || NULL == phBuy->pNext){
        printf("无购买信息，请选购彩票\n");
        return;
    }
    buyNode *temp = phBuy->pNext;
    printf("编号\t类型\t数量\t状态\n");
    while(NULL != temp){
        if(temp->data.account == pUser->data.account){
            showBuyInfo(temp);
        }
        temp = temp->pNext;
    }
    return;
}

//******************显示彩票的信息***********************
void showLotInfo(lotInfo temp)
{
    printf("%d\t%s\t%.2f\t %d\t",
            temp.ID,
            temp.type,
            temp.price,
            temp.num);
    printState(temp.state[0],temp.state[1]);
    putTime(temp.star);
    putTime(temp.last);
    printf("\n");
    return;
}
void printLotInfo(lotNode *phLot)
{
    if(NULL == phLot || NULL == phLot->pNext){
        printf("the link is empty!\n");
        return;
    }
    lotNode *temp = phLot->pNext;
    printf("编号\t类型\t单价\t数量\t状态\t发布时间\t开奖时间\n");
    while(NULL != temp){
        showLotInfo(temp->data);
        temp = temp->pNext;
    }
    return;
}

//****************对账户进行充值***************************
int Rechage(userInfo *temp)
{
    printf("请输入充值金额:\n");
    temp->balance += (float)putInt();
    return 1;
}

//*****************注销当前账户***************************
int delUser(userNode *phUser,userNode *pUser)
{
    userNode *pPre = phUser;
    userNode *pCur = phUser->pNext;
    while(NULL != pCur){
        if(pCur->data.account == pUser->data.account){
            pPre->pNext = pCur->pNext;
            return 1;
        }
        pPre = pPre->pNext;
        pCur = pCur->pNext;
    }
    return 0;
}

//*********************文件读写**********************************
userNode *makeUserNode()
{
    userNode *newNode = (userNode *)malloc(USER_NODE_LEN);
    if(NULL == newNode){
        userNode *newNode = (userNode *)malloc(USER_NODE_LEN);
    }
    newNode->pNext = NULL;

    return newNode;
}

buyNode *makeBuyNode()
{
    buyNode *newNode = (buyNode *)malloc(BUY_NODE_LEN);
    if(NULL == newNode){
            buyNode *newNode = (buyNode *)malloc(BUY_NODE_LEN);
    }
    newNode->pNext = NULL;
    return newNode;
}
lotNode *makeLotNode()
{
    lotNode *newNode = (lotNode *)malloc(LOT_NODE_LEN);
    if(NULL == newNode){
        lotNode *newNode = (lotNode *)malloc(LOT_NODE_LEN);
    }
    newNode->pNext = NULL;
    return newNode;
}

int userInfoWriteToFile(userNode *phUser)
{

    if(NULL == phUser){
        printf("there is not info to save!\n");
        return -1;
    }
    FILE *fpw = fopen("../userInfo.dat","w");
    if(NULL == fpw){
        perror("open error");
        //return -2;
    }
    userNode *temp = phUser->pNext;
    int ret = 0;
    while(NULL != temp){
        ret = fwrite(&temp->data,USER_INFO_LEN,1,fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }

    fclose(fpw);
    return 1;
}
userNode *userInfoReadFromFile()
{
    FILE *fpr = fopen("../userInfo.dat","r");
    if(NULL == fpr){
        perror("open error");
       // return -2;
    }

    userNode *phUser = makeUserNode();
    userNode *newNode = makeUserNode();

    while(fread(&newNode->data,USER_INFO_LEN,1,fpr) > 0){
        newNode->pNext = phUser->pNext;
        phUser->pNext = newNode;
        newNode = makeUserNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return phUser;
}

int buyInfoWriteToFile(buyNode *phBuy)
{
    if(NULL == phBuy){
        printf("there is not info to save!\n");
        return -1;
    }
    FILE *fpw =fopen("../buyInfo.dat","w");
    if(NULL == fpw){
        perror("open error");
        return -2;
    }
    buyNode *temp = phBuy->pNext;
    int ret = 0;
    while(NULL != temp){
        ret = fwrite(&temp->data,BUY_INFO_LEN,1,fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }
    fclose(fpw);
    return 1;
}

buyNode *buyInfoReadFromFile()
{
    FILE *fpr = fopen("../buyInfo.dat","r");
    if(NULL == fpr){
        perror("open error");
        exit(1);
    }
    buyNode *phBuy = makeBuyNode();
    buyNode *newNode = makeBuyNode();

    while(fread(&newNode->data,BUY_INFO_LEN,1,fpr) > 0){
        newNode->pNext = phBuy->pNext;
        phBuy->pNext = newNode;
        newNode = makeBuyNode();

    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return phBuy;
}

lotNode *lotInfoReadFromFile()
{
    FILE *fpr = fopen("../lotInfo.dat", "r");
    if(NULL == fpr)
    {
        perror("fopen error");
        exit(1);
    }
    lotNode *phLot = makeLotNode();
    lotNode *newNode = makeLotNode();

    while(fread(&newNode->data, LOT_INFO_LEN, 1, fpr) > 0)
    {
        newNode->pNext = phLot->pNext;
        phLot->pNext = newNode;
        newNode = makeLotNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return phLot;
}

int lotInfoWriteToFile(lotNode *pHead)
{
    if(NULL == pHead)
    {
        printf("\n\tthere is not info to save!\n");
        return -1;
    }
    FILE *fpw = fopen("../lotInfo.dat", "w");
    if(NULL == fpw)
    {
        perror("fopen error");
        return 0;
    }

    lotNode *temp = pHead->pNext;
    int ret = 0;
    while(NULL != temp)
    {
        ret = fwrite(&temp->data, LOT_INFO_LEN, 1, fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }

    fclose(fpw);
    return 1;
}





















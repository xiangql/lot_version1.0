#include "./list.h"
#include "./public.h"
#include "./test.h"
//***************添加彩票节点，并初始化----保证ＩＤ唯一性***********
int checkID(lotNode *pHead,int ID)
{
    lotNode *temp = pHead->pNext;
    while(NULL != temp){
        if(ID == temp->data.ID)
            return 0;  //ID重复 返回 0
        temp = temp->pNext;
    }
    if(NULL == temp)
        return 1;    //此ID唯一 返回 1
    return 1;
}

void initLotInfo(lotNode *pHead,lotInfo *temp)
{
    printf("\n=============彩票信息添加===============\n");
    temp->ID = setID();
    if(!checkID(pHead,temp->ID)){
        printf("此ID已占用，请重新录入\n");
        initLotInfo(pHead,temp);
        return;
    }
    printf("类型：");
    myGets(temp->type,sizeof(temp->type));
    printf("单价：");
    scanf("%f",&temp->price);
    getchar();
    //购买数量初始化为零
    temp->num = 0;
    temp->state[0] = true;    //初始化状态为未开奖
    temp->state[1] = 0;         //中奖金额初始化为零
    printf("发布时间：\n");
    setTime(&temp->star);
    printf("开奖时间：\n");
    setTime(&temp->last);
    return;
}

int addLottery(lotNode *pHead)
{
    if(NULL == pHead){
        printf("\n\t%s:the link is empty!\n",__func__);
        return 0;
    }

    lotNode *newNode = makeLotNode();
    initLotInfo(pHead,&newNode->data);

    newNode->pNext = pHead->pNext;
    pHead->pNext = newNode;
    newNode = NULL;
    return 1;
}

//**************删除彩票节点**************************************
int deleteLot(lotNode *pHead)
{
    if(NULL == pHead || NULL == pHead->pNext){
        printf("无彩票信息，请先添加\n");
        return -1;
    }
    int ID = setID();
    lotNode *pPre = pHead;
    lotNode *pCur = pHead->pNext;

    while(NULL != pCur)
    {
        if(ID == pCur->data.ID)
        {
            pPre->pNext = pCur->pNext;
            free(pCur);
            pCur = NULL;

            return 1;
        }
        pCur = pCur->pNext;
        pPre = pPre->pNext;
    }
    if(NULL == pCur){
        return 0; //未找到匹配项
    }
    return 1;
}

//*************根据彩票ID查找彩票信息并打印**************************
void showLotInfo(lotInfo temp)
{
    printf("编号\t类型\t单价\t数量\t状态\t发布时间\t开奖时间\n");
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

int searchID(lotNode *pHead)
{
    if(NULL == pHead || NULL == pHead->pNext){
        printf("无彩票信息，请先添加\n");
        return 0;
    }
    int ID = setID();
    lotNode *pCur = pHead->pNext;
    while(NULL != pCur){
        if(ID == pCur->data.ID){
            showLotInfo(pCur->data);
            return 1;
        }
        pCur = pCur->pNext;
    }
    if(NULL == pCur){
        return 0;   //没有相关信息
    }
    return 1;
}

//*************对彩票链表进行排序，并重新写入文件*********************
void swapNode(lotInfo *temp,lotInfo *loop)
{
    lotInfo p = *temp;
    *temp = *loop;
    *loop = p;
}

int sortID(lotNode *pHead)
{
    if(NULL == pHead || NULL == pHead->pNext){
        printf("%s the link is empty!\n",__func__);
        return -1;
    }
    lotNode *temp = pHead->pNext;
    if(NULL == temp->pNext)
        return 1;
    while(NULL != temp->pNext){
        lotNode * loop = temp->pNext;
        while(NULL != loop){
            if(temp->data.ID > loop->data.ID){  //从小到大排序
                //第一个节点存储最小值，如果不是比后面节点的值小，则交换结构体成员的值
                swapNode(&temp->data,&loop->data);
            }
            loop = loop->pNext;
        }
        temp = temp->pNext;
    }
    lotInfoWriteToFile(pHead);
    return 1;
}

//*********随机抽取未开奖彩票，设置中奖金额并显示彩票信息，刷新彩票－购买－用户信息****
int numRange(lotNode *phLot)
{
    int num = 0;
    lotNode *temp = phLot->pNext;
    while(NULL != temp){
        if(temp->data.state[0])
            num+=1;
        temp = temp->pNext;
    }
    if(num == 0){
        printf("无未开奖彩票\n");
    }
    return num;
}

int getWinID(lotNode *phLot,int money)
{
    if(NULL == phLot || NULL == phLot->pNext){
        printf("%s the link empty!\n",__func__);
        return 0;
    }
    srand(time(0));
    int size = (int)(rand()%numRange(phLot))+1;
    lotNode *p = phLot->pNext;
    while(NULL != p){
        if(p->data.state[0] == true)
            size-=1;
        if(size == 0)
            break;
        p = p->pNext;
    }
    p->data.state[0] = false;
    p->data.state[1] = money;
    showLotInfo(p->data);
    int ID = p->data.ID;
    p = NULL;
    return ID;
}

void update(int ID,int money,userNode *phUser,buyNode *phBuy)
{
    buyNode *pBuy = phBuy->pNext;
    while(NULL != pBuy){
        if(ID == pBuy->data.ID){
            pBuy->data.state[0] = false;
            pBuy->data.state[1]= money*pBuy->data.num;
            userNode *pUser = phUser->pNext;
            while(NULL != pUser){
                if(pBuy->data.account == pUser->data.account){
                    pUser->data.balance += pBuy->data.state[1];
                    break;
                }
                pUser = pUser->pNext;
            }
        }
        pBuy = pBuy->pNext;
    }
    return;
}


void showWinLotInfo(lotNode *phLot)
{
    int money = setMoney();
    int ID = getWinID(phLot,money);
    userNode *phUser = userInfoReadFromFile();
    buyNode *phBuy = buyInfoReadFromFile();
    update(ID,money,phUser,phBuy);
    buyInfoWriteToFile(phBuy);
    userInfoWriteToFile(phUser);
    return;
}

//*******************文件的读写*****************************

lotNode *makeLotNode()
{
    lotNode *newNode = (lotNode *)malloc(LOT_NODE_LEN);
    if(NULL == newNode){
        lotNode *newNode = (lotNode *)malloc(LOT_NODE_LEN);
    }
    newNode->pNext = NULL;
    return newNode;
}

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


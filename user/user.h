#ifndef _USER_H_
#define _USER_H_


#include<stdlib.h>
#include "./list.h"
#include "./public.h"
#include "./interfaceUI.h"

userNode *userLogin(userNode *phUser);
int userFunc(userNode *phUser,userNode *pUser);

#endif

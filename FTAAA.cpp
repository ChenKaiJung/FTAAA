#include <stdio.h>
#include <time.h>
#include "FTAAA.h"
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include "compat_windows.h"
#include <semaphore.h>
#endif


#include <vector>
#include <list>


using namespace std;

#define MAX_CONNECTION 10

string g_OAuthUrl="http://YOUR_DOMAIN:YOUR_PORT/YOUR_AUTH_SERVICE";
string g_BSWSUrl="http://YOUR_DOMAIN:YOUR_PORT/YOUR_BILLING_SERVICE";

string g_Client_Id ="";
string g_Client_Secret="";

int g_MaxConn = MAX_CONNECTION;

CRITICAL_SECTION g_CriticalSection;
//struct soap *g_Soap=NULL;
#ifdef _WIN32
	#define DEFAULT_FTAAA_INI_NAME "\\FTAAA.ini"
#else
	#define DEFAULT_FTAAA_INI_NAME "/FTAAA.ini"
#endif




#ifdef _WIN32
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{

    return TRUE;
}
#endif

bool FTAAAInit()
{

	InitializeCriticalSection(&g_CriticalSection);
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);
	
	ret=GetPrivateProfileString("INIT", "MAX_CONNECTION","10", Buffer, sizeof(Buffer), dir);
	if(ret==0) g_MaxConn=MAX_CONNECTION;
	else g_MaxConn=atoi(Buffer);

	ret=GetPrivateProfileString("INIT", "OAUTH_URL","http://YOUR_DOMAIN:YOUR_PORT/YOUR_AUTH_SERVICE", Buffer, sizeof(Buffer), dir);
	if(ret==0) g_OAuthUrl="http://YOUR_DOMAIN:YOUR_PORT/YOUR_AUTH_SERVICE";
	else g_OAuthUrl=Buffer;

	ret=GetPrivateProfileString("INIT", "BSWS_URL","http://YOUR_DOMAIN:YOUR_PORT/YOUR_BILLING_SERVICE", Buffer, sizeof(Buffer), dir);
	if(ret==0) g_BSWSUrl="http://YOUR_DOMAIN:YOUR_PORT/YOUR_BILLING_SERVICE";
	else g_BSWSUrl=Buffer;

	//Client Id for Facebook's AppID
	ret=GetPrivateProfileString("FUNTOWN", "CLIENT_ID","10171939", Buffer, sizeof(Buffer), dir);
	if(ret==0) 
		g_Client_Id="10791939";
	else 
		g_Client_Id=Buffer;

	//Client Id for Facebook's AppID
	ret=GetPrivateProfileString("FUNTOWN", "CLIENT_SECRET","10171939", Buffer, sizeof(Buffer), dir);
	if(ret==0) 
		g_Client_Secret="10791939";
	else 
		g_Client_Secret=Buffer;


	return true;
}

bool RequestOAuthToken(const RequestOAuthTokenReq *req,RequestOAuthTokenResult *result)
{
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);
	
	ret=GetPrivateProfileString("RequestOAuthTokenResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("RequestOAuthTokenResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);
	ret=GetPrivateProfileString("RequestOAuthTokenResult", "OAUTH_ACCESS_TOKEN","qrcikpf4tvilqauulb6csvso7a5pryakkvjvffzuu7gyluecid7ht2livaq2ipuvoxsy56thqollycwnhiusbkwdmzxpjoxcebaskd3jmyiscob3crl4nd5ao3wbcr3ddlvalabvtkgqjmpkhogsrt7p3u", result->OAUTH_ACCESS_TOKEN, OAUTH_TOKEN_LENGTH, dir);
	ret=GetPrivateProfileString("RequestOAuthTokenResult", "OAUTH_REFRESH_TOKEN","qrcikpf4tvilqauulb6csvso7a5pryakkvjvffzuu7gyluecid7ht2livaq2ipuvoxsy56thqollycwnhiusbkwdmzxpjoxcebaskd3jmyiscob3crl4nd5ao3wbcr3ddlvalabvtkgqjmpkhogsrt7p3u", result->OAUTH_REFRESH_TOKEN, OAUTH_TOKEN_LENGTH, dir);
	
	ret=GetPrivateProfileString("RequestOAuthTokenResult", "XOAUTH_ACCESS_TOKEN_EXPIRE_TIME_STAMP","3600", Buffer, sizeof(Buffer), dir);	
	if(ret==0) result->XOAUTH_ACCESS_TOKEN_EXPIRE_TIME_STAMP = 1299688503;
	result->XOAUTH_ACCESS_TOKEN_EXPIRE_TIME_STAMP = atoi(Buffer);
	
	ret=GetPrivateProfileString("RequestOAuthTokenResult", "XOAUTH_REFRESH_TOKEN_EXPIRE_TIME_STAMP","655360", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->XOAUTH_REFRESH_TOKEN_EXPIRE_TIME_STAMP = 1609394400;	
	result->XOAUTH_REFRESH_TOKEN_EXPIRE_TIME_STAMP = atoi(Buffer);
	LeaveCriticalSection(&g_CriticalSection);
	if(result->ERROR_CODE==100)	return true;
	else return false;
}

bool RefreshOAuthToken(const RefreshOAuthTokenReq *req,RefreshOAuthTokenResult *result)
{
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("RefreshOAuthTokenResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("RefreshOAuthTokenResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);
	ret=GetPrivateProfileString("RefreshOAuthTokenResult", "OAUTH_ACCESS_TOKEN","qrcikpf4tvilqauulb6csvso7a5pryakkvjvffzuu7gyluecid7ht2livaq2ipuvoxsy56thqollycwnhiusbkwdmzxpjoxcebaskd3jmyiscob3crl4nd5ao3wbcr3ddlvalabvtkgqjmpkhogsrt7p3u", result->OAUTH_ACCESS_TOKEN, OAUTH_TOKEN_LENGTH, dir);
	ret=GetPrivateProfileString("RefreshOAuthTokenResult", "OAUTH_REFRESH_TOKEN","qrcikpf4tvilqauulb6csvso7a5pryakkvjvffzuu7gyluecid7ht2livaq2ipuvoxsy56thqollycwnhiusbkwdmzxpjoxcebaskd3jmyiscob3crl4nd5ao3wbcr3ddlvalabvtkgqjmpkhogsrt7p3u", result->OAUTH_REFRESH_TOKEN, OAUTH_TOKEN_LENGTH, dir);

	ret=GetPrivateProfileString("RefreshOAuthTokenResult", "XOAUTH_ACCESS_TOKEN_EXPIRE_TIME_STAMP","3600", Buffer, sizeof(Buffer), dir);	
	if(ret==0) result->XOAUTH_ACCESS_TOKEN_EXPIRE_TIME_STAMP = 1299688503;
	result->XOAUTH_ACCESS_TOKEN_EXPIRE_TIME_STAMP = atoi(Buffer);

	ret=GetPrivateProfileString("RefreshOAuthTokenResult", "XOAUTH_REFRESH_TOKEN_EXPIRE_TIME_STAMP","655360", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->XOAUTH_REFRESH_TOKEN_EXPIRE_TIME_STAMP = 1609394400;	
	result->XOAUTH_REFRESH_TOKEN_EXPIRE_TIME_STAMP = atoi(Buffer);

	LeaveCriticalSection(&g_CriticalSection);	
	if(result->ERROR_CODE==100)	return true;
	else return false;

}


bool GetUserProfile(const GetUserProfileReq *req,GetUserProfileResult *result)
{
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);

	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("GetUserProfileResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("GetUserProfileResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("GetUserProfileResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);
	ret=GetPrivateProfileString("GetUserProfileResult", "USER_PROFILE",NULL, result->USER_PROFILE, USER_PROFILE_LENGTH, dir);	

	LeaveCriticalSection(&g_CriticalSection);

	if(result->ERROR_CODE==100)	return true;
	else return false;

}

bool QueryGamePoints(const QueryGamePointsReq *req,QueryGamePointsResult *result)
{
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("QueryGamePointsResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("QueryGamePointsResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("QueryGamePointsResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("QueryGamePointsResult", "TOTAL_GAME_BALANCE",0, Buffer, sizeof(Buffer), dir);	
	result->TOTAL_GAME_BALANCE = atoi(Buffer);
	LeaveCriticalSection(&g_CriticalSection);

	if(result->ERROR_CODE==100)	return true;
	else return false;

}


bool DeductGamePoints(const DeductGamePointsReq *req,DeductGamePointsResult *result)
{
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("DeductGamePointsResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("DeductGamePointsResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("DeductGamePointsResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("DeductGamePointsResult", "DEDUCT_FREE_POINTS",0, Buffer, sizeof(Buffer), dir);	
	result->DEDUCT_FREE_POINTS = atoi(Buffer);

	ret=GetPrivateProfileString("DeductGamePointsResult", "DEDUCT_POINTS",0, Buffer, sizeof(Buffer), dir);	
	result->DEDUCT_POINTS = atoi(Buffer);	

	ret=GetPrivateProfileString("DeductGamePointsResult", "TOTAL_GAME_BALANCE",0, Buffer, sizeof(Buffer), dir);	
	result->TOTAL_GAME_BALANCE = atoi(Buffer);

	ret=GetPrivateProfileString("DeductGamePointsResult", "TRANSACTION_SQ",0, Buffer, sizeof(Buffer), dir);	
	result->TRANSACTION_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("DeductGamePointsResult", "MAC",NULL, result->MAC, MAC_LENGTH, dir);

	LeaveCriticalSection(&g_CriticalSection);
	if(result->ERROR_CODE==100)	return true;
	else return false;

}

bool CancelGamePointsDeduction(const CancelGamePointsDeductionReq *req,CancelGamePointsDeductionResult *result)
{
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "CANCEL_FREE_POINTS",0, Buffer, sizeof(Buffer), dir);	
	result->CANCEL_FREE_POINTS = atoi(Buffer);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "CANCEL_POINTS",0, Buffer, sizeof(Buffer), dir);	
	result->CANCEL_POINTS = atoi(Buffer);	

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "TOTAL_GAME_BALANCE",0, Buffer, sizeof(Buffer), dir);	
	result->TOTAL_GAME_BALANCE = atoi(Buffer);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "TRANSACTION_SQ",0, Buffer, sizeof(Buffer), dir);	
	result->TRANSACTION_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "MAC",NULL, result->MAC, MAC_LENGTH, dir);

	LeaveCriticalSection(&g_CriticalSection);

	if(result->ERROR_CODE==100)	return true;
	else return false;

}

bool QueryBonusPoints(const QueryBonusPointsReq *req,QueryBonusPointsResult *result)
{
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;
	
	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("QueryBonusPointsResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("QueryBonusPointsResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("QueryBonusPointsResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("QueryBonusPointsResult", "TOTAL_BONUS_BALANCE",0, Buffer, sizeof(Buffer), dir);	
	result->TOTAL_BONUS_BALANCE = atoi(Buffer);
	
	LeaveCriticalSection(&g_CriticalSection);

	if(result->ERROR_CODE==100)	return true;
	else return false;


}

bool DeductBonusPoints(const DeductBonusPointsReq *req,DeductBonusPointsResult *result)
{
	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);

	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("DeductBonusPointsResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("DeductBonusPointsResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("DeductBonusPointsResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("DeductBonusPointsResult", "DEDUCT_POINTS",0, Buffer, sizeof(Buffer), dir);	
	result->DEDUCT_POINTS = atoi(Buffer);	

	ret=GetPrivateProfileString("DeductBonusPointsResult", "TOTAL_BONUS_BALANCE",0, Buffer, sizeof(Buffer), dir);	
	result->TOTAL_BONUS_BALANCE = atoi(Buffer);

	ret=GetPrivateProfileString("DeductBonusPointsResult", "TRANSACTION_SQ",0, Buffer, sizeof(Buffer), dir);	
	result->TRANSACTION_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("DeductBonusPointsResult", "MAC",NULL, result->MAC, MAC_LENGTH, dir);

	LeaveCriticalSection(&g_CriticalSection);
	if(result->ERROR_CODE==100)	return true;
	else return false;



}

bool CancelBonusPointsDeduction(const CancelBonusPointsDeductionReq *req,CancelBonusPointsDeductionResult *result)
{

	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;
	
	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("CancelBonusPointsDeductionResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("CancelBonusPointsDeductionResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("CancelBonusPointsDeductionResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("CancelBonusPointsDeductionResult", "CANCEL_POINTS",0, Buffer, sizeof(Buffer), dir);	
	result->CANCEL_POINTS = atoi(Buffer);	

	ret=GetPrivateProfileString("CancelBonusPointsDeductionResult", "TOTAL_BONUS_BALANCE",0, Buffer, sizeof(Buffer), dir);	
	result->TOTAL_BONUS_BALANCE = atoi(Buffer);

	ret=GetPrivateProfileString("CancelBonusPointsDeductionResult", "TRANSACTION_SQ",0, Buffer, sizeof(Buffer), dir);	
	result->TRANSACTION_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("CancelBonusPointsDeductionResult", "MAC",NULL, result->MAC, MAC_LENGTH, dir);

	LeaveCriticalSection(&g_CriticalSection);

	if(result->ERROR_CODE==100)	return true;
	else return false;


}

bool DepositBonusPoints(const DepositBonusPointsReq *req,DepositBonusPointsResult *result)
{

	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("DepositBonusPointsResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("DepositBonusPointsResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("DepositBonusPointsResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("DepositBonusPointsResult", "DEPOSIT_POINTS",0, Buffer, sizeof(Buffer), dir);	
	result->DEPOSIT_POINTS = atoi(Buffer);	

	ret=GetPrivateProfileString("DepositBonusPointsResult", "TOTAL_BONUS_BALANCE",0, Buffer, sizeof(Buffer), dir);	
	result->TOTAL_BONUS_BALANCE = atoi(Buffer);

	ret=GetPrivateProfileString("DepositBonusPointsResult", "TRANSACTION_SQ",0, Buffer, sizeof(Buffer), dir);	
	result->TRANSACTION_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("DepositBonusPointsResult", "MAC",NULL, result->MAC, MAC_LENGTH, dir);

	LeaveCriticalSection(&g_CriticalSection);

	if(result->ERROR_CODE==100)	return true;
	else return false;


}

bool CancelBonusPointsDeposit(const CancelBonusPointsDepositReq *req,CancelBonusPointsDepositResult *result)
{

	char Buffer[2048]={0};
	char dir[MAX_PATH]={0};
	DWORD ret=0;
	if(result==NULL) return false;

	EnterCriticalSection(&g_CriticalSection);
	::GetCurrentDirectory(MAX_PATH,Buffer);
	sprintf(dir,"%s%s",Buffer,DEFAULT_FTAAA_INI_NAME);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "ERROR_CODE","100", Buffer, sizeof(Buffer), dir);
	if(ret==0) result->ERROR_CODE=104;
	result->ERROR_CODE = atoi(Buffer);
	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "OAUTH_ERROR",NULL, result->OAUTH_ERROR, OAUTH_ERROR_LENGTH, dir);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "SERVICE_ACCOUNT_SQ","0", Buffer, sizeof(Buffer), dir);
	result->SERVICE_ACCOUNT_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "CANCEL_POINTS",0, Buffer, sizeof(Buffer), dir);	
	result->CANCEL_POINTS = atoi(Buffer);	

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "TOTAL_BONUS_BALANCE",0, Buffer, sizeof(Buffer), dir);	
	result->TOTAL_BONUS_BALANCE = atoi(Buffer);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "TRANSACTION_SQ",0, Buffer, sizeof(Buffer), dir);	
	result->TRANSACTION_SQ = atoi(Buffer);

	ret=GetPrivateProfileString("CancelGamePointsDeductionResult", "MAC",NULL, result->MAC, MAC_LENGTH, dir);

	LeaveCriticalSection(&g_CriticalSection);

	if(result->ERROR_CODE==100)	return true;
	else return false;

}

void FTAAARelease()
{

	DeleteCriticalSection(&g_CriticalSection);
}


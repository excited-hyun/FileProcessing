#include "recfile.h"
#include "member.h"
#include "game.h"
#include "purchase.h"

#include "indfile.h"
#include "buffile.h"
#include "tindbuff.h"
#include "textind.h"

#define MAX_BUF 256
#define MAX_MEM 256
#define MAX_GAME 9
#define MAX_PUR 13

using namespace std;

void PrintMenu();
void GamePurchaseSystem();
void MakeIndexFile();
int accessValidate(char recID[]);
void MemberTest(int print_flag);
void GameTest(int print_flag);
void PurchaseTest(int print_flag);
void GamePurchaseSystem_MemberMode(char accessID[]);
void DeleteFromPurchase(string want_ID);
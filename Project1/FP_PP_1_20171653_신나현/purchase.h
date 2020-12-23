#include "delim.h"
#include "recfile.h"
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

#define LENPID 12
#define LENGID 8
#define LENDATE 10
#define STDMAXBUF 256

using namespace std;

class Purchase {
private:
	char purchase_id[LENPID];
	char game_id[LENGID];
	string member_id;
	char purchase_date[LENDATE];

public:
	Purchase();
	Purchase(const char* new_purchase_id);
	Purchase(const Purchase& p);

	Purchase& operator = (const Purchase& p);
	bool operator == (const Purchase& p);
	bool operator != (const Purchase& p);

	friend istream& operator >> (istream& is, Purchase& p);
	friend ostream& operator << (ostream& os, Purchase& p);

	void update_purchase_id(const char* new_purchase_id);
	void update_game_id(const char* new_game_id);
	void update_member_id(string new_member_id);
	void update_purchase_date(const char* new_purchase_date);

	friend void showPurchase();
	friend void PurchaseTest();

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer& Buffer);

	char* getGameID() {
		return game_id;
	}
	string getMemberID() {
		return member_id;
	}
	char* getPurchaseID() {
		return purchase_id;
	}
	int get_length() {
		return strlen(purchase_id) + strlen(game_id) + member_id.size() + strlen(purchase_date);
	}
};

istream& operator >> (istream& is, Purchase& s);
ostream& operator << (ostream& os, Purchase& s);

void showPurchase();
void PurchaseTest();
int purchaseRecordCount();
int searchPurchase(char* PurchaseID);
int searchPurchase(char* PurchaseID, Purchase* pur);
int searchGameID(char* GameID);
int searchGameID(char* GameID, Purchase* pur);
int searchMemberID(char* MemberID);
int searchMemberID(char* MemberID, Purchase* pur);
void insertPurchase(char* PurchaseID);
void deletePurchase(char* PurchaseID);
void updatePurchase(char* PurchaseID);
void deleteMemPurchase(char* MemberID);
void deleteGamePurchase(char* GameID);




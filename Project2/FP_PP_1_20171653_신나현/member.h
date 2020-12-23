#include "delim.h"
#include "recfile.h"
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

#define LENBIR 10
#define LENCLS 1
#define STDMAXBUF 256

using namespace std;

class Member {
private:
	string id;
	string password;
	string name;
	string e_mail;
	string address;
	char birthday[LENBIR];
	char mem_class[LENCLS];
	string level;
	string key;

public:
	Member();
	Member(const string new_id);
	Member(const Member& s);

	Member& operator = (const Member& m);
	bool operator == (const string m);
	bool operator != (const Member& m);

	friend istream& operator >> (istream& is, Member& m);
	friend ostream& operator << (ostream& os, Member& m);

	void update_id(string new_id);
	void update_password(string new_password);
	void update_name(string new_name);
	void update_e_mail(string new_e_mail);
	void update_address(string new_address);
	void update_birthday(const char* new_birthday);
	void update_class(const char* new_class);
	void update_level(string new_level);

	friend void showMember();
	friend void MemberTest();

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer& Buffer);

	string get_id() {
		return id;
	}
	string get_password() {
		return password;
	}
	int get_length() {
		return id.size() + password.size() + name.size() + e_mail.size() + address.size() + strlen(birthday) +strlen(mem_class);
	}
	string get_level() {
		return level;
	}
	char* Key();
};

istream& operator >> (istream& is, Member& m);
ostream& operator << (ostream& os, Member& m);
void showMember();
void MemberTest();
int recordCount();
int searchMember(char* memberID);
int searchMember(char* memberID, Member* mem);
void insertMember(char* memberID);
void deleteMember(char* memberID);
void updateMember(string memberID);
void updateMember(string memberID, int mode);
#include "delim.h"
#include "recfile.h"
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

#define LENID 8
#define LENREL 10
#define LENSCR 2
#define LENPRI 3
#define STDMAXBUF 256

using namespace std;

class Game {
private:
	char id[LENID];
	string title;
	char release[LENREL];
	string developer;
	string platform;
	char score[LENSCR];
	char price[LENPRI];
	string key;
	
public:
	Game();
	Game(const char* new_id);
	Game(const Game& g);

	Game& operator = (const Game& g);
	bool operator == (const Game& g);
	bool operator != (const Game& g);

	friend istream& operator >> (istream& is, Game& g);
	friend ostream& operator << (ostream& os, Game& g);

	void update_id(const char* new_id);
	void update_title(string new_title);
	void update_release(const char* new_release);
	void update_developer(string new_developer);
	void update_platform(string new_platform);
	void update_score(const char* new_score);
	void update_price(const char* new_price);

	friend void showGame();
	friend void GameTest();

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer& Buffer);

	char* get_id() {
		return id;
	}
	int get_length() {
		return strlen(id) + title.size() + strlen(release) + developer.size() + platform.size() + strlen(score) + strlen(price);
	}

	char* Key();
};

istream& operator >> (istream& is, Game& s);
ostream& operator << (ostream& os, Game& s);
void showGame();
void GameTest();
int gameRecordCount();
int searchGame(char* GameID);
int searchGame(char* GameID, Game* mem);
void insertGame(char* GameID);
void deleteGame(char* GameID);
void updateGame(char* GameID);


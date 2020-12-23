#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include "recfile.h"
#include <sstream>

//생성자
Game::Game() {

}
Game::Game(const char* new_id) {
	Game();
	update_id(new_id);
}

//복사 생성자
Game::Game(const Game& g) {
	Game();

	update_id(g.id);
	update_title(g.title);
	update_release(g.release);
	update_developer(g.developer);
	update_platform(g.platform);
	update_score(g.score);
	update_price(g.price);
}

//객체 복사 생성자 (대입연산자)
Game& Game::operator = (const Game& g) {
	update_id(g.id);
	update_title(g.title);
	update_release(g.release);
	update_developer(g.developer);
	update_platform(g.platform);
	update_score(g.score);
	update_price(g.price);

	return *this;
}

//연산자 오버로딩
bool Game::operator == (const Game& g) {
	return !memcmp(id, g.id, LENID);
}
bool Game::operator != (const Game& g) {
	if (id != g.id) {
		return true;
	}
	return false;
}

istream& operator >> (istream& is, Game& g) {
	char str[100];
	char* temp;
	is.getline(str, 100);
	//printf("%s\n", str);

	temp = strtok(str, "|");
	g.update_id(temp);

	temp = strtok(NULL, "|");
	g.update_title(temp);

	temp = strtok(NULL, "|");
	g.update_release(temp);

	temp = strtok(NULL, "|");
	g.update_developer(temp);

	temp = strtok(NULL, "|");
	g.update_platform(temp);

	temp = strtok(NULL, "|");
	g.update_score(temp);

	temp = strtok(NULL, "\n");
	g.update_price(temp);

	return is;
}

ostream& operator << (ostream& os, Game& g) {
	char id[LENID + 1];
	char release[LENREL + 1];
	char score[LENSCR + 1];
	char price[LENPRI + 1];

	strncpy(id, g.id, LENID);
	id[LENID] = '\0';

	strncpy(release, g.release, LENREL);
	release[LENREL] = '\0';

	strncpy(score, g.score, LENSCR);
	score[LENSCR] = '\0';

	strncpy(price, g.price, LENPRI);
	price[LENPRI] = '\0';

	os << "ID: " << id << endl;
	os << "TITLE: " << g.title << endl;
	os << "RELEASE DATE: " << release << endl;
	os << "DEVELOPER: " << g.developer << endl;
	os << "PLATFORM: " << g.platform << endl;
	os << "SCORE: " << score << endl;
	os << "PRICE: " << price << endl;

	return os;
}

void Game::update_id(const char* new_id) {
	memcpy(id, new_id, LENID);
}
void Game::update_title(string new_title) {
	title = new_title;
}
void Game::update_release(const char* new_release) {
	memcpy(release, new_release, LENREL);
}
void Game::update_developer(string new_developer) {
	developer = new_developer;
}
void Game::update_platform(string new_platform) {
	platform = new_platform;
}
void Game::update_score(const char* new_score) {
	memcpy(score, new_score, LENSCR);
}
void Game::update_price(const char* new_price) {
	memcpy(price, new_price, LENPRI);
}

void showGame() {
	ifstream ifs("listOfGame.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	//cout << n;

	//vector<Game> m_list;

	for (int i = 0; i < n; i++) {
		//cout << i << endl;
		Game g;
		ifs >> g;
		if (i < 10)
			cout << g << endl;
		//m_list.push_back(m);
	}


	return;
}


bool Game::Pack(IOBuffer& Buffer) const {
	int numBytes;

	Buffer.Clear();

	string g_id(id, LENID);
	string g_release(release, LENREL);
	string g_score(score, LENSCR);
	string g_price(price, LENPRI);

	numBytes = Buffer.Pack(g_id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(title.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(g_release.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(developer.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(platform.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(g_score.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(g_price.c_str());
	if (numBytes == -1) return false;

	return true;
}


bool Game::Unpack(IOBuffer& Buffer) {
	int numBytes;

	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(id, LENID);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	title = buf;

	numBytes = Buffer.Unpack(release, LENREL);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	developer = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	platform = buf;

	numBytes = Buffer.Unpack(score, LENSCR);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(price, LENPRI);
	if (numBytes == -1) return false;

	return true;
}

void GameTest() {
	ifstream ifs("listOfGame.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	//printf("%d\n", n);
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);

	char filename[20] = "fileOfGame.dat";
	//Write test
	GameFile.Create(filename, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Game g;
		ifs >> g;
		int recaddr;
		if ((recaddr = GameFile.Write(g)) == -1) {
			cout << "Write Error!" << endl;
		}
	}

	GameFile.Close();

	//Read Test
	GameFile.Open(filename, ios::in);
	for (int i = 0; i < n; i++) {
		Game g;
		GameFile.Read(g);
		if (i < 10)
			cout << g << endl;
	}
	GameFile.Close();

	return;
}

int gameRecordCount() {
	int cnt = 0;
	Game g;
	char file_name[20] = "fileOfGame.dat";

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);
	GameFile.Open(file_name, ios::in);
	while (GameFile.Read(g) != -1)
		cnt++;
	GameFile.Close();
	return cnt;
}

int searchGame(char* GameID) {
	int num, addr, find = -1;
	char file_name[20] = "fileOfGame.dat";

	num = gameRecordCount();
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);

	GameFile.Open(file_name, ios::in);
	Game key(GameID);
	for (int i = 0; i < num; i++) {
		Game g;
		addr = GameFile.Read(g);
		if (g == GameID) {
			find = addr;
			break;
		}
	}
	GameFile.Close();
	return find;
}

int searchGame(char* GameID, Game* ga) {
	int num, addr, find = -1;
	char file_name[20] = "fileOfGame.dat";

	num = gameRecordCount();
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);

	GameFile.Open(file_name, ios::in);

	for (int i = 0; i < num; i++) {
		Game g;
		addr = GameFile.Read(g);
		if (g == GameID) {
			find = addr;
			*ga = g;
			break;
		}
	}
	GameFile.Close();
	return find;
}

void insertGame(char* GameID) {
	Game g;
	string buf;
	char* update_temp = new char(100);

	g.update_id(GameID);

	cout << "Title: ";
	cin >> buf;
	g.update_title(buf);

	cout << "Release Date(10char): ";
	cin >> update_temp;
	if (strlen(update_temp) != 10) {
		cout << "Wrong length" << endl;
		return;
	}
	g.update_release(update_temp);

	cout << "Developer: ";
	cin >> buf;
	g.update_developer(buf);

	cout << "Platform: ";
	cin >> buf;
	g.update_platform(buf);

	cout << "Score(2char): ";
	cin >> update_temp;
	if (strlen(update_temp) > 2) {
		cout << "Wrong length" << endl;
		return;
	}
	g.update_score(update_temp);

	cout << "Price(3char): ";
	cin >> update_temp;
	if (strlen(update_temp) > 3) {
		cout << "Wrong length" << endl;
		return;
	}
	g.update_price(update_temp);

	char file_name[20] = "fileOfGame.dat";

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);

	GameFile.Open(file_name, ios::in | ios::out | ios::app);
	if (GameFile.Write(g) == -1) {
		cout << "Insert Error!" << endl;
	}
	GameFile.Close();
}

void updateGame(char* gameID) {
	int num = gameRecordCount();
	ifstream ifs("fileOfGame.dat");
	string filename;
	char file_name[20] = "fileOfGame.dat";
	int index = 0;
	int up_index = 0;
	Game g;
	int ifs_last;
	int find_ID = 0;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Game> GameFile(buffer);
	Game* Game_arr = new Game[100000];

	if (ifs.fail()) {
		cout << "fileOfGame.dat open error!" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	GameFile.Open(file_name, ios::in);
	ifs.clear();	//because of c++98
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	//GameFile.Read(g);
	//cout << g.get_id() << endl;

	for (int i = 0; i < num; i++) {
		GameFile.Read(g);

		if (strncmp(g.get_id(), gameID, 8) == 0) {
			up_index = i;
			Game_arr[i] = g;
			//ifs.seekg(g.get_length(), ifs.cur);
		}
		else {
			Game_arr[i] = g;
		}
		//ifs.seekg(g.get_length(), ifs.cur);
	}
	GameFile.Close();
	g = Game_arr[up_index];

	string temp;
	char* update_temp = new char(100);

	cout << "++++++++++++++++++++++++" << endl;
	cout << "input new information" << endl;

	cout << "new Title: ";
	cin >> temp;
	g.update_title(temp);

	cout << "new Release date(10char): ";
	cin >> update_temp;
	if (strlen(update_temp) != 10) {
		cout << "Wrong length" << endl;
		return;
	}
	g.update_release(update_temp);

	cout << "new Developer: ";
	cin >> temp;
	g.update_developer(temp);

	cout << "new Platform: ";
	cin >> temp;
	g.update_platform(temp);

	cout << "new Score(2char): ";
	cin >> update_temp;
	if (strlen(update_temp) > 2) {
		cout << "Wrong length" << endl;
		return;
	}
	g.update_score(update_temp);

	cout << "new price(3char): ";
	cin >> update_temp;
	if (strlen(update_temp) > 3) {
		cout << "Wrong length" << endl;
		return;
	}
	g.update_price(update_temp);


	ifs.seekg(g.get_length(), ifs.cur);
	cout << endl;
	cout << "Update success!!!" << endl;
	cout << g;


	Game_arr[up_index] = g;
	ifs.seekg(g.get_length(), ifs.cur);

	GameFile.Close();

	GameFile.Create(file_name, ios::out | ios::trunc);
	int recaddr;
	for (int i = 0; i < num; i++) {
		if ((recaddr = GameFile.Write(Game_arr[i])) == -1)
			cout << "Write Error!" << endl;
	}
	GameFile.Close();

	ifs.close();
}

void deleteGame(char* GameID) {
	int num = gameRecordCount();
	int found = 0;
	ifstream ifs("fileOfGame.dat");
	char file_name[20] = "fileOfGame.dat";
	int index = 0;
	Game g;
	Game* Game_arr = new Game[100000];
	int ifs_last;

	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return;
	}

	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);

	GameFile.Open(file_name, ios::in);
	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	
	for(int i=0; i<num; i++) {
		GameFile.Read(g);

		if (strncmp(g.get_id(), GameID, 8) == 0) {
			found = 1;
			//ifs.seekg(g.get_length(), ifs.cur);
		}
		else {
			Game_arr[index] = g;
			index += 1;
		}
		//ifs.seekg(g.get_length(), ifs.cur);
	}
	GameFile.Close();


	if (found) {
		GameFile.Create(file_name, ios::out | ios::trunc);
		int recaddr;
		for (int i = 0; i < index; i++) {
			if ((recaddr = GameFile.Write(Game_arr[i])) == -1)
				cout << "Write Error!" << endl;
		}
		GameFile.Close();
		cout << "Deleting Complete from fileOfGame.dat" << endl;
	}
	ifs.close();
}
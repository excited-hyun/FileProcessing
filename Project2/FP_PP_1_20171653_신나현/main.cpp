#include "main.h"

int index, mindex, gindex, pindex;
Purchase* purchase_arr = new Purchase[11000];

int main(void) {
	static int testFlag = false;
	while (1) {
		int menu;
		int authority = 9;
		PrintMenu();
		cin >> menu;

		if (menu == 8)
			break;
		else if (menu == 1)
			showMember();

		else if (menu == 2) 
			showGame();
		
		else if (menu == 3) 
			showPurchase();
		
		else if (menu == 4) 
			MemberTest();
		
		else if (menu == 5) 
			GameTest();
		
		else if (menu == 6) 
			PurchaseTest();
		
		else if (menu == 7) {
			char accessID[MAX_BUF];
			if (!testFlag) {
				MemberTest(1);
				GameTest(1);
				PurchaseTest(1);
				MakeIndexFile();
				testFlag = true;
			}
			authority = accessValidate(accessID);
			if (authority == 9)
				GamePurchaseSystem_MemberMode(accessID);
			else if(authority==1)
				GamePurchaseSystem();

			MakeIndexFile();
			
		}
	}
}

void PrintMenu() {
	cout << "++++++++++++++++++++++++" << endl;
	cout << "1. showMember" << endl;
	cout << "2. showGame" << endl;
	cout << "3. showPurchase" << endl;
	cout << "4. MemberTest" << endl;
	cout << "5. GameTest" << endl;
	cout << "6. PurchaseTest" << endl;
	cout << "7. GamePurchaseSystem" << endl;
	cout << "8. Exit" << endl;
	cout << "++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";
}

void MakeIndexFile() {
	
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	//Todo...
	TextIndex MemberIndex(1000);

	char filename[20] = "fileOfMember.dat";
	MemberFile.Open(filename, ios::in);
	while (1) {		// 학생 데이터를 읽어서 인덱스를 생성
		Member m;
		int recaddr = MemberFile.Read(m);
		if (recaddr == -1) break;
		//Todo...
		MemberIndex.Insert(m.Key(), recaddr);
	
		//cout << recaddr << '\n' << m;
	}
	MemberFile.Close();

	// 생성한 인덱스를 인덱스 파일로 저장
	//Todo...
	TextIndexBuffer idxbuf(30, 1000);

	BufferFile MemIdxFile(idxbuf);
	char idxfilename[20] = "fileOfMember.ind";
	MemIdxFile.Create(idxfilename, ios::out | ios::trunc);
	MemIdxFile.Rewind(); //헤더 다음의 첫번째 레코드 위치로 이동
	//Todo...
	idxbuf.Pack(MemberIndex);
	int result = MemIdxFile.Write();
	MemIdxFile.Close();


	


	DelimFieldBuffer buffer1('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer1);

	//Todo...
	TextIndex GameIndex(1000);

	char filename1[20] = "fileOfGame.dat";
	GameFile.Open(filename1, ios::in);
	while (1) {		// 학생 데이터를 읽어서 인덱스를 생성
		Game g;
		int recaddr = GameFile.Read(g);
		if (recaddr == -1) break;
		//Todo...
		GameIndex.Insert(g.Key(), recaddr);
		//cout << recaddr << '\n' << s;
	}
	GameFile.Close();

	// 생성한 인덱스를 인덱스 파일로 저장
	//Todo...
	TextIndexBuffer gameidxbuf(LENID, 1000);

	BufferFile GameIdxFile(gameidxbuf);
	char idxfilename1[20] = "fileOfGame.ind";
	GameIdxFile.Create(idxfilename1, ios::out | ios::trunc);
	GameIdxFile.Rewind(); //헤더 다음의 첫번째 레코드 위치로 이동
	//Todo...
	gameidxbuf.Pack(GameIndex);
	int result1 = GameIdxFile.Write();
	GameIdxFile.Close();

}

void GamePurchaseSystem_MemberMode(char accessID[]) {
	int command, p_id;
	int recaddr;
	char recID[MAX_BUF];

	Member m;
	Game g;
	Purchase p;

	cout << "++++++++++++++++++++++++" << endl;
	cout << "1. Update Member" << endl;
	cout << "2. Delete Member" << endl;

	cout << "3. Search Game" << endl;

	cout << "4. Search Purchase" << endl;
	cout << "5. Insert Purchase" << endl;
	cout << "6. Update Purchase" << endl;
	cout << "7. Delete Purchase" << endl;
	cout << "++++++++++++++++++++++++" << endl;
	cout << "input the number of command >>> ";
	cin >> command;

	if (command < 1 || command > 7) {
		cout << "Wrong Command!" << endl;
		return;
	}

	switch (command) {
		//update member
	case 1:
		cout << "Update Mode (Member)" << endl;
		updateMember(accessID, 1);
		break;

		//delete member
	case 2:
		cout << "Delete Mode (Member)" << endl;
		deleteMember(accessID);
		cout << "Wait...(deleting form fileOfPurchase.dat" << endl;
		//if ((result = searchMemberID(recID, &p)) != -1) {
		DeleteFromPurchase(accessID);
		break;

	case 3:
		getchar();
		cout << "Search Mode (Game)" << endl;
		cout << "input Game ID (8char) : ";
		fflush(stdin);
		cin.getline(recID, MAX_GAME, '\n');
		if ((recaddr = searchGame(recID, &g)) == -1)
			cout << "Not founded : " << recID << endl;
		else {
			cout << "Game Founded! " << endl;
			cout << g;
		}
		fflush(stdin);
		break;

	case 4:
		cout << "++++++++++++++++++++++++" << endl;
		cout << "Search Mode (purchase)" << endl;
		cout << "1. By Purchase ID" << endl;
		cout << "2. By Game ID" << endl;
		cout << "3. Show All Purchase List" << endl;
		cout << "++++++++++++++++++++++++" << endl;
		cout << "input the number of ID that you want to search by >>> ";
		cin >> p_id;
		
		if (p_id == 1) {
			cout << "++++++++++++++++++++++++" << endl;
			cout << "input Purchase ID (12char) : ";
			getchar();
			cin.getline(recID, MAX_PUR, '\n');
			//cout << recID << endl;
			if ((recaddr = searchPurchase_Customer(recID, &p, accessID)) == -1)
				cout << "Not founded : " << recID << endl;

			fflush(stdin);
			break;
		}
		else if (p_id == 2) {
			cout << "++++++++++++++++++++++++" << endl;
			cout << "input game ID (8char) : ";
			getchar();
			cin.getline(recID, MAX_GAME, '\n');
			if ((recaddr = searchGame_Customer(recID, &p, accessID)) == -1)
				cout << "Not founded : " << recID << endl;

			fflush(stdin);

			break;
		}
		else if (p_id == 3) {
			cout << "++++++++++++++++++++++++" << endl;
			showAllPurchase_Customer(accessID);
			fflush(stdin);
			break;
		}

	case 5:
		cout << "Insert Mode (Purchase)" << endl;
		cout << "input Purchase ID (12char) : ";
		getchar();

		cin.getline(recID, MAX_PUR + 1, '\n');
		if ((searchPurchase(recID, &p)) != -1 || (recaddr = searchPurchase_Customer(recID, &p, accessID)) != -1) {	//duplicated

			cout << recID << " is a duplicated purchase ID!" << endl;
			break;
		}
		insertPurchase_Customer(recID, accessID);
		break;

	case 6:

		cout << "Update Mode (Purchase)" << endl;
		cout << "input Purchase ID (12char) : ";

		getchar();
		cin.getline(recID, MAX_PUR + 1, '\n');
		if ((recaddr = searchPurchase_Customer(recID, &p, accessID)) == -1) {	//not exist
			cout << "MemberID:" << accessID << " and Purchase ID:" << recID << "does not exist!" << endl;
			break;

		}

		updatePurchase_Customer(recID, accessID);
		fflush(stdin);
		break;

	case 7:
		cout << "Delete Mode (Purchase)" << endl;
		cout << "input Purchase ID (12char) : ";
		getchar();
		cin.getline(recID, MAX_PUR + 1, '\n');
		if ((recaddr = searchPurchase_Customer(recID, &p, accessID)) == -1) {	//not exist
			cout << "MemberID:" << accessID << " and Purchase ID:" << recID << "does not exist!" << endl;
			break;
		}

		deletePurchase(recID);

		break;
	}

}

void GamePurchaseSystem() {
	int command, file, p_id;
	char recID[MAX_BUF];
	int result;
	Member m;
	Game g;
	Purchase p;

	cout << "++++++++++++++++++++++++" << endl;
	cout << "1. Search (Using ID)" << endl;
	cout << "2. Insert (Using ID)" << endl;
	cout << "3. Delete (Using ID)" << endl;
	cout << "4. Update (Using ID)" << endl;
	cout << "++++++++++++++++++++++++" << endl;
	cout << "input the number of command >>> ";
	cin >> command;
	if (command < 1 || command >4) {
		cout << "Wrong Command!" << endl;
		return;
	}

	cout << "++++++++++++++++++++++++" << endl;
	cout << "1. Member Data File" << endl;
	cout << "2. Game Data File" << endl;
	cout << "3. Purchase Data File" << endl;
	cout << "++++++++++++++++++++++++" << endl;
	cout << "input the number of data file >>> ";
	cin >> file;
	if (file < 1 || file >3) {
		cout << "Wrong Data File!" << endl;
		return;
	}
	if (command == 1) {
		if (file == 1) {	//search member
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Search Mode (member)" << endl;
			cout << "input member ID >>> ";
			cin >> recID;
			//cout << recID <<"!" << endl;
			//cin.getline(recID, MAX_MEM, '\n');
			if ((result = searchMember(recID, &m)) == -1) {
				cout << "Can't find " << recID << endl;
			}
			else {
				//cout << "result: " << result << endl;
				cout << m <<endl;
			}
		}
		else if (file == 2) {	//search game
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Search Mode (game)" << endl;
			cout << "input game ID >>> ";
			cin >> recID;
			//cout << recID <<"!" << endl;
			//cin.getline(recID, MAX_MEM, '\n');
			if ((result = searchGame(recID, &g)) == -1) {
				cout << "Can't find " << recID << endl;
			}
			else {		
				//cout << "result: " << result << endl;
				cout << g << endl;
			}
		}
		else if (file == 3) {	//search purchase
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Search Mode (purchase)" << endl;
			cout << "1. By Purchase ID" << endl;
			cout << "2. By Game ID" << endl;
			cout << "3. By Member ID" << endl;
			cout << "++++++++++++++++++++++++" << endl;
			cout << "input the number of ID that you want to search by >>> ";
			cin >> p_id;
			if (p_id == 1) {
				cout << "++++++++++++++++++++++++" << endl;
				cout << "input purchase ID >>> ";
				cin >> recID;
				//cout << recID <<"!" << endl;
				//cin.getline(recID, MAX_MEM, '\n');
				if ((result = searchPurchase(recID, &p)) == -1) {
					cout << "Can't find " << recID << endl;
				}
				else {
					//cout << "result: " << result << endl;
					cout << p << endl;
				}
			}
			else if (p_id == 2) {
				cout << "++++++++++++++++++++++++" << endl;
				cout << "input game ID >>> ";
				cin >> recID;
				//cout << recID <<"!" << endl;
				//cin.getline(recID, MAX_MEM, '\n');
				if ((result = searchGameID(recID, &p)) == -1) {
					cout << "Can't find " << recID << endl;
				}
				else {
					//cout << "result: " << result << endl;
					//cout << p << endl;
				}
			}
			else if (p_id == 3) {
				cout << "++++++++++++++++++++++++" << endl;
				cout << "input member ID >>> ";
				cin >> recID;
				//cout << recID <<"!" << endl;
				//cin.getline(recID, MAX_MEM, '\n');
				if ((result = searchMemberID(recID, &p)) == -1) {
					cout << "Can't find " << recID << endl;
				}
				else {
					//cout << "result: " << result << endl;
					//cout << p << endl;
				}
			}
			else {
				cout << "You Chose Wrong ID!" << endl;
				return;
			}
		}
		
	}
	else if (command == 2) {
		if (file == 1) {	//insert member
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Insert Mode (member)" << endl;
			cout << "input member ID >>> ";
			cin >> recID;
			//cout << recID <<"!" << endl;
			//cin.getline(recID, MAX_MEM, '\n');
			if ((result = searchMember(recID, &m)) != -1) {
				cout << recID <<"is duplicated member ID" << endl;
				return;
			}
			else {
				insertMember(recID);
			}
		}
		else if (file == 2) {
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Insert Mode (game)" << endl;
			cout << "input game ID >>> ";
			cin >> recID;

			if ((result = searchGame(recID, &g)) != -1) {
				cout << recID << " is duplicated game ID " << endl;
				return;
			}
			else {
				insertGame(recID);
			}
		}
		else if (file == 3) {
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Insert Mode (purchase)" << endl;
			cout << "input purchase ID >>> ";
			cin >> recID;

			if ((result = searchPurchase(recID, &p)) != -1) {
				cout << recID << " is duplicated purchase ID " << endl;
				return;
			}
			else {
				insertPurchase(recID);
			}
		}
	}
	else if (command == 3) {
		if (file == 1) {	//delete member
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Delete Mode (member)" << endl;
			cout << "input member ID >>> ";
			cin >> recID;
			if ((result = searchMember(recID, &m)) == -1) {
				cout << recID << " does not exist " << endl;
				return;
			}
			else {
				deleteMember(recID);
			}
			cout << "Wait...(deleting form fileOfPurchase.dat" << endl;
			DeleteFromPurchase(recID);
		}
		else if (file == 2) {	//delete game
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Delete Mode (game)" << endl;
			cout << "input game ID >>> ";
			cin >> recID;
			if ((result = searchGame(recID, &g)) == -1) {
				cout << recID << " does not exist " << endl;
				return;
			}
			else {
				deleteGame(recID);
			}
			cout << "Wait...(deleting form fileOfPurchase.dat" << endl;
			//if ((result = searchGameID(recID, &p)) != -1) {
			DeleteFromPurchase(recID);
		}
		else if (file == 3) {	//delete purchase
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Delete Mode (purchase)" << endl;
			cout << "input purchase ID >>> ";
			cin >> recID;
			if ((result = searchPurchase(recID, &p)) == -1) {
				cout << recID << " does not exist " << endl;
				return;
			}
			else {
				deletePurchase(recID);
				cout << "Deleting Complete from fildOfPurchase.dat" << endl;
			}

		}
	}
	else if (command == 4) {
		if (file == 1) {	//update member
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Update Mode (member)" << endl;
			cout << "input member ID >>> ";
			cin >> recID;
			if ((result = searchMember(recID, &m)) == -1) {
				cout << recID << " does not exist " << endl;
				return;
			}
			else {
				updateMember(recID);
			}
		}
		else if (file == 2) {	//update game
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Update Mode (game)" << endl;
			cout << "input game ID >>> ";
			cin >> recID;
			if ((result = searchGame(recID, &g)) == -1) {
				cout << recID << " does not exist " << endl;
				return;
			}
			else {
				updateGame(recID);
			}
		}
		else if (file == 3) {	//update purchase
			cout << "++++++++++++++++++++++++" << endl;
			cout << "Update Mode (purchase)" << endl;
			cout << "input purchase ID >>> ";
			cin >> recID;
			if ((result = searchPurchase(recID, &p)) == -1) {
				cout << recID << " does not exist " << endl;
				return;
			}
			else {
				updatePurchase(recID);
			}
		}
	}
}

void MemberTest(int print_flag) {
	ifstream ifs("listOfMember.txt");
	if (ifs.fail())
	{
		cout << "listOfMember.txt File Open Error!" << endl;
		return;
	}
	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	mindex = n;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Member> MemberFile(buffer);

	// Write test
	char file_name[20] = "fileOfMember.dat";
	MemberFile.Create(file_name, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Member m;
		ifs >> m;
		int recaddr;
		if ((recaddr = MemberFile.Write(m)) == -1)
			if (!print_flag)
				cout << "Write Error!" << endl;
			else
				if (!print_flag)
					cout << "Write at " << recaddr << endl;
	}

	MemberFile.Close();

	// Read test
	char file_name1[20] = "fileOfMember.dat";
	MemberFile.Open(file_name1, ios::in);

	for (int i = 0; i < 10; i++) {
		Member s;
		MemberFile.Read(s);
		if (!print_flag)
			cout << s << endl;
	}
	MemberFile.Close();
	ifs.close();
	return;

}


void GameTest(int print_flag) {

	ifstream ifs("listOfGame.txt");
	if (ifs.fail())
	{
		cout << "listOfGame.txt File Open Error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	gindex = n;

	DelimFieldBuffer buffer('|', 1000);

	RecordFile <Game> GameFile(buffer);

	// Write test
	char file_name[20] = "fileOfGame.dat";
	GameFile.Create(file_name, ios::out | ios::trunc);

	for (int i = 0; i < n; i++) {
		Game s;
		ifs >> s;
		int recaddr;

		if ((recaddr = GameFile.Write(s)) == -1)
			if (!print_flag)
				cout << "Write Error!" << endl;

			else
				if (!print_flag)
					cout << "Write at " << recaddr << endl;
	}
	GameFile.Close();

	// Read test
	char file_name1[20] = "fileOfGame.dat";
	GameFile.Open(file_name1, ios::in);

	for (int i = 0; i < 10; i++) {
		Game s;
		GameFile.Read(s);
		if (!print_flag)
			cout << s << endl;
	}
	GameFile.Close();
	ifs.close();
	return;
}


void PurchaseTest(int print_flag) {
	ifstream ifs("listOfPurchase.txt");
	if (ifs.fail())
	{
		cout << "listOfPurchase.txt File Open Error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	pindex = n;

	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Purchase> PurchaseFile(buffer);

	// Write test
	char file_name[20] = "fileOfPurchase.dat";
	PurchaseFile.Create(file_name, ios::out | ios::trunc);

	for (int i = 0; i < n; i++) {
		Purchase s;
		ifs >> s;
		int recaddr;
		if ((recaddr = PurchaseFile.Write(s)) == -1)
			if (!print_flag)
				cout << "Write Error!" << endl;

			else
				if (!print_flag)
					cout << "Write at " << recaddr << endl;

	}

	PurchaseFile.Close();


	// Read test
	char file_name1[20] = "fileOfPurchase.dat";
	PurchaseFile.Open(file_name1, ios::in);

	for (int i = 0; i < 10; i++) {
		Purchase s;
		PurchaseFile.Read(s);
		if (!print_flag)
			cout << s << endl;
	}
	PurchaseFile.Close();
	ifs.close();
	return;
}

int accessValidate(char recID[]) {
	//char recID[BUFMAX];
	char pw[MAX_BUF];
	int recaddr;
	Member mem;

	getchar();
	cout << "Member ID: ";
	cin.getline(recID, MAX_MEM, '\n');
	cout << "Password: ";
	cin.getline(pw, 20, '\n');

	recaddr = searchMember(recID, &mem);
	if (recaddr == -1)
		cout << "Member ID Not founded : " << recID << endl;

	else {
		string pass = mem.get_password();
		if (pass == pw)
			return mem.get_level()[0] - '0';
		else {
			cout << "Password Error!" << endl;
			return false;
		}
	}

	fflush(stdin);
	return false;

}

void DeleteFromPurchase(string want_ID) {

	index = 0;
	ifstream ifs("fileOfPurchase.dat");
	if (ifs.fail()) {
		cout << "fileOfPurchase.dat open error!" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	Purchase m;
	int ifs_last;
	int find_ID = 0;
	DelimFieldBuffer buffer('|', 1200);

	RecordFile <Purchase> PurchaseFile(buffer);

	char file_name[20] = "fileOfPurchase.dat";
	PurchaseFile.Open(file_name, ios::in);

	//PurchaseFile.
	ifs.clear();	//because of c++98
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while (ifs.tellg() < ifs_last) {
		PurchaseFile.Read(m);

		if (!strcmp(m.getPurchaseID(), want_ID.c_str())) {
			find_ID = 1;
			ifs.seekg(m.get_length(), ifs.cur);
			pindex -= 1;
		}

		else if (!strncmp(m.getGameID(), want_ID.c_str(), 8)) {
			find_ID = 1;
			ifs.seekg(m.get_length(), ifs.cur);
			pindex -= 1;
		}

		else if (!m.getMemberID().compare(want_ID)) {
			find_ID = 1;
			ifs.seekg(m.get_length(), ifs.cur);
			pindex -= 1;
		}
		else {
			purchase_arr[index] = m;
			index += 1;

		}
		ifs.seekg(m.get_length(), ifs.cur);

	}
	PurchaseFile.Close();


	if (find_ID) {
		
		PurchaseFile.Create(file_name, ios::out | ios::trunc);

		int recaddr;
		for (int i = 0; i < index; i++) {
			if ((recaddr = PurchaseFile.Write(purchase_arr[i])) == -1)
				cout << "Write Error!" << endl;
		}

		PurchaseFile.Close();
		cout << "Deleting Complete from fildOfPurchase.dat" << endl;
	}

	ifs.close();

}
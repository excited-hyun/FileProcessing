#include "main.h"

int main(void) {
	while (1) {
		int menu;
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
			GamePurchaseSystem();
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
			//if ((result = searchMemberID(recID, &p)) != -1) {
			deleteMemPurchase(recID);
			//}
			cout << "Deleting Complete from fileOfPurchase.dat" << endl;
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
			deleteGamePurchase(recID);
			//}
			
			cout << "Deleting Complete from fildOfPurchase.dat" << endl;
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
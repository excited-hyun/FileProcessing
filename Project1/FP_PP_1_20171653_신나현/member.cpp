#define _CRT_SECURE_NO_WARNINGS
#include "member.h"
#include "recfile.h"
#include <sstream>

//생성자
Member::Member() {

}
Member::Member(const string new_id) {
	Member();
	update_id(new_id);
}

//복사 생성자
Member::Member(const Member& m) {
	Member();

	update_id(m.id);
	update_password(m.password);
	update_name(m.name);
	update_e_mail(m.e_mail);
	update_address(m.address);
	update_birthday(m.birthday);
	update_class(m.mem_class);
}

//객체 복사 생성자 (대입연산자)
Member& Member::operator = (const Member& m) {
	update_id(m.id);
	update_password(m.password);
	update_name(m.name);
	update_e_mail(m.e_mail);
	update_address(m.address);
	update_birthday(m.birthday);
	update_class(m.mem_class);

	return *this;
}

//연산자 오버로딩
bool Member::operator == (const string s) {
	//cout << s << " and " << id<<endl;
	return (id == s);
}

bool Member::operator != (const Member& s) {
	return (id != s.id);
}


istream& operator >> (istream& is, Member& m) {
	char str[100];
	char* temp;
	is.getline(str, 100);
	//printf("%s\n", str);

	temp = strtok(str, "|");
	m.update_id(temp);
	
	temp = strtok(NULL, "|");
	m.update_password(temp);

	temp = strtok(NULL, "|");
	m.update_name(temp);

	temp = strtok(NULL, "|");
	m.update_e_mail(temp);

	temp = strtok(NULL, "|");
	m.update_address(temp);

	temp = strtok(NULL, "|");
	m.update_birthday(temp);

	temp = strtok(NULL, "\n");
	m.update_class(temp);
	//printf("%s\n", temp);
	
	return is;
}

ostream& operator << (ostream& os, Member& m) {
	char birth[LENBIR + 1];
	char mem_class[LENCLS + 1];

	strncpy(birth, m.birthday, LENBIR);
	birth[LENBIR] = '\0';
	strncpy(mem_class, m.mem_class, LENCLS);
	mem_class[LENCLS] = '\0';

	os << "ID: " << m.id << endl;
	os << "PASSWORD: " << m.password << endl;
	os << "NAME: " << m.name << endl;
	os << "E-MAIL: " << m.e_mail << endl;
	os << "ADDRESS: " << m.address << endl;
	os << "BIRHTDAY: " << birth << endl;
	os << "CLASS: " << mem_class << endl;

	return os;
}

void Member::update_id(string new_id) {
	id = new_id;
}
void Member::update_password(string new_password) {
	password = new_password;
}
void Member::update_name(string new_name) {
	name = new_name;
}
void Member::update_e_mail(string new_e_mail) {
	e_mail = new_e_mail;
}
void Member::update_address(string new_address) {
	address = new_address;
}
void Member::update_birthday(const char* new_birthday) {
	memcpy(birthday, new_birthday, LENBIR);
}
void Member::update_class(const char *new_class) {
	memcpy(mem_class, new_class, LENCLS);
}

void showMember() {
	ifstream ifs("listOfMember.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return ;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	//cout << n;

	//vector<Member> m_list;

	for (int i = 0; i < n; i++) {
		//cout << i << endl;
		Member m;
		ifs >> m;
		if (i < 10)
			cout << m <<endl;
		//m_list.push_back(m);
	}
	
	
	return ;
}


bool Member::Pack(IOBuffer& Buffer) const {
	int numBytes;

	Buffer.Clear();

	string m_birthday(birthday, LENBIR);
	string m_class(mem_class, LENCLS);

	numBytes = Buffer.Pack(id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(password.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(name.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(e_mail.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(address.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(m_birthday.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(m_class.c_str());
	if (numBytes == -1) return false;

	return true;
}


bool Member::Unpack(IOBuffer& Buffer) {
	int numBytes;

	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	id = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	password = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	name = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	e_mail = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	address = buf;

	numBytes = Buffer.Unpack(birthday, LENBIR);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(mem_class, LENCLS);
	if (numBytes == -1) return false;

	return true;
}

void MemberTest() {
	ifstream ifs("listOfMember.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return ;
	}

	int n;
	ifs >> n;
	//printf("%d\n", n);
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	char filename[20] = "fileOfMember.dat";
	//Write test
	MemberFile.Create(filename, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Member m;
		ifs >> m;
		int recaddr;
		if ((recaddr = MemberFile.Write(m)) == -1) {
			cout << "Write Error!" << endl;
		}
	}

	MemberFile.Close();

	//Read Test
	MemberFile.Open(filename, ios::in);
	for (int i = 0; i < n; i++) {
		Member m;
		MemberFile.Read(m);
		if(i<10)
			cout << m << endl;
	}
	MemberFile.Close();

	return ;
}

int recordCount() {
	int cnt = 0;
	Member m;
	char file_name[20] = "fileOfMember.dat";

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);
	MemberFile.Open(file_name, ios::in);
	while (MemberFile.Read(m) != -1)
		cnt++;
	MemberFile.Close();
	return cnt;
}


int searchMember(char* memberID) {
	int num, addr, find = -1;
	char file_name[20] = "fileOfMember.dat";

	num = recordCount();
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	MemberFile.Open(file_name, ios::in);
	Member key(memberID);
	for (int i = 0; i < num; i++) {
		Member m;
		addr = MemberFile.Read(m);
		if (m == memberID) {
			find = addr;
			break;
		}
	}
	MemberFile.Close();
	return find;
}
int searchMember(char* memberID, Member* mem) {
	int num, addr, find = -1;
	char file_name[20] = "fileOfMember.dat";

	num = recordCount();
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	MemberFile.Open(file_name, ios::in);

	for (int i = 0; i < num; i++) {
		Member m;
		addr = MemberFile.Read(m);
		if (m == memberID) {
			find = addr;
			*mem = m;
			break;
		}
	}
	MemberFile.Close();
	return find;
}

void insertMember(char* memberID) {
	Member m;
	string buf;
	char* update_temp = new char(100);

	m.update_id(string(memberID));

	cout << "Password: ";
	cin >> buf;
	m.update_password(buf);

	cout << "Name: ";
	cin >> buf;
	m.update_name(buf);

	cout << "E-mail: ";
	cin >> buf;
	m.update_e_mail(buf);

	cout << "Address: ";
	cin >> buf;
	m.update_address(buf);

	cout << "Birthday(10char): ";
	cin >> update_temp;
	if (strlen(update_temp) != 10) {
		cout << "Wrong length" << endl;
		return;
	}

	m.update_birthday(update_temp);

	cout << "Class(1char): ";
	cin >> buf;
	m.update_class(buf.c_str());

	char file_name[20] = "fileOfMember.dat";

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	MemberFile.Open(file_name, ios::in | ios::out | ios::app);
	if (MemberFile.Write(m) == -1) {
		cout << "Insert Error!" << endl;
	}
	MemberFile.Close();
}

void deleteMember(char* memberID) {
	int num = recordCount();
	int found = 0;
	ifstream ifs("fileOfMember.dat");
	char file_name[20] = "fileOfMember.dat";
	int index= 0;
	Member m;
	Member* member_arr = new Member[100000];
	int ifs_last;

	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return;
	}
	
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	MemberFile.Open(file_name, ios::in);
	ifs.clear();	
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	//cout << ifs_last << " error!" << endl;
	for(int i=0; i<num; i++) {
		MemberFile.Read(m);

		//cout << m.get_id() << " error! " << memberID << endl;
		if (m.get_id().compare(memberID) == 0) {
			found = 1;
			//ifs.seekg(m.get_length(), ifs.cur);
		}
		else {
			member_arr[index] = m;
			index += 1;
		}
		//ifs.seekg(m.get_length(), ifs.cur);
	}
	MemberFile.Close();
	
	
	if (found) {
		MemberFile.Create(file_name, ios::out | ios::trunc);
		int recaddr;
		for (int i = 0; i < index; i++) {
			//cout << member_arr[i].get_id() << endl;
			if ((recaddr = MemberFile.Write(member_arr[i])) == -1)
				cout << "Write Error!" << endl;
		}
		MemberFile.Close();
		cout << "Deleting Complete from fileOfMember.dat" << endl;
	}
	ifs.close();
}

void updateMember(string memberID) {
	int num = recordCount();
	ifstream ifs("fileOfMember.dat");
	string filename;
	char file_name[20] = "fileOfMember.dat";
	int index = 0;
	int up_index = 0;
	Member m;
	int ifs_last;
	int find_ID = 0;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Member> MemberFile(buffer);
	Member* member_arr = new Member[100000];

	if (ifs.fail()) {
		cout << "fileOfMember.dat open error!" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	MemberFile.Open(file_name, ios::in);
	ifs.clear();	//because of c++98
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);

	for (int i = 0; i < num; i++) {
		MemberFile.Read(m);

		//cout << m.get_id() << " error! " << memberID << endl;
		if (m.get_id().compare(memberID) == 0) {
			up_index = i;
			//cout << m.get_id() << " error! " << up_index << endl;
			member_arr[i] = m;
			//ifs.seekg(m.get_length(), ifs.cur);
		}
		else {
			member_arr[i] = m;
		}
		//ifs.seekg(m.get_length(), ifs.cur);
	}
	MemberFile.Close();

	m = member_arr[up_index];

	string temp;
	char* update_temp = new char(100);

	cout << "++++++++++++++++++++++++" << endl;
	cout << "input new information" << endl;

	cout << "new Password: ";
	cin >> temp;
	m.update_password(temp);

	cout << "new Name: ";
	cin >> temp;
	m.update_name(temp);

	cout << "new E-mail: ";
	cin >> temp;
	m.update_e_mail(temp);

	cout << "new Address: ";
	cin >> temp;
	m.update_address(temp);

	cout << "new Birthday(10char): ";
	cin >> update_temp;
	if (strlen(update_temp) != 10) {
		cout << "Wrong length" << endl;
		return;
	}

	m.update_birthday(update_temp);

	cout << "new Class(1char): ";
	cin >> update_temp;
	if (strlen(update_temp) != 1) {
		cout << "Wrong length" << endl;
		return;
	}
	m.update_class(update_temp);

	ifs.seekg(m.get_length(), ifs.cur);
	cout << "Update success!!!" << endl;
	cout << m;


	member_arr[up_index] = m;
	ifs.seekg(m.get_length(), ifs.cur);


	MemberFile.Close();

	MemberFile.Create(file_name, ios::out | ios::trunc);
	int recaddr;
	for (int i = 0; i < num; i++) {
		if ((recaddr = MemberFile.Write(member_arr[i])) == -1)
			cout << "Write Error!" << endl;
	}
	MemberFile.Close();

	ifs.close();
}
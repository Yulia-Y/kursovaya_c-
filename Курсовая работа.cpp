#include <string>
#include <iostream>
#include <clocale>
#include <windows.h>
#include <fstream>

using namespace std;

struct Subject {
public:
	string Name;
	int mark;
	Subject() { Name = ""; mark = 0; };
	Subject(string Name, int mark) {
		this->Name = Name;
		this->mark = mark;
	}
};
struct Semestr {
public:
	int count;
	Subject sub[10];
	Semestr() { count = -1; Subject sub[10] = {}; }
};
struct Zachetka {
public:
	int count;
	Semestr sem[9];
	Zachetka() { count = -1; Semestr sem[9] = {}; }
};
class Student {
public:
	string sname, name, mname, fac, kaf, gr, nzach; int bd, by, bm, py;
	Zachetka zachetka;
	Student() {}
	Student(string sname, string name, string mname, string fac, string kaf, string gr, string nzach, int bd, int by, int bm, int py, Zachetka zachetka)
	{
		this->sname = sname;
		this->name = name;
		this->mname = mname;
		this->fac = fac;
		this->kaf = kaf;
		this->gr = gr;
		this->nzach = nzach;
		this->bd = bd;
		this->by = by;
		this->bm = bm;
		this->py = py;
		this->zachetka = zachetka;
	}
	void print() {
		cout << "��� : " << sname << " " << name << " " << mname << endl;
		if (bm>=10 && bd<10){cout << "���� �������� : 0" << bd << "." << bm << "." << by << endl;}
		if (bm<10 && bd>=10){cout << "���� �������� : " << bd << ".0" << bm << "." << by << endl;}
		if (bm<10 && bd<10){cout << "���� �������� : 0" << bd << ".0" << bm << "." << by << endl;}
		cout << "��� ����������� : " << py << endl;
		cout << "��������� : " << fac << "  ������� : " << kaf << endl;
		cout << "������ : " << gr << endl;
		cout << "����� �������� ������ : " << nzach << endl;
		for (int j = 0; j <= zachetka.count; j++)
		{
			cout << "������� " << j + 1 << endl;
			for (int k = 0; k <= zachetka.sem[j].count; k++)
			{
				cout << zachetka.sem[j].sub[k].Name << " " << zachetka.sem[j].sub[k].mark << endl;
			}
		}
	}
};
int Size = 0;
Student* student = new Student[0];
void DeleteStudent(int);
void ADDstudent(Student);
void menu();
void NEWStudent();
int FindStudent(string);
void StudentChange(int);
void StudentWork();
void addFile();
void readFile();
void ReWriteFile();
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	readFile();
	while (1)
		menu();
	return 0;
}
void menu() {
	char n;
menu_n:
	if (Size == 0) {
		cout << "!!!! ����� ������ ������������ ���������, ���������� ������� ��������� ��������� ��� ������ ������� ������ ���� !!!!" << endl;
	}
	cout << "������� ����� ��������, ������� ������ ���������: " << endl;
	cout << "1. ������/�������� ���������" << endl;
	cout << "2. ������� ��������" << endl;
	cout << "3. �������� ���� ��������� � ������������" << endl;
	cout << "4. �������� ���������� � ��������" << endl;
	cout << "5. �������� �������" << endl;
	cout << ">> ";

	cin >> n;
    cin.ignore(32767, '\n');

	switch (n)
	{
	case '1': {
		system("cls");
			NEWStudent();
			addFile();
		break;
	}
	case'2': {
		if (Size == 0) {
			system("cls");
			cout << "��������� ���" << endl;
			system("pause"); system("cls");
			break;
		}
		string nzach; int Delete;
	zenter:
		cout << "������� ����� �������� ������ ��������, �������� ������ ������� �� ������������: [0=����� � ����] >> ";
		cin >> nzach; cin.ignore(32767, '\n');
		if (nzach == "0") { system("cls"); break; }
		Delete = FindStudent(nzach);
		if (Delete == -1) {
			cout << "�� ������� ��������� � ����� ������� �������� ������ " << endl;
			goto zenter;
		}
		DeleteStudent(Delete);
		cout << "������� ������ ";
		system("pause"); system("cls");
		ReWriteFile();
		break;
	}
	case '3': {
		system("cls");
		for (int i = 0; i < Size; i++) {
			student[i].print();
			cout << endl;
		}
		system("pause");
		break;
	}
	case '4': {
		if (Size == 0) {
			system("cls");
			cout << "��������� ���" << endl;
			system("pause"); system("cls");
			break;
		}
		string zn; int edit;
		cout << "������� ����� �������� ������ >> ";
	checkZn:
		cin >> zn;
		cin.ignore(32767, '\n');
		if (zn == "0") {
			system("cls");
			break;
		}
		edit = FindStudent(zn);
		if (edit == -1) {
			cout << "�� ������� ��������� � ����� ������� �������, ���������� ����� [0=����� � ����] >> ";
			goto checkZn;
		}
		system("cls");
		StudentChange(edit);
		system("cls");
		break;
	}
	case '5': {
		if (Size == 0) {
			system("cls");
			cout << "��������� ���" << endl;
			system("pause"); system("cls");
			break;
		}
		system("cls");
		StudentWork();
		break;
	}
	default: { cout << "����� ������� ���!" << endl;
		system("pause"); system("cls");
		break;}
	}
}
void NEWStudent() {
	string sname, name, mname, fac, kaf, gr, nzach, Name; char N;  int bd, by, bm, py, mark;
	cout << "------------------ ������� [�" << Size + 1 << "]: ---------------------" << endl;
	cout << "���, ����������� ��������� >> ";
	cin >> sname >> name >> mname;
	cin.ignore(32767, '\n'); cin.clear();

bdate_input: cout << "���� �������� {�� �� ����}, ����������� ��������� >>";
	cin >> bd >> bm >> by;
	cin.ignore(32767, '\n'); cin.clear();
	if (bd < 1 || bd > 31 || bm < 1 || bm > 12 || by < 1900 || by > 2019) {
		cout << "������������ ���� ������" << endl;
		goto bdate_input;
	}

pdate_input:
	cout << "��� ����������� {����} >> ";
	cin >> py; cin.clear();
	cin.ignore(32767, '\n');
	if (py < 1947 || py > 2019 || py <= by ) {
		cout << "������������ ���� ������" << endl;
			goto pdate_input;
	}
	cout << "������� >> ";
		cin >> kaf;
		cin.ignore(32767, '\n'); cin.clear();

    cout << "��������� >> ";
	cin >> fac;
	cin.ignore(32767, '\n'); cin.clear();
	cout << "������ >> ";
	cin >> gr;
	cin.ignore(32767, '\n'); cin.clear();

znum:
	cout << "����� �������� ������ >> ";
	cin >> nzach;
	cin.ignore(32767, '\n'); cin.clear();
	if (FindStudent(nzach) != -1) {
		cout << "�������� ���� ����� �������� ������ ��� ���������� ��� �������� ������������ �������!" << endl;
		goto znum;
	}

	cout << "��������� �������: \n";
	Zachetka zachetka;
	for (int i = 1; i < 10; i++) {
	B:cout << "������� " << i << endl;
		zachetka.count++;
		for (int j = 1; j < 11; j++) {
		input_n:
			cout << "������� >>";
			cin >> Name; cin.ignore(32767, '\n'); cin.clear(); int flag; flag = 0;
			for (int k = 0; k < j; k++) { if (zachetka.sem[i - 1].sub[k].Name == Name) flag = 1; }
			if (Name.empty() || flag == 1) {
				cout << "������������ ���� ������ ��� ������� ��� ���������� � ���� ��������" << endl;
				goto input_n;
			}
		mark_input:
			cout << "������ >>";
			cin >> mark; cin.ignore(32767, '\n'); cin.clear();
			if (mark < 3 || mark > 5) {
				cout << "������������ ���� ������ (������ 3-5)" << endl;
				goto mark_input;
			}

			Subject NewSubject = Subject(Name, mark);
			zachetka.sem[i - 1].sub[j - 1] = NewSubject;
			zachetka.sem[i - 1].count++;
			cout << "����� ���������� ������� ����� ������, ����� ������� � ���������� �������� ������� 1, ����� ��������� ���������� ������� 0: ";
			cin >> N;
			cin.ignore(32767, '\n');
			if (N == '1') { i++; goto B; }
			if (N == '0') { goto C; }
		}
	}
C:Student NewStudent; NewStudent = Student(sname, name, mname, fac, kaf, gr, nzach, bd, by, bm, py, zachetka);
	ADDstudent(NewStudent);
	system("cls");
}
int FindStudent(string s) {
	for (int i = 0; i < Size; i++) {
		if (student[i].nzach == s) {
			return i;
		}
	}
	return -1;
}
void StudentChange(int flag) {
	string zach, New, object; int fl, n, S, mark; char change;
	cout << "1. �.�.�. �������� " << endl << "2. ���� ��������" << endl << "3. ��� �����������" << endl << "4. ���������" << endl;
	cout << "5. �������" << endl << "6. ������" << endl << "7. ����� �������� ������" << endl << "8. ������ � �������" << endl << "0. ����� " << endl;
	cout << "�������� ����� �������������� �� ������ �������� >> ";
	cin >> change;  cin.ignore(32767, '\n');
	switch (change)
	{
	case '1': {
		char N;
		cout << "1. �������" << endl << "2. ���" << endl << "3. ��������" << endl;
		cout << "�������� ����� �������������� �� ������ �������� >> ";
		cin >> N;  cin.ignore(32767, '\n');
		switch (N)
		{
		case '1': {
			cout << "������� ����� ������� >>";
			cin >> New;  cin.ignore(32767, '\n');
			student[flag].sname = New; ReWriteFile(); break;
		}
		case '2': {
			cout << "������� ����� ��� >>";
			cin >> New;  cin.ignore(32767, '\n');
			student[flag].name = New; ReWriteFile(); break;
		}
		case '3': {
			cout << "������� ����� �������� >>";
			cin >> New;  cin.ignore(32767, '\n');
			student[flag].mname = New; ReWriteFile(); break;
		}
		default: {cout << "����� ������� ���"; break;}
		} break;}
	case '2': {
		char N;
		cout << "1. ���� " << endl << "2. �����" << endl << "3. ���" << endl;
		cout << "�������� ����� �������������� �� ������ �������� >> ";
		cin >> N;  cin.ignore(32767, '\n');
		switch (N)
		{
		case '1': {
		nd:cout << "������� ����� ���� >>";
			cin >> n;  cin.ignore(32767, '\n');
			if (n < 1 || n > 31) {
				cout << "������������ ���� ������" << endl;
				goto nd;
			}
			student[flag].bd = n; ReWriteFile(); break;
		}
		case '2': {
		nm:cout << "������� ����� ����� >>";
			cin >> n;  cin.ignore(32767, '\n');
			if (n < 1 || n > 12) {
				cout << "������������ ���� ������" << endl;
				goto nm;
			}
			student[flag].bm = n; ReWriteFile(); break;
		}
		case '3': {
		ny:cout << "������� ����� ��� >>";
			cin >> n;  cin.ignore(32767, '\n');
			if (n < 1900 || n > 2019 || student[flag].py <= n) {
				cout << "������������ ���� ������" << endl;
				goto ny;
			}
			student[flag].by = n; ReWriteFile(); break;
		}
		default: {cout << "����� ������� ���"; break;}
		}break;}
	case '3': {
	nyp:cout << "������� ����� ��� ����������� >>";
		cin >> n;  cin.ignore(32767, '\n');
		if (n < 1947 || n > 2019 || n <= student[flag].by) {
			cout << "������������ ���� ������" << endl;
			goto nyp;
		}
		student[flag].py = n; ReWriteFile(); break;
	}
	case '4': {
		cout << "������� ����� ��������� >>";
		cin >> New;  cin.ignore(32767, '\n');
		student[flag].fac = New; ReWriteFile(); break;
	}
	case '5': {
		cout << "������� ����� ������� >>";
		cin >> New;  cin.ignore(32767, '\n');
		student[flag].kaf = New; ReWriteFile(); break;
	}
	case '6': {
		cout << "������� ����� ������ >>";
		cin >> New;  cin.ignore(32767, '\n');
		student[flag].gr = New; ReWriteFile(); break;
	}
	case '7': {
		int N;
	N:cout << "������� ����� ����� �������� ������ >>";
		cin >> New;  cin.ignore(32767, '\n');
		N = FindStudent(New);
		if (N == -1 || N == flag) { student[flag].nzach = New; }
		else { cout << "��� ���� ������� � ����� ������� �������� ������, ������� ������ �����!"; goto N; }
		ReWriteFile();
		break;
	}
	case '8': {
		char B;
		cout << "1. �������� ������ " << endl << "2. �������� ������" << endl << "3. ������� ������ " << endl;
		cout << "�������� ��� �� ������ ������� � �������� >>";
		cin >> B;  cin.ignore(32767, '\n');
		switch (B) {
		case '1': {
			sem: cout << "������� ����� ��������, � ������� ������ �������� ������ >>";
				cin >> S; cin.ignore(32767, '\n');
				if (S - 1 > student[flag].zachetka.count || S < 1) {
					cout << "������ �������� ���, �������� ������!(1-9)" << endl;
					goto sem;
				}
			fo:cout << "������� �������� ��������, ������� ������ �������� >>";
				cin >> object; cin.ignore(32767, '\n'); fl = -1;
				for (int k = 0; k <= student[flag].zachetka.sem[S - 1].count; k++) {
					if (student[flag].zachetka.sem[S - 1].sub[k].Name == object) {
					obj: cout << "������� ����� �������� �������� >>";
						cin >> New; cin.ignore(32767, '\n'); fl = 0;
						for (int k = 0; k <= student[flag].zachetka.sem[S - 1].count; k++) { if (student[flag].zachetka.sem[S - 1].sub[k].Name == New) fl = 1; }
						if (New.empty() || flag == 1) {
							cout << "������������ ���� ������ ��� ������� ��� ���������� � ���� ��������" << endl;
							goto obj;
						}
					mark: cout << "������ >>";
						cin >> mark; cin.ignore(32767, '\n'); cin.clear();
						if (mark < 3 || mark > 5) {
							cout << "������������ ���� ������ (������ 3-5)" << endl;
							goto mark;
						}
						student[flag].zachetka.sem[S - 1].sub[k].Name = New;
						student[flag].zachetka.sem[S - 1].sub[k].mark = mark;
					}
					if (fl == -1) { cout << "�� ������� �������� � ����� ���������, ������� ������" << endl; goto fo; }
				}
				ReWriteFile();
				break;
			}
		case '2': {
			cout << "1. �������� ������ � ������������ ������� " << endl << "2. ������� ����� �������" << endl;
			cout << ">>";
			cin >> B; cin.ignore(32767, '\n');
			if (B == '1') {
			se: cout << "������� ����� ��������, � ������� ������ �������� ������ >>";
				cin >> S; cin.ignore(32767, '\n');
				if (S > student[flag].zachetka.count + 1){cout << "����� ������� ��� �� ��� ������, �������� ������"<< endl; goto se;}
				if (student[flag].zachetka.sem[S - 1].count < 10) {
				n:
					cout << "������� >>";
					cin >> object; cin.ignore(32767, '\n'); cin.clear(); fl = 0;
					for (int k = 0; k <= student[flag].zachetka.sem[S - 1].count; k++) { if (student[flag].zachetka.sem[S - 1].sub[k].Name == object) fl = 1; }
					if (object.empty() || fl == 1) {
						cout << "������������ ���� ������ ��� ������� ��� ���������� � ���� ��������" << endl;
						goto n;
					}
				m:
					cout << "������ >>";
					cin >> mark; cin.ignore(32767, '\n'); cin.clear();
					if (mark < 3 || mark > 5) {
						cout << "������������ ���� ������ (������ 3-5)" << endl;
						goto m;
					}
					n = student[flag].zachetka.sem[S - 1].count + 1;
					Subject NewSubject = Subject(object, mark);
					student[flag].zachetka.sem[S - 1].sub[n] = NewSubject;
					student[flag].zachetka.sem[S - 1].count++;
				}
				else {
					cout << "���  ����� ������ ����� ���, �������� ������ �������" << endl; goto se;
				}
			}
			if (B == '2') {
				n = student[flag].zachetka.count + 1;
				cout << "������� " << n+1 << endl;
				student[flag].zachetka.count++;
				for (int j = 0; j < 10; j++) {
				input_n:
					cout << "������� >>";
					cin >> New; cin.ignore(32767, '\n'); cin.clear(); int flag; flag = 0;
					for (int k = 0; k < j; k++) { if (student[flag].zachetka.sem[n].sub[k].Name == New) flag = 1; }
					if (flag == 1) {
						cout << "������������ ���� ������ ��� ������� ��� ���������� � ���� ��������" << endl;
						goto input_n;
					}
				mark_input:
					cout << "������ >>";
					cin >> mark; cin.ignore(32767, '\n'); cin.clear();
					if (mark < 3 || mark > 5) {
						cout << "������������ ���� ������ (������ 3-5)" << endl;
						goto mark_input;
					}
					Subject NewSubject = Subject(New, mark);
					student[flag].zachetka.sem[n].sub[j] = NewSubject;
					student[flag].zachetka.sem[n].count++;
					cout << "����� ���������� ������� ����� ������, ����� ��������� ���������� ������� 0: ";
					cin >> B;
					cin.ignore(32767, '\n');
					if (B == '0') { break;}
				}
			}
			ReWriteFile();
			break;}
		case '3': {

		s: cout << "������� ����� ��������, � ������� ������ ������� ������ >>";
			cin >> S; cin.ignore(32767, '\n');
			if (S - 1 > student[flag].zachetka.count || S - 1 < 0) {
				cout << "������ �������� ���, �������� ������!(1-9)" << endl;
				goto s;
			}
		f:cout << "������� �������� ��������, ������� ������ ������� >>";
			getline(cin, object); cin.ignore(32767, '\n'); n = 11;
			for (int k = 0; k <= student[flag].zachetka.sem[S - 1].count; k++) {
				if (student[flag].zachetka.sem[S - 1].sub[k].Name == object) n = k;
			}
			for (int k = n; k < student[flag].zachetka.sem[S - 1].count; k++) {
				student[flag].zachetka.sem[S - 1].sub[k] = student[flag].zachetka.sem[S - 1].sub[k + 1];
			}
			if (n != 11) {
				n = student[flag].zachetka.sem[S - 1].count;
				student[flag].zachetka.sem[S - 1].sub[n] = {};
				student[flag].zachetka.sem[S - 1].count--;
			}
			else {
				cout << "������ �������� ���, ������� ������"; goto f;
			}
			ReWriteFile();
			break;}
		default: {cout << "����� ������� ���";
			break;}
		}
	case '0': break;
	default: break;
	}
	}
}
void StudentWork() {
	int fyear, syear, flag, n; char c;
	cout << "�������� ���� ���������, � ������� �� ��� ����� �������� �� ����� ������:" << endl;
	cout << "�. 3 " << endl << "�. 3 � 4" << endl << "�. 5" << endl << "�. 3 � 5" << endl << "�. 4 � 5" << endl;
	sw: cout << "�������� �������, �������� �������� ����� ���������� �������� >> ";
	cin >> c;
	if (c!='�' && c!='�' && c!='�' && c!='�' && c!='�'){
		cout << "������ ������� ���" << endl; goto sw;
	}
	cout << "������� �������� ����� ��������, ����� ������� ����� ������������ �����, ����� ������ {���� ����} >> ";
	cin >> fyear >> syear;
	cin.ignore(32767, '\n'); 
	switch (c)
	{
	case '�': {
		n = 0;
		for (int i = 0; i < Size; i++) {
			flag = 0;
			if (student[i].by >= fyear && student[i].by <= syear) {
				for (int j = 0; j <= student[i].zachetka.count; j++) {
					for (int k = 0; k <= student[i].zachetka.sem[j].count; k++) {
						if (student[i].zachetka.sem[j].sub[k].mark == 3) {
							flag++;
						}
					}
				}
				if (flag == 0) {
					student[i].print();
					cout << endl;
					n++;
				}
			}
		}
		if (n == 0) {
			cout << "���������, ���������� ������� �� �������" << endl;
		}
		system("pause"); system("cls");
		break;
	}
	case '�': {
		n = 0;
		for (int i = 0; i < Size; i++) {
			flag = 0;
			if (student[i].by >= fyear && student[i].by <= syear) {
				for (int j = 0; j <= student[i].zachetka.count; j++) {
					for (int k = 0; k <= student[i].zachetka.sem[j].count; k++) {
						if (student[i].zachetka.sem[j].sub[k].mark == 3 || student[i].zachetka.sem[j].sub[k].mark == 4) {
							flag++;
						}
					}
				}
				if (flag == 0) {
					student[i].print();
					cout << endl;
					n++;
				}
			}
		}
		if (n == 0) {
			cout << "���������, ���������� ������� �� �������" << endl;
		}
		system("pause"); system("cls");
		break;
	}
	case '�': {
		n = 0;
		for (int i = 0; i < Size; i++) {
			flag = 0;
			if (student[i].by >= fyear && student[i].by <= syear) {
				for (int j = 0; j <= student[i].zachetka.count; j++) {
					for (int k = 0; k <= student[i].zachetka.sem[j].count; k++) {
						if (student[i].zachetka.sem[j].sub[k].mark == 5) {
							flag++;
						}
					}
				}
				if (flag == 0) {
					student[i].print();
					cout << endl;
					n++;
				}
			}
		}
		if (n == 0) {
			cout << "���������, ���������� ������� �� �������" << endl;
		}
		system("pause"); system("cls");
		break;
	}
	case '�': {
		n = 0;
		for (int i = 0; i < Size; i++) {
			flag = 0;
			if (student[i].by >= fyear && student[i].by <= syear) {
				for (int j = 0; j <= student[i].zachetka.count; j++) {
					for (int k = 0; k <= student[i].zachetka.sem[j].count; k++) {
						if (student[i].zachetka.sem[j].sub[k].mark == 3 || student[i].zachetka.sem[j].sub[k].mark == 5) {
							flag++;
						}
					}
				}
				if (flag == 0) {
					student[i].print();
					cout << endl;
					n++;
				}
			}
		}
		if (n == 0) {
			cout << "���������, ���������� ������� �� �������" << endl;
		}
		system("pause"); system("cls");
		break;
	}
	case '�': {
		n = 0;
		for (int i = 0; i < Size; i++) {
			flag = 0;
			if (student[i].by >= fyear && student[i].by <= syear) {
				for (int j = 0; j <= student[i].zachetka.count; j++) {
					for (int k = 0; k <= student[i].zachetka.sem[j].count; k++) {
						if (student[i].zachetka.sem[j].sub[k].mark == 5 || student[i].zachetka.sem[j].sub[k].mark == 4) {
							flag++;
						}
					}
				}
				if (flag == 0) {
					student[i].print();
					cout << endl;
					n++;
				}
			}
		}
		if (n == 0) {
			cout << "���������, ���������� ������� �� �������" << endl;
		}
		system("pause"); system("cls");
		break;
	}
	default: { cout << "������ ������� ���"; break;}
	}
}
void ADDstudent(Student NewStudent) {
	Student* newStudent = new Student[Size + 1];
	for (int i = 0; i < Size; i++) {
		newStudent[i] = student[i];
	}
	newStudent[Size] = NewStudent;
	delete[] student;
	student = newStudent;
	Size++;
}
void DeleteStudent(int Delete) {
	Size--;
	Student* newStudent = new Student[Size];
	for (int i = 0; i < Delete; i++) {
		newStudent[i] = student[i];
	}
	for (int i = Delete; i < Size; i++) {
		newStudent[i] = student[i + 1];
	}
	delete[] student;
	student = newStudent;
}

void addFile(){
	
	fstream fout;
    fout.open("Students.txt",ios_base::app);
    if (fout){
            
            fout << endl << student[Size-1].sname << " " << student[Size-1].name << " " << student[Size-1].mname << " " << student[Size-1].fac << " " << student[Size-1].kaf << " ";
			fout << student[Size-1].gr << " " << student[Size-1].nzach << " " << student[Size-1].bd << " " << student[Size-1].bm << " " << student[Size-1].by << " " << student[Size-1].py << endl ;
			fout << student[Size-1].zachetka.count;
			for (int i=0; i <= student[Size-1].zachetka.count; i++){
				fout << " " << student[Size-1].zachetka.sem[i].count;
				for ( int j=0; j <= student[Size-1].zachetka.sem[i].count; j++){
					fout << " " << student[Size-1].zachetka.sem[i].sub[j].Name << " " << student[Size-1].zachetka.sem[i].sub[j].mark;
				}
			}
    }
    fout.close();
}

void readFile(){
	
	Student Newstudent;
	fstream fin;
	fin.open("Students.txt");
    if (fin.peek() != EOF){
	while (!fin.eof()){
	fin >> Newstudent.sname >> Newstudent.name >> Newstudent.mname >> Newstudent.fac >> Newstudent.kaf;
	fin >> Newstudent.gr >> Newstudent.nzach >> Newstudent.bd >> Newstudent.bm >> Newstudent.by >> Newstudent.py;
	fin >> Newstudent.zachetka.count;
			for (int i=0; i <= Newstudent.zachetka.count; i++){
				fin >> Newstudent.zachetka.sem[i].count;
				for ( int j=0; j <= Newstudent.zachetka.sem[i].count; j++){
					fin >> Newstudent.zachetka.sem[i].sub[j].Name >> Newstudent.zachetka.sem[i].sub[j].mark;
				}
			}
	ADDstudent(Newstudent);}}
	fin.close();
}

void ReWriteFile(){
	
	fstream fout;
    fout.open("Students.txt",ios_base::out);
    if (fout){
        for ( int i =0; i < Size; i++){
            fout << endl << student[i].sname << " " << student[i].name << " " << student[i].mname << " " << student[i].fac << " " << student[i].kaf << " ";
			fout << student[i].gr << " " << student[i].nzach << " " << student[i].bd << " " << student[i].bm << " " << student[i].by << " " << student[i].py << endl ;
			fout << student[i].zachetka.count;
			for (int k=0; k <= student[i].zachetka.count; k++){
			    fout << " " << student[i].zachetka.sem[k].count;
				for ( int j=0; j <= student[i].zachetka.sem[k].count; j++){
				    fout << " " << student[i].zachetka.sem[k].sub[j].Name << " " << student[i].zachetka.sem[k].sub[j].mark;
				}
			}
		}
    }
    fout.close();
}


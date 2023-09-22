
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
string* Files = new string[3];
int FileC = 0;
typedef struct {
	string name;
	string athor;
	string text;
	int year;
}Info;

void add()
{

	Info song;
	cout << "������� ��������: " << endl;
	string song_text;
	Files[FileC] = song_text;
	Files++;
	int choise;
	cin.sync();
	getline(cin, song.name);
	cout << "������� ������: ";
	cin >> song.athor;
	cout << "������� ��� �����: ";
	cin >> song.year;
	cout << "��� �� ��������� ����� �� ����� �������� 1\n��� �� �������� ����� ������ ������� 2\n��� �����: ";
	cin >> choise;
	if (choise == 1) {
		ifstream file;
		cout << "������� �������� �����: ";
		string fileName;
		cin >> fileName;
		file.open(fileName + ".TXT");
		string line;
		if (file.is_open()) {
			int i = 0;
			string arr[3] = { "��������:","�����:","�����:" };
			while (file >> line)
			{

				for (string word : arr)
				{
					if (word == line) {
						i++;
					}
					else {
						continue;
					}

				}

			}
			if (i == 3) {
				cout << "����� �� ����� �������� � �������";
			}
			else {
				cout << "������ � �����.";
			}
			file.close();
		}
		else {
			cout << "\n������";
		}



	}
	if (choise == 2) {
		cin.ignore();
		cout << "������� ����� ����� (��� �� ��������� ������ ������� enter )";
		while (true) {
			getline(cin, song_text);
			{
				if (song_text.empty()) {
					break;
				}
			}
			song.text += song_text + "\n";
		}
		cout << "���� ���������� �����";
		ofstream file;
		file.open(song.name + ".TXT");
		if (file.is_open()) {
			file << "���������� � �����: ";
			file << "\n��������: " << song.name;
			file << "\n�����: " << song.athor;
			file << "\n���: " << song.year;
			file << "\n";
			file << "�����: ";
			file << "\n";
			file << song.text;

		}
		else {
			cout << "������";
		}
		file.close();
	}

}


void Del()
{
	string text;
	cout << "������� �������� ����� ��� ��������: ";
	cin >> text;
	ifstream file;
	file.open(text + ".TXT");
	if (file.is_open())
	{
		file.close();
		string file_name = text + ".TXT";
		remove(file_name.c_str());
		cout << "���� � ������ ��� ������.";

	}
	else {
		cout << "������.";
	}

}


void redacting(string text) {
	string line;
	string FileName = text + ".TXT";
	remove(FileName.c_str());
	ofstream NewFile(FileName);
	fstream TestFile;
	TestFile.open("TestFile.TXT");
	while (getline(TestFile, line)) {

		NewFile << line;
		NewFile << "\n";

	}
	TestFile.close();
	NewFile.close();
	remove("TestFile.TXT");

}


void Redact() {
	string text;
	cout << "����� ����� ����� �� ������ ��������? ";
	cin >> text;
	fstream File;
	ofstream TestFile("TestFile.TXT");
	File.open(text + ".TXT");
	Info song;
	string line;
	bool live = true;
	if (File.is_open()) {

		while (getline(File, line)) {
			if (live == false) {
				break;
			}
			if (line.find("�����:") != std::string::npos)
			{
				cin.ignore();
				cout << "������� ����� ����� (��� �� ��������� ������ ������� enter ): " << endl;
				string song_text;

				while (live) {
					getline(cin, song_text);
					{
						if (song_text.empty()) {
							TestFile << "�����:";
							TestFile << "\n";
							TestFile << song.text;
							live = false;
							break;
						}
					}
					song.text += song_text + "\n";
				}
			}
			else {
				TestFile << line << endl;
			}
		}
		TestFile.close();
		File.close();
		redacting(text);


	}

}

void PrintMusic() {
	cout << "����� ����� ����� �� ������ ���������� �� ������?: ";
	string music;
	cin >> music;
	fstream File;
	string line;
	bool live = true;
	bool con = false;
	File.open(music + ".TXT");
	if (File.is_open()) {
		while (getline(File, line)) {
			if (line.find("�����:") != std::string::npos)
			{
				con = true;
			}
			else {
				if (con == true) {
					cout << line;
					cout << "\n";
				}
				else {
					continue;
				}
			}
		}
	}
	File.close();
}

void Find()
{
	int n = 0;
	cout << "������� ���������� �����: ";
	cin >> n;
	cout << endl;
	string* songs = new string[n];
	string song;
	for (int i = 0; i < n; i++)
	{
		cout << "�������� " << i << " ����� (�����): ";
		cin >> song;
		songs[i] = song;
		cout << endl;
	}
	string find_word;
	int q = 0;
	cout << "\n�� ������ ����� ��� ������ ����� ����������� ����� \n1)�� �����\n2)�� ������." << endl;
	cin >> q;
	if (q == 1) {
		cout << "������� �����: ";
		cin.ignore();
		getline(cin, find_word);
		string line;
		for (int i = 0; i < n; i++) {
			fstream File;
			File.open(songs[i] + ".TXT");
			while (File >> line)
			{
				if (line == find_word)
				{
					cout << "����� ���� ������� � ����� " << songs[i];
					File.close();
					File.open(songs[i] + ".TXT");
					while (getline(File, line)) {
						cout << line;
						cout << endl;
					}
					break;
				}
			}
			cout << "\n";

		}

	}
	else {

		string line;
		cout << "������� ������: ";
		cin >> find_word;
		cout << endl;
		for (int i = 0; i < n; i++) {
			fstream File;
			File.open(songs[i] + ".TXT");
			while (getline(File, line))
			{
				if (line == "�����: " + find_word)
				{
					cout << "����� ��� ������ ����� " << songs[i] << endl;
					File.close();
					File.open(songs[i] + ".TXT");
					while (getline(File, line)) {
						cout << line;
						cout << endl;
					}
					break;

				}

			}


		}
		cout << endl;
	}



}

int main()
{
	setlocale(LC_ALL, "rus");
	int choise;
	Info* info = new Info[5];

	while (true) {

		cout << endl;
		cout << "\t\t���������� ������� ������� �����\n1)��������\n2)�������\n3)��������\n4)����������\n5)�����";
		cout << endl;

		cin >> choise;

		switch (choise) {
		case 1:
		{
			cin.ignore();
			add();
			break;

		}
		case 2:
		{
			Del();
			break;

		}
		case 3: {
			Redact();
		}
		case 4: {
			PrintMusic();
		}
		case 5:
		{

			Find();



		}
		}
	}
}








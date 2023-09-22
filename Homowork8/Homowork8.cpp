
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
	cout << "Введите название: " << endl;
	string song_text;
	Files[FileC] = song_text;
	Files++;
	int choise;
	cin.sync();
	getline(cin, song.name);
	cout << "Введите автора: ";
	cin >> song.athor;
	cout << "Введите год песни: ";
	cin >> song.year;
	cout << "Что бы загрузить песню из файла нажимите 1\nЧто бы записать песню вручну нажмите 2\nВаш выбор: ";
	cin >> choise;
	if (choise == 1) {
		ifstream file;
		cout << "Введите название файла: ";
		string fileName;
		cin >> fileName;
		file.open(fileName + ".TXT");
		string line;
		if (file.is_open()) {
			int i = 0;
			string arr[3] = { "Название:","Автор:","Текст:" };
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
				cout << "Текст из песни сохранен в каталог";
			}
			else {
				cout << "Ошибка в файле.";
			}
			file.close();
		}
		else {
			cout << "\nОшибка";
		}



	}
	if (choise == 2) {
		cin.ignore();
		cout << "Введите текст песни (Что бы закончить запись нажмите enter )";
		while (true) {
			getline(cin, song_text);
			{
				if (song_text.empty()) {
					break;
				}
			}
			song.text += song_text + "\n";
		}
		cout << "идет сохранение файла";
		ofstream file;
		file.open(song.name + ".TXT");
		if (file.is_open()) {
			file << "Информация о песни: ";
			file << "\nНазвание: " << song.name;
			file << "\nАвтор: " << song.athor;
			file << "\nГод: " << song.year;
			file << "\n";
			file << "Текст: ";
			file << "\n";
			file << song.text;

		}
		else {
			cout << "Ошибка";
		}
		file.close();
	}

}


void Del()
{
	string text;
	cout << "Введите название песни для удаления: ";
	cin >> text;
	ifstream file;
	file.open(text + ".TXT");
	if (file.is_open())
	{
		file.close();
		string file_name = text + ".TXT";
		remove(file_name.c_str());
		cout << "Файл с песней был удален.";

	}
	else {
		cout << "Ошибка.";
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
	cout << "Текст какой песни вы хотите изменить? ";
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
			if (line.find("Текст:") != std::string::npos)
			{
				cin.ignore();
				cout << "Введите текст песни (Что бы закончить запись нажмите enter ): " << endl;
				string song_text;

				while (live) {
					getline(cin, song_text);
					{
						if (song_text.empty()) {
							TestFile << "Текст:";
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
	cout << "Текст какой песни вы хотите отобразить на экране?: ";
	string music;
	cin >> music;
	fstream File;
	string line;
	bool live = true;
	bool con = false;
	File.open(music + ".TXT");
	if (File.is_open()) {
		while (getline(File, line)) {
			if (line.find("Текст:") != std::string::npos)
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
	cout << "Введите количевсто песен: ";
	cin >> n;
	cout << endl;
	string* songs = new string[n];
	string song;
	for (int i = 0; i < n; i++)
	{
		cout << "Название " << i << " песни (файла): ";
		cin >> song;
		songs[i] = song;
		cout << endl;
	}
	string find_word;
	int q = 0;
	cout << "\nПо какому слову или автору будет проводиться поиск \n1)По слову\n2)По автору." << endl;
	cin >> q;
	if (q == 1) {
		cout << "введите слово: ";
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
					cout << "Слово было найдено в песни " << songs[i];
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
		cout << "Введите автора: ";
		cin >> find_word;
		cout << endl;
		for (int i = 0; i < n; i++) {
			fstream File;
			File.open(songs[i] + ".TXT");
			while (getline(File, line))
			{
				if (line == "Автор: " + find_word)
				{
					cout << "Автор был найден песни " << songs[i] << endl;
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
		cout << "\t\tПриложение католог текстов песен\n1)Добавить\n2)Удалить\n3)Изменить\n4)Отобразить\n5)Поиск";
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








#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/types.h>
#include <fcntl.h> 
#include <string>
#include <Windows.h>
#pragma warning(disable : 4996)

using namespace std;

const string NAMES[5] = { "Cray", "Dell", "Hewlett-Packard", "IBM", "Sequent" };
const string DISPLAY_TYPES[3] = { "IPS", "TN", "OLED" };
const float DISPLAY_SIZES[5] = { 15.6F, 19.5F, 21.5F, 23.8F, 24.5F };
const int CAPACITIES[3] = { 512, 1024, 2048 };
const int RAMs[3] = { 2048, 4096, 8192 };

struct Computer
{
	string name;
	string displayType;
	float displaySize = 0;
	float frequency = 0;
	unsigned int price = 0;
	unsigned int ram = 0;
	unsigned int capacity = 0;

	void generateInf()
	{
		name = NAMES[rand() % 5];
		displayType = DISPLAY_TYPES[rand() % 3];
		displaySize = DISPLAY_SIZES[rand() % 5];
		capacity = CAPACITIES[rand() % 3];
		ram = RAMs[rand() % 3];
		price = rand() % 401 + 400;
		frequency = float(int(rand()) % 23 + 18) / 10;
	}

	void getInf()
	{
		cout << name << "\nPrice: " << price << "$\nDisplay size: " << displaySize << "\"\nDisplay type: " << displayType
			<< "\nRAM: " << ram << " Mb\nHDD: " << capacity << " Gb\nProcessor frequency: " << frequency << " GHz\n";
	}
};

size_t getFileSize(FILE* file)
{
	size_t sizeOfFile;

	fseek(file, 0L, SEEK_END);
	sizeOfFile = ftell(file);
	fseek(file, 0L, SEEK_SET);
	return sizeOfFile;
}

void output(char path[])
{
	// Записываем информацию о десяти компьютерах в файл
	const int AMOUNT = 10;
	Computer* computers = new Computer[AMOUNT];

	for (size_t i = 0; i < AMOUNT; i++)
	{
		computers[i].generateInf();
	}

	FILE* f_out = fopen(path, "wb");

	fwrite(computers, sizeof(Computer), AMOUNT, f_out);
	fclose(f_out);
	delete[] computers;
	computers = nullptr;

	system("cls");
	cout << "Information has been written\n\n";
}

void input(char path[])
{
	// Читаем информацию из файла и выводим на консоль
	system("cls");

	FILE* f_in = fopen(path, "rb");
	size_t fileSize = getFileSize(f_in);
	Computer* computers = new Computer[fileSize / sizeof(Computer)], bestComputer;

	fread(computers, sizeof(Computer), fileSize / sizeof(Computer), f_in);
	for (size_t i = 0; i < fileSize / sizeof(Computer); i++)
	{
		(computers + i)->getInf();
		cout << endl;
		if ((computers + i)->frequency > bestComputer.frequency && (computers + i)->ram > RAMs[0])
			bestComputer = *(computers + i);
	}
	cout << "Best computer:\n";
	bestComputer.getInf();
	cout << endl;

	fclose(f_in);
}

void lowLevel()
{
	char path[] = "C:\\Users\\User\\Desktop\\Computers.bin";
	int choice = 0;

	while (true)
	{
		cout << "Choose operation:\n1 - to read information \t2 - to write information\t else - to exit\n";
		cin >> choice;

		if (choice == 1)
			input(path);
		else if (choice == 2)
			output(path);
		else break;
	}
}

void writeLine(string path, string processedLine = "")
{
	/*FILE* f_out = fopen(path, "wb");
	string line = processedLine, * ptr = &line;

	if (line == "")
	{
		cout << "Введите строку: ";
		cin >> line;
	}

	fwrite(ptr, sizeof(string), 1, f_out);
	fclose(f_out);*/

	ofstream out(path, ios::out | ios::binary);
	size_t length = 0;

	if (processedLine == "")
	{
		cout << "Введите строку: ";
		cin >> processedLine;
		cout << endl;
	}
	length = processedLine.length() + 1;
	out.write((char*)&length, sizeof(length));
	out.write((char*)processedLine.c_str(), length);

	out.close();
}

string readLine(string path)
{
	/*FILE* f_in = fopen(path, "rb");
	string line = "", * ptr = &line;
	
	fread(ptr, sizeof(string), 1, f_in);
	fclose(f_in);

	cout << endl << "Полученная строка: " << line << endl << endl;
	for (size_t i = 0; i < line.length(); i++)
	{
		if (line[i] == 'ф' || line[i] == 'Ф')
			line[i] = 'д';
	}
	cout << "Обработанная строка: " << line << endl;*/

	ifstream in(path, ios::in | ios::binary);
	string line = "";
	size_t length = 0;
	
	in.read((char*)&length, sizeof(length));
	char* buf = new char[length];
	in.read((char*)buf, length);
	in.close();

	line = buf;
	delete[] buf;
	buf = nullptr;

	cout << "Полученная строка: " << line << endl << endl;
	for (size_t i = 0; i < line.length(); i++)
	{
		if (line[i] == 'ф' || line[i] == 'Ф')
			line[i] = 'д';
	}
	cout << "Обработанная строка: " << line << endl;

	return line;
}

void mediumLevel()
{
	string path = "C:\\Users\\User\\Desktop\\Symbols.bin";

	writeLine(path); // Запись последовательности символов в файл
	
	writeLine(path, readLine(path)); // Считывание символов, обработка и снова запись в файл
}

unsigned short currentDay = 14;
unsigned short currentMonth = 5;
unsigned short currentYear = 2020;

struct Date
{
	unsigned short day = 0;
	unsigned short month = 0;
	unsigned short year = 0;
};

struct Customer
{
	string fullname;
};

void highLevel()
{

}

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	//lowLevel();
	mediumLevel();
}
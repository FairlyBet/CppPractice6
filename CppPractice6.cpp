#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/types.h>
#include <fcntl.h> 
#include <string>
#pragma warning(disable : 4996)

using namespace std;

const string NAMES[5] = { "Cray", "Dell", "Hewlett-Packard", "IBM", "Sequent" };
const string DISPLAY_TYPES[3] = { "IPS", "TN", "OLED" };
const float DISPLAY_SIZES[5] = { 15.6, 19.5, 21.5, 23.8, 24.5 };
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

size_t getFileSize(FILE* fp)
{
	size_t save_pos, size_of_file;

	save_pos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	size_of_file = ftell(fp);
	fseek(fp, save_pos, SEEK_SET);
	return size_of_file;
}

void output(char path[])
{
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

void mediumLevel()
{
	char path[] = "C:\\Users\\User\\Desktop\\Symbols.bin";
	const unsigned short AMOUNT_OF_SYMBOLS = 60;
	wchar_t line[AMOUNT_OF_SYMBOLS];
	cout << "Введите строку: ";
	wcin >> line;

	FILE* f_out = fopen(path, "wb"), * f_in = fopen(path, "rb");
	fwrite(line, sizeof(wchar_t[AMOUNT_OF_SYMBOLS]), 1, f_out);
	fclose(f_out);

	fread(line, sizeof(wchar_t[AMOUNT_OF_SYMBOLS]), 1, f_in);
	fclose(f_in);

	cout << endl << "Полученная строка: ";
	wcout << line;
}

void highLevel()
{

}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	//lowLevel();
	mediumLevel();
}
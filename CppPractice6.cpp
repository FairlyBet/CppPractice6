#include <iostream>
#include <fstream>
#include <ctime>

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
		price = rand() % 401 + 300;
		frequency = (float(rand() % 23 + 18) / 10);
	}

	void getInf()
	{
		cout << name << "\nPrice: " << price << "$\nDisplay size: " << displaySize << "\"\nDisplay type: " << displayType 
			<< "\nRAM: " << ram << " Mb\nHDD: " << capacity << " Gb\nProcessor frequency: " << frequency << " GHz\n";
	}
};

void inputInf(ifstream& in, Computer computer)
{
	in.read((char*)&computer, sizeof(computer));
}

void outputInf(ofstream& out, Computer computer)
{
	out.write((char*)&computer, sizeof(computer));
}

void lowLevel()
{
	string path = "C:\\Users\\User\\Desktop\\Computers.bin";

	Computer computer1, computer2;	

	ofstream out(path,ios ::binary | ios::out );
	if (out.is_open())
	{
		computer1.generateInf();
		computer1.getInf();

		out.write((char*) &computer1, sizeof(computer1));

		out.close();
	}

	/*ifstream in(path, ios::binary | ios::in);
	if (in.is_open())
	{
		in.read((char*)&computer2, sizeof(Computer));
		computer2.getInf();;

		in.close();
	}*/
}

void mediumLevel()
{
	string path = "C:\\Users\\User\\Desktop\\Symbols.bin"; //line = "";
	u16string line;
	//cin >> line;

	ifstream in(path, ios::in | ios::binary);
	if (in.is_open())
	{
		in.read(reinterpret_cast<char*>(&line), sizeof(line));
		in.close();
	}	

	/*ofstream out(path, ios::out | ios::binary);
	if (out.is_open())
	{
		out.write(reinterpret_cast<char*>(&line), sizeof(line));
		out.close();
	}*/
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	mediumLevel();
}

//#include <iostream>
//#include <fstream>      // std::fstream
//
//using namespace std;
//
//typedef struct
//{
//	int year;
//	string fio;
//} Anketa;
//
//int main()
//{
//	Anketa anketa;
//	anketa.year = 1643;
//	anketa.fio = "Isaac John Newton";
//
//	// *** Writing ***
//	fstream fs;
//	fs.open("anketa.dat", std::fstream::out | std::fstream::binary);
//
//	fs.write((char*)&anketa.year, sizeof(int));
//	size_t len = anketa.fio.length();
//	fs.write((char*)&len, sizeof(size_t));
//	fs.write(anketa.fio.data(), len);
//
//	fs.close();
//
//	// *** Reading *** 
//	fs.open("anketa.dat", std::fstream::in | std::fstream::binary);
//
//	fs.read((char*)&anketa.year, sizeof(int));
//	fs.read((char*)&len, sizeof(size_t));
//	char buf[len + 1];
//	fs.read(buf, len);
//	buf[len] = 0;
//	anketa.fio = buf;
//
//	fs.close();
//
//	cout << anketa.year << " " << anketa.fio << endl;
//
//	return 0;
//}
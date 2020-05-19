#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

const std::string FNAME = "phonebook";

struct bookRecord {
	std::string name;
	std::string famil;
	std::string phone;
	std::string note;
	std::string adress;
	std::string dro;
};

std::vector<bookRecord> recs;

bool loadFromFile(std::string fn)
{
	std::ifstream fin(fn);

	if (fin.bad() || !fin.is_open())
	{
		fin.close();
		return false;
	}

	recs.clear();

	while (!fin.eof())
	{
		bookRecord t;
		if (!getline(fin, t.name) ||
			!getline(fin, t.famil) ||
			!getline(fin, t.note) ||
			!getline(fin, t.phone) ||
			!getline(fin, t.dro) ||
			!getline(fin, t.adress))
			break;
		recs.push_back(t);
	}

	fin.close();
	return true;
}

bool saveToFile(std::string fn)
{
	std::ofstream fout(fn);

	if (fout.bad() || !fout.is_open())
	{
		fout.close();
		return false;
	}

	for (int i = 0; i < recs.size(); i++)
	{
		fout << recs[i].name << std::endl
			<< recs[i].famil << std::endl
			<< recs[i].dro << std::endl
			<< recs[i].phone << std::endl
			<< recs[i].note << std::endl
			<< recs[i].adress << std::endl;
	}

	fout.close();
	return true;
}

void writeRecord(int i)
{
	std::cout << i + 1 << "|" << std::left << std::setw(20) << recs[i].name << "|" << std::setw(20) << recs[i].famil << " | " << std::setw(20) << recs[i].phone << " | " << std::setw(20) << recs[i].adress << " | " << std::setw(20) << recs[i].dro << " | ";
	int sz = 520 - recs[i].name.size() - recs[i].phone.size() - recs[i].adress.size() - recs[i].dro.size() - recs[i].famil.size();
	if (recs[i].note.size() > sz)
		std::cout << recs[i].note.substr(0, sz) << "...";
	else std::cout << recs[i].note;
	std::cout << std::endl;
}

int findRecord()
{
	int sel;

	std::cout << "Вам нужно найти запись:" << std::endl
		<< "1. По порядковому номеру" << std::endl
		<< "2. По имени, номеру телефона или заметке" << std::endl
		<< "\n\n > ";

	std::cin >> sel;
	std::cout << std::endl;

	if (sel == 2)
	{
		std::string val;

		std::cout << "Введите значение для поиска: ";

		std::cin.ignore();
		getline(std::cin, val);

		for (int i = 0; i < recs.size(); i++)
			if (recs[i].name.find(val) != recs[i].name.npos ||
				recs[i].note.find(val) != recs[i].note.npos ||
				recs[i].phone == val || recs[i].adress.find(val) != recs[i].adress.npos)
				writeRecord(i);

		std::cout << std::endl;
	}

	int number = 0;
	bool fail = false;

	std::cout << "Введите порядковый номер записи: ";
	std::cin >> number;
	std::cin.ignore();

	return (number < 1 || number > recs.size()) ? -1 : number - 1;
}

void writeRecords()
{
	std::cout << "Всего " << recs.size() << " записей:" << std::endl;

	for (int i = 0; i < recs.size(); i++)
		writeRecord(i);

	std::cin.get();
}

void addRecord()
{
	bookRecord r;
	std::cout << "\n\n\t\t[ Добавление новой записи ]\n\n";

	std::cout << "Введите номер телефона: ";
	getline(std::cin, r.phone);
	std::cout << "Введите имя: ";
	getline(std::cin, r.name);
	std::cout << "Введите фамилию: ";
	getline(std::cin, r.famil);
	std::cout << "Введите дату рождения: ";
	getline(std::cin, r.dro);
	std::cout << "Введите адрес: ";
	getline(std::cin, r.adress);
	std::cout << "Напишите примечание к записи: ";
	getline(std::cin, r.note);

	recs.push_back(r);
	std::cout << "Новая запись с порядковым номером "
		<< recs.size() << " добавлена!" << std::endl;
	std::cin.get();
}

void editRecord()
{
	std::cout << "\n\n\t\t[ Изменение записи ]\n\n";

	int id = findRecord();
	if (id == -1)
	{
		addRecord();
		return;
	}
	std::string temp = "";

	std::cout << "(чтобы оставить поле без изменений, просто нажмите Ввод)\n\n";

	std::cout << "Введите номер телефона: ";
	getline(std::cin, temp);
	if (temp.size() > 0)
		recs[id].phone = temp;
	std::cout << "Введите имя записи: ";
	getline(std::cin, temp);
	if (temp.size() > 0)
		recs[id].name = temp;
	std::cout << "Введите фамилию: ";
	getline(std::cin, temp);
	if (temp.size() > 0)
		recs[id].famil = temp;
	std::cout << "Введите адрес: ";
	getline(std::cin, temp);
	if (temp.size() > 0)
		recs[id].adress = temp;
	std::cout << "Введите дату рождения: ";
	getline(std::cin, temp);
	if (temp.size() > 0)
		recs[id].dro
		= temp;
	std::cout << "новое примечание: " << std::endl;
	getline(std::cin, temp);
	if (temp.size() > 0)
		recs[id].note = temp;

	std::cout << "запись изменена" << std::endl;
	std::cin.get();
}

void deleteRecord()
{
	std::cout << "\n\n\t\t[ Изменение записи ]\n\n";

	char ans = 'n';
	int id = findRecord();
	if (id == -1)
	{
		std::cout << "удаление не удалось!" << std::endl;
		return;
	}

	std::cout << std::endl;
	writeRecord(id);
	std::cout << std::endl;
	std::cout << "Точно? (да-1   нет-2)? ";
	std::cin.get(ans);

	if (ans == '1')
	{
		recs.erase(recs.begin() + id);
		std::cout << "порядковый номер записи "
			<< id + 1 << " !удалено!" << std::endl
			<< "Все порядковые номера записей сдвинулись" << std::endl;
		std::cin.ignore();
		std::cin.get();
	}
}

bool thinkMenu()
{
	int sel;

	std::cout << "\n\n\t\t[ Главное меню ]\n\n";
	std::cout << "(1)просмотр записей (" << recs.size() << ")" << std::endl
		<< "(2)добавить запись" << std::endl
		<< "(3)редактировать запись" << std::endl
		<< "(4)yдалить запись" << std::endl
		<< "(5)cохранить телефонную книжку" << std::endl
		<< "(6)cохранить и выйти" << "\n\n > ";

	std::cin >> sel;
	std::cin.ignore();
	std::cout << std::endl;

	switch (sel)
	{
	case 1: writeRecords(); break;
	case 2: addRecord(); break;
	case 3: editRecord(); break;
	case 4: deleteRecord(); break;
	case 5:
		std::cout << (saveToFile(FNAME) ? "cохранили" : "Ошибка сохранения") << std::endl;
		std::cin.get();
		break;
	case 6: return false; break;
	default: break;
	}

	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	loadFromFile(FNAME);

	while (thinkMenu()) {};

	bool doTryAgain = true;
	while (!saveToFile(FNAME) && doTryAgain)
	{
		std::cout << "\n\n\t\t[ Внимание! ]\n\n"
			<< "Возникла ошибка при сохранении файла телефонной книжки: "
			<< FNAME << "\nХотите попробовать сохранить еще раз (да-1   нет-2)? ";
		char ans = 'n';
		std::cin.get(ans);
		doTryAgain = (ans == '1');
	}

	return 0;
}

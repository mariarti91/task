#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

std::string getErrorMessage(int code)
{
	switch(code)
	{
		case 0:
			return "Так и должно быть";
		case -1:
			return "Для запуска программы введите команду ./quest.bin [входной файл] [выхдной файл]";
		case -2:
			return "Не удается получить доступ к файлу с входными данными";
		case -3:
			return "Не удается получить доступ к файлу для вывода результата";
		default:
			return "Неизвестная ошибка";
	}
}

struct less_second {
    typedef std::pair<std::string, int> type;
    bool operator ()(type const& a, type const& b) const {
        return a.second > b.second;
    }
};

int main(int argc, char** argv)
{
	std::setlocale(LC_ALL, "Russian");
	if(argc != 3)
	{
		printf("%s\n", getErrorMessage(-1).c_str());
		return -1;
	}

	std::ifstream fInput;
	fInput.open(argv[1]);
	if(!fInput)
	{
		printf("%s\n", getErrorMessage(-2).c_str());
		return -2;
	}

	std::ofstream fOutput;
	fOutput.open(argv[2]);
	if(!fOutput)
	{
		printf("%s\n", getErrorMessage(-3).c_str());
		return -3;
	}

	std::map <std::string, int> *counters = new std::map <std::string, int>();
	std::map<std::string, int>::iterator i;
	std::string word;
	while(fInput >> word)
	{
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		word.erase(std::remove_if(word.begin(), word.end(), [](char c) {return !std::isalpha(c);}), word.end());
		i = counters->find(word);
		if(i == counters->end())
		{
			counters->insert({word, 1});
		}
		else
		{
			++i->second;
		}
	}	
	fInput.close();

	std::vector<std::pair<std::string, int>> *buf = new std::vector<std::pair<std::string, int>>(counters->begin(), counters->end()); 
	counters->clear();
	delete counters;
	sort(buf->begin(), buf->end(), less_second());
	for(std::vector<std::pair<std::string, int>>::iterator i = buf->begin(); i != buf->end(); ++i)
	{
		fOutput << i->second << " " << i->first << '\n';
	}
	fOutput.close();
	buf->clear();
	delete buf;
	return 0;
}

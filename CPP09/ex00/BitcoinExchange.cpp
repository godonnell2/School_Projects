#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	get_data();
}

BitcoinExchange::~BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	(void)other;
	return *this;
}

// iss: input string stream é uma forma mais simples de lidar com strings
//  if (!std::getline(iss, date, ','): iss é tudo antes da "," e é armazenado em date
//  !(iss >> btc_data)): o que vem depois da "," é armazenado em btc_data.

void BitcoinExchange::get_data() {
	std::ifstream file("data.csv");
	if (!file.is_open()) {
		throw std::runtime_error("Error data.csv: file not found");
	}

	std::string line;
	std::getline(file, line);
	if (line != "date,exchange_rate") {
		throw std::runtime_error("Error: invalid data.csv file format");
	}

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		double btc_data;

		if (!std::getline(iss, date, ',') || !(iss >> btc_data)) {
			std::cerr << "Error: invalid data format in data.csv" << std::endl;
			continue;
		}
		_data[date] = btc_data;
	}
	file.close();
}

//std::remove reorganiza os espaços da string e retorna um ponteiro para o primeiro espaço
//str.erase apaga os espaços desde o primeiro até ao final da string.

void removeSpaces(std::string &str) {
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

//c.str() converte a string para const char* para poder usar o atoi

bool dateIsValid(const std::string &date) {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;

	bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (month == 2) {
		if (isLeap && day > 29)
			return false;
		if (!isLeap && day > 28)
			return false;
	}

	return true;
}

bool checkline(const std::string &line) {
	if (line.empty() || line.find("|") == std::string::npos)
		return false;

	std::string date = line.substr(0, line.find("|"));
	std::string value = line.substr(line.find("|") + 1);

	removeSpaces(date);
	removeSpaces(value);

	if (date.empty() || value.empty())
		return false;
	if (date.find_first_not_of("0123456789-") != std::string::npos)
		return false;
	if (value.find_first_not_of("0123456789.-") != std::string::npos)
		return false;

	return true;
}

void parseInput(std::string &line, std::ifstream &file, int argc, char **argv)
{
	if (argc != 2) {
		throw std::runtime_error("Usage: ./btc [filename]");
	}
	file.open(argv[1]);
	if (!file.is_open()) {
		throw std::runtime_error("Error: file not found");
	}
	std::getline(file, line);
	if (line != "date | value") 
		throw std::runtime_error("Error: invalid file format");
}

void BitcoinExchange::outputData(std::string date, double btc_data) {
	auto it = _data.lower_bound(date);
	
	if (it == _data.end() || it->first != date) {
		if (it != _data.begin())
			--it;
	}

	if (it == _data.end()) {
		std::cout << "Error: no exchange rate data available for " << date << std::endl;
		return;
	}

	double exchangeRate = it->second;
	if (btc_data * exchangeRate > std::numeric_limits<int>::max()) {
		std::cout << "Error: too large a number." << std::endl;
		return;
	}

	std::cout << date << " => " << btc_data << " = " << (btc_data * exchangeRate) << std::endl;
}

void BitcoinExchange::execute(int argc, char **argv) {
	std::ifstream file;
	std::string line;
	parseInput(line, file, argc, argv);

	while (std::getline(file, line)) {
		std::string parsedLine = line;
		removeSpaces(parsedLine);
		if (!checkline(parsedLine))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::istringstream iss(parsedLine);
		std::string date;
		double btc_data;

		std::getline(iss, date, '|');
		iss >> btc_data;

		if (!dateIsValid(date) || date < "2009-01-02") {
			std::cerr << "Error: invalid or out-of-range date => " << date << std::endl;
			continue;
		}

		if (btc_data < 0) {
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		} else if (btc_data > 1000) {
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		outputData(date, btc_data);
	}

	file.close();
}
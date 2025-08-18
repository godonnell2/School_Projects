#ifndef BitcoinExchange_H
# define BitcoinExchange_H

# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <exception>
# include <algorithm>
# include <limits>
# include <string>

class BitcoinExchange {
    private:
        std::map<std::string, double> _data;
        BitcoinExchange(const BitcoinExchange &copy);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        void    get_data();

    public:
        BitcoinExchange();
        ~BitcoinExchange();
        void    execute(int ac, char **av);
        void    outputData(std::string data, double btc);
};

#endif
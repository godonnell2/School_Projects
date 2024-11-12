#include "ft_printf.h"

int ft_printulong(unsigned long nbr, int fd) {
    char digit;
    int count = 0;
    int error_check;

    if (nbr > 9) {
        error_check = ft_printulong(nbr / 10, fd);
        if (error_check == -1) {
            return -1;
        }
        count += error_check;
    }

    digit = (nbr % 10) + '0';
    if (ft_putchar_fd(digit, fd) == -1) {
        return -1;
    }
    return count + 1;
}
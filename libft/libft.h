#ifndef FT_LIBFT_H
#define FT_LIBFT_H

#include <stddef.h>

int	ft_isalnum(int i);
int	ft_isalpha(int c);
int	ft_isascii(int c);
int	ft_isdigit(int c);
int	ft_strlen(char *str);
int	ft_strncmp(const char *s1, char *s2, size_t n);
int	ft_toupper(int c);

#endif // FT_LIBFT_H

/* need to include stddef here to include size_t  Prevent Multiple Definitions: If a header file is included multiple times in different source files or even within the same source file, without include guards, the compiler would see the same declarations and definitions multiple times, leading to errors like "redefinition of type" or "multiple definitions of functions."*/

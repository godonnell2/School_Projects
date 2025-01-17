#include <stdarg.h>
#include <unistd.h>

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

static void	ft_printchar(char c, int fd)
{
	ft_putchar_fd(c, fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	char	*str;
	int		len;

	str = (char *)s;
	chr = (char)c;
	len = ft_strlen(str);
	if (chr == '\0')
		return (str + len);
	while (*str)
	{
		if (chr == *str)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}

static void	ft_printstring(char *s, int fd)
{
	if (s == NULL)
	{
		s = "(null)";
	}
	ft_putstr_fd(s, fd);
}

static void	ft_printtype(const char c, va_list *args, int fd)
{
	if (c == 'c')
		ft_printchar(va_arg(*args, int), fd);
	else if (c == 's')
		ft_printstring(va_arg(*args, char *), fd);
}

static void	handle_format(char format, va_list *args, int fd)
{
	if (ft_strchr("cdisupxX", format))
		ft_printtype(format, args, fd);
	else if (format == '%')
		ft_printchar('%', fd);
}

static void	parse_format(const char *mandatory_string, va_list *args, int fd)
{
	unsigned int	i;

	i = 0;
	while (mandatory_string[i])
	{
		if (mandatory_string[i] == '%')
		{
			i++;
			handle_format(mandatory_string[i], args, fd);
		}
		else
			ft_printchar(mandatory_string[i], fd);
		i++;
	}
}

void	ft_printf(const char *mandatory_string, ...)
{
	int fd = 2;
	va_list	args;

	if (mandatory_string != NULL)
		va_start(args, mandatory_string);
	parse_format(mandatory_string, &args, fd);
	va_end(args);
}

#include "minishell.h"

void *ft_memset(void *b, int c, size_t len);
char *ft_strrchr(const char *s, int c);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
void *ft_calloc(size_t count, size_t size);
void ft_bzero(void *s, size_t n);

int my_strcmp(const char *s1, const char *s2) 
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int ft_strlen(const char *s)
{
	int	i;

	i = 0;
    if(!s)
    return 0;
	while (s[i])
		i++;
	return (i);
}
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		len--;
	}
	return (b);
}



char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		len;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		string[i++] = s2[j++];
	}
	string[i] = '\0';
	return (string);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			ptr = (char *)s;
		s++;
	}
	if (*s == (char)c)
		ptr = (char *)s;
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (start + len > s_len)
		len = s_len - start;
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;

	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
}


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	d = (unsigned char *)dest;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dest);
}

char    *ft_strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
  
    if ((char)c == '\0')
        return ((char *)s);
    return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	const char	*p = s;
	char		*dup;
	size_t		i;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (*p++)
	{
		len++;
	}
	dup = malloc(len + 1);
	if (!dup)
	{
		return (NULL);
	}
	while (i <= len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
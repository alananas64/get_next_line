#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*ft_strcpy(char *src, char *dest)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	unsigned int	i;
	char			*dest;

	i = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!(dest))
		return (NULL);
	return (ft_strcpy(src, dest));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*constr;

	i = 0;
	j = 0;
	if (!s1 || !*s1)
		return (ft_strdup((char *)s2));
	if (!s2 || !*s2)
		return (ft_strdup((char *)s1));
	constr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!(constr))
		return (free (constr), NULL);
	while (s1[i] != '\0')
	{
		constr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		constr[i + j] = s2[j];
		j++;
	}
	constr[i + j] = '\0';
	return (constr);
}

char	*ft_strchr(const char *s, int c)
{
	char	n;
	char	*str;
	int		i;

	n = (char)c;
	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == n)
		{
			return (str + i);
		}
		i++;
	}
	if (str[i] == n)
	{
		return (str + i);
	}
	return (NULL);
}

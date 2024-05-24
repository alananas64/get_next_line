#include "get_next_line.h"

char	*read_one_line(int fd, char *line)
{
	char		*word;
	char		*temp;
	int			bytes_num;

	bytes_num = 1;
	if (line == NULL)
		line = ft_strdup("");
	while (bytes_num > 0)
	{
		word = (char *)malloc(sizeof(char) * (((size_t)BUFFER_SIZE) + 1));
		if (!word)
			return (NULL);
		bytes_num = read(fd, word, BUFFER_SIZE);
		if (bytes_num == -1)
			return (free(line), free (word), NULL);
		word[bytes_num] = '\0';
		temp = line;
		line = ft_strjoin(line, word);
		free (temp);
		free (word);
		if (ft_strchr(line, '\n') != NULL)
			break ;
	}
	return (line);
}

int	line_length(char *line)
{
	int	i;

	i = 0;
	while ((line[i] != '\0') && (line[i] != '\n'))
	{
		i++;
	}
	if (line[i] == '\n')
		i++;
	i++;
	return (i);
}

char	*read_n_lines(char *first_try)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (first_try[i] != '\0' && first_try[i] != '\n')
		i++;
	if (ft_strchr(first_try, '\n') == NULL)
		return (free (first_try), NULL);
	line = (char *)malloc(ft_strlen(first_try) - i + 2);
	if (!line)
		return (NULL);
	i++;
	while (first_try[i] != '\0')
	{
		line[j] = first_try[i];
		i++;
		j++;
	}
	line[j] = '\0';
	return (free(first_try), line);
}

char	*set_line(char *first_try, int line_size)
{
	char	*line;
	int		i;

	i = 0;
	line = (char *)malloc(sizeof(char) * line_size);
	if (!line)
		return (free(first_try), first_try = NULL, NULL);
	while ((first_try[i] != '\0') && (first_try[i] != '\n'))
	{
		line[i] = first_try[i];
		i++;
	}
	if (first_try[i] == '\0')
		line[i] = '\0';
	if (first_try[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*first_try;
	char		*line;
	int			i;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (BUFFER_SIZE > 2147483647))
		return (NULL);
	first_try = read_one_line(fd, first_try);
	if (!first_try)
		return (NULL);
	i = 0;
	if (first_try[i] == '\0')
		return (free(first_try), first_try = NULL, NULL);
	line = set_line(first_try, line_length(first_try));
	first_try = read_n_lines(first_try);
	return (line);
}

int	main()
{
	int		fd;
	int		i;
	char	*buff;

	i = 0;
	fd = open("e", O_RDONLY);
	buff = NULL;
	while (buff != NULL || i == 0)
	{
		buff = get_next_line(fd);
		printf("%s", buff);
		free(buff);
		i++;
	}
	free (buff);
	close(fd);
}

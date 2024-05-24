#include "get_next_line_bonus.h"

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
	static char	*first_try[10240];
	char		*line;
	int			i;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (BUFFER_SIZE > 2147483647)
		|| (fd > 10240))
		return (NULL);
	first_try[fd] = read_one_line(fd, first_try[fd]);
	if (!first_try[fd])
		return (NULL);
	i = 0;
	if (first_try[fd][i] == '\0')
		return (free(first_try[fd]), first_try[fd] = NULL, NULL);
	line = set_line(first_try[fd], line_length(first_try[fd]));
	first_try[fd] = read_n_lines(first_try[fd]);
	return (line);
}
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

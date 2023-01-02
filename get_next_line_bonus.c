/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooheekim <jooheekim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:26:50 by joohekim          #+#    #+#             */
/*   Updated: 2022/12/31 01:50:47 by jooheekim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"
#include <stdio.h>

int BUFFER_SIZE = 1;

static t_gnl_node	*new_fd(int fd)
{
	t_gnl_node	*new;

	new = (t_gnl_node *)malloc(sizeof(t_gnl_node));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->backup = ft_strdup("");
	if (!new->backup)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static t_gnl_node	*find_fd(int fd, t_gnl_list *list)
{
	if (list->start)
	{
		list->cur = list->start;
		list->pre = NULL;
		while (list->cur)
		{
			if (list->cur->fd == fd)
			{
				if (!(list->pre))
					list->pre = NULL;
				return (list->cur);
			}
			else
			{
				list->pre = list->cur;
				list->cur = list->cur->next;
			}
		}
	}
	else
		list->pre = NULL;
	list->cur = new_fd(fd);
	list->fd_cnt++;
	if (list->pre)
		list->pre->next = list->cur;
	if (!(list->start))
		list->start = list->cur;
	if (!list->cur)
		return (NULL);
	return (list->cur);
}

static char	*read_line(t_gnl_list *list, int *cnt)
{
	char	buf[BUFFER_SIZE + 1];
	int		i;
	char	*temp;

	buf[0] = '\0';
	if (list->cur->backup[0] == '\0')
	{
		*cnt = read(list->cur->fd, buf, BUFFER_SIZE);
		if (*cnt == 0)
			return (NULL);
	}
	while (*cnt > -1)
	{
		if (*cnt == 0)
			return (list->cur->backup);
		buf[*cnt] = '\0';
		temp = ft_strjoin(list->cur->backup, buf);
		free(list->cur->backup);
		list->cur->backup = temp;
		i = 0;
		while (list->cur->backup[i])
		{
			if (list->cur->backup[i] == '\n')
				return (list->cur->backup);
			i++;
		}
		*cnt = read(list->cur->fd, buf, BUFFER_SIZE);
	}
	return (NULL);
}

static char	*substr_line(t_gnl_list *list)
{
	char	*line;
	char	*temp;
	size_t	len;
	int		i;

	i = 0;
	while (list->cur->backup[i] && list->cur->backup[i] != '\n')
		i++;
	if (!list->cur->backup[i])
		return (list->cur->backup);
	line = ft_substr(list->cur->backup, 0, i + 1);
	if (!line)
		return (NULL);
	len = ft_strlen(list->cur->backup);
	temp = ft_substr(list->cur->backup, i + 1, len);
	if (!temp)
		return (NULL);
	free(list->cur->backup);
	list->cur->backup = ft_strjoin("", temp);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*list;
	char				*line;
	int					cnt;
	char *temp;

	cnt = 1;
	if (fd < 0)
		return (NULL);
	if (list == NULL)
	{
		list = (t_gnl_list *)malloc(sizeof(t_gnl_list));
		if (!list)
			return (NULL);
		list->fd_cnt = 0;
		list->start = NULL;
		list->cur = NULL;
		list->pre = NULL;
	}
	if (!(find_fd(fd, list)))
	{
		free(list);
		list = NULL;
		return (NULL);
	}
	if (!(read_line(list, &cnt)))
	{
		if (list->start == list->cur)
			list->start = list->start->next;
		del_fd(list);
		return (NULL);
	}
	line = substr_line(list);
	if (cnt == 0)
	{
		temp = substr_line(list);
		if (!temp)
			return (NULL);
		line = ft_strdup(temp);
		del_fd(list);
	}
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_utils_bonus.c"

int main(void)
{
	char *result = "";
	// int fd[3];
	// fd[0] = open("lines_around_10.txt", O_RDWR);
	// fd[1] = open("lines_around_10.txt", O_RDWR);
	// fd[2] = open("lines_around_10.txt", O_RDWR);
	int fd = open("empty.txt", O_RDONLY);
	close(fd);
	result = get_next_line(fd);
	printf("%s\n", result);
	// result = get_next_line(fd[1]);
	// printf("%s\n", result);
	// result = get_next_line(fd[1]);
	// printf("%s\n", result);
	// result = get_next_line(fd[2]);
	// printf("%s\n", result);
	// result = get_next_line(fd[1]);
	// printf("%s\n", result);
	// result = get_next_line(fd[0]);
	// printf("%s\n", result);
	// result = get_next_line(fd[2]);
	// printf("%s\n", result);
	// close(fd);
	system("leaks --list -- a.out");

// 	char *name = "lines_around_10.txt";
// 	int fd_1 = open(name, O_RDONLY);
// 	int fd_2 = open(name, O_RDONLY);
// 	int fd_3 = open(name, O_RDONLY);
// 	/* 1 */ result = get_next_line(fd_1);
// 	printf("%s\n", result);
// 	/* 2 */ result = get_next_line(fd_2);
// 	printf("%s\n", result);
// 	/* 3 */ result = get_next_line(fd_3);
// 	printf("%s\n", result);
// 	/* 4 */ result = get_next_line(fd_1);
// 	printf("%s\n", result);
// 	/* 5 */ result = get_next_line(fd_2);
// 	printf("%s\n", result);
// 	/* 6 */ result = get_next_line(fd_2);
// 	printf("%s\n", result);

// 	int fd_4 = open("giant_line_nl.txt", O_RDONLY);
// 	/* 7 */ result = get_next_line(fd_2);
// 	printf("%s\n", result);
// 	/* 8 */ result = get_next_line(fd_3);
// 	printf("%s\n", result);
// 	/* 9 */ result = get_next_line(fd_4);
// 	printf("%s\n", result);
// 	/* 10 */ result = get_next_line(fd_2);
// 	printf("%s\n", result);
// 	/* 11 */ result = get_next_line(fd_2);
// 	printf("%s\n", result);
// 	/* 12 */ result = get_next_line(fd_1);
// 	printf("%s\n", result);
// 	/* 13 */ result = get_next_line(fd_4);
// 	printf("%s\n", result);
// 	/* 14 */ result = get_next_line(fd_1);
// 	printf("%s\n", result);
// 	/* 15 */ result = get_next_line(fd_4);
// 	printf("%s\n", result);
// 	/* 16 */ result = get_next_line(fd_1);
// 	printf("%s\n", result);
// 	/* 17 */ result = get_next_line(fd_4);
// 	printf("%s\n", result);
// 	/* 18 */ result = get_next_line(fd_3);
// 	printf("%s\n", result);
// 	/* 19 */ result = get_next_line(fd_3);
// 	printf("%s\n", result);
// 	/* 20 */ result = get_next_line(fd_1);
// 	printf("%s\n", result);
// 	/* 21 */ result = get_next_line(fd_3);
// 	printf("%s\n", result);
// 	/* 22 */ result = get_next_line(fd_3);
// 	printf("%s\n", result);
	// system("leaks --list -- a.out");
}

// int main()
// {
// 	char *result = "";
// 	int fd[1];
// 	fd[0] = open("1char.txt", O_RDWR);
// 	result = get_next_line(fd[0]);
// 	printf("%s\n", result);
// 	result = get_next_line(fd[0]);
// 	printf("%s\n", result);
// }
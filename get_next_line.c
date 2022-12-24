/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooheekim <jooheekim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:26:50 by joohekim          #+#    #+#             */
/*   Updated: 2022/12/23 04:46:19 by jooheekim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int BUFFER_SIZE = 3;

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (s_len < start + len)
		len = s_len - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (len--)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (s1_len--)
		str[i++] = *s1++;
	while (s2_len--)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

t_gnl_node	*new_fd(int fd)
{
	t_gnl_node	*new;

	new = (t_gnl_node *)malloc(sizeof(t_gnl_node));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	if (!(new->backup = ft_strdup("")))
		return (NULL);
	new->next = NULL;
	return (new);
}

t_gnl_node	*find_fd(int fd, t_gnl_list *list)
{
	while (list->cur != NULL)
	{
		if (list->cur->fd == fd)
			break ;
		list->pre = list->cur;
		list->cur = list->cur->next;
	}
	if (!(list->cur = new_fd(fd)))
		return (NULL);
	return (list->cur);
	
	

	// void	ft_lstadd_back(t_list **lst, t_list *new)
	// {
	// 	t_list	*last;

	// 	if (*lst == NULL)
	// 		*lst = new;
	// 	else
	// 	{
	// 		last = ft_lstlast(*lst);
	// 		last->next = new;
	// 	}
	// }

}

char	*get_next_line(int fd)
{
	char buf[BUFFER_SIZE];
	char *line;
	int cnt;
	int i;
	size_t len;
	char *temp;
	static t_gnl_list *list;

	list = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	while (fd != -1)
	{
		if (!(find_fd(fd, list)))
			return (NULL);
		cnt = read(list->cur->fd, buf, BUFFER_SIZE);
		if (cnt == 0)
			return (list->cur->backup);
		else if (cnt == -1)
			return (NULL);
		i = 0;
		// list->cur->backup = ft_strjoin(list->cur->backup, buf);
		while (buf[i] && cnt)
		{
			if (buf[i] == '\n')
			{
				line = ft_substr(buf, 0, i);
				len = ft_strlen(list->cur->backup);
				temp = ft_substr(buf, i + 1, len);
				list->cur->backup = ft_strjoin(list->cur->backup, temp);
				return (line);
			}
			i++;
			cnt--;
		}
		if (cnt == 0)
			cnt = read(list->cur->fd, buf, BUFFER_SIZE);
	}
	return (list->cur->backup);
}

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("./abc.txt", O_RDONLY);
	char *result = get_next_line(fd);
	printf("%s\n", result);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooheekim <jooheekim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:26:50 by joohekim          #+#    #+#             */
/*   Updated: 2023/01/03 04:49:42 by jooheekim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

static t_gnl_node	*new_node(int fd)
{
	t_gnl_node	*new;

	if (fd < 0)
		return (NULL);
	new = (t_gnl_node *)malloc(sizeof(t_gnl_node));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->backup = ft_strdup("");
	if (new->backup == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

static char	*read_line(t_gnl_node *node, int *cnt, char *buf)
{
	char	*temp;

	if (node->backup[0] == '\0')
	{
		*cnt = read(node->fd, buf, BUFFER_SIZE);
		if (*cnt == 0)
			return (NULL);
	}
	while (*cnt > -1)
	{
		if (*cnt == 0)
			return (node->backup);
		buf[*cnt] = '\0';
		temp = ft_strjoin(node->backup, buf);
		if (temp == NULL)
			return (NULL);
		free(node->backup);
		node->backup = temp;
		if (check_nl(node) == 1)
			return (node->backup);
		*cnt = read(node->fd, buf, BUFFER_SIZE);
	}
	return (NULL);
}

static char	*substr_line(t_gnl_node *node)
{
	char	*line;
	char	*temp;
	size_t	len;
	int		i;

	i = 0;
	while (node->backup[i] && node->backup[i] != '\n')
		i++;
	if (!node->backup[i])
		return (node->backup);
	line = ft_substr(node->backup, 0, i + 1);
	if (!line)
		return (NULL);
	len = ft_strlen(node->backup);
	temp = ft_substr(node->backup, i + 1, len);
	if (!temp)
		return (NULL);
	free(node->backup);
	node->backup = ft_strjoin("", temp);
	if (!(node->backup))
		return (NULL);
	free(temp);
	return (line);
}

static char	*return_line(t_gnl_node **node, int *cnt)
{
	char	*temp;
	char	*line;

	line = substr_line(*node);
	if (line == NULL)
		return (NULL);
	if (*cnt == 0)
	{
		temp = substr_line(*node);
		if (temp == NULL)
			return (NULL);
		line = ft_strdup(temp);
		if (line == NULL)
			return (NULL);
		free((*node)->backup);
		free(*node);
		*node = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl_node	*node;
	char				*line;
	char				buf[BUFFER_SIZE + 1];
	int					cnt;

	cnt = 1;
	buf[0] = '\0';
	if (node == NULL)
	{
		node = new_node(fd);
		if (node == NULL)
			return (NULL);
	}
	if (!read_line(node, &cnt, buf))
	{
		free(node->backup);
		free(node);
		node = NULL;
		return (NULL);
	}
	line = return_line(&node, &cnt);
	if (line == NULL)
		return (NULL);
	return (line);
}

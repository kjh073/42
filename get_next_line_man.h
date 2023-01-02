/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooheekim <jooheekim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:26:53 by joohekim          #+#    #+#             */
/*   Updated: 2023/01/03 04:43:51 by jooheekim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

typedef struct s_gnl_node
{
	int					fd;
	char				*backup;
}	t_gnl_node;

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
int		check_nl(t_gnl_node *node);

#endif

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// #endif

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// #else
// # if BUFFER_SIZE < 1
// #  error INVALID BUFFER_SIZE!
// #endif
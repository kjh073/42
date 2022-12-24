/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joohekim <joohekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:26:53 by joohekim          #+#    #+#             */
/*   Updated: 2022/12/21 22:18:34 by joohekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct s_gnl_node
{
	int			fd;
	char		*backup;
	struct s_gnl_node	*next;
}	t_gnl_node;

typedef struct s_gnl_list
{
	t_gnl_node	*pre;
	t_gnl_node	*cur;
}	t_gnl_list;

char	*get_next_line(int fd);

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
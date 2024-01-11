/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffidha <ffidha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:28:42 by ffidha            #+#    #+#             */
/*   Updated: 2023/12/16 10:30:12 by ffidha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// # define BUFFER_SIZE 4

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

//utils
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*gettheline(char *all);
char	*remain(char *all);
//main function
char *get_next_line(int fd);
# endif

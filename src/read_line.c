/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:13:44 by akoaik            #+#    #+#             */
/*   Updated: 2025/10/28 13:39:27 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*read_from_pipe(t_list_head *n_head)
{
	char	buffer[4096];
	ssize_t	bytes_read;
	int		i;

	bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	i = 0;
	while (i < bytes_read && buffer[i] != '\n')
		i++;
	buffer[i] = '\0';
	return (my_strdup(buffer, n_head));
}

char	*get_user_input(t_list_head *n_head)
{
	char	*input;

	if (!isatty(STDIN_FILENO))
		input = read_from_pipe(n_head);
	else
		input = readline("minishell$ ");
	if (input && *input != '\0' && isatty(STDIN_FILENO))
		add_history(input);
	return (input);
}

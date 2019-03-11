/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:17:00 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/12 00:30:34 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "get_next_line.h"

static int		is_whitespaces_line(const char *str)
{
	size_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (!ft_isspace(str[index]))
			return (0);
		index++;
	}
	return (1);
}

static size_t	label_check(char *line)
{
	size_t index;

	index = 0;
	while (line[index] && ft_isspace(line[index]))
		index++;
	while (line[index] && !ft_isspace(line[index]) &&
			line[index] != SEPARATOR_CHAR)
		index++;
	index -= 1;
	if (line[index] == LABEL_CHAR)
		return (index);
	return (0);
}

int		create_line(t_file *file, char *line, size_t nbr_lines, int line_type)
{
	t_line *new_line;

	new_line = (t_line*)malloc(sizeof(t_line));
	new_line->tokens = NULL;
	new_line->str = NULL;
	new_line->nbr_params = 0;
	new_line->id = nbr_lines;
	new_line->type = line_type;
	new_line->index = 0;
	new_line->bytecode = NULL;
	return (1);
}

int		add_lines(t_file *file, char *line, size_t *nbr_lines, size_t label_pos)
{
	size_t	len;

	len = ft_strlen(line);
	if (label_pos)
	{
		line[label_pos] = '\0';
		create_line(file, line, *nbr_lines, T_LABEL);
		line[label_pos] = ' ';
		if (len > label_pos + 1 && !is_whitespaces_line((&line[label_pos + 2])))
			create_line(file, line + label_pos + 2, ++(*nbr_lines), T_UNKNOWN);

	}
	else
	{
		create_line(file, line, *nbr_lines, T_UNKNOWN);
	}
	return (1);
}

int		read_file(t_file *file)
{
	char	*line;
	size_t	nbr_lines;

	nbr_lines = 0;
	line = NULL;
	while ((file->ret = get_next_line(file->fd_s, &line)) > 0)
	{
		if (line && (line[0] =='\0' || is_whitespaces_line(line)))
		{
			free(line);
			continue ;
		}
		if (add_lines(file, line, &nbr_lines, label_check(line)) == ASM_FAIL)
		{
			free(line);
			file_error("syntax error in line.\n");
		}
		free(line);
		nbr_lines++;
	}
	if (file->ret == -1)
		file_error("get_next_line failed.\n");
	file->nbr_line = nbr_lines;
	return (1);
}

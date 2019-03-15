/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:10:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/15 06:09:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/* categorize the line type
.name = T_NAME
.comment = T_CMD_COMMENT

different tokens
	- T_LABEL = string + :

	- T_INSTR
		- 1 params instructions
		- 2 params instructions
		- 3 params instructions
	- parameters
		- T_REGISTRY = r + INTEGER
		- T_DIRECT = % + INTEGER
		- T_DIRLAB = % + : + LABEL
		- T_INDIRECT = INTEGER error ?
		- T_INDIRLAB = : + LABEL
*/
int		add_token(t_line *line, int token_id, int start, int end)
{
	t_token		token;
	int			len;

	len = start - end;
	if (!(token.str = ft_strsub(line->str, start,len)))
		ERROR("ft_strsub failed.", LINE_FAIL);
	check_token_type();

}

int		tokenize_line(t_line *line)
{
	t_token	*token;
	size_t	len;
	int		start;
	int		end;
	int		token_id;

	token_id = 0;
	len = ft_strlen(line);
	if (!(token = (t_token*)malloc(sizeof(t_token))))
		ERROR("malloc failed.", LINE_FAIL);
	while (line->pos < len)
	{
		while (line->str[line->pos] && is_whitespaces_line(line->str))
			line->pos++;
		start = line->pos;
		while (line->str[line->pos] && !(is_whitespaces_line(line->str)) &&
			line->str[line->pos] != SEPARATOR_CHAR)
			line->pos++;
		end = line->pos;
		if (add_token(line, token_id, start, end) == LINE_FAIL)
			ERROR("tokenize failed.", LINE_FAIL);
		token_id++;
		if (token_id > 4)
			ERROR("Too many tokens.", LINE_FAIL);
	}
	return (SUCCESS);
}

int		check_instrutions(t_line *line)
{
	/* TODO */
	return (SUCCESS);
}



int		parse_file(t_file *file)
{
	t_list	*traverse;

	traverse = file->lines;
	while(traverse)
	{
		if (/* LINE is not T_COMMENT */)
		{
			if (!(file->header.prog_name[0]))
				set_progname(file);
			if (!(file->header.how[0]))
				set_how(file);
			if (LINE->type != T_LABEL)
				LINE->type = T_ASMCODE;
			if (LINE->type == T_ASMCODE && (!(tokenize_line(LINE)) ||
				!(check_instructions(LINE))))
					file_error("parse failed", file);
			traverse = traverse->next;
		}
	}
}



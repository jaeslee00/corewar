/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:17:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/12 13:18:03 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H
# include "libft.h"
# include "list.h"
# include "op.h"
# include <stdint.h>
#include <stdio.h>
# define ASM_FAIL 0
# define ASM_SUCCESS 1

typedef enum e_token_types
{
	T_NAME,
	T_CMD_COMMENT,
	T_COMMENT,
	T_LABEL,
	T_INTSTR,
	T_REGISTRY,
	T_DIRECT,
	T_INDIRECT,
	T_DIRLAB,
	T_INDIRLAB,
	T_UNKNOWN
}			t_token_types;

# define TOKEN ((t_token*)(lst->content))
# define LINE ((t_line*)(lst->content))

typedef struct	s_token
{
	t_op				*op;
	char				*str;
	size_t				id;
	int					type;
	int					value;
}				t_token;

typedef struct	s_line
{
	t_list				*tokens;
	char				*str;
	int					type;
	size_t				nbr_params;
	size_t				id;
	size_t				index;
	char				*bytecode;

}				t_line;

typedef struct	s_file
{
	t_list		*lines;
	size_t		nbr_line;
	char		*name_s;
	char		*name_cor;
	int			fd_cor;
	int			fd_s;
	int			ret;
}				t_file;

void	file_error(const char *str, t_file *file);
int		read_file(t_file *file);

#endif

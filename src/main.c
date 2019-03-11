/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/11 18:35:32 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "assembler.h"
#include <fcntl.h>

int		check_file_name(const char *filename, t_file *file)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 2] != '.' || filename[len - 1] != 's')
	{
		ft_putendl("the filename has to end with '.s'");
		exit(-1);
	}
	if ((file->fd_s = open(filename, O_RDONLY)) == -1)
	{
		ft_putendl("Cannot open the file");
		exit(-1);
	}
	if (!(file->name_s = ft_strdup(filename)))
	{
		ft_putendl("ft_strdup failed");
		exit(-1);
	}
	if (!(tmp = (char*)ft_strndup(filename, len - 2)))
	{
		ft_putendl("ft_strndup failed");
		exit(-1);
	}
	if (!(file->name_cor = ft_strjoin(tmp, ".cor")))
	{
		ft_putendl("ft_strjoin failed");
		exit(-1);
	}
	return (1);
}

void	check_file(int argc, t_file *file)
{
		if (argc == 1)
		{
			ft_putendl("no file identified");
			exit(-1);
		}
		if (argc > 2)
		{
			ft_putendl("too many files");
			exit(-1);
		}
}

void	init_file(t_file *file)
{
	file->lines = NULL;
	file->nbr_line = 0;
	file->name_s = NULL;
	file->name_cor = NULL;
	file->fd_s = -1;
	file->fd_cor = -1;
}

int		main(int argc, char **argv)
{
	t_file	file;

	init_file(&file);
	check_file(argc, &file);
	check_file_name(argv[1], &file);
	return (0);
}

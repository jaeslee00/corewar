/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/11 22:50:17 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "assembler.h"
#include <fcntl.h>
#include <stdio.h>

static void	check_file_name(const char *filename, t_file *file)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 2] != '.' || filename[len - 1] != 's')
		file_error("the filename has to end with '.s'");
	(file->fd_s = open(filename, O_RDONLY));
	if (file->fd_s == -1)
		file_error("Cannot open the file");
	if (!(file->name_s = ft_strdup(filename)))
		file_error("ft_strdup failed");
	if (!(tmp = (char*)ft_strndup(filename, len - 2)))
		file_error("ft_strndup failed");
	if (!(file->name_cor = ft_strjoin(tmp, ".cor")))
		file_error("ft_strjoin failed");
	printf("%s\n", file->name_cor);
}

static void	check_file(int argc)
{
		if (argc == 1)
			file_error("no file identified");
		if (argc > 2)
			file_error("too many files");
}

static void	init_file(t_file *file)
{
	file->lines = NULL;
	file->nbr_line = 0;
	file->name_s = NULL;
	file->name_cor = NULL;
	file->fd_s = -1;
	file->fd_cor = -1;
}

static int		main(int argc, char **argv)
{
	t_file	file;

	init_file(&file);
	check_file(argc);
	check_file_name(argv[1], &file);
	if (read_file(&file) == ASM_FAIL)
		return (ASM_FAIL);
	if (parse_file(&file) == ASM_FAIL)
		return (ASM_FAIL);
	return (0);
}

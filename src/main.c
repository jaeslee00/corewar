/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/12 13:49:58 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "assembler.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static void	check_file_name(const char *filename, t_file *file)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 2] != '.' || filename[len - 1] != 's')
		file_error("the filename has to end with '.s'\n", file);
	if (!(file->name_s = ft_strdup(filename)))
		file_error("ft_strdup failed\n", file);
	if (!(tmp = (char*)ft_strndup(filename, len - 2)))
		file_error("ft_strndup failed\n", file);
	if (!(file->name_cor = ft_strjoin(tmp, ".cor")))
		file_error("ft_strjoin failed\n", file);
	free(tmp);
	printf("%s\n", file->name_cor);
}

static void	check_file(int argc, t_file *file)
{
		if (argc == 1)
			file_error("no file identified\n", file);
		if (argc > 2)
			file_error("too many files\n", file);
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

int		main(int argc, char **argv)
{
	t_file	file;

	init_file(&file);
	check_file(argc, &file);
	check_file_name(argv[1], &file);
	if ((file.fd_s = open(argv[1], O_RDONLY)) == -1)
		file_error("failed to open the file.\n", &file);
	printf("%d\n", file.fd_s);
	if (read_file(&file) == ASM_FAIL)
	{
		printf("asdf\n");
		return (ASM_FAIL);
	}
	file_error(NULL, &file);
	/*if (parse_file(&file) == ASM_FAIL)
		return (ASM_FAIL);*/
	return (0);
}

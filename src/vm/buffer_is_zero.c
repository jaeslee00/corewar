/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_is_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:18:37 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:22:26 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		buffer_is_zero(t_bigend_buffer buffer)
{
	size_t	index;

	index = 0;
	while (index < sizeof(buffer.buffer))
	{
		if (*(buff_index(&buffer, index)))
			return (0);
		index++;
	}
	return (1);
}

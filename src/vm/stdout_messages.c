/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:39:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/06 16:33:57 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "ft_printf.h"
#include "vm.h"

void	print_prelude(t_vm_state *state)
{
	size_t	i;
	t_array	players;

	players = state->players;
	i = 0;
	ft_printf("Introducing the contestants...\n");
	while (i < state->players.length)
	{
		ft_printf("PLAYER %d, weighing %u bytes, ",
			((t_player*)players.ptr)[i].id,
			((t_player*)players.ptr)[i].header.prog_size);
		ft_printf("'%s', ('%s')\n",
			((t_player*)players.ptr)[i].header.prog_name,
			((t_player*)players.ptr)[i].header.comment);
		i++;
	}
}

void	print_ending(t_vm_state *state)
{
	size_t	winner;

	winner = get_winner(state);
	if (winner < state->players.length)
		ft_printf("THE WINNER IS : PLAYER %d!  '%s' !!!\n",
			((t_player*)state->players.ptr)[winner].id,
			((t_player*)state->players.ptr)[winner].header.prog_name);
	else
		ft_printf("IT'S A DRAW!\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolas <acolas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:13:31 by alex              #+#    #+#             */
/*   Updated: 2019/06/05 22:17:08 by acolas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_assert.h"

size_t	vm_new_id(t_vm_state *state)
{
	return (state->process_count++);
}

void	vm_init_process(t_vm_state *state, int player_id, size_t address)
{
	t_process	new_process;
	size_t		search;

	ft_bzero(&new_process, sizeof(t_process));
	new_process.registers[0].content = byte_order_swap(
			(t_bigend_buffer){(int32_t)player_id});
	search = 0;
	while (search < state->players.length
		&& !((player_get(state, search))->id == player_id))
		search++;
	ft_assert(search < state->players.length,
		"Tried to init process with player id that does not exist.");
	new_process.player = player_get(state, search);
	new_process.program_counter = address % MEM_SIZE;
	new_process.has_jumped = 1;
	new_process.id = vm_new_id(state);
	new_process.pending_operation = fetch_opcode(state,
			new_process.program_counter);
	new_process.birth_cycle = state->cycle_count;
	if (new_process.pending_operation < e_invalid)
		new_process.busy = g_op_tab[new_process.pending_operation].cycles;
	else
		new_process.busy = 1;
	array_push_back(&state->processes, &new_process);
}

void	vm_clone_process(t_vm_state *state, size_t address, t_process *original)
{
	t_process	new_process;

	ft_bzero(&new_process, sizeof(t_process));
	ft_memcpy(new_process.registers, original->registers,
		sizeof(original->registers));
	new_process.program_counter = address % MEM_SIZE;
	new_process.carry = original->carry;
	new_process.player = original->player;
	new_process.has_jumped = 1;
	new_process.id = vm_new_id(state);
	new_process.pending_operation = fetch_opcode(state,
			new_process.program_counter);
	new_process.birth_cycle = state->cycle_count;
	if (new_process.pending_operation < e_invalid)
		new_process.busy = g_op_tab[new_process.pending_operation].cycles;
	else
		new_process.busy = 1;
	array_push_back(&state->processes, &new_process);
}

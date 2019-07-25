/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolas <acolas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/06/05 22:17:10 by acolas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_lfork(t_vm_state *state, size_t p_index, t_instr *instr)
{
	int32_t	offset;

	offset = byte_order_swap(
			(arg_dir(instr, 0))->content).buffer;
	offset = (process_get(state, p_index))->program_counter + offset;
	vm_clone_process(state, offset, process_get(state, p_index));
	log_level(&state->log_info, e_log_fork,
		"Process %zu creates %zu at offset %zu",
		(process_get(state, p_index))->id,
		(process_get(state, state->processes.length - 1))->id,
		offset % MEM_SIZE);
}

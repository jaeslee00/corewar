/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/08 13:12:18 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		do_load(t_vm_state *state, t_process *process,
					t_instr *instr, int32_t offset)
{
	offset = process->program_counter + (offset % IDX_MOD);
	(register_get(process, *(arg_reg(instr, 2)) - 1))->content = mem_load(state,
			offset, REG_SIZE);
	process->carry = buffer_is_zero(
			(register_get(process, *(arg_reg(instr, 2)) - 1))->content);
	log_level(&state->log_info, e_log_load,
		"Loading [%#.8zx] into r%d, val %#.8zx",
		offset % MEM_SIZE,
		*(arg_reg(instr, 2)),
		(register_get(process, *(arg_reg(instr, 2)) - 1))->content);
}

void			impl_ldi(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_bigend_buffer	first_p;
	t_bigend_buffer	second_p;
	int32_t			offset;
	t_process		*process;

	process = process_get(state, p_index);
	first_p.buffer = 0;
	second_p.buffer = 0;
	if (*(arg_type(instr, 0)) == e_register)
		first_p = (register_get(process, *(arg_reg(instr, 0)) - 1))->content;
	else if (*(arg_type(instr, 0)) == e_index)
	{
		offset = byte_order_swap((arg_ind(instr, 0))->content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		first_p = mem_load(state, offset, REG_SIZE);
	}
	else
		first_p = (arg_dir(instr, 0))->content;
	if (*(arg_type(instr, 1)) == e_register)
		second_p = (register_get(process, *(arg_reg(instr, 1)) - 1))->content;
	else
		second_p = (arg_dir(instr, 1))->content;
	offset = (int32_t)byte_order_swap(
		add_bigend(first_p, second_p, 0)).buffer;
	do_load(state, process, instr, offset);
}

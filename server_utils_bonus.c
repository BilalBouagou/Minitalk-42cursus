/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:20:59 by bbouagou          #+#    #+#             */
/*   Updated: 2023/01/18 16:09:37 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	fill_with_zeroes(t_info *info)
{
	info->bytes_ptr[0] = 0;
	info->bytes_ptr[1] = 0;
	info->bytes_ptr[2] = 0;
	info->bytes_ptr[3] = 0;
	info->bytes_ptr[4] = 0;
	info->bytes_ptr[5] = 0;
}

void	detect_unicode(t_info *info)
{
	int			i;

	if (!(*info).bytes_count && !(*info).flag)
	{
		write(1, &(*info).byte, 1);
		return ;
	}
	if ((*info).bytes_count < (*info).flag && (*info).flag)
	{
		(*info).bytes_ptr[(*info).bytes_count] = (*info).byte;
		(*info).bytes_count++;
	}
	i = -1;
	if ((*info).bytes_count == (*info).flag)
	{
		while (++i < (*info).bytes_count)
			write(1, &(*info).bytes_ptr[i], 1);
		fill_with_zeroes(&(*info));
		(*info).bytes_count = 0;
		(*info).flag = 0;
	}
}

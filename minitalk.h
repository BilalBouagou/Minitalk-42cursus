/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:04:28 by bbouagou          #+#    #+#             */
/*   Updated: 2023/01/18 20:58:47 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_info
{
	int				byte;
	int				flag;
	int				bytes_count;
	int				bytes_ptr[6];
	int				ptr_allc;
	pid_t			client_pid;
	sig_atomic_t	sigcount;
}	t_info;

void	detect_unicode(t_info *info);
void	fill_with_zeroes(t_info *info);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 14:02:34 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/22 13:12:58 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void		ft_perror(char *title, char *error)
{
	ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", PRGRM_NAME, title, error);
	exit(-1);
}

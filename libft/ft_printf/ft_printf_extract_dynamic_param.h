/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_extract_dynamic_param.h                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:38:40 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/30 13:34:30 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_EXTRACT_DYNAMIC_PARAM_H
# define FT_PRINTF_EXTRACT_DYNAMIC_PARAM_H
# include <stdarg.h>

int		extract_dyn_param(int *minus, va_list ap);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:59:58 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/06 17:21:33 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

int		assert_lex(t_lex *lex)
{
	DEBUG(lex);
	return (lex && lex->token_type != ERROR);
}

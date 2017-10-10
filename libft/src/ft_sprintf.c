/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 12:40:10 by nicolas           #+#    #+#             */
/*   Updated: 2017/10/06 12:49:25 by nmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	init_modif(t_modif **modif)
{
	(*modif)->att = 0;
	(*modif)->champ = -2;
	(*modif)->precision = -2;
	(*modif)->modif = 0;
	(*modif)->conv = 0;
	return (1);
}

char		*ft_sprintf(const char *format, ...)
{
	va_list		ap;
	t_modif		*modif;
	int			nb_wrote;
	char		*ret_str;

	if (!format)
		return (0);
	ret_str = NULL;
	nb_wrote = 0;
	va_start(ap, format);
	(!(modif = (t_modif *)malloc(sizeof(t_modif)))) ? exit(-1) : 0;
	while (*format)
	{
		nb_wrote += copy_until_mod(&format, &ret_str, nb_wrote);
		if (*format)
		{
			init_modif(&modif) && (format = get_info(format, modif, ap));
			put_arg(modif, &ret_str, &nb_wrote, ap);
		}
	}
	free(modif);
	va_end(ap);
	return (ret_str);
}

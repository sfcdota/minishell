/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:55:36 by cbach             #+#    #+#             */
/*   Updated: 2020/12/27 14:55:37 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
** Modifying str to lower register symbols
*/

void	uncapitalize_str(char *str)
{
	while (str && *str)
	{
		ft_tolower(*str);
		str++;
	}
}

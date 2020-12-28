/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:25:37 by cbach             #+#    #+#             */
/*   Updated: 2020/12/28 23:25:39 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	clear_redirection(void *redirection_content)
{
	t_redirection *redirection;

	redirection = (t_redirection *)redirection_content;
	clear_ptr((void **)&redirection->filename);
	clear_ptr((void **)&redirection);
}
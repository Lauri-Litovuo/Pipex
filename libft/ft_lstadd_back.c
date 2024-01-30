/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:51:36 by llitovuo          #+#    #+#             */
/*   Updated: 2023/12/27 16:41:05 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_ptr;

	lst_ptr = *lst;
	if (*lst == 0)
		*lst = new;
	else
	{
		while (lst_ptr->next != NULL)
		{
			lst_ptr = lst_ptr->next;
		}
		lst_ptr->next = new;
	}
}

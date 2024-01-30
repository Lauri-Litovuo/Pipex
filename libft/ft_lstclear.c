/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:53:45 by llitovuo          #+#    #+#             */
/*   Updated: 2023/12/27 16:41:47 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_ptr;
	t_list	*next;

	if (!lst)
		return ;
	lst_ptr = *lst;
	while (lst_ptr != 0)
	{
		next = lst_ptr->next;
		ft_lstdelone(lst_ptr, del);
		lst_ptr = next;
	}
	*lst = NULL;
}

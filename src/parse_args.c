/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:41:57 by anammal           #+#    #+#             */
/*   Updated: 2023/06/09 19:42:02 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static int	parse_int(char	*item, int *status)
{
	int		parsed;
	int		iszero;

	parsed = ft_atoi(item);
	if ((*item == '-' || *item == '+') && ft_isdigit(*(item + 1)))
		item++;
	iszero = 0;
	while (ft_isdigit(*item))
		iszero += *(item++) - '0';
	if (*item != '\0'
		|| (parsed == 0 && iszero != 0)
		|| (parsed == -1 && iszero != 1))
		*status = 0;
	return (parsed);
}

static t_array	*export_args(t_list **list)
{
	t_array	*arr;
	t_list	*tmp;
	int		status;
	int		i;

	arr = (t_array *)malloc(sizeof(t_array));
	if (arr == NULL)
		return (ft_lstclear(list, free), NULL);
	arr->size = ft_lstsize(*list);
	arr->items = (int *)malloc(arr->size * sizeof(int));
	if (arr->items == NULL)
		return (ft_lstclear(list, free), free(arr), NULL);
	tmp = *list;
	status = 1;
	i = 0;
	while (tmp)
	{
		arr->items[i++] = parse_int(tmp->content, &status);
		if (status == 0)
			return (ft_lstclear(list, free), free(arr->items), free(arr), NULL);
		tmp = tmp->next;
	}
	return (ft_lstclear(list, free), arr);
}

static void	add_to_list(t_list **item, char **args)
{
	t_list	*new;

	while (*args)
	{
		new = ft_lstnew(*args);
		if (new == NULL || new->content == NULL)
		{
			ft_lstdelone(new, free);
			ft_lstclear(item, free);
			*item = NULL;
			break ;
		}
		ft_lstadd_back(item, new);
		args++;
	}
}

t_array	*parse_args(int count, char const **args)
{
	t_list	*item;
	char	**tmp;

	item = NULL;
	while (count--)
	{
		tmp = ft_split(*args, ' ');
		if (tmp == NULL)
			return (ft_lstclear(&item, free), NULL);
		else if (*tmp == NULL)
			return (ft_lstclear(&item, free), free(tmp), NULL);
		add_to_list(&item, tmp);
		free(tmp);
		if (item == NULL)
			return (NULL);
		args++;
	}
	return (export_args(&item));
}

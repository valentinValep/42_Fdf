/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:25 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:26 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include <stdlib.h>

void	init_queue(t_queue *queue)
{
	queue->first = NULL;
	queue->last = NULL;
}

int	add_queue(t_queue *queue, t_queue_content value)
{
	t_element	*new;

	new = malloc(sizeof(t_element));
	if (!new)
		return (0);
	new->content = value;
	new->next = NULL;
	if (!queue->first)
		queue->first = new;
	else
		queue->last->next = new;
	queue->last = new;
	return (1);
}

int	queue_next(t_queue *queue, t_queue_content *res)
{
	t_element	*second;

	if (!queue->first)
		return (0);
	second = queue->first->next;
	if (res)
		*res = queue->first->content;
	free(queue->first);
	queue->first = second;
	if (!queue->first)
		queue->last = NULL;
	return (1);
}

void	destroy_queue(t_queue *queue)
{
	while (queue_next(queue, NULL))
		;
}

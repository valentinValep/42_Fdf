#include "queue.h"
#include <stdlib.h>

void	init_queue(t_queue *queue)
{
	queue->first = NULL;
	queue->last = NULL;
	queue->current = 0;
}

int	add_queue(t_queue *queue, int value)
{
	t_element	*new;

	new = malloc(sizeof(t_element));
	if (!new)
		return (1);
	new->content = value;
	new->next = NULL;
	if (!queue->first)
		queue->first = new;
	else
		queue->last->next = new;
	queue->last = new;
	return (0);
}

const int	*queue_next(t_queue *queue)
{
	t_element	*second;

	if (!queue->first)
		return (NULL);
	second = queue->first->next;
	queue->current = queue->first->content;
	free(queue->first);
	queue->first = second;
	if (!queue->first)
		queue->last = NULL;
	return (&queue->current);
}

void	destroy_queue(t_queue *queue)
{
	while (queue_next(queue))
		;
}

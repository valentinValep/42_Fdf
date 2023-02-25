#ifndef QUEUE_H
# define QUEUE_H

typedef struct s_element
{
	int					content;
	struct s_element	*next;
}	t_element;

typedef struct s_queue
{
	t_element	*first;
	t_element	*last;
	int			current;
}	t_queue;

void		init_queue(t_queue *queue);

int			add_queue(t_queue *queue, int value)
			__attribute__((warn_unused_result));

/// @brief return next element ptr in queue and
/// destroy it (so do not store the result!)
/// @param queue
/// @return const int *: ptr to the next int of the queue
const int	*queue_next(t_queue *queue);

void		destroy_queue(t_queue *queue);

#endif

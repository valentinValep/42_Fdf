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

void	init_queue(t_queue *queue);

/// @brief Add an int to queue
/// @param queue : an initialized queue
/// @param value : value to add
/// @return 1 on success | 0 on malloc fail
int		add_queue(t_queue *queue, int value)
		__attribute__((warn_unused_result));


/// @brief Get next int of the queue and consume it
/// @param queue : an initialized
/// @param res : ptr to the value to get
/// @return 1 on success | 0 on empty queue
int		queue_next(t_queue *queue, int *res);

void	destroy_queue(t_queue *queue);

#endif

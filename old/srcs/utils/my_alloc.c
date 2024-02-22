#include "../../includes/headers/minishell.h"

int	my_alloc(size_t size, size_t len, void **dst)
{
	*dst = ft_calloc(len, size);
	if (*dst == NULL)
		return (1);
	else
		return (0);
}

#include "../includes/headers/minishell.h"

static void	ft_bzero(void *ptr, size_t num)
{
	unsigned char	*aux;

	aux = ptr;
	while (num > 0)
	{
		aux[num - 1] = 0;
		num --;
	}
}

static void	*ft_calloc(size_t ne, size_t size)
{
	void	*aux;

	aux = malloc(ne * size);
	if (aux == NULL)
		return (NULL);
	ft_bzero(aux, ne * size);
	return (aux);
}

int	my_alloc(size_t size, size_t len, void **dst)
{
	*dst = ft_calloc(len, size);
	if (*dst == NULL)
		return (1);
	else
		return (0);
}

#include "../includes/headers/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*stra;
	unsigned char	*strb;

	stra = (unsigned char *)s1;
	strb = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((stra[i] == strb[i]) && (stra[i]) && (i < n - 1))
	{
		i ++;
	}
	return (stra[i] - strb[i]);
}
/*
int main()
{
	printf("\n%i\n",ft_strncmp("test\200", "test\0", 6));
	return (0);
}
*/

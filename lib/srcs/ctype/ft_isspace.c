
#include "../../includes/ft_ctype.h"

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13)) 
		return (0);
	return (1);
}

#ifndef PROJECT
# define PROJECT
# define FILE_NAME "urunMaliyet.txt"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct s_str
{
	int productSize;
	int rawSize;
	int file_line;
	char *all_file;
}				t_str;

typedef struct s_raws
{
	int rawsId;
	int rawsPrice;
	int productionCost;

	char **raws;
}				t_raws;

typedef struct s_products
{
	int productId;
	int productPrice;
	char *productName;
	t_raws *raws;
	t_str *str;
}				t_products;

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif

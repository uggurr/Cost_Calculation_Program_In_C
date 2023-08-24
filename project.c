#include "project.h"

char	*get_all_file(char *str)
{
	char	*map;
	char	*get_line;
	int		i;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		printf("file not found");
		close(fd);
		exit(0);
	}
	map = NULL;
	get_line = NULL;
	i = -1;
	while (get_line != NULL || ++i == 0)
	{
		get_line = get_next_line(fd);
		if (get_line != NULL)
			map = ft_gnl_strjoin(map, get_line);
		free(get_line);
	}
	return (map);
}

int checkSameProduct(char *all_file, char *line, t_str *str)
{
	int i = 0;
	char **file_line;
	file_line = ft_split(all_file, '\n');
	while (file_line[i])
	{
		if (ft_strncmp(file_line[i], line, ft_strlen(line)) == 0)
		{
			printf("\n--------------------------------------------------------------\n");
			printf("Girdiğiniz ürün Dosyada bulunmaktadır. Lütfen kontrol ediniz!\n");
			printf("--------------------------------------------------------------\n\n");
			return (1);
		}
		i++;
	}
	str->file_line = i + 1;
	return (0);
}

t_products *get_product(t_str *str)
{
	t_products *product;
	char line[20];
	int i = 0;
	printf("Belirttiğiniz ürün sayısı kadar liste açılacaktır!\n");
	printf("lütfen girmek istediğiniz ürün sayısını giriniz: ");
	scanf("%d", &str->productSize);
	product = malloc(sizeof(t_products) * str->productSize);

    // Clear the newline character from the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    while (i < str->productSize)
    {
        printf("Lütfen %d. ürünü giriniz: ", i + 1);
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';  // Remove the trailing newline
		if (str->all_file != NULL)
		{
			while (checkSameProduct(str->all_file, line, str))
			{
				printf("Lütfen %d. ürünü tekrar giriniz: ", i + 1);
        		fgets(line, sizeof(line), stdin);
				line[strcspn(line, "\n")] = '\0';
			}
		}
		str->file_line += i+1;
		product[i].productId = str->file_line;
		product[i].productName = malloc(sizeof(char) * 2);
        product[i].productName = strdup(line);
		product[i].productPrice = 0;
        i++;
    }
	return (product);
}

void ft_write_product(t_products *product)
{
	int out = dup(1);
	int	fd;

	fd = 0;
	fd = open(FILE_NAME, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("Bir şeyler ters gitti");
	}
    dup2(fd, 1);
    close(fd);

    char productIdStr[10];
    sprintf(productIdStr, "%d", product->productId);

    char productPriceStr[10];
    sprintf(productPriceStr, "%d", product->productPrice);
    write(1, productIdStr, strlen(productIdStr));
    write(1, "| ", 2);
    write(1, product->productName, strlen(product->productName));
    write(1, " = ", 3);
    write(1, productPriceStr, strlen(productPriceStr));

	write(1, "\n", 1);

    dup2(out, 1);
    close(out);
}

int main()
{
	t_str *str = malloc(sizeof(t_str));
	t_products *product;
	//t_raws *raws;
	str->all_file = get_all_file(FILE_NAME);
	//if (checkSameProduct(str->all_file, "dnemee 2"))
	//	printf("girdi");
	//printf("%s", str->all_file);
	product = get_product(str);
	write(1, &product->productId, 1);
	write(1, "g", 1);
	int i = 0;
	while (i < str->productSize)
	{
		ft_write_product(&product[i]);
		printf("ID: %d Ürün adı: %s\n", product[i].productId ,product[i].productName);
		i++;
	}
}

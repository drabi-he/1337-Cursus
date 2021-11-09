#include "libft/libft.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

t_list *all;

char strmapi_add(unsigned int i,char c)
{
	char rst;
	rst = c +i;
	return (rst);
}
void striteri_add(unsigned int i,char *c)
{
	*c += i;
}

void	lst_affich(t_list	*list)
{
	t_list *tmp;
	int i = 0;

	tmp = list;
	while(tmp)
	{
		printf("element %d = %s \n",i+1,(char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
}


int main()
{
	int choix;
	char again;

	do
	{
		printf("******************************************\n");
		printf("*  1-isalpha        *                    *\n");
		printf("*  2-isdigit        *  13-toupper        *\n");
		printf("*  3-isalnum        *  14-tolower        *\n");
		printf("*  4-isascii        *  15-strchr         *\n");
		printf("*  5-isprint        *  16-strrchr        *\n");
		printf("*  6-strlen         *  17-strncmp        *\n");
		printf("*  7-memset         *  18-memchr         *\n");
		printf("*  8-bzero          *  19-memcmp         *\n");
		printf("*  9-memcpy         *  20-strnstr        *\n");
		printf("* 10-memmove        *  21-atoi           *\n");
		printf("* 11-strlcpy        *                    *\n");
		printf("* 12-strlcat        *                    *\n");
		printf("******************************************\n");
		printf("* 22-calloc        *  23-strdup          *\n");
		printf("******************************************\n");
		printf("* 24-substr        *  30-striteri        *\n");
		printf("* 25-strjoin       *  31-putchar_fd      *\n");
		printf("* 26-strtrim       *  32-putstr_fd       *\n");
		printf("* 27-split         *  33-putendl_fd      *\n");
		printf("* 28-itoa          *  34-putnbr_fd       *\n");
		printf("* 29-strmapi       *                     *\n");
		printf("******************************************\n");
		printf("* 35-lstnew        *  39-lstdelone       *\n");
		printf("* 36-lstadd_front  *  40-lstclear        *\n");
		printf("* 37-lstsize       *  41-lstiter         *\n");
		printf("* 38-lstlast       *  34-lstmap          *\n");
		printf("* 40-lstadd_back   *                     *\n");
		printf("******************************************\n");
		printf("choose a fct\n");
		scanf("%d", &choix);

		switch (choix)
		{
		case 1:
		{
			printf("dec val isalpha original\n");
			for (int i = 0; i < 128; i++)
				printf("%3d  %3c = %4d %4d\n", i, i, ft_isalpha(i), isalpha(i));
			break;
		}
		case 2:
		{
			printf("dec val isdigit original\n");
			for (int i = 0; i < 128; i++)
				printf("%3d  %3c = %4d %4d\n", i, i, ft_isdigit(i), isdigit(i));
			break;
		}
		case 3:
		{
			printf("dec val isalnum original\n");
			for (int i = 0; i < 128; i++)
				printf("%3d  %3c = %4d %4d\n", i, i, ft_isalnum(i), isalnum(i));
			break;
		}
		case 4:
		{
			printf("dec val isascii original\n");
			for (int i = -128; i < 128; i++)
				printf("%3d  %3c = %4d %4d\n", i, i, ft_isascii(i), isascii(i));
			break;
		}
		case 5:
		{
			printf("dec val isprint original\n");
			for (int i = 0; i < 128; i++)
				printf("%3d  %3c = %4d %4d\n", i, i, ft_isprint(i), isprint(i));
			break;
		}
		case 6:
		{
			char word[100] = "\0";
			printf("write your string : ");
			scanf("%s", word);
			printf("your word lenght is : %lu\n", ft_strlen(word));
			break;
		}
		case 7:
		{
			char word[100] = "\0";
			int c;
			size_t size;
			printf("write your string : ");
			scanf("%s", word);
			printf("write your char : ");
			scanf("%d", &c);
			printf("write the size : ");
			scanf("%lu", &size);
			printf("your word is : %s\n", word);
			ft_memset(word, c, size);
			printf("your word after memset is : %s\n", word);
			break;
		}
		case 8:
		{
			char word[100] = "\0";
			size_t size;
			printf("write your string : ");
			scanf("%s", word);
			printf("write the size : ");
			scanf("%lu", &size);
			printf("your word is : %s\n", word);
			ft_bzero(word, 3);
			printf("your word after bzero is : %s\n", word);
			break;
		}
		case 9:
		{
			char src[100] = "\0";
			char dst1[100] = "hello world";
			char dst2[100] = "hello world";
			size_t size;
			printf("write your string : ");
			scanf("%s", src);
			printf("write the size : ");
			scanf("%lu", &size);
			memcpy(dst1+3, dst1, 12);
			ft_memcpy(dst2+3, dst2, 12);
			printf("your word after memcpy is : %s\n", dst1);
			printf("your word after ft_memcpy is : %s\n", dst2);
			break;
		}
		case 10:
		{
			/*char src[100] = "\0";
			char dst1[100] = "hello world";
			char dst2[100] = "hello world";
			size_t size;
			printf("write your string : ");
			scanf("%s", src);
			printf("write the size : ");
			scanf("%lu", &size);
			memmove(((void *)0), ((void *)0), 5);
			ft_memmove(((void *)0), ((void *)0), 5);
			*/printf("your word after memmove is : %s\n", memmove(((void *)0), ((void *)0), 5));
			printf("your word after ft_memmove is : %s\n", ft_memmove(((void *)0), ((void *)0), 5));
			break;
		}
		case 11:
		{
			char src[100] = "\0";
			char dst1[100] = "\0";
			size_t size;
			printf("write your string : ");
			scanf("%s", src);
			printf("write the size : ");
			scanf("%lu", &size);
			printf("ft_strlcpy return val is : %lu dst is : %s\n", ft_strlcpy(dst1,src,size),dst1);
			break;
		}
		case 12:
		{
			char src[100] = "\0";
			char dst1[100] = "\0";
			size_t size;
			printf("write your src : ");
			scanf("%s", src);
			printf("write your dst : ");
			scanf("%s", src);
			printf("write the size : ");
			scanf("%lu", &size);
			printf("ft_strlcat return val is : %lu dst is : %s\n", ft_strlcat(dst1,src,size),dst1);
			break;
		}
		case 13:
		{
			printf("dec val toupper original\n");
			for (int i = 97; i < 123; i++)
				printf("%3d  %3c = %4c %4c\n", i, i, ft_toupper(i), toupper(i));
			break;
		}
		case 14:
		{
			printf("dec val tolower original\n");
			for (int i = 65; i < 90; i++)
				printf("%3d  %3c = %4c %4c\n", i, i, ft_tolower(i), tolower(i));
			break;
		}
		case 15:
		{
			char src[100] = "\0";
			char c = '\0';
			printf("write your src : ");
			scanf("%s", src);
			printf("write your char : ");
			scanf(" %c", &c);
			printf("strchr rst is : %s\n", strchr(src,c));
			printf("ft_strchr rst is : %s\n", ft_strchr(src,c));
			break;
		}
		case 16:
		{
			char src[100] = "\0";
			char c = '\0';
			printf("write your src : ");
			scanf("%s", src);
			printf("write your char : ");
			scanf(" %c", &c);
			printf("strrchr rst is : %s\n", strrchr(src,c));
			printf("ft_strrchr rst is : %s\n", ft_strrchr(src,c));
			break;
		}
		case 17:
		{
			char s1[100] = "\0";
			char s2[100] = "\0";
			size_t n = 0;
			printf("write your s1 : ");
			scanf("%s", s1);
			printf("write your s2 : ");
			scanf("%s", s2);
			printf("choose number : ");
			scanf("%lu", &n);
			printf("strncmp rst is : %d\n", strncmp(s1,s2,n));
			printf("ft_strncmp rst is : %d\n", ft_strncmp(s1,s2,n));
			break;
		}
		case 18:
		{
			char src[100] = "\0";
			int c = 0;
			size_t n = 0;
			printf("write your src : ");
			scanf("%s", src);
			printf("write your char : ");
			scanf("%d", &c);
			printf("choose a number : ");
			scanf("%lu", &n);
			printf("memchr rst is : %s\n", memchr(src,c,n));
			printf("ft_memchr rst is : %s\n", ft_memchr(src,c,n));
			break;
		}
		case 19:
		{
			char s1[100] = "\0";
			char s2[100] = "\0";
			size_t n = 0;
			printf("write your s1 : ");
			scanf("%s", s1);
			printf("write your s2 : ");
			scanf("%s", s2);
			printf("choose number : ");
			scanf("%lu", &n);
			printf("memcmp rst is : %d\n", memcmp(s1,s2,n));
			printf("ft_memcmp rst is : %d\n", ft_memcmp(s1,s2,n));
			break;
		}
		case 20:
		{
			char s1[100] = "abcd";
			char s2[100] = "c";
			size_t n = -1;
			printf("write your haystack : ");
			scanf("%s", s1);
			printf("write your needle : ");
			scanf("%s", s2);
			printf("choose lenght : ");
			scanf("%lu", &n);
			printf("strnstr rst is : %s\n", strnstr(s1,s2,n));
			printf("ft_strnstr rst is : %s\n", ft_strnstr(s1,s2,n));
			break;
		}
		case 21:
		{
			char *str = "     \t \v   -12 34abd";
			printf("atoi rst is : %d\n",atoi(str));
			printf("ft_atoi rst is : %d\n",ft_atoi(str));
			break;
		}
		case 22:
		{
			int *t;
			t=ft_calloc(5,sizeof(int));
			for(int i=0 ; i < 5; i++)
				printf("| %d ",t[i]);
			printf("|\n");
			break;
		}
		case 23:
		{
			char *p;
			p=ft_strdup("Hello world!");
			printf("ft_strdup rst is : %s\n",p);
			break;
		}
		case 24:
		{
			char *p = "Hello World !!";
			printf("ft_substr rst is : %s\n",ft_substr(p,5,6));
			break;
		}
		case 25:
		{
			char *s1="Hello ";
			char *s2="World !!";
			printf("ft_strjoin rst is : %s\n",ft_strjoin(s1,s2));
			break;
		}
		case 26:
		{
			char *src = "   xxx   xxx";
			char *set = " x";
			printf("%s\n",ft_strtrim(src,set));
			break;
		}
		case 27:
		{
			char *s = "                  olol";
			char **rst = ft_split(s, ' ');
			int k = 0;
			while (rst[k])
			{
				printf("rst[%d] = %s\n", k + 1, rst[k]);
				k++;
			}
			break;
		}
		case 28:
		{
			int n = -15;
			printf("ft_itoa rst is : %s\n",ft_itoa(n));
			break;
		}
		case 29:
		{
			char *s = "aaaaaa";
			printf("ft_strmapi rst is : %s\n",ft_strmapi(s,&strmapi_add));
			break;
		}
		case 30:
		{
			char s[] = "000000";
			ft_striteri(s,&striteri_add);
			printf("ft_striteri rst is : %s\n",s);
			break;
		}
		case 31:
		{
			int fd = open("test_putchar.txt",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			ft_putchar_fd('c',fd);
			printf("fd = %d \n",fd);
			close(fd);
			break;
		}
		case 32:
		{
			int fd = open("test_putstr.txt",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			ft_putstr_fd("Hello World!!",fd);
			printf("fd = %d \n",fd);
			close(fd);
			break;
		}
		case 33:
		{
			int fd = open("test_putendl.txt",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			ft_putendl_fd("Skip To Next Line",fd);
			printf("fd = %d \n",fd);
			close(fd);
			break;
		}
		case 34:
		{
			int fd = open("test_putnbr.txt",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			ft_putnbr_fd(123456789,fd);
			printf("fd = %d \n",fd);
			close(fd);
			break;
		}
		case 35:
		{
			t_list *new;
			char s[100] = "\0";
			printf("write content : ");
			scanf("%s",s);
			new = ft_lstnew(s);
			lst_affich(new);
			break;
		}
		case 36:
		{
			t_list *new;
			char s[100] = "\0";
			printf("write content : ");
			scanf("%s",s);
			new = ft_lstnew(s);
			ft_lstadd_front(&all,new);
			lst_affich(all);
			break;
		}
		case 37:
		{
			printf("list size is : %d \n",ft_lstsize(all));
			break;
		}
		case 38:
		{
			lst_affich(ft_lstlast(all));
			break;
		}
		case 39:
		{

			break;
		}
		case 40:
		{

			break;
		}
		case 41:
		{

			break;
		}
		case 42:
		{

			break;
		}
		case 43:
		{

			break;
		}
		default:
		{
			printf("wrong choice !!!\n");
		}
		}

		printf("again ?(y/n) : ");
		scanf(" %c", &again);
		system("@cls||clear");
	} while (again == 'y');

	return 0;
}

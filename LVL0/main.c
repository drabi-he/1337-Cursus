#include "libft/libft.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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
			for (int i = 0; i < 128; i++)
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
			//char src[100] = "\0";
			char dst1[100] = "hello world";
			char dst2[100] = "hello world";
			size_t size;
			/*printf("write your string : ");
			scanf("%s", src);
			*/printf("write the size : ");
			scanf("%lu", &size);
			memmove(dst1+3, dst1, 12);
			ft_memmove(dst2+3, dst2, 12);
			printf("your word after memmove is : %s\n", dst1);
			printf("your word after ft_memmove is : %s\n", dst2);
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
			break;
		}
		case 14:
		{
			break;
		}
		case 15:
		{
			break;
		}
		case 16:
		{
			break;
		}
		case 17:
		{
			break;
		}
		case 18:
		{
			break;
		}
		case 19:
		{
			break;
		}
		case 20:
		{
			break;
		}
		case 21:
		{
			break;
		}
		default:
		{
			printf("wrong choice !!!\n");
		}
		}

		printf("again ?(y/n) :\n");
		scanf(" %c", &again);
		system("@cls||clear");
	} while (again == 'y');

	return 0;
}

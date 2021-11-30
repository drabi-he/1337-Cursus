#include <stdio.h>
#include "ft_printf/ft_printf.h"
#include <limits.h>

int main()
{
	printf("************ test 68 ***************\n");
	printf("%d\n",ft_printf(" %04x |\n", 16 ));
	printf("%d\n",printf(" %04x |\n", 16 ));

}


/********************* notes ************************/

/*TODO:				-				*/
// -	: works with all
// -.	: works with all
// -0	: works with s
// -0.	: error all

/*TODO:				0				*/
// 0	: error c & s & p
// 0-	: error all;
// 0.	: error c & s & p
// 0-.	: error all
// 0.-	: syntax error

/*TODO:				.				*/
// .	: works with all
// .0	: error c & p
// .-	: syntax error
// .-0	: error all
// .0-	: syntax error

/*TODO:				#				*/
// #	: works with x & X

/*TODO:				 				*/
//  	: works with d & i & s

/*TODO:				+ 				*/
// +	: works with d & i

//TODO: d & i	= - & 0 & . & sp & +
//TODO: u		= - & 0 & . &
//TODO: x & X	= - & 0 & . & #



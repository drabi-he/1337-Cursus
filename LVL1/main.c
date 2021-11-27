#include <stdio.h>
#include "ft_printf/ft_printf.h"


int main()
{
	 printf("%d\n",ft_printf(" %2p |\n", -1));
	 printf("%d\n",printf(" %2p |\n", -1 ));
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


//TODO: for p
// check if - exist
// work backwards
// check if precision exist
// if exist check precision if percision > 12 pad the diffrence with 0s in front
// if width > precision + 2 pad the diffrence with space

//14 + (precision - 14)
//14 + (width - 14) + (precision - 12)

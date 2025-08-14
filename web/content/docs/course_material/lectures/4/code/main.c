#include <stdio.h>

//This is one line comment, and it will be ignored by the compiler

/*

this 
is multiple 
lien comment

*/
int main() {
printf("this is lecture-3\n"); // this is parrtial line comment

printf("---------------------\n");
// define the variables
int a= 10,  b=20 ;
char a_char='C';
float a_float= 12.17;
char s[4]="lect";

// print all the value stored in variables

printf("%d %d\n",a, b);
printf("%c\n", a_char);
printf("%f\n",a_float );
printf("%s\n",s );
printf("-------------------\n");

// more variables
int a_int_from_scanf = 100;
char a_char_from_scanf = 'L';

//Take one char input  and store it  in the a_char_from_scanf variable 
printf("Enter your char here:   " );
scanf("%c", &a_char_from_scanf);

// take a string as input and store it  in  the 's' variable
printf("Enter your string here:  ");
scanf("%s",s);

// take an integer as input and store it in a_int_from_scanf variable
printf("Enter your number here:  ");
scanf("%d", &a_int_from_scanf);

// use printf to show all the inputs 
printf("%d\n", a_int_from_scanf);
printf("%c\n",a_char_from_scanf);
printf("%s\n", s);

// write an expression to test the order of execution of different operations
a = (a  + b) * a - a_int_from_scanf;
printf("%d\n", a);

return 0;

}

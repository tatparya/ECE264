
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This does not work... fix it.
// Hint: look up swap(int *, int *) in the course notes
void swapString(const char * a, const char * b)
{
    printf("&a = %p\n", &a);
	printf("&b = %p\n\n", &b);
	printf("a = %p\n", a);
	printf("b = %p\n\n", b);
	printf("a = %s\n", a);
	printf("b = %s\n", b);

	const char * tmp = a;

	

    a = b;
    b = tmp;
    printf("\nCalling swapString(...)\n");
    printf("&a = %p\n", &a);
    printf("&b = %p\n\n", &b);
    printf("a = %p\n", a);
	printf("b = %p\n\n", b);
	printf("a = %s\n", a);
	printf("b = %s\n", b);


	printf("&tmp = %p\n", &tmp);
	printf("tmp = %p\n\n", tmp);
}

int main(int argc, char * * argv)
{
    printf("Welcome to PA03.\n"
	   "\n"
	   "Please make sure that the swapString(...) function works\n"
	   "\n");
    
    printf("Print out some memory addresses for argc, argv...\n"
	   "to illustrate how memory is laid out.\n");
    printf("&argc = %p\n", &argc);
    printf("&argv = %p\n", &argv);
    printf("argv = %p\n", argv);
    printf("*argv = %p\n", *argv);
    printf("*argv = %s\n", *argv);
    printf("**argv = %c\n", **argv);

    // Let's create our own array of strings
    printf("\nTesting swapString(...)\n");
    const char * str1 = "one";
    const char * str2 = "two";
    printf("Before swap, str1 == %p (i.e., '%s'), \n"
	   "str2 == %p (i.e., '%s')\n\n", str1, str1, str2, str2);
    swapString(str1, str2);
    printf("After swap, str1 == %p (i.e., '%s'), \n"
	   "str2 == %p (i.e., '%s')\n\n", str1, str1, str2, str2);
	
    return EXIT_SUCCESS;
}



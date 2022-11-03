// pre-compiler inclusion commands
#include <stdio.h> // include access to the printf statement and file I/O
#include <math.h> // for sin, log command. Compile with the -lm option
double F(double x)
{
// return the requested function
return sin(x) - 2. * log(x + 1.) + x * x / 5.;
}
void write_file(char *filename, double x0, double x1)
{
// This function prints 101 values of the function F to file. The function
// evaluations lie between x0 and x1, the filename is the argument filename
int i; // define an integer i to use as loop counter
double x; // define x, which we will use to denote the current position
// within the interval.
FILE *p_file; // a pointer to a file.
// open the file for writing
p_file = fopen(filename, "w");
// perform a loop using the loop counter
for (i = 0; i <= 100; i++)
{
// set x to current position within the interval
x = x0 + i * (x1 - x0) / 100;
// step size Delta x = (x1 - x0) / 100, for 100 steps
fprintf(p_file, "%e, %e\n", x, F(x)); // print in scientific notation two
// values, the first the value of x, the second the return value of
// the function that can be found in memory starting at the location
// pointed at by p_func
}
// don’t forget to close the file afterwards
fclose(p_file);
}
int main()
{
// call the function to write the file
write_file("data.txt", 0., 5.);
return 0; // return ’all is well’ when exiting program
}
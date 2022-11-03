#include <stdio.h> // include access to printf statement
#include <math.h> // include access to the sqrt function
#include <stdlib.h> // include access to fabs function

typedef struct integraltype
{
// structure for the different integral types containing the values
// for the different integrals and the mean values of the coordinates achieved
    double p, xp, yp, zp;
    double meanx, meany, meanz;
} integraltype;

double random_double()
{
// generate the next random number from the seed, updates the seed and
// returns the seed scaled to a double between 0 (exclusive) and 1 (inclusive)
// some constants that have historically often been used for this method
    static const int a = 16807;
    static const int c = 0;
    static const long long m = 2147483647;
// a random ’seed’ value. Pick any nonzero number for a different
// random series.
    static long long seed = 1;
    seed = (a * seed + c) % m;
// scale the updated value by first typecasting it to a floating point,
// turning the division into a floating point division
    return ((double) seed) / m;
}

double f(double x, double y)
{
// function that takes x and y coordinates and returns 1 if within the given
// domain or 0 if not
    double func;
    func = sqrt(x * x + y * y);
    if (func > 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

double g(double x, double y, double z, int state)
{
// function that takes x, y and z coordinates along with a state and returns 0 if outside the domain and
// 1 or the x or y or z coordinate based on the state with which the function was ran
    if (x < 1)
    {
        return 0;
    }
    if (y < -3)
    {
        return 0;
    }
    if ((z * z + (sqrt(x * x + y * y) - 3) * (sqrt(x * x + y * y) - 3)) > 1)
    {
        return 0;
    }
    else
    {
        if (state == 1)
        {
            return x;
        }
        if (state == 2)
        {
            return y;
        }
        if (state == 3)
        {
            return z;
        }
        else
        {
            return 1;
        }
    }
}

double randomintegration(int n, int state)
{
// the random integration routine which computes the integral approximated as a sum with n iterations
// the function also takes different states as a parameter in order to be able to compute multiple integrals
    int i;
    double sum, integral;
    sum = 0;
    for (i = 0; i < n; i++)
    {
        sum = sum + g(random_double() * 3 + 1, random_double() * 7 - 3, random_double() * 2 - 1, state);
// the random double function only returns values between 0 and 1 so for each x,y,z the value is scaled
// according to the range of values the coordinates could take
    }
    double average;
    average = sum / n;
    integral = average * 42;
    return integral;
}

double regularintegration(int n, int state)
{
// the regular step integration routine which computes the integral approximated as a sum with n iterations
// the function also takes different states as a parameter in order to be able to compute multiple integrals 
    int i, j, k;
    double sum, sum2, integral;
    double x, y, z;
    double deltax, deltay, deltaz;
    double lx, ly, lz;
    x, y, z = 0.;
    deltax = 3./ n;
    deltay = 7./ n;
    deltaz = 2./ n;
    lx = 1.;
    ly = -3.;
    lz = -1.;
    sum = 0;
// the x, y and z coordinates are defined along with their respective deltas and the lower bounds they will start from
    for (i = 0; i < n; i++)
    {
        x = lx + (i + 0.5) * deltax;
        for (j = 0; j < n; j++)
        {
            y = ly + j * deltay;
            for (k = 0; k < n; k++)
            {
                z = lz + k * deltaz;
                sum = sum + g(x, y, z, state);
// x, y and z are incremented in steps of their respective deltas then put through the g function which checks they're
// within the domain and if so adds the result of g onto the sum
            }
        }
    }
    integral = sum * deltax * deltay * deltaz;
    return integral;
}

void display(integraltype *type, int state)
{
// the display function takes the pointer to the location of the integraltype and adjusts the values at the locations of the integrals and 
// mean values contained within it according to whether regular or random was passed through it
    if (state == 0)
    {
// this if statement allows to seperate the adjusting of values at the locations for integrals between the random and regular integration
        type->p = randomintegration(1000000, 0);
        type->xp = randomintegration(1000000, 1);
        type->yp = randomintegration(1000000, 2);
        type->zp = randomintegration(1000000, 3);
    }
    else
    {
        type->p = regularintegration(100, 0);
        type->xp = regularintegration(100, 1);
        type->yp = regularintegration(100, 2);
        type->zp = regularintegration(100, 3);
    }
    type->meanx = type->xp / type->p;
    type->meany = type->yp / type->p;
    type->meanz = type->zp / type->p;        
    printf("Volume integral pdxdydz: %f\n", type->p);
    printf("Volume integral xpdxdydz: %f\n", type->xp);
    printf("Volume integral ypdxdydz: %f\n", type->yp);
    printf("Volume integral zpdxdydz: %f\n", type->zp);
    printf("Mean x: %f\n", type->meanx);
    printf("Mean y: %f\n", type->meany);
    printf("Mean z: %f\n", type->meanz);
// the results stored in locations of the respective integraltype structure are all printed
}

void savetofile(integraltype *type, int state)
{
// the savetofile function takes the pointer to the location of the integraltype and adjusts the values at the locations of the integrals
// and mean values contained within it according to whether regular or random was passed through it
    FILE *fp;
    if (state == 0)
    {
// the if statement chooses which file to open and write to based on the state 
        fp = fopen("data.txt","w");
    }
    else
    {
        fp = fopen("data2.txt","w");
    }
    int n;   
    for (n = 0; n < 101; n++)
    {
// for the varying number of iterations and depending on the state the savetofile function was ran with either random or regular integration
// is computed for the given iterations and saved to the location of the passed through struct
        if (state == 0)
        {
            type->p = randomintegration(n * n * n, 0);
            type->xp = randomintegration(n * n * n, 1);
// for random n * n * n is taken as it only has 1 sum and so it goes up to a total of 1000000 iterations
        }
        else
        {
            type->p = regularintegration(n, 0);
            type->xp = regularintegration(n, 1);
// for regular only n is taken as it has 3 nested sums which will amount to n * n * n total iterations
        }
        type->meanx = type->xp / type->p;
        double xproximity;
        xproximity = fabs(type->meanx - 2.4076) / 2.4076;
// the proximity to 2.4076 for mean x is calculated, the fabs function computes the modulus of the bracket as to only give positive values
        fprintf(fp,"%d, %f\n", n * n * n, xproximity);
// the number of total iterations and the proximity to 2.4076 for the mean x for the given iterations is written to the respective file
    }
    fclose(fp);
// and the file closed after the routine has finished
}
int main()
{
// this is the main function from which the whole program is run
    int i;
    double sum, integral;
    for (i = 0; i < 1000000; i++)
    {
        sum = sum + f(random_double(), random_double());
    }
    integral = sum / 1000000;
    printf("a) Integral: %f\n", integral);
// the integral for the first part is computed within the main function similarly to how the randomintegration function does so

    integraltype random;
    integraltype regular;   
// structs of integraltype random and regular are declared

    printf("b) RANDOM INTEGRATION\n");   
    display(&random, 0);
// runs the display function passing through the location of the random struct which computes all the corresponding integrals and means
// and prints them to the terminal
    printf("b) REGULAR INTEGRATION\n");
    display(&regular, 1);
// runs the display function passing through the location of the regular struct which computes all the corresponding integrals and means
// and prints them to the terminal
    savetofile(&random, 0);
    savetofile(&regular, 1);
// the savetofile is run, passing through both the location of the random and regular struct and saving the results for varying iterations
// to their respective files
    return 0;
// returns all is well :)
}

/*=============================================================================$
|   Source code: babylonianSqrt.c
|   Author:  Alejandro Martinez
|   Student ID: 3625175
|   Assignment:  Program #2 Babylonian Square Root Calculations
|
|   Course:  [COP 4338 (Programming 3)]
|   Section:  [U04 1198]
|   Instructor:  William Feild
|   Due Date:  [10/01/2019], at the beginning of class
|
|    I hereby certify that this collective work is my own
|   and none of it is the work of any other person or entity.
|   ______________________________________ [Alejandro Martinez]
|
|  Language:  [C]
|  Compile/Run:
|             gcc -lm babylonianSqrtCalc.c -o babylonianSqrtCalc.out
|             ./babylonianSqrtCalc.out
|  +-------------------------------------------------------------------------
|
|  Description: This program determines the 'perfect numbers' from 1-100,000,
|                including both 1 and 100,000, and then computes the square
|                root of each perfect number using the Babylonian approach.
|
|               According to https://www.britannica.com/science/perfect-number,
|               the definition of a perfect number, is a positive number that
|               the sum of its divisors, not including the number itself,
|               equals to the number.
|
|               For example 6 and 28 are perfect numbers.
|
|                 6 = 1 + 2 + 3 = 6
|                 28 = 1 + 2 + + 4 + 7 + 14 = 28
|
|               As mentioned before, the program will iterate through all
|               numbers from 1 - 100,000 and will verify if the summation
|               of its factors, not including the number itself, ads up to
|               that number.
|
|               The user is required to enter a desired decimal-place
|               accuracy from 1 - 15 including both 1 and 15.
|               This decimal-place accuracy will be used to find the square
|               root of the perfect number using the mathematical series,
|               the babylonian method. According to the source below,
|               https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
|               the babylonian formula is as follows:
|
|                         ∞
|                         √S  = ∑  xn+1 = 1/2(xn + S/xn)
|                         n=0
|                         where x0 is the initial “guess”
|                         S = desired Square Root
|
|                The user input is very relevant because it represents the
|                proximity of the calculation. The lower the user input is,
|                within the range from 1 - 15, the less accurate the square
|                root approximation will be. However, the program will run
|                faster as it needs less iterations as we have less accuracy.
|                This works vice-versa if the user inputs a high value for
|                accuracy, the program will provide a more accurate result
|                but it will take longer to compute the calculations as it
|                will require more iterations.
|
|                The program will validate the input from the user, making
|                sure the user does not input any strings or letter characters.
|                After, the program validates the input, the program will print
|                the results. The results of the output will be detailed
|                explained in the Output section below.
|
|
|        Input:  Program will prompt the user to provide the desired decimal-
|                place accuracy, in the range of [1-15], inclusive. User
|                prompt must clearly indicate what is a valid input. User
|                input must be validated - ensuring that the value entered
|                is an integer in the above range.
|
|
|	    Output:  Output will include all of the perfect numbers between
|                [1-100000], along with an ordered list of their factors
|                to confirm the factors sum to the perfect number. For each
|                perfect number, the output will also include the initial
|                square root guess, the expected value using sqrt() (or a
|                similar function), your computed value for the square root
|                of that number, the required decimal-place accuracy
|                (as indicated by the user), the required threshold, and
|                the number of terms (iterations) it took to reach the required
|                decimal-place accuracy.
|
|                If output takes more than ten seconds, then a message would be
|                displayed to the screen indicating the “worst-case”
|                (approximate but accurate) for how long we should wait for
|                your results.
|
|                Results will be formatted and displayed in the following way:
|
|                    "
|                    This may take up to 30 seconds to complete…
|
|                        Perfect number: 6 = 1 + 2 + 3;
|                        Initial “guess” = 2.0
|                        Expected square root of 6 = 2.4494897…
|                        Computed square root of 6 = 2.4494897…
|                            reached in 8 iterations
|                            using threshold of 0.0000…
|                            for 12 decimal-place accuracy
|                    "
|
|                Within these results there are several things that should be
|                clarified:
|
|                Line #1 shows the perfect number found and its factors.
|                Line #2 shows an initial guess needed for the babylonian
|                   method. The initial guess its a variable  generated by
|                   our program. All details of this function will be explained
|                   in description of function
|                   generateGuess(int perfectNumber))
|                   This similar output will be shown for all perfect numbers
|                   found between our range of [1-100,000].
|                 Line #3 shows the expected square root, that is not part of
|                   our babylonian calculation but rather is a computation used
|                   for comparision.
|                 Line #4 shows the computed square root by the babylonian.
|                 Line #5 show the number of iterations it took to complete the
|                   babylonian calculation.
|                 Line #6 is the threshold or the discrepancy of our
|                   approximation. I highly recommend reading the source of the
|                   babylonian definition to understand this better.
|                 Line #7 is the accuracy of the calculation that the user
|                   desired.
|
|
|     Process:   The program's steps are as follows:
|
|                1. The program displays its purpose
|                2. The user its prompt to enter an integer from the range
|                   1-15.
|                3. If the input is valid the perfect squares are found between
|                   1-100,000, the factors of each perfect square is found,
|                   and the square root is found using the Babylonian method.
|                4. The results of the each perfect number are shown as stated
|                   in the Output Section.
|
|.  Source of Formulas Required For Calculations:
|                Refer to the link below for full explanation of what is a
|                perfect number and how to find it.
|               https://www.britannica.com/science/perfect-number
|
|                Refer to the link below for full explanation of what is a
|                Babylonian Series and how to calculate it.
|
|               https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
|
|                Formula used for the babylonian is:
|                |              ∞
|                         √S  = ∑  xn+1 = 1/2(xn + S/xn)
|                               n=0
|                         where x0 is the initial “guess”
|                         S = desired Square Root
|
|   Required Features Not Included:
|                Not included: All required features are included.
|
|   Known Bugs:  Not know Bugs in this program
|
|
|
|  *=====================================================================
|  */

#include <stdio.h>
#include <math.h> //Used for square root and pow computations
#include <ctype.h> //Used for computation isDigit()
#define DBL_EPISILON 2.2204460492503131e-16 //Used for input = 15
#define LOWER_BOUND_FOR_INPUT 1 //Lower bound for input
#define UPPER_BOUND_FOR_INPUT 15 //Upper bound for input
#define LOWER_BOUND_FOR_PERFECTNUMBERS 1 //Lower bound for loop
#define LOWER_BOUND_FOR_RANGE 1 //Lower bound of range
#define UPPER_BOUND_FOR_PERFECTNUMBERS 100000 //Upper limit of range
#define FALSE_STATUS 0 //Used to state an operation is FA:SE
#define TRUE_STATUS 1 //Used to state an operation is TRUE
#define EMPTY_INPUT -1 //Indicates that input stream has nothing
#define NO_ERROR 0


/*     *Function Prototypes*     */
void explainTheProgram ();
int requestInput();
int numberRange (int numberToCheck);
void perfectNumberCalculation(int validatedUserInput);
void isTheNumberPerfect(int numberToCheck, int userInput);
void findFactors(int perfectNumber);
void expectedSquareRoot (int perfectNumber);
void babylonianCalculation(int perfectNumber, int userInput, float guess);
float generateGuess (int perfectNumber);


int main() {

    //Explain the user the intention of the program.
    explainTheProgram ();
    /*
     * Prompt & Read input from the user, the input from the user
     * will be assigned to variable input.
     * */
    int input = requestInput();

    /*
     * Find perfect numbers in our desired range, compute initial
     * babylonian guess, calculate the expected square root result,
     * calculate the babylonian square approximation with all other
     * variables derived from the babylonian such as the threshold
     * and iterations done for calculation
     * */
    perfectNumberCalculation (input);


    return NO_ERROR;
}

/*----------------------- explainTheProgram() -------------------------
|   Function explainTheProgram()
|
|   Purpose:  This function explains the purpose of the program to the user.
|
|    @param  none
|
|    @return  none
 *-------------------------------------------------------------------*/

void explainTheProgram ()
{
    printf("%s", "\nWelcome to the  Perfect Numbers and Babylonian\n"
                 "Calculations game. This is a program that will calculate\n"
                 "the perfect numbers from [1-100000], inclusive.\n"
                 "If you have any questions on what is a perfect number\n"
                 "please refer to our detailed documentation.\n\n"
                 "After finding the perfect numbers, the program will\n"
                 "use the babylonian method to approximate the square\n"
                 "root of the perfect number. Now, in order to compute\n"
                 "the Babylonian method, please provide the accuracy\n"
                 "you would like for the calculation.\n\n");
}

/*---------------------------- requestInput() -------------------------
|   Function  requestInput()
|
|   Purpose:  Validate the input of the user. This function validates
|             for characters that are not integers or integers that
|             are not in the desired range of accuracy.
|
|    @param  none
|
|   @return  validatedNumber, int, validated integer for the required
|            decimal accuracy.
 *-------------------------------------------------------------------*/

int requestInput()
{
    int input = 0;
    int status = 0;
    int validatedNumber = 0;
    int validatedInput = 0;

    do
    {
        int checkChar = EMPTY_INPUT;

        printf("%s", "Please input an integer from [1-15], inclusive.\n"
                     "Make sure you do not put a string or characters that\n"
                     "are not numbers. Enter the number: ");

        /*
        Assigning scanf to an int variable allows us to know if the user input
         the correct data type. If the user did not input a correct data type
         status will be 0. If the user did status will return 1.
        */
        status = scanf("%d", &input);

        /*
            This clears up the input stream every time a scanf is performed.
            While it does so, it checks for non-digits in the input,
            like letters or periods or whatever. Newline doesn't count
            since there will always be a newline.
        */
        while (checkChar != '\n')
        {
            checkChar = getchar();
            if (!isdigit(checkChar) && checkChar != '\n')
            {
                status = FALSE_STATUS;
            }

        }

        if (status == TRUE_STATUS)
        {
            validatedNumber = input;
            validatedInput = numberRange(validatedNumber);
        }

    } while( status != TRUE_STATUS || validatedInput == FALSE_STATUS );

    printf("%s\n", "");

    return validatedNumber;

}

/*------------------- numberRange(int numberToCheck) ------------------
|   Function  numberRange(int numberToCheck)
|
|   Purpose:  Validates if the input number of the user is within
|             the required range.
|
|    @param  numberToCheck, int, input number from the user to check.
|
|   @return  statusOfNumber, int, returns 0 if number is not in the
|                                 range or 1 if number is in the range
 *-------------------------------------------------------------------*/
int numberRange (int numberToCheck)
{
    /*
    statusOfNumber is a boolean that indicates 1 if it's in the range,
     or 0 if it's not.
    */
    int statusOfNumber = TRUE_STATUS;
    if (numberToCheck < LOWER_BOUND_FOR_INPUT ||
            numberToCheck > UPPER_BOUND_FOR_INPUT)
    {
        printf("%s\n", "Please input a number from the required range ");
        statusOfNumber = FALSE_STATUS;
    }

    return statusOfNumber;

}

/*------- perfectNumberCalculation(int validatedUserInput) ------------
|   Function  perfectNumberCalculation(int validatedUserInput)
|
|   Purpose:  This function will iterate for our targeted range
|               [1-100,0000]. It will call function
|               isTheNumberPerfect(counter, userInput) to know
|               if the number in the range is a perfect number.
|
|   Citation for the Explanation Below:
|       https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
|
|    Calculation Explanation:
|               Nobody has ever found an odd perfect number.
|               According to the site stated above it can be infer
|               that any number used in real life that is odd will not
|               be a perfect number. Therefore, in order to gain
|               efficiency in the algorithm, the program does modulus 2
|               to know if the number is even, and therefore have a real
|               possibility to be perfect.
|
|    @param  validatedUserInput, int, validatedInput from the user
|
|   @return  none
 *-------------------------------------------------------------------*/

void perfectNumberCalculation(int validatedUserInput)
{
    int counter = 0;

    printf ("\n%s\n\n", "This may take up to 25 seconds to complete.. ");

    for(counter = LOWER_BOUND_FOR_PERFECTNUMBERS;
        counter <= UPPER_BOUND_FOR_PERFECTNUMBERS; counter++)
    {
        if (counter % 2 == 0)
        {
            isTheNumberPerfect(counter, validatedUserInput);
        }
    }
}

/*------ isTheNumberPerfect(int numberToCheck, int userInput) --------
|   Function  isTheNumberPerfect(int numberToCheck, int userInput)
|
|   Purpose:  This function will add the factors of the parameter
|               'numberToCheck' and will state if the number is
|                perfect or not. This will be done by adding the
|                factors and seeing if adds to the 'numberToCheck'
|
|   Citation  Refer to the following citation to know more about
|               perfect numbers:
|             https://www.britannica.com/science/perfect-number
|
|   Calculation: The formula to find perfect numbers will be
|               shown in the code as:
|
|               (perfectNumber % counter == 0)
|
|    @param  numberToCheck, int, number that will be checked
|            userInput, int, input from the user
|
|   @return  none
 *-------------------------------------------------------------------*/

void isTheNumberPerfect(int numberToCheck, int userInput)
{

    int counter, sum = 0;

    for (counter = LOWER_BOUND_FOR_RANGE; counter < numberToCheck;
            counter++)
    {
        if (numberToCheck % counter == 0)
        {
            sum = sum + counter;
        }
    }

    /*If the sum of the factors equal to the number then the
     * number is perfect*/

    if (sum == numberToCheck)
    {
        printf("%s","Perfect Number: ");
        printf("%d\t", numberToCheck);
        printf("%s", " = ");
        findFactors(numberToCheck);

        float guess;
        guess = generateGuess(numberToCheck);
        expectedSquareRoot (numberToCheck);
        babylonianCalculation(numberToCheck, userInput,guess);

    }
}

/*---------------- findFactors (int perfectNumber) ------------------
|   Function  findFactors (int perfectNumber)
|
|   Purpose:  This function will print the factors of the
|               perfect number.
|
|      Citation:  https://www.britannica.com/science/perfect-number
|
|   Calculation: The formula to find perfect numbers will be
|               shown in the code as:
|
|               (perfectNumber % counter == 0)
|
|    @param  perfectNumber, int, number to find the factors of
|               perfect numbers.
|
|   @return  none
 *-------------------------------------------------------------------*/

void findFactors (int perfectNumber)
{
    int counter = 0;
    int factor, sum = 0;

    for (counter = LOWER_BOUND_FOR_RANGE; counter < perfectNumber;
            counter++)
     {
         if (perfectNumber % counter == 0)
         {
             sum = sum + counter;
             factor = counter;
             printf("%d", factor);

             if (sum < perfectNumber)
             {
                 printf("%s", " + ");
             }
             else{
                 printf("%s", "  ");
             }
         }
     }
    printf("%s\n", "");
}

/*---------------- expectedSquareRoot (int perfectNumber) --------------
|   Function  expectedSquareRoot (int perfectNumber)
|
|   Purpose:  This function will use the square root from the math library
|               to know the exact square root of the perfect number.
|
|    @param  perfectNumber, int, number to compute the square root
|
|   @return  none
 *-------------------------------------------------------------------*/

void expectedSquareRoot (int perfectNumber)
{
    float expectedSQRoot;

    expectedSQRoot = sqrtf(perfectNumber);
    printf("%s", "The Expected Square Root is ");
    printf("%d", perfectNumber);
    printf("%s", " = ");
    printf("%.15f\n", expectedSQRoot);
}

/*--babylonianCalculation(int perfectNumber, int userInput, int guess)--
|   Function  babylonianCalculation(int perfectNumber, int userInput,
|                                   int guess)
|
|   Purpose:  The purpose of this function is to calculate the
|               approximated square root using the babylonian method.
|               As explained in the documentation this calculation
|               will use the userInput to have an accurate result.
|   Formula:
|
|   Computation for Accuracy:
|   Citation: https://en.wikipedia.org/wiki/Accuracy_and_precision
|
|               The accuracy of the threshold is computated by the
|               following formula:
|
|               Accuracy = 1 / (pow(10,userInput))
|
|   Computation for Delta:
|              The program uses the function fabs from the math
|               library here. fabs takes the absolute value of the
|               previous and actual guess.
|
|              fabsf(temp - computatedGuess) > accuracy
|
|   Computation for Babylonian:
|   Citation: https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
|                         ∞
|                         √S  = ∑  xn+1 = 1/2(xn + S/xn)
|                         n=0
|                         where x0 is the initial “guess”
|                         S = desired Square Root
|
|               In the code will be shown as follows:
|               computatedGuess = (computatedGuess +
|                               (desiredSqrt/computatedGuess)) / 2;
|
|
|
|    @param  perfectNumber, int, perfectNumber to the calculations
|            userInput, int, number used for desired accuracy
|            guess,
|
|   @return  none
 *-------------------------------------------------------------------*/

void babylonianCalculation(int perfectNumber, int userInput, float guess)
{
    float desiredSqrt = perfectNumber;
    float computatedGuess = guess;
    float accuracy = 1 / (pow(10,userInput)); //Refer to formula in docs.
    float previousComputation = 0;
    float delta = 0;
    int numberOfIterations = 0;

    if (userInput == UPPER_BOUND_FOR_INPUT)
    {
        accuracy = DBL_EPISILON;
    }

    while (fabsf(previousComputation - computatedGuess) > accuracy) {
        previousComputation = computatedGuess;
        computatedGuess = (computatedGuess + (desiredSqrt/computatedGuess)) / 2;
        delta = fabsf(previousComputation - computatedGuess);
        numberOfIterations++;
    }

    printf("%s", "Computed Square root of ");
    printf("%d", perfectNumber);
    printf("%s", " = ");
    printf("%.*f\n", userInput, computatedGuess);

    printf("\t%s", "reached in ");
    printf("%d", numberOfIterations);
    printf("%s\n", " iterations");

    printf("\t%s", "using threshold of ");
    printf("%.*f\n", userInput, delta);

    printf("\t%s", "for ");
    printf("%d", userInput);
    printf("%s\n\n", " decimal-place accuracy");

}

/*---------------- generateGuess (int perfectNumber) -----------------
|   Function  generateGuess (int perfectNumber)
|
|   Purpose:  This function will guess estimate the initial guess
|               required by the babylonian method.
|
|   Explanation of GeneratingGuess:
|           The program is generating the guess by dividing the
|           perfect number by 2.
|
|           guess = perfectNumber / 2;
|
|           This is a trivial guess that approximates our answer to the
|           desired square root. This trivial guess is not
|           mathematically proven.
|
|    @param  perfectNumber, int, perfectNumber used to compute guess
|
|   @return  numberToApproximate, int, babylonian guess
 *-------------------------------------------------------------------*/

float generateGuess (int perfectNumber)
{
    float numberToApproximate;
    numberToApproximate = perfectNumber / 2;
    printf("%s", "The initial guess is ");
    printf("%.3f\n", numberToApproximate);

    return numberToApproximate;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// functions prototypes
unsigned int long computeString_BitMask(char *word, int size);
void compute_CheckSum(int size, char *input, unsigned int long *check);
void computeCheckSum_InputFile(char *filename, int size);
// main function
int main(int argc, char *argv[])
{
   // define the string fileName to store the name of the file
   // from the command line argument
   char *fileName = malloc(sizeof(char) *30);
   // declare the variable to store the checksum bit size
   int checkSumBits;
   // if arguments at command line are less than 2 then display
   // an error message
   if(argc < 2)
   {
       printf("Error! Insufficient arguments are provided at command line.\n");
       printf("At the command line pass the input file name followed by the checksum size\n");
   }
   // otherwise, get the arguments from the command line and
   // compute the checksum for the given file.
   else
   {
       // copy the name of the file into fileName
       strcpy(fileName, argv[1]);
       // convert the second argument into int and store it in
       // checkSumBits variable
       checkSumBits = atoi(argv[2]);
       // check whether the value of the checkSumSizes are 8, 16, or 32
       if(checkSumBits != 8 && checkSumBits != 16 && checkSumBits != 32)
       {
           fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
           return;
       }
       // call the
       computeCheckSum_InputFile(fileName, checkSumBits);
   }
   // to pause the screen from being closed
   getchar();
   getchar();
   return 0;
}
// computeCheckSum_InputFile() function, accepts a string(char pointer) and
// an integer.
// This function reads the data from the file, computes the checksum value and
// displays the check sum size, check sum value, and the count of characters
void computeCheckSum_InputFile(char *filename, int checkSumSize)
{
   // declare a file pointer
   FILE *fileInput;
   // declare and initialize the requried variables to the default values
   int charValue = 0;  
   int characterCnt = 0;
   // compute the length of the word
   int length_of_word = checkSumSize / 8 + 1;
   // allocate memory to the checksum and sets the variable to zero
   unsigned int long *checksum = calloc(1, sizeof(unsigned int long));
   // allocate memeory for the input char pointer
   char *inputChar = malloc(sizeof(char) * length_of_word);
   // define the iterative variables
   int i = 0, j = 0, k =0;
      
   // open the file in read mode
   fileInput = fopen(filename, "r");
   // if fileInput pointer is null, display the error message and
   // return
   if(fileInput == NULL)
   {
       printf("ERROR! Unable to open the file.\n");
       return;
   }
   // otherwise, perform the following steps to compute
   // the checksum and count of characters in the file until
   // the pointer reaches the end of file
   while(charValue != EOF)
   {
       // if the remaining of the length of word is 1 then do the
       // following
       if(length_of_word - i == 1)
       {
           // set the termination character to output
           inputChar[i] = '\0';
           // display the string stored in inputChar
           printf("%s", inputChar);
           // call the function compute_CheckSum() to compute the checksum for the
           // string inputChar and checksum
           compute_CheckSum(checkSumSize, inputChar, checksum);
           // increment the j value
           j++;
           // reset the value of i to zero
           i = 0;
                      
           // condition to check wether the given length of the line(word)
           // is equal to 80 characters if so, then move the cursor to
           // newline
           if(j * (length_of_word - 1) == 80)
               printf("\n");
       }
       // otherwise, do the following
       else
       {
           // read the character from the fileInput
           charValue = fgetc(fileInput);
           // if the charValue is EOF, then do the following
           if(charValue == EOF)
           {
               // check whether the checkSumSize is 16 or 32, if so
               // do the following
               if(checkSumSize == 16 || checkSumSize == 32)
               {
                   // condition to check whether the remaining length is not
                   // either one or length of word, then compute the required
                   // values
                   if(length_of_word - i != 1 && length_of_word - i != length_of_word)
                   {
                       // set the k iterator to zero
                       k = 0;
                       // loop unitl the remaining length of word is
                         // either one or length of word
                       while(length_of_word - i != 1 && length_of_word - i != length_of_word)
                       {
                           // set the 'X' value to inputChar at index i
                           inputChar[i] = 'X';
                           // increment i value
                           i++;
                           // increment the k value
                           k++;
                       }
                       // set the i'th character of inputChar to termination
                       // character
                       inputChar[i] = '\0';
                       // display the inputChar (string) read from the file
                       printf("%s", inputChar);
                       // call the function compute_CheckSum() to compute the checksum for the
                       // string inputChar and checksum
                       compute_CheckSum(checkSumSize, inputChar, checksum);
                       // increment j value
                       j++;
                       // increment the characterCnt value
                       characterCnt += k - 1;
                       // reset the i value to zero
                       i = 0;
                                              
                       // condition to check wether the given length of the line(word)
                       // is equal to 80 characters if so, then move the cursor to
                       // newline
                       if(j * (length_of_word - 1) == 80)
                           printf("\n");
                   }
                   // otherwise break
                   else
                       break;
               }
               // otherwise break
               else
                   break;
           }
           // otherwise, set the charValue to inputChar at index i
           else
               inputChar[i] = charValue;
           // increment the charterCnt
           characterCnt++;
           // increment the i value
           i++;          
       }
   }
   // close the file
   fclose(fileInput);
   printf("\n");
   // display the computed value
   printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, *checksum, characterCnt);
}
// function compute_CheckSum() accepts an int, character pointer and a unsigned int long
// variable. This function computes the checksum for the given string value inputString
// and returns the value through checksum variable
void compute_CheckSum(int checkSumSize, char *inputString, unsigned int long *checksum)
{
   // declare the unsigned int long variable bitMask
   unsigned int long bitMask;
   // call the function computeString_BitMask() by passing the
   // inputString and checkSumSize
   bitMask = computeString_BitMask(inputString, checkSumSize);
   // steps to calculate the checksum
   *checksum = bitMask + *checksum;
   *checksum = *checksum << (64 - checkSumSize);
   *checksum = *checksum >> (64 - checkSumSize);
}
// function computeString_BitMask() accepts character pointer and int variable.
// This function computes the masked bit value for the given string value inputString
// and returns the value of maskedBits
unsigned int long computeString_BitMask(char *inputString, int checkSumSize)
{
   // declare the iterative variable
   int i = 0;
   // declare the unsigned int long variable which holds
   // masked bits value
   unsigned int long maskedBits;
   // set the starting value of inputString(ASCII) into maskedBits
   maskedBits = inputString[i];
   // decrement the checkSumSize by 8
   checkSumSize -= 8;
   // loop until checkSumSize is zero
   while(checkSumSize != 0)
   {
       // compute the value for maskedBits
       maskedBits = (maskedBits << 8) + inputString[i + 1];
       // decrement the checkSumSize by 8
       checkSumSize -= 8;
       // increment the value of i
       i++;
   }
   // return maskedBits value
   return maskedBits;
}

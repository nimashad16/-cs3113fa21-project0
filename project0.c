//
//  main.c
//  Project 0
//
//  Created by Nima $wagaram on 10/13/21.
//  Copyright © 2021 Nima $wagaram. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1112000


struct element{                                         //This will store the unicode chars in a struct
    int counter;
    int size;
    
    unsigned char byte_size1;
    unsigned char byte_size2;
    unsigned char byte_size3;
    unsigned char byte_size4;
};



void swapUniCode (struct element  *pos1, struct element *pos2) {          //Will swap the two positions of the object values of two different uni characters
    int newSize;
    int newCounter;
    
    unsigned char store1 = pos1->byte_size1;                        //Stores the positions of the bytes
    unsigned char store2 = pos1->byte_size2;
    unsigned char store3 = pos1->byte_size3;
    unsigned char store4 = pos1->byte_size4;
     
    newSize = pos1->size;
    newCounter = pos1->counter;
    
    pos1->byte_size1 = pos2->byte_size1;                            //assigns the different byte size to their respected positions
    pos1->byte_size2 = pos2->byte_size2;
    pos1->byte_size3 = pos2->byte_size3;
    pos1->byte_size4 = pos2->byte_size4;
    pos1->size = pos2->size;
    pos1->counter = pos2->counter;
   
    pos2->byte_size1 = store1;                                  //Stores the bytes in to another unsigned char storage variable
    pos2->byte_size2 = store2;
    pos2->byte_size3 = store3;
    pos2->byte_size4 = store4;
    pos2->size = newSize;                                       //Updates the size to go back to the original position
    pos2->counter = newCounter;
}


void printValues(struct element values[], int sizeOfStruct){                         //Sorts the values and then prints them after swapping
    int maximum;
    int a;
    int b;
    for (a = 0; a<sizeOfStruct - 1; a++){                                   //In charge of finding the new max in each of the arrays
        maximum = a;
        for (b = a + 1; b < sizeOfStruct; b++) {
            if (values[b].counter > values[maximum].counter)
                maximum = b;
        }
        if (maximum != a) {
            swapUniCode(&values[a], &values[maximum]);
        }
    }
    
    
    for (a  = 0; a < sizeOfStruct; a++){                      //This for loop will print out the values
        unsigned char byteArray[4];
        byteArray[3] = values[a].byte_size4;
        byteArray[2] = values[a].byte_size3;
        byteArray[1] = values[a].byte_size2;
        byteArray[0] = values[a].byte_size1;
      
        unsigned char *characters = &byteArray[0];
        
     
        printf("%s", characters);                                       //Will print the characters and their values
        printf("->");
        printf("%d\n", values[a].counter);
    }
}

int main(int argc, char **argv){
    
    struct element *UTFG;
    UTFG = malloc(MAX_SIZE * sizeof(struct element));    //This will point to the variable in the memory
     
    memset(UTFG, 0, sizeof(UTFG));
    
     int result;                                     //stores byte size result
     int memory = 0;                                    //Accesses the struct variables from the memory
     int compare = 0;                               //int variable to compare 2 unicode characters
     int x;                                         //reads in first byte of unicode character
     char secChar;                                   //Stores the bytes of the characters
     char thirdChar;
     char fourthChar;
    char letter;
    letter = fgetc(stdin);                         //Gets the letter of the standard input
    
    
   
   
    while (letter  != EOF) {                //This will determine the number of bytes to be assigned
        if ((unsigned char) letter < 192){
            result = 1;
        }
        else if ((unsigned char) letter >= 192 & (unsigned char)letter < 224){
            result = 2;
        }
       else if ((unsigned char) letter >= 224 & (unsigned char)letter < 240){
            result = 3;
        }
       else{
            result = 4;
        }
        
        
        if (result == 2){                              //Will use the variable to assign the character
            secChar = fgetc(stdin);
        }
       else if (result == 3) {
            secChar = fgetc(stdin);
            thirdChar = fgetc(stdin);
        }
        else if (result == 4) {
            secChar = fgetc(stdin);
            thirdChar = fgetc(stdin);
            fourthChar = fgetc(stdin);
        }
           
            for (x = 0; x < memory; x++) {              //Check to determine if the unicode was already put in
                if (result == 4){
                                 compare = (UTFG[x].byte_size1 == (unsigned char) letter) & (UTFG[x].byte_size2 == (unsigned char) secChar) &
                                       (UTFG[x].byte_size3 == (unsigned char) thirdChar) & (UTFG[x].byte_size4 == (unsigned char) fourthChar);
                             }
                else if (result == 3){
                    compare = (UTFG[x].byte_size1 == (unsigned char) letter) & (UTFG[x].byte_size2 == (unsigned char) secChar) & (UTFG[x].byte_size3 == (unsigned char) thirdChar);
                }
                else if (result == 2){
                    compare = ((UTFG[x].byte_size1 == (unsigned char) letter) & ((UTFG[x].byte_size2) == (unsigned char) secChar));
                }
                
               else if (result == 1){
                    compare = (UTFG[x].byte_size1 == (unsigned char) letter);
                }
              
                if (compare == 1){
                    break;
                }
            }
        if (compare == 1){                           //Increases the count of unicode characters
                UTFG[x].counter++;
            compare = 0;
             letter = fgetc(stdin);
        }
        else {
                UTFG[memory].counter++;
            if (result == 1) {                                          //Uses the result that was assigned to determine the letter in the UTFG array
                    UTFG[memory].byte_size1 = (unsigned char) letter;
            }
                else if (result == 2) {
                    UTFG[memory].byte_size1 = (unsigned char) letter;
                    UTFG[memory].byte_size2 = (unsigned char) secChar;
                }
                else if (result == 3){
                    UTFG[memory].byte_size1 = (unsigned char) letter;
                    UTFG[memory].byte_size2 = (unsigned char) secChar;
                    UTFG[memory].byte_size3 = (unsigned char) thirdChar;
                }
               else if (result == 4){
                    UTFG[memory].byte_size1 = (unsigned char) letter;
                    UTFG[memory].byte_size2 = (unsigned char) secChar;
                    UTFG[memory].byte_size3 = (unsigned char) thirdChar;
                    UTFG[memory].byte_size4 = (unsigned char) fourthChar;
                }
               else{
                   break;
               }
                compare = 0;
             letter = fgetc(stdin);
                UTFG[memory].size = UTFG[memory].byte_size1 + UTFG[memory].byte_size2 + UTFG[memory].byte_size3 + UTFG[memory].byte_size4;
                memory++;
            }
    }
    printValues(UTFG, memory);
    return 0;
}


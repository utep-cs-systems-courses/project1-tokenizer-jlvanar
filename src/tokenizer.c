#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokenizer.h"

/*
 * So this whole program is supposed to do a couple things IAW the tokenizer.h file. 
 * The gist is that it's meant to take in a number of strings, and transform each word 
 * into a token, and store it.
 * First we've got to put the pieces together.
 */

int space_char(char c)
{
  /*
   * This bad boy is supposed to return true if char c is not a whitespace character
   * i.e. 'tab', 'space', etc. It should also generate a false when reading a 0 terminator. 
   */
  if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'){
    // if c is a whitespace character, return true
    return 1;
  }
  else{ //otherwise, false
    return 0;
  }
}

int non_space_char(char c)
{
  /* 
   * return true if c is not a whitespace char, otherwise return false. 
   * Must return false on 0 terminator.
   */
  
  if (c == '0' || !space_char(c)){
    // false if 0 terminator, or not a whitespace character
    return 0;
  }
  else{ // otherwise, return true
    return 1;
  }
  
}

char *word_start(char *word)
{
  /* This one returns a pointer that references the first terminator char after *word */

    /*
     * so let's say we have a space char
     * check it, probably with space_char()
     * now we gotta increment to the next char in the array
     * is this a pointer thing?
     * feels like a pointer thing
     * definitely a pointer thing
     * either way, keep checking c until it returns a value not consistent with any space chars
     * kinda cut and dry, now that I've got the theory down
     */
  
  while (space_char(*word)){ //checks if *word points at a space char
    word++;                  //increments to the next char
    }
  return word;              //returns a pointer referencing the first non-space char come across
}

char *word_terminator(char *word)
{
  /*
   * this one returns a pointer that referencing the zero terminator at the end of a word
   */

  /*
   * let's think this through
   * assume we aren't at a terminator
   * make a temp pointer
   * iterate through a word using...non_space_char?
   * non_space_char returns false on a 0
   * function works for finding 0 terminators or whitespace characters
   */

  while (non_space_char(*word)){
    // if the char pointed to by temp is not a whitespace character, increment
    word++;
  }
  return word; // return pointer referencing 0 terminator or whitespace signifying word-end
}

int count_words(char *str)
{
  /* This exists to count the number of words in *str */

  
  /* 
   * Bear with me, gonna have to think through this one
   * prolly gonna need a while loop to iterate through the array
   * maybe two, one to iterate over a given word to find the end
   * and another to increment at the end of every word
   * but how do we know we're at the last word?
   */
  
  /* 
   * assuming we're getting the beginning of the array, we:
   * use space_char to get to the end of the word
   * increment the counter
   * use non_space_char to find the beginning of the next word
   * repeat
   * USE WORDSTART AND WORDTERMINATOR
  */
  int counter = 0;
  str = word_start(str); // ensure we're at the start of a word
  while (*str != '\0')
    {
      str = word_terminator(str);
      counter++;
    }
counter++; //increment counter a final time for last word
return counter; //return counter, which contains a full count of the words before reaching zero terminator
}

char *copy_str(char *inStr, short len)
{
  
  /* 
   * this one may be a doozy and take some thinking
   * no need for temporary pointer  
   */

  char *copiedStr = (char*)(malloc(word_terminator(inStr) - word_start(inStr)));
  /* malloc for an array the length of the word (terminator - start) */
  char *temp = copiedStr; //point at the new array

  for (int i = 0; i < len; i++)
    { 
      copiedStr[i] = *temp++; //no need to increment temp
    }
  copiedStr[len] = '\0'; //add a terminator at the last position of the array
  return copiedStr; // return a copy of the original string 				 
}

char **tokenize(char *str)
{
  /* 
   * dip into already created methods
   * introduce a counter checked against length
   * DON'T FORGET TO INCREMENT COUNTER
   */
  int word_count = count_words(str); //important for data allocation
  char **tokens = (char**)malloc(sizeof(char**) * (word_count+1)); //extra space for terminator
  /*
   * initialize positional pointers and word length
   */
  
  char *head = str;
  char *tail = word_terminator(str);
  int length;

  if(word_count == 0) {return tokens;} // quick null check

  /*
   * loop using word count, ignore terminator since there won't be one between words
   */

  for (int index = 0; index < word_count; index++)
    {
      /*
       * start work if whitespace
       */
      if (space_char(*head))
	{
	  /*
	   * get start of next word
	   */
	  head = word_start(head);
	  /*
	   * get end of same word
	   */
	  tail = word_terminator(head);
	}
      /* 
       * calculate individual word length
       */
      length = tail - head;
      tokens[index] = malloc(sizeof(char) * length);

      /*
       * loop through the current word, placing every char into it's own element in tokens
       */
      for (int windex = 0; windex < length; windex++)
	{
	  tokens[index][windex] = head[windex];
	}
      /* 
       * position head pointer for the logic of the next word
       */
      head = tail;
	
    }
  /* 
   * slap a terminator on it send it out
   */
  tokens[word_count] = '\0';
  return tokens;
}

void print_tokens(char **tokens)
{
  /*
   * time for a terminator search
   */
  for (int index = 0; tokens[index] != NULL; index++)
    {
      /*
       * print it
       */
      printf("%d. %s \n", index, tokens[index]);
    }
}

void free_tokens(char **tokens)
{
  /*
   * free *each* element
   * THEN free array at end
   */
  for (int index = 0; tokens[index] != NULL; index++)
    {
      /*
       * free *each* element
       */
      free(tokens[index]);
    }
  /* 
   * free the array at the end
   */
  free(tokens);
}

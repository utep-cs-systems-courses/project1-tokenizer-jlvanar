#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"

/* 
 * I feel like I probably don't have to rewrite the function definitions in the header?
 */

List *init_history()
{
  List *history = (List*)malloc(sizeof(List));
  /* arrows for attributes, not dots */
  history -> root = NULL;

  return history;
}

void add_history(List *list, char *str)
{
  /* 
   * Here goes the signature giant comment block
   * prolly make an Item pointer and point at the List head first
   * make a new node first, or find the tail first?
   * eh, prolly get the node skeleton set up first, THEN find the tail
   * and then its that pointer algorithm
   * > tail's next points at new node
   * > new node's id is the old tail's id +1
   * gonna have to think about how to load it, might come up with something next time
   */
  
  /* 
   * Item pointer referencing List head 
   */
  Item *current_link = list -> root;

  /* 
   * make the link that's gonna be slapped on the end
   */
  Item *new_link = malloc(sizeof(Item));

  /*
   * load inputted string into str field and point to nothing
   */
  new_link -> str = str;
  new_link -> next = NULL;

  /* 
   * okay, newLink -> str is now pointing at the new string
   * not enough, though
   * link needs it's own copy of the data
   * so let's make room for them parameters and point at the string to be copied
   * we can actually add it to the node when it's all manipulated
   */
  short length = 0;
  
  /* 
   * if its an empty list, though, just put the newLink in front
   */
  if (current_link == NULL)
    {
      list -> root = new_link;
      new_link -> id = 0;
      /* 
       * if the list ISN'T empty, find that tail
       */
    } else {
    while (current_link -> next != NULL)
      {
	/*
	 * move link-next forward one more space to dangle into ether 
	 */
	current_link = current_link -> next;
      }
    /*
     * now that the link-next is dangling, hook it up to the new_link
     */
    current_link -> next = new_link;
    new_link -> id = current_link -> id+1;
  }

  /*
   * get that string length
   */
  length = (word_terminator(str) - word_start(str));

  /*
   * ALLOCATE the memory for the string
   */
  char *fresh_word = (char*)malloc(sizeof(char));
  fresh_word = copy_str(str, length);
  /*
   * point new-str at the copied string
   */
  new_link -> str = fresh_word;
}

char *get_history(List *list, int id)
{
  /*
   * A lot of the same work done on the previous method needs to be done here
   * instead of seeking the tail, iterate until id
   * ensure error messages on account of bad id
   */
  
  Item *current_link = list -> root;

  /*
   * Null check, put your hands up
   * I guess print to let users know they sent in an empty List
   * ha, I wonder if I can send a string back as a pointer instead of the expected String
   * should work, right?
   */
  if (current_link == NULL)
    {
      return "History is empty, unable to retrieve data.";
    }else{
  /*
   * lets go find that tail again
   * this is exactly why people make functions for this
   * why not do it pretty much the same way?
   */
    while (current_link != NULL)
      {
	if (current_link -> id == id)
	  {
	    return current_link -> str;
	  }
	/*
	 * ITERATE IN THE WHILE
	 */
	current_link = current_link -> next;
      }

    /*
     * if it makes it out without finding the id, print a bad id message
     */
    return "The requested ID was not found in the History.";
}

  void print_history(List *list)
  {
    /*
     * heey, it's pretty much the same algorithm
     * look for the tail, BUT
     * this time, just print whatever current_link-str is pointing to
     * then iterate to next node, and do it again
     * start by pointing an Item pointer at the head again
     */

    Item *current_link = list -> root;
    /* NULL CHECK */

    if (current_link == NULL)
      {
	printf("History is empty.");
      }
    /* doing it again, baby, find that tail */
    while (current_link != NULL)
      {
	printf("%d. %s\n", current_link -> id, current_link -> str);
	current_link = current_link -> next;
      }
  }
}
  void free_history(List *list)
  {
    Item *current_link;

    while (list -> root != NULL)
      {
	current_link = list -> root;
	list -> root = list -> root -> next;
	free(current_link -> str);
	free(current_link);
      }
    /*
     * Finally, free the structure
     */
    free(list);
  }

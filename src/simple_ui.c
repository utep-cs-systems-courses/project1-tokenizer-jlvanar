#include <stdio.h>
#include <string.h>


int simple_echo();

int main(){
  puts("Thus begins the tokenizer UI: as of yet, it simply echoes the input, unless the input 'x'is received. This particular input will exit the program's loop.");
  simple_echo();
  
  return 0;

  
}

int simple_echo(){
  char input[256];
  fputs(">", stdout);
  while(fgets(input, 256, stdin)){
    printf("%s\n", input);
    if(strcmp(input, "x") == 10){
      /* This feels like it might be really sloppy? Hard coded based on trial and error */
      fputs("Alright, later, man.\n", stdout);
      return 0;
    }
    else{
      fputs(">", stdout);
    }
  }
  return 1;
}

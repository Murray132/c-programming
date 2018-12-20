#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "deck.h"
#include "cards.h"

void assert_card_valid(card_t c);
const char * ranking_to_string(hand_ranking_t r);
char value_letter(card_t c);
char suit_letter(card_t c);
void print_card(card_t c);
card_t card_from_letters(char value_let, char suit_let);
card_t card_from_num(unsigned c);

void print_hand(deck_t * hand) {

  size_t n = (*hand).n_cards;

   card_t ** ptc1 = (*hand).cards;

   for(int i = 0; i < n; i++) {
     print_card(**ptc1);
     printf(" ");
     ptc1++;
   }

}

int deck_contains(deck_t * d, card_t c) {
   size_t n = (*d).n_cards;

   unsigned a1 = 0;
   size_t b1 = 0;

   unsigned a2 = 0;
   size_t b2 = 0;

   for(int i = 0; i < n; i++) {
   a1 = (*(*((*d).cards+i))).value;
   b1 = (*(*((*d).cards+i))).suit;
   a2 = c.value;
   b2 = c.suit;
   if ((a1 == a2) && (b1 == b2)) {
    return 1;
   }
   }
  return 0;
}

void shuffle(deck_t * d){


  size_t n = (*d).n_cards;
  card_t ** ptc = (*d).cards;
  
  card_t ** ptc1=ptc;
  card_t ** ptc2=ptc;
  card_t * temp = *ptc1;
  *ptc1 = *ptc2;
  *ptc2 =temp;
  
  for(int i = 0; i <n-1; i++){
  
  int k = random()%(n-i);
  ptc1 = ptc +i;
  ptc2 = ptc +k;
 
  card_t * temp = *ptc1;
    *ptc1 = *ptc2;
    *ptc2 = temp;
      }
}
    

void assert_full_deck(deck_t * d) {

  size_t n = (*d).n_cards;
  card_t ** ptc = (*d).cards;

  unsigned a1 = 0;
  size_t b1 = 0;

  unsigned a2 = 0;
  size_t b2 = 0;

  for(int j = 0; j<n;j++){

    a2 = (**(ptc+j)).value;
    b2 = (**(ptc+j)).suit;
    int e = 0 ;
    
    for(int i = 0; i < n; i++) {


      a1 = (*(*((*d).cards+i))).value;
      b1 = (*(*((*d).cards+i))).suit;
      
      if ((a1 == a2) && (b1 == b2)){
	e = e + 1;
      }
    }
    assert (e == 1);

    //printf ("%d ",e);
      
    }
}
 
  //for (int i = 0 ; i< n ; i++){

  //if (i==0){
  //  card_t ** new = ptc;
  //  (*d).n_cards = n-1;
  //  (*d).cards = ptc+1;
  //  int e = deck_contains(d,**new);
  //  assert(e == 0);
  //}

  //card_t ** new  = ptc + i;
  //card_t * temp1 = *ptc;
  //card_t * temp2 = *new;
    //*ptc = *new;
    //*new = temp1;
    //(*d).n_cards = n-1;
    //(*d).cards = ptc+1 ;
    //int e = deck_contains(d, **new);
    //assert(e == 0);
    //*ptc = temp1;
    //*new = temp2;
  //}
  
  


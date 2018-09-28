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
  suit_t n = (*hand).n_cards;
  for(int i = 0; i < n; i++) {
    if (i == n-1) {
      card_t * ptc = *((*hand).cards)+i;
      print_card(*ptc);
    }
    card_t * ptc1 = *((*hand).cards)+i;
    print_card(*ptc1);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  suit_t n = (*d).n_cards;

  unsigned a1;
  size_t b1;

  unsigned a2;
  unsigned b2;

  for(int i = 0; i < n; i++) {
    a1 = (*(*((*d).cards)+i)).value;
    b1 = (*(*((*d).cards)+i)).suit;
    a2 = c.value;
    b2 = c.suit;
    if (a1 == a2 && b1 == b2) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  suit_t n = (*d).n_cards;
  card_t * ptc = *((*d).cards);
  card_t * arr[n];
  for (int j = 0; j < n; j++) {
    arr[j] = ptc + j;
  }
  //use a different seed value so that we don't get same result each time we run this program
  srand(time(NULL));
  for(int i = n-1; i > 0; i--) {
    int k = rand() % (i+1);
    card_t * temp = arr[i];
    arr[i] = arr[k];
    arr[k] = temp;
  }
}
    

void assert_full_deck(deck_t * d) {
  suit_t n = (*d).n_cards;
  card_t * ptc = *((*d).cards);
  for (int i = n-1; i > 0; i--) {
deck_t new;
new.n_cards = n-i;
*(new.cards) = ptc + n - i;
  deck_t * d1;
d1 = &new;
    card_t c = *(ptc + n - 1 - i);
    
    int e = deck_contains(d1,c);
    assert(e == 1);
  }
}

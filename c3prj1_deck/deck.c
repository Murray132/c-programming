#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "deck.h"

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
  }
}


void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards = deck->n_cards + 1;
  deck->cards = realloc(deck->cards, (deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards-1] = NULL;
  deck->cards[deck->n_cards-1] = realloc(deck->cards[deck->n_cards-1], sizeof(*(deck-> cards[deck->n_cards-1])));
  deck->cards[deck->n_cards-1]->suit = c.suit;
  deck->cards[deck->n_cards-1]->value = c.value;
}

card_t * add_empty_card(deck_t * deck) {
  card_t * temp = malloc(sizeof(*temp));
  temp->suit = 0;
  temp->value = 0;
  deck->n_cards = deck->n_cards + 1;
  deck->cards = realloc(deck->cards, (deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards-1] = temp;
  return temp;
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  card_t temp;
  deck_t * exclude_deck = malloc(sizeof(*exclude_deck));
  exclude_deck -> n_cards = 0;
  exclude_deck -> cards = NULL;
  int compare = 0;
  for(unsigned i = 0; i<52; i++) {
    temp = card_from_num(i);
    compare = deck_contains(excluded_cards, temp);
    if(compare == 0) {
      add_card_to(exclude_deck, temp);
    }
  }
  return exclude_deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * deck = malloc(sizeof(*deck)); // this deck will contain cards from hands
  deck -> n_cards = 0;
  deck -> cards = NULL;
  deck_t * remaining;
  
  deck_t * temp;  
  for(size_t i =0; i< n_hands; i++) {
    temp = hands[i];
    for(size_t j=0; j< temp->n_cards; j++) {
      deck->cards = realloc(deck->cards, (deck->n_cards+1)*sizeof(*(deck->cards)));
      deck->cards[deck->n_cards] = temp->cards[j];
      deck->n_cards = deck->n_cards + 1;
    }
  }

  remaining = make_deck_exclude(deck);
 
  free(deck->cards);
  free(deck);
  return remaining;
}

void free_deck(deck_t * deck) {
  for(size_t i =0; i< deck->n_cards; i++){
    free(deck->cards[i]);
  }
  
  free(deck->cards);
  free(deck);
}
  

  
  


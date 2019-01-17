#include <stdio.h>
#include <stdlib.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr ) {
  if (index < fc -> n_decks) {
    fc -> decks[index].cards =realloc (fc->decks[index].cards,(fc->decks[index].n_cards+1)*sizeof(*(fc->decks[index].cards)));
    fc -> decks[index].cards[fc->decks[index].n_cards] = ptr;
    fc -> decks[index].n_cards++;
  }
  else{

    while(fc -> n_decks <= index) {
      fc -> decks = realloc(fc->decks, (fc->n_decks+1)*sizeof(*(fc->decks)));
      fc -> decks[fc->n_decks].cards = NULL;
      fc -> decks[fc->n_decks].n_cards = 0;
      fc -> n_decks++;
    }

    fc->decks[index].cards = realloc(fc->decks[index].cards,(fc->decks[index].n_cards+1)*sizeof(*(fc->decks[index].cards)));
    fc->decks[index].cards[fc->decks[index].n_cards]=ptr;
    fc->decks[index].n_cards ++;
  }
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if(fc==NULL){
    fprintf(stderr, "Null future cards");
  }
  if(fc->n_decks > deck->n_cards){
    fprintf(stderr, "Not enough cards in deck");
  }
  deck_t d;
  card_t *c;
  for(size_t i=0; i<fc->n_decks; i++){
    c = deck->cards[i];
    d = fc->decks[i];
    for(size_t j=0; j<d.n_cards; j++){
      (*(d.cards[j])).value = (*c).value;
      (*(d.cards[j])).suit = (*c).suit;
    }
  }
}

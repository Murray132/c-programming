#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"
  
  void assert_card_valid(card_t c) {
    assert( c.value >= 2);
    assert( c.value <= VALUE_ACE);
    assert( c.suit >= SPADES );
    assert( c.suit <= CLUBS );
  }
  
  const char * ranking_to_string(hand_ranking_t r) {
    switch (r) {
    case STRAIGHT_FLUSH : return "STRAIGHT_FLUSH" ;   
    case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
    case FULL_HOUSE: return "FULL_HOUSE" ;
    case FLUSH: return "FLUSH";
    case STRAIGHT: return "STRAIGHT";
    case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
    case TWO_PAIR: return "TWO_PAIR";
    case PAIR: return "PAIR";
    case NOTHING: return "NOTHING";
    default : return "Invalid Thing ";
      }
   }
   char value_letter(card_t c) {
      char x;
       switch (c.value){
       case 2: x ='2' ; break;
       case 3: x ='3' ; break;
       case 4: x ='4' ; break;
       case 5: x ='5' ; break;
       case 6: x ='6' ; break;
       case 7: x ='7' ; break;
       case 8: x ='8' ; break;
       case 9: x ='9' ; break;
       case 10: x ='0' ; break;
       case VALUE_JACK : x ='J' ; break;
       case VALUE_QUEEN : x ='Q' ; break;
       case VALUE_KING : x ='K' ; break;
       case VALUE_ACE : x = 'A' ; break;
       default : x = 'N'; break;
      }
    return x;
  }
   char suit_letter(card_t c) {
     char x;
    switch (c.suit){
    case SPADES: x = 's'; break;
    case HEARTS: x = 'h'; break;
    case DIAMONDS: x = 'd'; break;
    case CLUBS: x = 'c'; break;
    default : x = 'n'; break;
   } 
   return x;
  }
  void print_card(card_t c) {
    char v = value_letter(c);
    char s = suit_letter(c);
    printf("%c%c",v,s);   
  }
  card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  int s = suit_let;
  int v = value_let;                                                    
  assert(v==48|| v== 50|| v== 51||v== 52||  v== 53|| v==54|| v==55|| v==56|| v==57|| v==65 || v== 75 || v==74 || v==81 );
         
  assert( s == 99 ||  s== 100 ||  s==104 ||  s==115 );
  if (v ==65){ temp.value =VALUE_ACE;
  }
  else if (v == 75){
    temp.value = VALUE_KING;
  }
  else if(v== 81) {
    temp.value = VALUE_QUEEN;
  }
  else if (v== 74)
    {
      temp.value = VALUE_JACK;
    }
  // else if (v==57){
  //  temp.value = 9;
  // }
  //else if (v == 56){
  //  temp.value = 8;
  //}
  //else if (v== 55){
  //  temp.value = v-48;
  // }
  for (int i =2, i <10,i++){
    if (v==i+48){
       temp.value = i
    }
  }
  else{
    temp.value = VALUE_JACK;
  }
  
  switch (s){
  case 99: temp.suit = CLUBS; break;
  case 100: temp.suit = DIAMONDS; break;
  case 104: temp.suit = HEARTS ; break;
  case 115: temp.suit = SPADES; break;   
  }
  return temp;
  }
  
  card_t card_from_num(unsigned c) {
  assert(c >= 0);
  assert(c < 52);
  card_t temp;
  temp.value=0;
  temp.suit =0;
  unsigned c1 = c%13;
  unsigned c2 = c/13;
  int i = 0;
  int j = 0;
  while (i<4){
    if(c2 == i){
      temp.suit= i ;
      while (j<13){
	if(c1 == j){
	  temp.value = j+2;
	}
	j++;
      }
      
    }
    i++ ;
  }
  // switch (c1){
  // case 0: temp.value = 2; break;
  //case 1: temp.value = 3; break;
  //case 2: temp.value = 4 ; break;
  //case 3: temp.value = 5 ; break;
  //case 4: temp.value = 6 ; break;
  //case 5: temp.value = 7 ; break;
  //case 6: temp.value = 8 ; break;
  //case 7: temp.value = 9 ; break;
  //case 8: temp.value = 10 ; break;
  //case 9: temp.value = VALUE_JACK ; break;
  //case 10: temp.value = VALUE_QUEEN; break;
  //case 11: temp.value = VALUE_KING; break;
  //case 12: temp.value = VALUE_ACE; break;
  //}
  // if( c2 ==0 ){
  //    temp.suit = SPADES ;
  //  }
  //  else if (c2 == 1){
  //    temp.suit = HEARTS ;
  //  }
  //  else if (c2 == 2){
  //    temp.suit = DIAMONDS ;
  //  }
  //  else if(c2 ==3 ){
  //    temp.suit = CLUBS;
  //  }
    return temp;
  }  
   

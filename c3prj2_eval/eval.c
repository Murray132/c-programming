#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {  
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  
  if((**cp1).value > (**cp2).value){
    
    return -1;
    
  }else if((**cp1).value < (**cp2).value){
    
    return 1;
    
  }else{
    
    if((**cp1).suit > (**cp2).suit){
      
      return -1;
      
    }else if((**cp1).suit < (**cp2).suit){
      
      return 1;
      
    }
    
  }
  
  return 0;
  
}



suit_t flush_suit(deck_t * hand) {
  
  int size = (int)(hand -> n_cards);
  
  card_t ** ptr = (hand -> cards);
  
  int count_array[] = {0,0,0,0,0};
  
  for(int i=0; i<size; i++){
    
    card_t card = **ptr;
    
    (*(count_array+card.suit))++;
    
    ptr++;
    
  }
  
  for(int j=0; j<4; j++){
    
    if(*(count_array+j)>4){
      
      return j;
      
    }
    
  }
  
  return NUM_SUITS;
  
}



unsigned get_largest_element(unsigned * arr, size_t n) {
  
  unsigned max_val = 0;
  
  for(int i=0; i<(int)n; i++){
    
    if(*arr > max_val){
      
      max_val = *arr;
      
    }
    
    arr++;
    
  }
  
  return max_val;
  
}



size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  
  for(size_t i=0; i<n; i++){
    
    if(*match_counts == n_of_akind){
      
      return i;
      
    }
    
    match_counts++;
    
  }
  
  return -1;
  
}

ssize_t  find_secondary_pair(deck_t * hand,
			     
			     unsigned * match_counts,size_t match_idx) {
  

  
  size_t first = -1;
  
  size_t second = -1;
  
  size_t size = hand -> n_cards;
  
  unsigned match_value = *(match_counts + match_idx);
  
  if(match_idx>0){
    
    if(get_match_index(match_counts, match_idx,2)<=get_match_index(match_counts, match_idx,3)){
      
      first = get_match_index(match_counts, match_idx,2);
      
    }else{
      
      first = get_match_index(match_counts, match_idx,3);
      
    }
    
  }
  

  
  if(match_idx+(size_t)match_value < size){
    
    if(get_match_index(match_counts+(unsigned)match_idx+match_value, size - match_idx - match_value,2)
       
       <=get_match_index(match_counts+(unsigned)match_idx+match_value, size - match_idx-match_value,3)){
      
      second = get_match_index(match_counts+(unsigned)match_idx+match_value, size - match_idx - match_value,2);
      
    }else{
      
      second = get_match_index(match_counts+(unsigned)match_idx+match_value, size - match_idx - match_value,3);
      
    }
    
  }
  

  
  if(second!=-1){
    
    second = second + match_idx + (size_t)match_value;
    
  }
  
  if(first!=-1){
    
    return first;
    
  }
  

  
  return second;
  
}



int is_n_length_straight_at(deck_t * hand,size_t index, suit_t fs, int n){
  
  card_t ** ptr = hand -> cards;
  
  size_t size = hand -> n_cards;
  
  if(fs!=NUM_SUITS && (*(ptr+index))->suit !=fs){
    
    return EXIT_FAILURE;
    
  }
  
  unsigned last_val = (**(ptr+index)).value;
  
  unsigned cur_val = last_val;
  
  suit_t cur_suit = (**(ptr+index)).suit;
  

  
  int mach=1;
  
  if(index == size -1 && n!=1){
    
    return EXIT_FAILURE;
    
  }
  
  for(size_t i=index+1; i<size; i++){
    
    cur_val = (**(ptr+i)).value;
    
    cur_suit = (**(ptr+i)).suit;
    
    if(cur_val == last_val -1){
      
      if(fs!=NUM_SUITS){
	
	if(cur_suit == fs){
	  
	  last_val = cur_val;
	  
	  mach++;
	  
	}
	
      }else{
	
	last_val = cur_val;
	
	mach++;
	
      }
      
      if(mach==n){
	
	return EXIT_SUCCESS;
	
      }
      
    }else if(cur_val < last_val -1){
      
      return EXIT_FAILURE;
      
    }
    
  }
  
  return EXIT_FAILURE;
  
}



int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs){
  
  card_t ** ptr = hand -> cards;
  
  card_t test_card = **ptr;
  
  if((*(ptr+index))->value != VALUE_ACE){
    
    return EXIT_FAILURE;
    
  }
  
  if(fs!=NUM_SUITS && ((*(ptr+index))-> suit != fs)){
    
    return EXIT_FAILURE;
    
  }
  
  for(size_t i=0; i<(hand->n_cards); i++){
    
    test_card = **(ptr+i);
    
    if(test_card.value==5){
      
      if(fs!=NUM_SUITS){
	
	if(test_card.suit == fs){
	  
	  return is_n_length_straight_at(hand, i, fs, 4);
	  
	}
	
      }else{
	
	return is_n_length_straight_at(hand, i, fs, 4);
	
      }
      
    }
    
  }
  
  return EXIT_FAILURE;
  
}



int is_straight_at(deck_t * hand, size_t index, suit_t fs){
  
  int ace_low_cond = is_ace_low_straight_at(hand, index, fs);
  
  int str_cond = is_n_length_straight_at(hand, index, fs, 5);
  
  if(str_cond == EXIT_SUCCESS)  return 1;
  
  else if(ace_low_cond == EXIT_SUCCESS)  return -1;
  
  else return 0;
  
}





hand_eval_t build_hand_from_match(deck_t * hand,
				  
				  unsigned n,
				  
				  hand_ranking_t what,
				  
				  size_t idx) {
  

  
  hand_eval_t ans;
  
  ans.ranking = what;
  
  card_t ** dk_card_ptr = hand-> cards;
  
  card_t cur_card = **dk_card_ptr;
  
  unsigned n_k_val = (**(dk_card_ptr+idx)).value;
  
  unsigned delta_ptr = 0;
  

  
  if(n==0){
    
    while(delta_ptr<5){
      
      *(ans.cards + delta_ptr) = *(dk_card_ptr + delta_ptr);
      
      delta_ptr++;
      
    }
    
    return ans;
    
  }
  

  
  while(delta_ptr<n){
    
    *(ans.cards + delta_ptr) = *(dk_card_ptr + idx + delta_ptr);
    
    delta_ptr++;
    
  }
  

  
  int count = 0;
  
  while(delta_ptr<5){
    
    cur_card =  **(dk_card_ptr+count);
    
    if(cur_card.value != n_k_val){
      
      *(ans.cards + delta_ptr) = *(dk_card_ptr + count);
      
      delta_ptr++;
      
    }
    
    count++;
    
  }
  

  
  return ans;
  
}





int compare_hands(deck_t * hand1, deck_t * hand2) {
  
  qsort(hand1->cards, hand1->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
  
  qsort(hand2->cards, hand2->n_cards, sizeof(hand2->cards[0]), card_ptr_comp);
  

  
  hand_eval_t hand1_val = evaluate_hand(hand1);
  
  hand_eval_t hand2_val = evaluate_hand(hand2);
  

  
  card_t ** hand1_ptr = hand1_val.cards;
  
  card_t ** hand2_ptr = hand2_val.cards;
  

  
  if(hand1_val.ranking != hand2_val.ranking){
    
    if(hand1_val.ranking <  hand2_val.ranking) return 1;
    
    else return -1;
    
  }
  
  else{
    
    unsigned cpr_val1 = (**hand1_ptr).value;
    
    unsigned cpr_val2 = (**hand2_ptr).value;
    
    for(int i=0; i<5; i++){
      
      cpr_val1 = (**(hand1_ptr+i)).value;
      
      cpr_val2 = (**(hand2_ptr+i)).value;
      
      if(cpr_val1 > cpr_val2)  return 1;
      
      else if(cpr_val1 < cpr_val2)  return -1;
      
    }
    
  }
  
  return 0;
  
}







/*
#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {

  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;

  unsigned v1 = (**cp1).value;
  suit_t s1 = (**cp1).suit;

  unsigned v2 = (**cp2).value;
  suit_t s2 = (**cp2).suit;

  if(v1>v2){
    return v2 - v1;
  }// card1 > card2

  else if (v1<v2){
    return v2 -v1;
  }// card1 < card2
  
  else{

    if(s1>s2){
      return s2-s1;
    }//so, in this case card1 > card2 

    else if (s1<s2){
      return s2-s1;
    }//In this case card1 < card2

    else{
      return 0;
    }// card1 == card2

  }
}

suit_t flush_suit(deck_t * hand) {

  deck_t h = *hand;
  size_t n = h.n_cards;
  card_t ** c = h.cards;

  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  int a4 = 0;

  for (int i =0 ; i < n; i++ ){
    suit_t suit = (**(c+i)).suit;
    if(suit == SPADES){
      a1++;
    }
    else if(suit == HEARTS){
      a2++;
    }
    else if(suit == DIAMONDS){
      a3++;
    }
    else{
      a4++;
    }  
  }

  if (a1 >= 5){
    return SPADES;
  }

  else if (a2 >= 5){
    return HEARTS;
  }

  else if (a3 >= 5){
    return DIAMONDS;
  }

  else if (a4 >= 5){
    return CLUBS;
  }

  else {
    return NUM_SUITS;
  }
}

unsigned get_largest_element(unsigned * arr, size_t n) {

  int largestIndex = 0;
  for (int i=1; i<n; i++ ){
    if (arr[i]>arr[largestIndex]){
      largestIndex = i;
    }
  }
      
  return arr[largestIndex];
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){

  int LowestIndex = 0;
  if (match_counts[LowestIndex] == n_of_akind ){
    return 0;
  }
  else{
    for (int i =1; i<n;i++){
      int temp = LowestIndex +1;
     
      if(match_counts[temp] == n_of_akind ){
	LowestIndex = i;
	break;
      }
      else{
	LowestIndex++;
      }
     
    }
    return LowestIndex;
  }
}

ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  size_t n = (*hand).n_cards;
  card_t ** card_in_hand = (*hand).cards;
  
  
  int second_lowest = 0 ;
  card_t ** card_of_original = card_in_hand + match_idx;
  
  for(int i =0; i<n;i++ ){
    card_t ** current_card = card_in_hand + i ;
    

    if ( i == match_idx || (**current_card).value == (**card_of_original).value || match_counts[i] == 1  ){

      second_lowest ++;
      
    }
    else {
      second_lowest = i;
      break;
    }


  }

  if(second_lowest <n){
    return second_lowest;
  }
  else{
    return -1;
  }
}

int n_length (deck_t * hand, int n, size_t index ) { // using this function to find the successive cards of length n from a given index mutiple value is allowed so 5,5,4 and 5,4 are both length of 2 
    size_t n1 =(*hand).n_cards;
    card_t ** c1 = (*hand).cards;
    if(index+n-1>n1 ){
      return 0;// there is no n length of cards starting at index
    }
    else {
      int temp =0 ; 
      for (int i = index; i<n1-1 ;i++ ){
        if( (**(c1+i)).value - (**(c1+i+1)).value <= 1 ) {
	  temp = temp+ (**(c1+i)).value - (**(c1+i+1)).value;
	  if(temp == n-1 ){
	    return 1;
	  }
	}
	else{
	  return 0;
	}
      }
      return 0;
    }
  }

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {

  size_t n =(*hand).n_cards;
  card_t ** c = (*hand).cards;
  if(fs == NUM_SUITS){
    if(  (**(c+index)).value == VALUE_ACE   ) { //the current card is ACE
      int checkidx1 = n_length(hand,5,index);
      if(checkidx1 ==1 ){
	return 1;
      }
      else{// find the index of 5, if 5 doesn't exist then return 0
	for(int k=index+1; k<n;k++){
	  if((**(c+k)).value ==5){
	    int checkidx2 = n_length(hand,4,k);
	    if(checkidx2 ==1){
	      return -1;
	    }
	  }
	}
	return 0;
      }
    }

    else{

      int checkidx = n_length(hand,5,index);
      if(checkidx == 1){
	return 1;
      }
      else{
	return 0;
      }
    }
  }
  
  else { // fs != NUM_SUITS
    if((**(c+index)).suit == fs){
      
      if( (**(c+index)).value != VALUE_ACE ){
        int checkidx = n_length(hand,5,index);
        if(checkidx == 1){
	  int temp =1;
	  for(int i = index+1; i< n; i++){
            if( ((**(c+i)).suit == fs) && ( (**(c+i-1)).value -(**(c+i)).value   <= 1   ) ){
              temp++;
	      if(temp ==5){
		return 1;
	      }
	    }	    
	  }
	  return 0;
        }
        return 0;
      }
      else { //the current card is ACE
        int checkidx1 = n_length(hand,5,index);
        if(checkidx1 ==1 ){
          int temp =1;
	  for(int i = index+1; i< n; i++){
            if( ((**(c+i)).suit == fs) && ( (**(c+i-1)).value -(**(c+i)).value   <= 1   )    ){              
              temp++;
	      if(temp ==5){
		return 1;
	      }		
	    }   
	  }
	  return 0; 
        }
	
        else{// find the index of 5, if 5 doesn't exist then return 0
	  for(int k=index+1; k<n;k++){
	    if((**(c+k)).value ==5){
	      int checkidx2 = n_length(hand,4,k);
	      if(checkidx2 ==1){
		int temp =1;
	        for(int i = index+1; i<n ; i++){
                  if((**(c+i)).suit == fs && ( (**(c+i-1)).value -(**(c+i)).value <= 1   ) ){
		    temp++;
		    if(temp ==4){
		      return -1;
		    }
		  }
		}
		return 0;
	      }
	    }
	  }
	  return 0;
        }
      }
    }
    return 0;
  }
}



hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;
  ans.ranking = what ;
  card_t ** c = (*hand).cards;
  int array[7]={0,0,0,0,0,0,0};
  for (int j =0; j<idx; j++){
    array[j]= j;
    
  }
  for (int l= idx+n; l < 7 ; l++){
    int temp = l - n ;
    array[temp]= l;
  }
      
  for (int i=0; i < 5 ;i++){
    if(i<n){
      ans.cards[i] = *(c+idx+i);
    }
    else{
      ans.cards[i] = *(c+array[i-n]);
    }
  }
  
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  card_t ** c1 = (*hand1).cards;
  size_t n1 = (*hand1).n_cards;
  qsort(c1,n1,sizeof(const card_t *),card_ptr_comp);
  card_t ** c2 = (*hand2).cards;
  size_t n2 = (*hand2).n_cards ;
  qsort(c2,n2,sizeof(const card_t *),card_ptr_comp);
  hand_eval_t h1 = evaluate_hand(hand1);
  hand_eval_t h2 = evaluate_hand(hand2);

  if(h1.ranking != h2.ranking){
    if(h1.ranking > h2.ranking){
      return -1;
    }
    else{ // h1.ranking < h2.ranking
      return 1;
    }

  }
  else{ // h1.ranking = h2.ranking
    for (int i =0; i< 5;i++){
    
      if( (*(h1.cards[i])).value > (*(h2.cards[i])).value   ){
	return 1;
      }
      else if( (*(h1.cards[i])).value < (*(h2.cards[i])).value ){
	return -1;
      }
      
      
      
    }
  }

  return 0;
}
*/


//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.

unsigned * get_match_counts(deck_t * hand){
  
  unsigned * ret_array = malloc((hand->n_cards)*sizeof(*ret_array));
  
  if(ret_array == NULL){
    
    return NULL;
    
  }
  
  card_t ** d_cards = hand->cards;
  
  unsigned cur_val = d_cards[0]->value;
  
  size_t st_idx = 0;
  
  unsigned count = 0;
  
  card_t * card_p;
  
  for(size_t i=0; i<hand->n_cards; i++){
    
    card_p = d_cards[i];
    
    if(card_p->value == cur_val){
      
      count++;
      
    }else{
      
      for(size_t j=st_idx; j<i; j++){
	
	ret_array[j] = count;
	
      }
      
      st_idx = i;
      
      cur_val = card_p->value;
      
      count = 1;
      
    }
    
  }
  
  for(size_t j=st_idx; j<hand->n_cards; j++){
    
    ret_array[j] = count;
    
  }
  
  return ret_array;
  
}

/*
unsigned * get_match_counts(deck_t * hand) {
  unsigned * match_counts = malloc((hand->n_cards)*sizeof(*match_counts));
  if(match_counts == NULL) {
    return NULL;
  }

  card_t ** c = hand ->cards;

  unsigned current_card_value = c[0]->value;

  size_t card_idx = 0;
  unsigned count = 0;

  card_t * card_ptr;

  for (size_t i = 0; i<hand->n_cards; i++) {
    card_ptr = c[i]; // start from the first card in the hand
    if(card_ptr->value == current_card_value){
      count++;
    }
    else{
      for(size_t j = card_idx; j < i;j++){// now fill the fist i boxes in the array
	match_counts[j] = count;
      }
      card_idx = i;
      current_card_value = card_ptr->value;
      count = 1; // new card appears, so we have count 1 now
    }
  }
  //we may still have the remianing box to fullfill(only 1 box in fact) if the last card is a new one
  for(size_t k  = card_idx; k<hand->n_cards;k++ ) {
    match_counts[k] = count;
  }
  return match_counts;

}
*/

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}

 
//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4]; 
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}

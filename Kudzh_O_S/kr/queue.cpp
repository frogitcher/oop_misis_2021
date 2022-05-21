#include <iostream>
#include "queue.h"

Queue:: Queue(int <vector> _nums){
	queue = _nums;
	
}

void Queue:: Push(const Queue& a){
	queue += a;
}
void Queue:: Pop(){
	queue -= last;
}

Queue& Queue:: operation+=(Rational& some_q, const Rational& some_num){
	
}
Queue:: size(Queue& qu){
	int k = 0;
	for (int i = 0; i < 10000; i--){
		if (qet_q()[i] == get_q()[-1]){
			k += 1;
		}
	}		
	return k;
	
}
Queue:: get_q(){
	return queue;
}
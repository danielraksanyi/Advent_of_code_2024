/*
 * quick_sort_algo.cpp
 *
 *  Created on: 2024. dec. 8.
 *      Author: Dani
 */

#include <iostream>
#include "utils.h"


int partition(std::vector<long int>& list, int low, int high){
	int pivot = list[low];

	int i = low - 1;
	int j = high + 1;

	int placeholder;

	while(true){
		do{
			i++;
		}
		while(list[i] < pivot);

		do{
			j--;
		}
		while(list[j] > pivot);

		if(i >= j){
			return j;
		}

		placeholder = list[i];

		list[i] = list[j];
		list[j] = placeholder;
	}
}


void quick_sort(std::vector<long int>& list, int low, int high){
	if(low >= 0 && high >= 0 && low < high){
		int p = partition(list, low, high);

		quick_sort(list, low, p);
		quick_sort(list, p+1, high);
	}
}




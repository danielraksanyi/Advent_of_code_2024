#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "../utils/utils.h"



int main() {
	std::ifstream file("advent_of_code_2024_day_1_input.txt");

	std::vector<long int> list1;
	std::vector<long int> list2;

	std::string line;

	while(std::getline(file, line)){
		int num1, num2;
		std::istringstream iss(line);

		iss >> num1 >> num2;

		list1.push_back(num1);
		list2.push_back(num2);
	}

	std::size_t short_len = std::min(list1.size(), list2.size());

	double total_dist = 0;

	quick_sort(list1, 0, list1.size()-1);
	quick_sort(list2, 0, list2.size()-1);

	// task 1
	for(std::size_t i=0; i<short_len; i++){
		total_dist += std::abs(list1[i] - list2[i]);
	}

	if(list1.size() != list2.size()){
		printf("Lengths of the lists are not equal!\n");
		printf("1st list: %d\t2nd list: %d\n", list1.size(), list2.size());
	}

	printf("Total distance = %g\n", total_dist);

	// task 2
	std::unordered_map<std::string, long int> list2_count_map;
	std::string key;

	for(const long int& i : list2){
		key = std::to_string(i);

		if(list2_count_map.find(key) == list2_count_map.end()){
			list2_count_map[key] = 1;
		}
		else{
			list2_count_map[key]++;
		}
	}

	long int similarity = 0;
	int count = 0;

	for(const long int& i : list1){
		key = std::to_string(i);

		if(list2_count_map.find(key) == list2_count_map.end()){
			count = 0;
		}
		else{
			count = list2_count_map[key];
		}

		similarity += std::stoi(key) * count;
	}

	printf("Similarity score: %ld\n", similarity);

	system("pause");

	return 0;
}

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>


int sign(int num) {
    if (num > 0) return 1;
    if (num < 0) return -1;
    return 0;
}

int task_1(std::vector<int> levels){
    int row_sign = sign(levels[0] - levels[1]);
    bool task_1_safe = true;
    int diff;

    for(std::size_t i=0; i<levels.size()-1; i++){
        diff = levels[i] - levels[i+1];

        if((sign(diff) != row_sign) || (std::abs(diff) > 3) || (levels[i] == levels[i+1])){
            task_1_safe = false;
            return 0;
        }
    }

    return 1;
}

std::vector<int> get_error_indices(std::vector<int> levels){
    int row_sign = sign(levels[0] - levels[1]);
    std::vector<int> fail_indices;
    int diff;

    for(std::size_t i=0; i<levels.size()-1; i++){
        diff = levels[i] - levels[i+1];

        if((sign(diff) != row_sign) || (std::abs(diff) > 3) || (levels[i] == levels[i+1])){
            fail_indices.push_back(i);
        }
    }

    return fail_indices;
}


int task_2(std::vector<int> levels){
    std::vector<int> fail_indices;
    std::vector<int> temp_levels;
    bool no_second_depth_error = false;
    
    fail_indices = get_error_indices(levels);
    
    if(fail_indices.empty()) return 1;
    else{
        for(int i=0; i<levels.size(); i++){
            temp_levels = levels;
            temp_levels.erase(temp_levels.begin() + i);
            no_second_depth_error = no_second_depth_error || get_error_indices(temp_levels).empty();
        }
    }

    return no_second_depth_error;
}


int main(){
    std::fstream file("input.txt");
    std::string line;
    std::vector<int> levels;
    int task_1_safe_count = 0;
    int task_2_safe_count = 0;

    while(std::getline(file, line)){
        levels.clear();

        std::istringstream iss(line);
        
        int temp;

        while (iss >> temp) {
            levels.push_back(temp);
        }

        task_1_safe_count += task_1(levels);
        task_2_safe_count += task_2(levels);
    }

    std::cout << "Task 1 safe count: " << task_1_safe_count << std::endl;
    std::cout << "Task 2 safe count: " << task_2_safe_count << std::endl;

    system("pause");
}
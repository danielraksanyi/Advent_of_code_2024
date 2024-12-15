#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <tuple>



std::vector<int> parse_string(const std::string &line, char sep){
    std::vector<int> result;
    std::stringstream ss(line);
    std::string num;

    while(std::getline(ss, num, sep)){
        result.push_back(std::stoi(num));
    }

    return result;
}


void insert_into_order_map(std::unordered_map<int, std::vector<int>> &map, int key_num, int val_num){
    if(map.find(key_num) == map.end()){
                map[key_num] = {val_num};
    }
    else{
        map[key_num].push_back(val_num);
    }
}


void parse_orders(std::unordered_map<int, std::vector<int>> &left_map, 
                    std::unordered_map<int, std::vector<int>> &right_map,
                    std::string line){
    std::vector<int> nums = parse_string(line, '|');

    insert_into_order_map(left_map, nums[0], nums[1]);
    insert_into_order_map(right_map, nums[1], nums[0]);
}





std::tuple<std::vector<int>, std::vector<int>> parse_file(std::string file_name){
    std::ifstream file("test.txt");
    std::string line;
    bool ordering = true;

    std::unordered_map<int, std::vector<int>> left_map;
    std::unordered_map<int, std::vector<int>> right_map;

    std::vector<std::vector<int>> updates;

    while(std::getline(file, line)){
        if(line.empty() || std::find(std::begin(line), std::end(line), line) == std::end(line)){
            ordering = false;
            continue;
        }

        if(ordering){
            parse_orders(left_map, right_map, line);
        }
        else{
            updates.push_back(parse_string(line, ','));
        }
    }

}




int main(){
    


    return 0;
}
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>


int task_1(std::string text){
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::smatch match;
    std::vector<std::pair<int,int>> pairs;

    auto start = text.cbegin();
    auto end = text.cend();
    try{
        while(std::regex_search(start, end, match, pattern)){
            int num1 = std::stoi(match[1].str());
            int num2 = std::stoi(match[2].str());

            pairs.emplace_back(num1, num2);

            start = match.suffix().first;
        }

        int sum = 0;

        for(std::pair<int, int> i : pairs){
            sum += i.first * i.second;
        }

        return sum;
    }
    catch (const std::exception& e){
        std::cerr << e.what();
        system("pause");
    }
}


int task_2(std::string text){
    std::regex pattern(R"(mul\((\d+),(\d+)\)|(do\(\))|(don't\(\)))");
    std::smatch match;

    std::vector<std::pair<int,int>> pairs;

    auto start = text.cbegin();
    auto end = text.cend();

    bool keep = true;

    while(std::regex_search(start, end, match, pattern)){
        std::string matched_str = match[0].str();
        matched_str.erase(0, matched_str.find_first_not_of(" \t\n\r"));
        matched_str.erase(matched_str.find_last_not_of(" \t\n\r") + 1);

        if(matched_str == "do()"){
            keep = true;        
        }
        else if(matched_str == "don't()"){
            keep = false;
        }
        else if(keep){
            int num1 = std::stoi(match[1].str());
            int num2 = std::stoi(match[2].str());

            pairs.emplace_back(num1, num2);
        }

        start = match.suffix().first;
    }

    int sum = 0;

    for(std::pair<int, int> i : pairs){
        sum += i.first * i.second;
    }

    return sum;

}


int main(){
    std::fstream file("input.txt");

    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    int task_1_sum = task_1(text);
    int task_2_sum = task_2(text);

    std::cout << "Task 1 result: " << task_1_sum << std::endl;
    std::cout << "Task 2 result: " << task_2_sum << std::endl;

    system("pause");

   
    return 0;
}
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>


void strip(std::string& str){
    str.erase(0, str.find_first_not_of(" \t\n\r"));
    str.erase(str.find_last_not_of(" \t\n\r") + 1);
}


int xmas_finder(std::vector<std::string> text){
    int text_len = text.size();
    int line_len = text[0].size();

    int xmas_counter = 0;

    // lines
    for(int i=0; i<text_len; i++){
        std::string line = text[i];
        std::string reverse_line = text[i];
        std::reverse(reverse_line.begin(), reverse_line.end());

        strip(line);
        strip(reverse_line);

        // positions in line back and forth
        for(int j=0, k=line_len-1; j<line_len-3 && k>2; j++, k--){
            if(i < text_len - 3){    
                // this part could have been vectorized, but that would make it harder to understand
                // also could have used std::reverse()

                // -90 deg backslash
                std::string backslash_forward;
                std::string backslash_backward;

                // +90 deg slash /
                std::string slash_forward;
                std::string slash_backward;

                for(int l=0; l<4; l++){
                    backslash_forward += std::string(1, text[i+l][j+l]);
                    backslash_backward += std::string(1, text[i+3-l][j+3-l]);

                    slash_forward += std::string(1, text[i+3-l][j+l]);
                    slash_backward += std::string(1, text[i+l][j+3-l]);
                }
                strip(backslash_forward);
                strip(backslash_backward);
                strip(slash_forward);
                strip(slash_backward);

                if(backslash_forward == "XMAS") xmas_counter++;
                if(backslash_backward == "XMAS") xmas_counter++;
                if(slash_forward == "XMAS") xmas_counter++;
                if(slash_backward == "XMAS") xmas_counter++;

                // vertical
                if(j <= k){
                    std::string vertical_forward = {text[i][j], text[i+1][j], text[i+2][j], text[i+3][j]};
                    std::string vertical_backward = {text[i][k], text[i+1][k], text[i+2][k], text[i+3][k]};
                    
                    strip(vertical_forward);
                    strip(vertical_backward);

                    std::string vertical_forward_up = vertical_forward;
                    std::reverse(vertical_forward.begin(), vertical_forward.end());
                    std::string vertical_backward_up = vertical_backward;
                    std::reverse(vertical_backward.begin(), vertical_backward.end());

                    if(vertical_forward == "XMAS") xmas_counter++;
                    if(vertical_backward == "XMAS") xmas_counter++;
                    if(vertical_forward_up == "XMAS") xmas_counter++;
                    if(vertical_backward_up == "XMAS") xmas_counter++;
                }

            }
            // horizontal
            std::string forward_line = line.substr(j, 4);
            std::string backward_line = reverse_line.substr(j, 4);

            strip(forward_line);
            strip(backward_line);

            if(forward_line == "XMAS") xmas_counter++;
            if(backward_line == "XMAS") xmas_counter++;
        }
    }

    return xmas_counter;
}



int cross_finder(std::vector<std::string> text){
    int text_len = text.size();
    int line_len = text[0].size();

    int mas_counter = 0;

    // lines
    for(int i=0; i<text_len-2; i++){
        // positions in line back and forth
        for(int j=0; j<line_len-2; j++){
            if(
                (
                    ((text[i][j]=='M' && text[i][j+2]=='M') && (text[i+2][j]=='S' && text[i+2][j+2]=='S')) || 
                    ((text[i][j]=='S' && text[i][j+2]=='S') && (text[i+2][j]=='M' && text[i+2][j+2]=='M')) ||
                    ((text[i][j]=='M' && text[i][j+2]=='S') && (text[i+2][j]=='M' && text[i+2][j+2]=='S')) || 
                    ((text[i][j]=='S' && text[i][j+2]=='M') && (text[i+2][j]=='S' && text[i+2][j+2]=='M'))
                ) &&
                (text[i+1][j+1]=='A')
            ) mas_counter++;
        }
    }

    return mas_counter;
}


int main(){
    std::ifstream file("input.txt");
    std::vector<std::string> text;
    std::string line;

    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string temp;

        while(iss >> temp){
            text.push_back(temp);
        }
    }

    std::cout << xmas_finder(text) << std::endl;
    std::cout << cross_finder(text) << std::endl;

    system("pause");

    return 0;
}
/*  Advent of Code 2023 Day 2 - Cube Conundrum
 *  A program to establish the possibility of a
 *  number of games, based on pre-established limits.
 *  https://adventofcode.com/2023/day/2
 *  ----------
 *  Created: 02-12-23    Ewan Burnett
 *  Revised: 03-12-23    Ewan Burnett
 */

#include <cstdio>
#include <vector>
#include <string> 
#include <stdexcept>
#include <fstream>
#include <unordered_map>

static const std::unordered_map<const char*, uint8_t> g_CubeLimits {
    {"red", 12},
    { "green", 13 },
    { "blue", 14 },
};

void LoadInputData(const std::string& inFile, std::vector<std::string>& outData) {
    //Attempt to open the file. 
    std::fstream file;
    file.open(inFile);

    if (!file.is_open() || !file.good()) {
        throw(std::runtime_error("Unable to open Input Data file.\n"));
        return;
    }

    //Load each line of the file into the vector. 
    outData.clear();

    std::string line;
    while (std::getline(file, line)) {

        //Convert the string to lowercase. (for parsing sanity)
        std::string lwr;
        lwr.resize(line.length());
        for (size_t i = 0; i < line.length(); i++) {
            lwr[i] = std::tolower(line[i]);
        }

        outData.push_back(lwr);
    }

    return;
}


uint64_t PossibleGames(const std::vector<std::string>& input) {

    uint64_t acc = 0;

    //The input array is sorted, so there's no need to extract the game number. 
    for (size_t i = 0; i < input.size(); i++) {
        uint64_t gameID = i + 1;

        //If the number of either the red, green or blue cubes in each round of the game 
        //is greater than our limits, then the game is impossible. 
        //Otherwise, accumulate the ID. 

        std::unordered_map<std::string, uint64_t> count{
            {"red", 0},
            { "green", 0 },
            { "blue", 0 },
        };

        std::string_view v{input[i]};
        size_t offset = v.find_first_of(':');

        //Extract each "game" 
        while (offset < v.size()) {

            offset = v.find_first_of("1234567890", offset, 10); //Extract the number
            auto number = std::atoi(v.data() + offset);

            //offset++;
            offset = v.find_first_not_of(" ;1234567890", offset, 12);

            auto colour = v.data() + offset; //Extract the colour

            auto len = v.find_first_not_of("abcdefghijklmnopqrstuvwxyz", offset, 26) - offset;      //Remove extra characters

            printf("col: %.*s, val: %d\n", len, colour, number);
            offset += len;
            
        }
        printf("--------\n");



    }

    return acc;
}

int main(int argc, const char** argv) {
    printf("Advent of Code 2023 Day 2\tCube Conundrum\nEwan Burnett\n");

    std::vector<std::string> inputData;
    try {
        //Load the Input Data
        const char* inputFile = "input.txt";
        if (argc > 1) {
            inputFile = argv[1];
        }

        LoadInputData(inputFile, inputData);

    }
    catch (std::exception e) {
        printf("[Error]\t%s\n", e.what());
        return -1;
    }

    uint64_t count = PossibleGames(inputData);

    return 0;
}

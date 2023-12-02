/*  Advent of Code 2023 Day 2 - Cube Conundrum
 *  A program to establish the possibility of a
 *  number of games, based on pre-established limits. 
 *  https://adventofcode.com/2023/day/2
 *  ----------
 *  Created: 02-12-23    Ewan Burnett
 *  Revised: 02-12-23    Ewan Burnett
 */

#include <cstdio>
#include <vector>
#include <string> 
#include <stdexcept>
#include <fstream>

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

int main(int argc, const char** argv) {
    printf("AoC Day 2\n");

    const char* inputFile = "input.txt";
    if (argc > 1) {
        inputFile = argv[1];
    }

    std::vector<std::string> inputData; 
    LoadInputData(inputFile, inputData);

}

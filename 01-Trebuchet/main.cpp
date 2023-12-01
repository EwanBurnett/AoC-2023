/*  Advent of Code 2023 Day 1 - Trebuchet
 *  Given a list of strings, for each string extract
 *  the 2 digit number consisting of the first and 
 *  last digits in the string, then compute their sum.
 *  ----------
 *  Created: 01-12-23    Ewan Burnett
 *  Revised: 01-12-23    Ewan Burnett
 */

#include <cstdio>
#include <fstream>
#include <string> 
#include <vector> 
#include <string_view>
#include <stdexcept>

std::vector<std::string> g_InputData; 

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
    while (std::getline(file, line)){
        outData.push_back(line); 
    }

    return; 
}


uint64_t ComputeCalibrationValues(const std::vector<std::string>& data) {

}

int main(int argc, const char** argv) {
    try {
        //Load the Input Data
        std::string inputSource = "input.txt";
        if (argc > 1) {
            inputSource = argv[1];  //Load the supplied file if specified. 
        }

        LoadInputData(inputSource, g_InputData);
        

    }
    catch (std::exception e) {
        printf("Error:\t%s", e.what());
    }

}
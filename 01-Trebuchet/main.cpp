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
    while (std::getline(file, line)) {
        outData.push_back(line);
    }

    return;
}


uint64_t ComputeCalibrationValues(const std::vector<std::string>& data) {

    uint64_t acc = 0;

    for (const auto& str : data) {
        std::string_view v{str};    //Acquire a view of the string we're processing. 

        //Assuming the input data is ASCII characters
        int8_t first = -1;
        int8_t last = -1;

        //crawl through the string, checking each element for an integer.
        for (size_t i = 0; i < v.length(); i++) {
            if (v[i] < '0') {
                continue;
            }
            else if (v[i] > '9') {
                continue;
            }

            first = v[i] - '0'; //Convert from ASCII into an int. 
            last = first;   //Assume the last int is equal to the first int, before the second pass. 
            break;
        }

        //Do the same, but backwards through the string.
        for (size_t i = v.length() - 1; i > 0; i--) {
            if (v[i] < '0') {
                continue;
            }
            else if (v[i] > '9') {
                continue;
            }

            last = v[i] - '0'; //Convert from ASCII into an int. 
            break;
        }

        if (first > -1 && last > -1) {   //Only add to the accumulator if a value has been found. 
            //Promote the numbers to 2 digits, and add to the accumulator. 
            auto cal = (first * 10) + last;
            printf("%d\t%s\n", cal, v.data());
            acc += cal;             }
    }

    return acc;
}

int main(int argc, const char** argv) {

    printf("Recalibrating Values...\n");

    try {
        //Load the Input Data
        std::string inputSource = "input.txt";
        if (argc > 1) {
            inputSource = argv[1];  //Load the supplied file if specified. 
        }

        LoadInputData(inputSource, g_InputData);

        //Compute the calibration value
        uint64_t val = ComputeCalibrationValues(g_InputData);
        printf("Recalibration Complete!\n>> %d", val);


    }
    catch (std::exception e) {
        printf("Error:\t%s", e.what());
    }

}
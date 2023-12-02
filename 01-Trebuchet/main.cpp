/*  Advent of Code 2023 Day 1 - Trebuchet
 *  Given a list of strings, for each string extract
 *  the 2 digit number consisting of the first and
 *  last digits in the string, then compute their sum.
 *  ----------
 *  Created: 01-12-23    Ewan Burnett
 *  Revised: 02-12-23    Ewan Burnett
 */
#define PART_1 0

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

        //Convert the string to lowercase.
        std::string lwr;
        lwr.resize(line.length());
        for (size_t i = 0; i < line.length(); i++) {
            lwr[i] = std::tolower(line[i]);
        }

        outData.push_back(lwr);
    }

    file.close(); 

    return;
}

#if PART_1
/*  Computes the sum Calibration Values from a given input data array
 *  from the first and last integral values (0..9) of each element.
 *  e.g. the string "treb7uchet" would give first = 7, last = 7, value = 77
 *  e.g. the string "pqr3stu8vwx" would give first = 3, last = 8, value = 38
 */
uint64_t ComputeCalibrationValues_Part1(const std::vector<std::string>& data) {

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
            acc += cal;
        }
    }

    return acc;
}

#else
/*  Computes the sum Calibration Values from a given input data array
 *  from the first and last numerical values of each element, including
 *  numbers spelled out in English.
 *  e.g. the string "eightwothree" would give first = 8, last = 3, value = 83
 *  e.g. the string "zoneight234" would give first = 1, last = 4, value = 14
  */
uint64_t ComputeCalibrationValues_Part2(const std::vector<std::string>& data) {

    uint64_t acc = 0;

    //Compare the string with potential values. 
    auto getDigit = [](const char* str, int8_t& val) {
        //utility lambda to compare two substrings. 
        //NOTE: this is unsafe, as no bounds checking is performed. 
        //If this is being called, then the first token has already been successfully validated. 
        auto compareString = [](const char* pA, const char* pB, const uint8_t length) {
            for (uint8_t i = 1; i < length; i++) {
                if (pA[i] != pB[i]) {
                    return false;
                }
            }

            return true;
        };


        switch (str[0]) {
        case 'o':
            if (compareString(str, "one", 3)) {
                val = 1;
                break;
            }
            return false;
        case 't':
            if (compareString(str, "two", 3)) {
                val = 2;
                break;
            }
            else if (compareString(str, "three", 5)) {
                val = 3;
                break;
            }
            return false;
        case 'f':
            if (compareString(str, "four", 4)) {
                val = 4;
                break;
            }
            else if (compareString(str, "five", 4)) {
                val = 5;
                break;
            }
            return false;
        case 's':
            if (compareString(str, "six", 3)) {
                val = 6;
                break;
            }
            else if (compareString(str, "seven", 5)) {
                val = 7;
                break;
            }
            return false;
        case 'e':
            if (compareString(str, "eight", 5)) {
                val = 8;
                break;
            }
            return false;
        case 'n':
            if (compareString(str, "nine", 4)) {
                val = 9;
                break;
            }
            return false;
        default:
            return false;
        }

        return true; 
    };


    int8_t first = -1;
    int8_t last = -1;
    for (const auto& str : data) {
        std::string_view v{str};    //Acquire a view of the string we're processing. 

        //crawl through the string, checking each element for an integer.
        for (size_t i = 0; i < v.length(); i++) {
            if (v[i] < '0') {
                continue;
            }
            else if (v[i] > '9') {  //This might be a numerical string. 
                if (v[i] < 'a') {
                    continue;   //the character is either uppercase or a special character
                }

                auto digit = getDigit(&v[i], first);

                if (!digit) {
                    continue;
                }
                break;

                last = first;   //Assume the last int is equal to the first int, before the second pass. 
                break;

            }

            else {  //This is an integer. 
                first = v[i] - '0'; //Convert from ASCII into an int. 
                last = first;   //Assume the last int is equal to the first int, before the second pass. 
                break;
            }
        }

        //Do the same, but backwards through the string.
        for (size_t i = v.length() - 1; i >= 0; i--) {
            if (v[i] < '0') {
                continue;   //Ignore special characters
            }
            else if (v[i] > '9') {  //This might be a numerical string. 
                if (v[i] < 'a') {
                    continue;   //the character is either uppercase or a special character
                }

                const auto digit = getDigit(&v[i], last);

                if(!digit){
                    continue;
                }
                break;

            }
            else {
                last = v[i] - '0'; //Convert from ASCII into an int. 
                break;
            }
        }


        if (first > -1 && last > -1) {   //Only add to the accumulator if a value has been found. 
            //Promote the numbers to 2 digits, and add to the accumulator. 
            auto cal = (first * 10) + last;
            printf("[%d]\t%d\t%s\n", acc, cal, v.data());
            acc += cal;


        }
        first = -1;
        last = -1;
    }

    return acc;
}
#endif

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
#if PART_1
        uint64_t val = ComputeCalibrationValues_Part1(g_InputData);
#else
        uint64_t val = ComputeCalibrationValues_Part2(g_InputData);
#endif
        printf("Recalibration Complete!\n>> %d", val);


    }
    catch (std::exception e) {
        printf("Error:\t%s", e.what());
    }

    return 0;
}
/*  Advent of Code 2023 Day 1 - Trebuchet
 *  Given a list of strings, for each string extract
 *  the 2 digit number consisting of the first and
 *  last digits in the string, then compute their sum.
 *  ----------
 *  Created: 01-12-23    Ewan Burnett
 *  Revised: 01-12-23    Ewan Burnett
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
            acc += cal;             }
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

    for (const auto& str : data) {
        std::string_view v{str};    //Acquire a view of the string we're processing. 

        int8_t first = -1;
        int8_t last = -1;

        //crawl through the string, checking each element for an integer.
        for (size_t i = 0; i < v.length(); i++) {
            if (v[i] < '0') {
                continue;
            }
            else if (v[i] > '9') {  //This might be a numerical string. 
                if (v[i] < 'a') {
                    continue;   //the character is either uppercase or a special character
                }

                //Compare the string with potential values. 
               switch(v[i]){
                case 'o':
                    if (std::strcmp(&v[i], "one") == 0) {
                        first = 1;
                    break;
                    }
                    continue;
                case 't':
                    if (std::strcmp(&v[i], "two") == 0) {
                        first = 2;
                        break;
                    }
                    else if (std::strcmp(&v[i], "three") == 0) {
                        first = 3;
                        break;
                    }
                    continue;
                case 'f':
                    if (std::strcmp(&v[i], "four") == 0) {
                        first = 4;
                        break;
                    }
                    else if (std::strcmp(&v[i], "five") == 0) {
                        first = 5;
                    break;
                    }
                    continue;
             case 's':
                    if (std::strcmp(&v[i], "six") == 0) {
                        first = 6;
                        break;
                    }
                    else if (std::strcmp(&v[i], "seven") == 0) {
                        first = 7;
                    break;
                    }
                    continue;
             case 'e':
                    if (std::strcmp(&v[i], "eight") == 0) {
                        first = 8;
                    break;
                    }
                    continue;
             case 'n':
                    if (std::strcmp(&v[i], "nine") == 0) {
                        first = 9;
                    break;
                    }
                    continue;
                default:
                    continue;
                }

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
        for (size_t i = v.length() - 1; i > 0; i--) {
            if (v[i] < '0') {
                continue;   //Ignore special characters
            }
            else if (v[i] > '9') {  //This might be a numerical string. 
                if (v[i] < 'a') {
                    continue;   //the character is either uppercase or a special character
                }

                //Compare the string with potential values. 
                switch(v[i]){
                case 'o':
                    if (std::strcmp(&v[i], "one") == 0) {
                        last = 1;
                    break;
                    }
                    continue;
                case 't':
                    if (std::strcmp(&v[i], "two") == 0) {
                        last = 2;
                        break;
                    }
                    else if (std::strcmp(&v[i], "three") == 0) {
                        last = 3;
                        break;
                    }
                    continue;
                case 'f':
                    if (std::strcmp(&v[i], "four") == 0) {
                        last = 4;
                        break;
                    }
                    else if (std::strcmp(&v[i], "five") == 0) {
                        last = 5;
                    break;
                    }
                    continue;
             case 's':
                    if (std::strcmp(&v[i], "six") == 0) {
                        last = 6;
                        break;
                    }
                    else if (std::strcmp(&v[i], "seven") == 0) {
                        last = 7;
                    break;
                    }
                    continue;
             case 'e':
                    if (std::strcmp(&v[i], "eight") == 0) {
                        last = 8;
                    break;
                    }
                    continue;
             case 'n':
                    if (std::strcmp(&v[i], "nine") == 0) {
                        last = 9;
                    break;
                    }
                    continue;
                default:
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
            printf("%d\t%s\n", cal, v.data());
            acc += cal;             }
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

}
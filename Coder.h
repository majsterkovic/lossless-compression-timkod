#ifndef KODOWANIE_CODER_H
#define KODOWANIE_CODER_H

#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <bitset>
#include <cmath>
#include <unordered_map>


class Coder {

protected:
    std::string coded_text;
    std::string text;
    std::string input_filename;
    std::string output_filename;

public:
    unsigned int MAX_DICTIONARY_SIZE;
    
    virtual void save() = 0;
    virtual void code() = 0;
    virtual void load() = 0;

    std::string get_coded_text() const;
    std::string get_text() const;
    std::string get_input_filename() const;
    std::string get_output_filename() const;


    Coder(std::string input_filename,
          std::string output_filename,
          int dict_size);
};


#endif //KODOWANIE_CODER_H
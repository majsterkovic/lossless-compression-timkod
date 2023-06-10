#include <iostream>
#include "Encoder.h"
#include "Decoder.h"


#include <vector>
#include <fstream>

bool compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream stream1(file1, std::ios::binary);
    std::ifstream stream2(file2, std::ios::binary);

    if (!stream1.is_open() || !stream2.is_open()) {
        std::cout << "Error opening files." << std::endl;
        return false;
    }

    std::vector<uint8_t> content1((std::istreambuf_iterator<char>(stream1)), std::istreambuf_iterator<char>());
    std::vector<uint8_t> content2((std::istreambuf_iterator<char>(stream2)), std::istreambuf_iterator<char>());
    stream1.close();
    stream2.close();

    if (content1.size() != content2.size()) {
        return false;
    }

    for (std::size_t i = 0; i < content1.size(); i++) {
        if (content1[i] != content2[i]) {
            return false;
        }
    }

    return true;
}



int main(int argc, char **argv) {

    if (argc != 6) {
        std::cout << "Usage: " << argv[0] <<
                  " <input_filename> <output_encoded_filename>" <<
                  " <input_encoded_filename> <output_decoded_filename>"
                  " <dict_size>"
                  << std::endl;

        return 1;
    }

    std::string filename = argv[1];
    std::string encoded_filename = argv[2];
    std::string todecode_filename = argv[3];
    std::string decoded_filename = argv[4];
    int dict_size = std::stoi(argv[5]);

    Encoder encoder(filename, encoded_filename, dict_size);
    encoder.load();
    encoder.code();
    encoder.save();

    Decoder decoder(todecode_filename, decoded_filename, dict_size);
    decoder.load();
    decoder.code();
    decoder.save();

    if (compareFiles(filename, decoded_filename)) {
        std::cout << " >>> Files are equal. <<<" << std::endl;
    } else {
        std::cout << "\033[1;31m";
        std::cout << " #### Files are not equal. ####" << std::endl;
        std::cout << "\033[0m";
    }
    return 0;
}
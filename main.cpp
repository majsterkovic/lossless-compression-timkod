#include <iostream>
#include "Encoder.h"
#include "Decoder.h"


bool compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream stream1(file1);
    std::ifstream stream2(file2);

    if (!stream1.is_open() || !stream2.is_open()) {
        std::cout << "Error opening files." << std::endl;
        return false;
    }

    std::string content1((std::istreambuf_iterator<char>(stream1)), std::istreambuf_iterator<char>());
    std::string content2((std::istreambuf_iterator<char>(stream2)), std::istreambuf_iterator<char>());

    stream1.close();
    stream2.close();

    return content1 == content2;
}


int main(int argc, char **argv) {

    if (argc != 7) {
        std::cout << "Usage: " << argv[0] <<
                                            "<filename>"
                                            "<codemap_filename>"
                                            "<encoded_filename>"
                                            "<todecode_filename>"
                                            "codemap_filename>"
                                            "<decoded_filename>"
                                             << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string codemap_filename = argv[2];
    std::string encoded_filename = argv[3];

    std::string todecode_filename = argv[4];
    std::string codemap_filename2 = argv[5];
    std::string decoded_filename = argv[6];


    Encoder encoder(filename, encoded_filename, codemap_filename);

    encoder.load();
    encoder.create_codemap();
    encoder.save_codemap();
    encoder.code();
    encoder.save();

    Decoder decoder(todecode_filename, decoded_filename, codemap_filename2);

    decoder.load();
    decoder.load_codemap();
    decoder.code();
    decoder.save();

    if (compareFiles(filename, decoded_filename)) {
        std::cout << "Files are equal." << std::endl;
    } else {
        std::cout << "Files are not equal." << std::endl;
    }

    return 0;
}

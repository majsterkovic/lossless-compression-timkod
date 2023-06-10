#include <unordered_map>
#include "Decoder.h"

void Decoder::code() {
    std::cout << "Decoding..." << std::endl;

    std::string text_size = std::bitset<32>(coded_text.substr(0, 32)).to_string();
    unsigned int size =  std::bitset<32>(coded_text.substr(0, 32)).to_ulong();
    coded_text = coded_text.substr(32);

    std::unordered_map<unsigned int, std::string> dictionary;
    std::string alphabet;
    for (int i = 0; i < 256; i++) {
        alphabet += static_cast<char>(i);
    }

    for (auto &c : alphabet) {
        dictionary[dictionary.size()] = std::string(1, c);
    }

    int bits = ceil(log2( (double) dictionary.size()));
    unsigned int nextInt = std::bitset<32>(coded_text.substr(0, bits)).to_ulong();
    std::string old = dictionary[nextInt];
    this->text = old;
    std::string c;
    std::string word;

    for (unsigned int i = bits; i < coded_text.size();) {
        if (dictionary.size() >= (1u << bits)) { bits++; }

        if (i + bits > coded_text.size()) { break; }

        nextInt = std::bitset<32>(coded_text.substr(i, bits)).to_ulong();
        i += bits;

        if (dictionary.find(nextInt) != dictionary.end()) {
            word = dictionary[nextInt];
        } else if (nextInt == dictionary.size()) {
            word = old + c;
        }

        this->text += word;
        if (text.size() == size)
        {
            break;
        }
        c = word[0];

        if (dictionary.size() <= MAX_DICTIONARY_SIZE || MAX_DICTIONARY_SIZE == 0) {
            dictionary[dictionary.size()] = old + c;
        }
        old = word;
    }
}


void Decoder::load() {
    std::cout << "Loading encoded file..." << std::endl;

    std::ifstream encoded_file(this->input_filename, std::ios::binary);
    if (!encoded_file.is_open()) {
        std::cout << "Error opening file " << this->input_filename << std::endl;
        return;
    }

    encoded_file.seekg(0, std::ios::end);
    std::streamsize file_size = encoded_file.tellg();
    encoded_file.seekg(0, std::ios::beg);

    std::vector<char> bytes(file_size);
    encoded_file.read(reinterpret_cast<char*>(bytes.data()), file_size);
    encoded_file.close();

    std::string encoded_text;
    for (const char& byte : bytes) {
        std::bitset<8> bits(byte);
        encoded_text += bits.to_string();
    }
    this->coded_text = encoded_text;
}

void Decoder::save() {
    std::cout << "Saving decoded file..." << std::endl;

    std::ofstream decoded_file(this->output_filename);
    if (!decoded_file.is_open()) {
        std::cout << "Error opening file " << this->output_filename << std::endl;
        return;
    }

    decoded_file << this->text;
    decoded_file.close();
}
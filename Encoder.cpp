#include "Encoder.h"


void Encoder::save() {
    std::cout << "Saving encoded file..." << std::endl;

    std::ofstream encoded_file(this->output_filename, std::ios::binary);
    if (!encoded_file.is_open()) {
        std::cout << "Error opening file " << this->output_filename << std::endl;
        return;
    }
    std::vector<char> bytes;
    std::size_t new_size = ((this->coded_text.size() + 7) / 8) * 8;
    this->coded_text.resize(new_size, '0');

    for (std::size_t i = 0; i < this->coded_text.size(); i += 8) {
        std::bitset<8> bits(this->coded_text.substr(i, 8));
        bytes.push_back(static_cast<char>(bits.to_ulong()));
    }

    encoded_file.write(reinterpret_cast<const char *>(bytes.data()), (long long) bytes.size());
}


void Encoder::code() {

    std::cout << "Encoding..." << std::endl;
    std::unordered_map<std::string, unsigned int> dictionary;


    std::string size_bits_string = std::bitset<32>(text.size()).to_string();
    coded_text += size_bits_string;

    std::string alphabet;
    for (int i = 0; i < 256; i++) {
        alphabet += static_cast<char>(i);
    }

    for (auto &c : alphabet) {
        dictionary[std::string(1, c)] = dictionary.size();
    }

    std::string current = std::string(1, text[0]);
    int bits;
    int index;

    for (int i = 0; i < text.size() - 1; i++) {
        std::string next = std::string(1, text[i + 1]);

        while(dictionary.count(current + next)) {
            current += next;
            i++;
            next = std::string(1, text[i + 1]);
        }

        bits = ceil(log2((double) dictionary.size()));
        index = (int) dictionary[current];
        std::string index_bits_string = std::bitset<32>(index).to_string().substr(32 - bits);
        coded_text += index_bits_string;

        if (dictionary.size() <= MAX_DICTIONARY_SIZE || MAX_DICTIONARY_SIZE == 0) {
            dictionary[current + next] = dictionary.size();
        }
        current = next;
    }

    bits = ceil(log2( (double) dictionary.size()));
    index = (int) dictionary[current];
    std::string index_bits_string = std::bitset<32>(index).to_string().substr(32 - bits);
    coded_text += index_bits_string;
}

void Encoder::load() {
    std::cout << "Loading text file..." << std::endl;
    std::ifstream text_file(this->input_filename);
    if (!text_file.is_open()) {
        std::cout << "Error opening file " << input_filename << std::endl;
        return;
    }
    this->text = std::string((std::istreambuf_iterator<char>(text_file)),
                             std::istreambuf_iterator<char>());
    if (text_file.bad()) {
        std::cout << "Error reading file " << input_filename << std::endl;
        return;
    }
}
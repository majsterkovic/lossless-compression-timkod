#include "Decoder.h"

void Decoder::code() {
    std::cout << "Decoding..." << std::endl;

    this->text = "";
    int n = (int) this->codemap.begin()->first.length();
    for(int i = 0; i + n < this->coded_text.length(); i=i+n) {
        std::string code = this->coded_text.substr(i, n);
        this->text += this->codemap[code];
    }
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


void Decoder::load_codemap() {
    std::cout << "Loading codemap..." << std::endl;

    std::ifstream codemap_file(this->codemap_filename);
    if (!codemap_file.is_open()) {
        std::cout << "Error opening file " << this->codemap_filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(codemap_file, line)) {
        if (line.length() < 3) {
            std::cout << "Incorrect line format:  " << line << std::endl;
            continue;
        }
        char character = line[0];
        std::string code = line.substr(2);
        this->codemap[code] = character;
    }
}

std::string Decoder::get_coded_text() const {
    return this->coded_text;
}

std::string Decoder::get_text() const {
    return this->text;
}

std::map<std::string, char> Decoder::get_codemap() const {
    return this->codemap;
}

#include "Encoder.h"
#include <cmath>

// Konstruktor klasy Encoder, inicjalizuje nazwy plików wejściowych, wyjściowych i pliku z mapą kodów.


void Encoder::create_codemap() {
    std::cout << "Creating codemap..." << std::endl;

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz 0123456789";

    /* Calculate frequencies - use later */
    std::map<char, double> freq;
    for (char character: alphabet) {
        freq[character] = 0;
    }
    for (char character: this->text) {
        freq[character]++;
    }
    for (auto &pair: freq) {
        pair.second /= (double) this->text.size();
    }

    int n = 1;
    while (pow(2, n) < (double) alphabet.size() + 1) {
        n++;
    }

    for(int i = 0; i < alphabet.size(); i++) {
        std::string code = std::bitset<8>(i + 1).to_string();
        code = code.substr(8 - n);
        this->codemap[alphabet[i]] = code;
    }
}

void Encoder::code() {
    std::cout << "Encoding..." << std::endl;

    for (char character: this->text) {
        std::string code = this->codemap[character];
        this->coded_text += code;
    }
}


void Encoder::save_codemap() {
    std::cout << "Saving codemap..." << std::endl;

    std::ofstream codemap_file(this->codemap_filename);
    if (!codemap_file.is_open()) {
        std::cout << "Error opening file " << this->codemap_filename << std::endl;
        return;
    }
    for (auto &pair: this->codemap) {
        codemap_file << pair.first << " " << pair.second << std::endl;
    }

}


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


std::map<char, std::string> Encoder::get_codemap() const {
    return this->codemap;
}
#include "Encoder.h"
#include <cmath>
#include <queue>
#include <utility>

// Konstruktor klasy Encoder, inicjalizuje nazwy plików wejściowych, wyjściowych i pliku z mapą kodów.



void Encoder::create_codemap() {
    std::cout << "Creating codemap..." << std::endl;

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz 0123456789";
    alphabet += '\0'; // Dodanie symbolu EOF do alfabetu


    for (char character: alphabet) {
        this->freq[character] = 0;
    }
    for (char character: this->text) {
        this->freq[character]++;
    }

    this->freq['\0'] = 1; // Dodanie symbolu EOF do mapy częstotliwości

    for (auto &pair: freq) {
        pair.second /= ((double) this->text.size() + 1);
    }

    std::priority_queue<Node *, std::vector<Node *>, compare> heap;

    for (auto &pair: freq) {
        Node *newNode = new Node;
        newNode->symbol = pair.first;
        newNode->freq = pair.second;
        newNode->left = nullptr;
        newNode->right = nullptr;
        heap.push(newNode);
    }

    while (heap.size() != 1) {
        Node *left = heap.top();
        heap.pop();

        Node *right = heap.top();
        heap.pop();

        Node *top = new Node;
        top->freq = left->freq + right->freq;
        top->symbol = '*'; // temporary symbol
        top->left = left;
        top->right = right;

        heap.push(top);
    }

    create_codemap_helper(heap.top(), "");
}

void Encoder::create_codemap_helper(Node* root, std::string str) {
    if (!root) {
        return;
    }

    if (root->symbol != '*') {
        this->codemap[root->symbol] = str;
    }

    create_codemap_helper(root->left, str + "0");
    create_codemap_helper(root->right, str + "1");
}

void Encoder::code() {
    std::cout << "Encoding..." << std::endl;

    for (char character: this->text) {
        std::string code = this->codemap[character];
        this->coded_text += code;
    }
    this->coded_text += this->codemap['\0']; // Dodanie kodu EOF na końcu tekstu

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

double Encoder::compute_entropy() {
    double entropy = 0;
    for (auto &pair: freq) {
        if (pair.second != 0) {
            entropy -= pair.second * log2(pair.second);
        }
    }
    return entropy;
}

double Encoder::compute_average_code_length() {
    double average_code_length = 0;
    for (auto &pair: this->codemap) {
        //average_code_length += (double) pair.second.size();
        average_code_length += freq[pair.first] * pair.second.size();
    }
    //average_code_length /= (double) this->codemap.size();
    return average_code_length;
}

double Encoder::compute_efficiency() {
    double entropy = this->compute_entropy();
    double average_code_length = this->compute_average_code_length();
    return entropy / average_code_length;
}

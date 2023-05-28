#ifndef KODOWANIE_ENCODER_H
#define KODOWANIE_ENCODER_H


#include "Coder.h"

class Encoder : Coder {

private:
    std::map<char, std::string> codemap;
    void create_codemap_helper(Node* root, std::string str);
    std::map<char, double> freq;

public:
    void create_codemap();
    void code() override;
    void save_codemap();
    void save() override;
    void load() override;

    std::map<char, std::string> get_codemap() const;

    double compute_entropy();
    double compute_average_code_length();
    double compute_efficiency();


    using Coder::Coder;
};

#endif //KODOWANIE_ENCODER_H
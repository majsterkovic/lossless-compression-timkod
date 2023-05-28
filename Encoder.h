#ifndef KODOWANIE_ENCODER_H
#define KODOWANIE_ENCODER_H


#include "Coder.h"

class Encoder : Coder {

private:
    std::map<char, std::string> codemap;

public:
    void create_codemap();
    void code() override;
    void save_codemap();
    void save() override;
    void load() override;

    std::map<char, std::string> get_codemap() const;

    using Coder::Coder;
};

#endif //KODOWANIE_ENCODER_H
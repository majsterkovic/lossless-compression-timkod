#ifndef KODOWANIE_DECODER_H
#define KODOWANIE_DECODER_H

#include "Coder.h"

class Decoder : Coder {
private:
    std::string coded_text;
    std::string text;


public:
    void code() override;
    void save() override;
    void load() override;

    using Coder::Coder;

    std::string get_coded_text() const;
    std::string get_text() const;
};


#endif //KODOWANIE_DECODER_H
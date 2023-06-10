#ifndef KODOWANIE_ENCODER_H
#define KODOWANIE_ENCODER_H

#include "Coder.h"

class Encoder : public Coder {

private:
    std::string text;

public:
    void code() override;
    void save() override;
    void load() override;

    std::string coded_text;

    using Coder::Coder;
};

#endif //KODOWANIE_ENCODER_H
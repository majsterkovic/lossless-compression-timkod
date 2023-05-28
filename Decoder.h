#ifndef KODOWANIE_DECODER_H
#define KODOWANIE_DECODER_H

#include "Coder.h"

class Decoder : Coder {
private:
    std::string coded_text;
    std::string text;
    std::map<std::string, char> codemap;

public:
    void code() override;
    void save() override;
    void load() override;

    using Coder::Coder;

    void load_codemap();

    std::string get_coded_text() const;
    std::string get_text() const;
    std::map<std::string, char> get_codemap() const;
};


#endif //KODOWANIE_DECODER_H

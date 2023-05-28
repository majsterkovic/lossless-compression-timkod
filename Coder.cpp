#include "Coder.h"

Coder::Coder(std::string input_filename,
             std::string output_filename,
             std::string codemap_filename) {

    this->input_filename = std::move(input_filename);
    this->output_filename = std::move(output_filename);
    this->codemap_filename = std::move(codemap_filename);
}

std::string Coder::get_coded_text() const {
    return this->coded_text;
}

std::string Coder::get_text() const {
    return this->text;
}

std::string Coder::get_input_filename() const {
    return this->input_filename;
}

std::string Coder::get_output_filename() const {
    return this->output_filename;
}

std::string Coder::get_codemap_filename() const {
    return this->codemap_filename;
}

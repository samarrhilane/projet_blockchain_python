#include <stdio.h>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <pybind11/pybind11.h>
#include <nlohmann/json.hpp>
#include <pybind11_json/pybind11_json.hpp>
#include <pybind11/stl.h>
#include <pybind11/functional.h>


namespace py = pybind11;

using namespace std;

class Signature {
public:
    string Message_Signature(string message, string private_key);
    string Signature_validation(string message, string public_key, string signature);

private:
    uint8_t* hex_str_to_uint8(const char* string);
    string uint8_to_hex_str(vector<uint8_t>& v);
    unsigned char hexchr2bin(const char hex);
    void hexStringToBin(unsigned char* out, const char* hexPrivate);
    char* binToHexString(char* out, const unsigned char* bin, size_t len);
    vector<uint8_t> fill_vector(uint8_t* data, int size);
    string SHA256(string data);

};


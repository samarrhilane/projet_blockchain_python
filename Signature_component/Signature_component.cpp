
//  Samar, Luiz, Taoufiq 27/05/2022


#include "Signature_component.h"
#include "micro-ecc/uECC.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include "micro-ecc/uECC_vli.h"


//using namespace std;

// Convert charactere to binary
unsigned char Signature::hexchr2bin(const char hex)
{
    unsigned char result;

    if (hex >= '0' && hex <= '9') {
        result = hex - '0';
    }
    else if (hex >= 'A' && hex <= 'F') {
        result = hex - 'A' + 10;
    }
    else if (hex >= 'a' && hex <= 'f') {
        result = hex - 'a' + 10;
    }
    else {
        return 0;
    }
    return result;
}


// Convert String to binary
void Signature::hexStringToBin(unsigned char* out, const char* hexPrivate) {
    for (int i = 0; i < 32; i++) {
        out[i] = hexchr2bin(hexPrivate[2 * i]) << 4 | hexchr2bin(hexPrivate[2 * i + 1]);
    }
}

//Convert binary to String 
char* Signature::binToHexString(char* out, const unsigned char* bin, size_t len)
{
    size_t  i;

    if (bin == NULL || len == 0)
        return NULL;

    for (i = 0; i < len; i++) {
        out[i * 2] = "0123456789abcdef"[bin[i] >> 4];
        out[i * 2 + 1] = "0123456789abcdef"[bin[i] & 0x0F];
    }
    out[len * 2] = '\0';

    return out;
}

string Signature::Message_Signature(string message, string private_key) {
    uECC_Curve curve = uECC_secp256k1(); // create ECC type secp256k1 : elliptic curve used by Bitcoin
    string dataHashed = SHA256(message); // hashing message 
    //uint8_t* hash = hex_str_to_uint8(dataHashed.c_str()); 
    //uint8_t hash[67];
    // hexStringToBin(hash, dataHashed.c_str());
    //uint8_t _private[32];
    //hexStringToBin(_private, private_key.c_str());
    uint8_t* hash = hex_str_to_uint8(dataHashed.c_str());
    uint8_t* _private = hex_str_to_uint8(private_key.c_str());
    uint8_t sig[128] = { 0 };

    if (!uECC_sign(_private, hash, sizeof(hash), sig, curve)) {
        cout << "uECC_sign() failed" << endl;
    }
 
    vector<uint8_t> sigVector = fill_vector(sig, 64);
    return uint8_to_hex_str(sigVector);
    //char Sig_to_String[128];
    //binToHexString(Sig_to_String, sig, 64);
    //return  Sig_to_String;
}

string Signature::Signature_validation(string message, string public_key, string _signature) {
    uECC_Curve curve = uECC_secp256k1();
    string dataHashed = SHA256(message);

    uint8_t* hash = hex_str_to_uint8(dataHashed.c_str());
    uint8_t* _public = hex_str_to_uint8(public_key.c_str());
    uint8_t* _sig = hex_str_to_uint8(_signature.c_str());

/*  uint8_t hash[67];
    hexStringToBin(hash, dataHashed.c_str());
    uint8_t _public[32];
    hexStringToBin(_public, public_key.c_str());
    uint8_t _sig[32];
    hexStringToBin(_sig, _signature.c_str());
*/

    if (!uECC_verify(_public, hash, sizeof(hash), _sig, curve)) {
        return "Signature not valid";
    }
    return "Signature Valid";
}

uint8_t* Signature::hex_str_to_uint8(const char* string) {

    if (string == NULL)
        return NULL;

    size_t slength = strlen(string);
    if ((slength % 2) != 0)
        return NULL;

    size_t dlength = slength / 2;

    uint8_t* message = (uint8_t*)malloc(dlength);

    memset(message, 0, dlength);

    size_t index = 0;
    while (index < slength) {
        char c = string[index];
        int value = 0;
        if (c >= '0' && c <= '9')
            value = (c - '0');
        else if (c >= 'A' && c <= 'F')
            value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
            value = (10 + (c - 'a'));
        else
            return NULL;

        message[(index / 2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return message;
}

string Signature::uint8_to_hex_str(vector<uint8_t>& v) {
    stringstream ss;
    ss << std::hex << setfill('0');
    vector<uint8_t>::const_iterator it;

    for (it = v.begin(); it != v.end(); it++) {
        ss << setw(2) << static_cast<unsigned>(*it);
    }
    return ss.str();
}

vector<uint8_t> Signature::fill_vector(uint8_t* message, int size) {
    std::vector<uint8_t> out;
    for (int x = 0; x < size; x++) {
        out.push_back(message[x]);
    }
    return out;
}

string Signature::SHA256(string message) {
    return "d3751d33f9cd5049c4af2b462735457e4d3baf130bcbb87f389e349fbaeb20b9";
}

namespace py = pybind11;
PYBIND11_MODULE(Signature_component, m) {
    py::class_<Signature>(m, "Signature")
        .def(py::init())
        .def("Message_Signature", &Signature::Message_Signature)
        .def("Signature_validation", &Signature::Signature_validation);
}

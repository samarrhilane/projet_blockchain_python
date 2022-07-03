#include "sha256/sha256/sha256.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

using std::cout; using std::endl;
class component_Hash {
    public:
        component_Hash() {}
        ~component_Hash() {}

        std::string SHA256 (std::string input){
            std::string result;
            if(input.empty()) {
                cout << "ERROR input is empty !!" <<endl;
            }else {
                result = sha256(input);

            }
            return result;
        }
};

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(component_Hash, m) {
    py::class_<component_Hash>(m, "component_Hash")
        .def(py::init())
        .def("SHA256", &component_Hash::SHA256);

}

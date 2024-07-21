// #include <cstdlib>  // for free
// #include <cxxabi.h> // for abi::__cxa_demangle
// #include <iostream>
// #include <memory> // for unique_ptr
// #include <typeinfo>

// using namespace std;

// class Base {
//     virtual void dummy() {}
// };
// class Deeeeerived : public Base { /* ... */
// };

// string demangle(const char *name) {
//     int status = 0;
//     unique_ptr<char[], void (*)(void *)> res{
//         abi::__cxa_demangle(name, nullptr, nullptr, &status),
//         free};
//     return (status == 0) ? res.get() : name;
// }

// int main() {
//     Base *base_ptr = new Deeeeerived;

//     cout << "Type: " << demangle(typeid(*base_ptr).name()) << '\n';

//     delete base_ptr;
//     return 0;
// }
#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl\evp.h>
#include <openssl\err.h>

std::string sha256(const std::string& input) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    // Create and initialize the context
    if((mdctx = EVP_MD_CTX_new()) == nullptr) {
        // Handle errors
    }

    md = EVP_sha256();

    if(1 != EVP_DigestInit_ex(mdctx, md, nullptr)) {
        // Handle errors
    }

    if(1 != EVP_DigestUpdate(mdctx, input.c_str(), input.length())) {
        // Handle errors
    }

    if(1 != EVP_DigestFinal_ex(mdctx, hash, &lengthOfHash)) {
        // Handle errors
    }

    EVP_MD_CTX_free(mdctx);

    std::stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    std::string hash = sha256(input);
    std::cout << "SHA256 hash: " << hash << std::endl;

    return 0;
}

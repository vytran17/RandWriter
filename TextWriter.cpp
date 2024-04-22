//  Copyright 2024 Vy Tran

#include <fstream>
#include <sstream>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " k L < input_file" << std::endl;
        return 1;
    }
    size_t k = std::stoi(argv[1]);
    size_t L = std::stoi(argv[2]);

    std::ostringstream ss;
    ss << std::cin.rdbuf();
    std::string text = ss.str();

    try {
        RandWriter rw(text, k);
        std::string kgram = text.substr(0, k);
        std::string output = rw.generate(kgram, L);
        std::cout << output << std::endl;
        // std::cout << "Model State: \n" << rw << std::endl; // Print model state
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


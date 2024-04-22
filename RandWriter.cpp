//  Copyright 2024 Vy Tran

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include <stdexcept>
#include "RandWriter.hpp"


RandWriter::RandWriter(const std::string& text, size_t k) : text(text), k(k) {
    // std::cout << "Building from: " << text << std::endl;
    if (text.length() < k) {
        throw std::invalid_argument("Text length must be at least k.");
    }
    buildModel();
}

size_t RandWriter::orderK() const {
    return k;
}

int RandWriter::freq(const std::string& kgram) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must be k.");
    }
    auto it = model.find(kgram);
    if (it == model.end()) {
        return 0;
    }
    int total = 0;
    for (const auto& pair : it->second) {
        total += pair.second;
    }
    return total;
}

int RandWriter::freq(const std::string& kgram, char c) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must be k.");
    }
    auto it = model.find(kgram);
    if (it == model.end()) {
        return 0;
    }
    auto charIt = it->second.find(c);
    if (charIt == it->second.end()) {
        return 0;
    }
    return charIt->second;
}

char RandWriter::kRand(const std::string& kgram) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must be k: " + kgram);
    }
    auto it = model.find(kgram);
    if (it == model.end()) {
        throw std::invalid_argument("No such kgram: " + kgram);
    }

    std::vector<std::pair<char, int>> chars;
    for (const auto& pair : it->second) {
        chars.push_back(pair);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> weights;
    for (const auto& pair : chars) {
        weights.push_back(pair.second);
    }
    std::discrete_distribution<> d(weights.begin(), weights.end());
    return chars[d(gen)].first;
}

std::string RandWriter::generate(const std::string& kgram, size_t L) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must be k: " + kgram);
    }
    if (L < k) {
        throw std::invalid_argument("L must be at least k.");
    }

    std::string result = kgram;
    for (size_t i = k; i < L; ++i) {
        char nextChar = kRand(result.substr(result.size() - k));
        result += nextChar;
    }
    return result;
}

void RandWriter::buildModel() {
    for (size_t i = 0; i < text.length(); ++i) {
        // Handle the k-gram at the end that wraps to the beginning
        std::string kgram;
        for (size_t j = 0; j < k; ++j) {
            kgram += text[(i + j) % text.length()];
        }

        char nextChar = text[(i + k) % text.length()];
        model[kgram][nextChar]++;
    }
}

// Overload the stream insertion operator << and display the internal state
// of the Markov model. Print out the order, alphabet, and the frequencies
// of the k-grams and k+1-grams
std::ostream& operator<<(std::ostream& os, const RandWriter& rw) {
    os << "Order: " << rw.orderK() << "\n";
    os << "Model Internal State:\n";
    for (const auto& kgram : rw.model) {
        os << "K-gram '" << kgram.first << "':\n";
        for (const auto& nextChar : kgram.second) {
            os << "  '" << nextChar.first << "' : " << nextChar.second << "\n";
        }
    }
    return os;
}

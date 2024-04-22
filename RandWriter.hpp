//  Copyright 2024 Vy Tran

#ifndef RANDWRITER_HPP
#define RANDWRITER_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include <stdexcept>

class RandWriter {
 public:
    // Create a Markov model of order k from given text
    // Assume that text has length at least k.
    RandWriter(const std::string& text, size_t k);

    size_t orderK() const;

    // Number of occurences of kgram in text
    // Throw an exception if kgram is not length k
    int freq(const std::string& kgram) const;

    // Number of times that character c follows kgram
    // if order=0, return num of times that char c appears
    // (throw an exception if kgram is not of length k)
    int freq(const std::string& kgram, char c) const;

    // Random character following given kgram
    // (throw an exception if kgram is not of length k)
    // (throw an exception if no such kgram)
    char kRand(const std::string& kgram);

    // Generate a string of length L characters by simulating a trajectory
    // through the corresponding Markov chain. The first k characters of
    // the newly generated string should be the argument kgram.
    // Throw an exception if kgram is not of length k.
    // Assume that L is at least k
    std::string generate(const std::string& kgram, size_t L);

    friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

 private:
    void buildModel();
    std::string text;
    size_t k;
    std::unordered_map<std::string, std::unordered_map<char, int>> model;
};

#endif  // RANDWRITER_HPP

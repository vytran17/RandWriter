//  Copyright 2024 Vy Tran

#define BOOST_TEST_MODULE RandWriterTest
#include <boost/test/included/unit_test.hpp>
#include "RandWriter.hpp"  // Make sure to include your RandWriter class header

BOOST_AUTO_TEST_CASE(constructor_test) {
    // Should throw because text length < k
    BOOST_REQUIRE_THROW(RandWriter("", 1), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(RandWriter("hello", 1));  // Should not throw
}

BOOST_AUTO_TEST_CASE(orderK_test) {
    RandWriter rw("hello", 1);
    BOOST_REQUIRE(rw.orderK() == 1);  // The order should be 1
}

BOOST_AUTO_TEST_CASE(freq_test) {
    RandWriter rw("hello", 1);
    BOOST_REQUIRE(rw.freq("h") == 1);  // 'h' appears once
    BOOST_REQUIRE(rw.freq("e") == 1);  // 'e' appears once
    // Should throw, kgram length != k
    BOOST_REQUIRE_THROW(rw.freq("he"), std::invalid_argument);
    BOOST_REQUIRE(rw.freq("l") == 2);  // 'l' appears twice
}

BOOST_AUTO_TEST_CASE(freq_with_char_test) {
    RandWriter rw("hello", 1);
    BOOST_REQUIRE(rw.freq("h", 'e') == 1);  // 'e' follows 'h' once
    BOOST_REQUIRE(rw.freq("l", 'l') == 1);  // 'l' follows 'l' once
    // Should throw, kgram length != k
    BOOST_REQUIRE_THROW(rw.freq("he", 'l'), std::invalid_argument);
    BOOST_REQUIRE(rw.freq("l", 'o') == 1);  // 'o' follows 'l' once
    BOOST_REQUIRE(rw.freq("o", 'h') == 1);  // 'h' follows 'o' once, considering circular text
}

BOOST_AUTO_TEST_CASE(kRand_test) {
    RandWriter rw("hello", 1);
    // Should throw, kgram length != k
    BOOST_REQUIRE_THROW(rw.kRand("he"), std::invalid_argument);
    BOOST_REQUIRE_NO_THROW(rw.kRand("h"));  // Should not throw, 'h' is a valid kgram
}

BOOST_AUTO_TEST_CASE(generate_test) {
    RandWriter rw("hello", 2);
    // Should not throw, valid conditions
    BOOST_REQUIRE_NO_THROW(rw.generate("he", 2));
    // Generate a string of length 5 starting with "he"
    std::string generated = rw.generate("he", 5);
    // The first 2 characters should be "he"
    BOOST_REQUIRE(generated.substr(0, 2) == "he");
}

BOOST_AUTO_TEST_CASE(circular_text) {
    RandWriter rw("gagggagaggcgagaaa", 3);
    BOOST_REQUIRE(rw.freq("aga") == 3);
}

BOOST_AUTO_TEST_CASE(GeneratedTextLength) {
    std::string inputText = "example text to test the generated length";
    size_t k = 3;
    RandWriter rw(inputText, k);

    size_t expectedLength = 100;
    std::string kgram = inputText.substr(0, k);
    std::string generatedText = rw.generate(kgram, expectedLength);
    BOOST_REQUIRE(generatedText.length() == expectedLength);
}

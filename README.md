# PS6: RandWriter

## Contact
Name: Vy Tran
Section: 201
Time to Complete: 5 hours

## Description
This project implements a Markov model text generator, which generates text based on the analysis of a given input text. The generator predicts the next character in the sequence based on the order `k` of previous characters.

### Features
- Markov Model Construction: Built a model by analyzing input text to predict text sequences.
- Exception Handling: Used to ensure the input text length is at least `k` and handle invalid `kgram` inputs.
- Circular Text Analysis: Treated text as circular for continuous prediction, enhancing the model's versatility.

## Testing
- Employed Boost.Test for unit testing, covering all class methods.
- Tested exceptions for edge cases, like invalid `kgram` lengths and text shorter than `k`.
- All tests pass, ensuring reliability.

## Lambda
- Utilized a lambda expression within the `kRand` method to filter and process character frequencies. It enhanced efficiency and readability.
- Passed to standard library functions to succinctly apply operations on character frequency distributions.

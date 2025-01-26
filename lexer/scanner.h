#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <optional>


class Scanner {
private:
  std::string stream; // File to be compiled as a string.
  std::optional<char> buffer; // Stores the next character.

public:
  Scanner(std::string stream) : stream(stream) {}

  bool stream_empty() {
    return stream.empty();
  }

  // Returns the element currently in the buffer, without 
  // consuming it.
  std::optional<char> peek() {
    if (!buffer.has_value())
      buffer = next();
    return buffer.value();
  }

  // If the buffer is empty, the next char is read into the 
  // buffer. Else the buffer is consumed and returned.
  char next() {
    if (buffer.has_value()) {
      char c = buffer.value();
      buffer.reset();
      return c;
    }

    char temp = stream[0];
    stream = stream.length() > 0 ? stream.substr(1) : "";
    return temp;
  }
};

#endif

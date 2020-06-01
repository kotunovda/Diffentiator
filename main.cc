#include <iostream>
#include <cstdio>
#include <string>

#include "Vector.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Diff.hpp"

int main() {
  Differenciator * diff = new Differenciator;
  std::cout << "Lexing...\n";
  diff -> Lexing();
  std::cout << "done\n";
  std::cout << "Parsing...\n";
  diff -> Parsing();
  std::cout << "done\n";
  std::cout << "Differenciating...\n";
  diff -> StartDiff();
  std::cout << "done\n";
  std::cout << "Printing...\n";
  diff -> StartPrint();
  std::cout << "done\n";
  delete diff;
}

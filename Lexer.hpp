#pragma once
#include <cstdio>
#include<string>
#include <iostream>

#include "Vector.hpp"
#include "Types.hpp"

class Lexer{
  MyVector<std::string> lexems;
  std::string buf;
public:
  void Tokenisation();
  friend class Parser;
};

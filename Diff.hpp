#pragma once

#include "SyntaxTree.hpp"
#include "Parser.hpp"

class Differenciator{
  SyntaxTree tree;
  Parser parser;
public:
  void Parsing(){parser.Parsing();}
  void Lexing() {parser.Lexing();}
  void StartDiff();
  SyntaxNodeI* CopyTree(SyntaxNodeI* node);
  SyntaxNodeI* MakeDiff(SyntaxNodeI* node);
  Syntax::Types GetSyntType(SyntaxNodeI * node);
  Tokens::Types GetTokenType(SyntaxNodeI* node);
  SyntaxNodeI* MakeSimple(SyntaxNodeI* node);
  void Print(SyntaxNodeI* node);
  void StartPrint();
  
};

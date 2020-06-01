#include "Parser.hpp"

using namespace Tokens;

void Parser::Parsing() {
  tree.root = Expr();
}

SyntaxNodeI * Parser::Expr() {
  
  SyntaxNodeI* buf = Mult();
  
  if (idx >= lexer.lexems.size()) return buf;
  
  std::string token = lexer.lexems[idx];
  if(token == "+" || token == "-") {

    std::cout << "+/-!\n";
    SyntaxNodeI * op = new SyntaxNodeBin;
    
    if(token == "+") {op -> SetType(Types::PLUS);}
    if(token == "-") {op -> SetType(Types::MINUS);}
    op -> SetLeft(buf);
    ++idx;
    op -> SetRight(Expr());
    return op;
  }

  else {
    return buf;
  }
}

SyntaxNodeI * Parser::Mult() {
  
  SyntaxNodeI* buf = Term();

  if(idx >= lexer.lexems.size()) return buf;

  std::string token = lexer.lexems[idx];
  if(token == "*" || token == "/") {
    SyntaxNodeI * op = new SyntaxNodeBin;

    if(token == "*") {op -> SetType(Types::MULT);}
    if(token == "/") {op -> SetType(Types::DIV);}

    op -> SetLeft(buf);
    ++idx;
    op -> SetRight(Mult());

    return op;
  }

  if(token == "^") {
    SyntaxNodeI * op = new SyntaxNodeBin;
    op -> SetType(Types::UPPER);
    op -> SetLeft(buf);
    ++idx;
    op -> SetRight(Term());
    return op;
  }

  else {
    return buf;
  }
}

SyntaxNodeI * Parser::Term() {
  
  std::string token = lexer.lexems[idx];
  int number = std::atoi(token.c_str());
  if(number) {
    std::cout << "NUM!\n";
    SyntaxNodeI * num = new SyntaxNodeNum;
    num -> SetType(Types::NUM);
    num -> SetData(number);
    ++idx;
    return num;
  }

  else if(token == "x") {
    std::cout << "X!\n";
    SyntaxNodeI * var = new SyntaxNodeI;
    var -> SetType(Types::VAR);
    ++idx;
    return var;
  }

  else if(token == "(") {
    ++idx;
    SyntaxNodeI* buf = Expr();
    assert(lexer.lexems[idx] == ")");
    ++idx;
    return buf;
  }

  else if(token == "cos" || token == "ln" || token == "sin" ||
	  token == "tg" || token == "ctg" || token == "exp") {
  
    SyntaxNodeI * func = new SyntaxNodeUno;
    
    if(token == "cos") {func -> SetType(Types::COS);}
    else if(token == "sin") {func -> SetType(Types::SIN);}
    else if(token == "ln") {func -> SetType(Types::LN);}
    else if(token ==  "tg") {func -> SetType(Types::TG);}
    else if(token == "ctg") {func -> SetType(Types::CTG);}
    else if(token == "exp") {func -> SetType(Types::EXP);}
    
    ++idx;
    assert(lexer.lexems[idx] == "(");
    func -> SetLeft(Term()); 
    return func;
  }

  else {
    std::cout << "Unexpected token " << token << std::endl;
    std::abort(); 
  }
}

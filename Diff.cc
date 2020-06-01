#include"Diff.hpp"

using namespace Tokens;

Syntax::Types Differenciator::GetSyntType(SyntaxNodeI * node) {
  assert(node != NULL);
  if(node -> GetType() == Types::COS || node -> GetType() == Types::SIN || 
     node -> GetType() == Types::TG || node -> GetType() == Types::CTG ||
     node -> GetType() == Types::LN || node -> GetType() == EXP) {
    return Syntax::UNO;
  }

  else if(node -> GetType() == Types::PLUS || node -> GetType() == Types::MINUS || 
	  node -> GetType() == Types::MULT || node -> GetType() == Types::DIV ||
	  node -> GetType() == Types::UPPER) {
    return Syntax::BIN;
  }

  else if(node -> GetType() == Types::VAR) return Syntax::VAR;

  else if(node -> GetType() == Types::NUM) return Syntax::NUM;
}

Tokens::Types Differenciator::GetTokenType(SyntaxNodeI * node) {
  assert(node != NULL);

  
  if(node -> GetType() == Types::COS || node -> GetType() == Types::SIN || 
     node -> GetType() == Types::TG || node -> GetType() == Types::CTG ||
     node -> GetType() == Types::LN || node -> GetType() == EXP) {
    return Types::FUNC;
  }

  else if(node -> GetType() == Types::PLUS || node -> GetType() == Types::MINUS || 
	  node -> GetType() == Types::MULT || node -> GetType() == Types::DIV ||
	  node -> GetType() == Types::UPPER) {
    return Types::OP;
  }

  else if(node -> GetType() == Types::VAR) return Types::VAR;

  else if(node -> GetType() == Types::NUM) return Types::NUM;
}



SyntaxNodeI* Differenciator::CopyTree(SyntaxNodeI * node) {
  assert(node != NULL);
  switch(GetSyntType(node)) {
    case Syntax::Types::UNO : {
		                SyntaxNodeI * newnode = new SyntaxNodeUno(node -> GetType());
                                assert(node -> GetLeft() != NULL);
		                newnode -> SetLeft(CopyTree(node -> GetLeft()));
                                return newnode;
		              }
    case Syntax::Types::BIN : {
		                SyntaxNodeI* newnode = new SyntaxNodeBin(node -> GetType());
			        assert(node -> GetLeft() != NULL && node -> GetRight() != NULL);
			        newnode -> SetLeft(CopyTree(node -> GetLeft()));
			        newnode -> SetRight(CopyTree(node -> GetRight()));
			        return newnode;
		              }
    case Syntax::Types::VAR : {
                                SyntaxNodeI* newnode = new SyntaxNodeI(node -> GetType());
				return newnode;
                              }
    case Syntax::Types::NUM : {
                                SyntaxNodeI* newnode = new SyntaxNodeNum(node -> GetType());
				newnode -> SetData(node -> GetData());
                              }
  }
}

SyntaxNodeI * Differenciator::MakeDiff(SyntaxNodeI* node) {
  assert(node != NULL);
  if(node -> GetType() == Types::PLUS || node -> GetType() == Types::MINUS) {
    SyntaxNodeI * op = new SyntaxNodeBin(node -> GetType());
    op -> SetLeft(MakeDiff(node -> GetLeft()));
    op -> SetRight(MakeDiff(node -> GetRight()));
    return op;
  }

  else if(node -> GetType() == Types::MULT) {
    SyntaxNodeI * op = new SyntaxNodeBin(Types::PLUS);
    SyntaxNodeI * left = CopyTree(node -> GetLeft());
    SyntaxNodeI * right = CopyTree(node -> GetRight());
    op -> SetLeft(new SyntaxNodeBin(Types::MULT));
    op -> SetRight(new SyntaxNodeBin(Types::MULT));
    op -> GetLeft() -> SetLeft(MakeDiff(node -> GetLeft()));
    op -> GetLeft() -> SetRight(right);
    op -> GetRight() -> SetLeft(left);
    op -> GetRight() -> SetRight(MakeDiff(node -> GetRight()));
    return op;
  }
  
  else if(node -> GetType() == Types::DIV) {}

  else if(node -> GetType() == Types::NUM) {
    SyntaxNodeI * num = new SyntaxNodeNum(Types::NUM, 0);
    return num;
  }

  else if (node -> GetType() == Types::VAR) {
    SyntaxNodeI* num = new SyntaxNodeNum(Types::NUM, 1);
    return num;
  }

  else if(node -> GetType() == Types::COS) {
    SyntaxNodeI* sin = new SyntaxNodeUno(Types::SIN);
    SyntaxNodeI* num = new SyntaxNodeNum(Types::NUM, 0);
    SyntaxNodeI* minus = new SyntaxNodeBin(Types::MINUS, num, sin);
    sin -> SetLeft(CopyTree(node -> GetLeft()));
    SyntaxNodeI* mult = new SyntaxNodeBin(Types::MULT, minus, MakeDiff(sin -> GetLeft()));
    return mult;
  }

  else if(node -> GetType() == SIN) {
    SyntaxNodeI* cos = new SyntaxNodeUno(Types::COS);
    cos -> SetLeft(CopyTree(node -> GetLeft()));
    SyntaxNodeI* mult = new SyntaxNodeBin(Types::MULT, cos, MakeDiff(cos -> GetLeft()));
    return mult;
  }

  else if(node -> GetType() == TG) {}
  else if(node -> GetType() == CTG) {}
  else if(node -> GetType() == LN) {}
  else if(node -> GetType() == EXP) {}

  else if(node -> GetType() == UPPER) {
    assert(node -> GetRight() -> GetType() == Types::NUM);
    assert(node -> GetRight() -> GetData() != 0 && node -> GetRight() -> GetData() != 1);
    SyntaxNodeI* num = new SyntaxNodeNum(Types::NUM, node -> GetRight() -> GetData());
    SyntaxNodeI* upper = CopyTree(node);
    upper -> GetRight() -> SetData(num -> GetData() - 1);
    SyntaxNodeI* mult1 = new SyntaxNodeBin(Types::MULT, num, upper);
    SyntaxNodeI* mult2 = new SyntaxNodeBin(Types::MULT, mult1, MakeDiff(upper -> GetLeft()));
    return mult2; 
  }

  else {std::cout << "Unexpected type in expression\n";
        std::abort();
  }
}

SyntaxNodeI* Differenciator::MakeSimple(SyntaxNodeI* node) {
  assert(node != NULL);
  
  if(node -> GetRight() != NULL) node -> SetRight(MakeSimple(node -> GetRight()));
  if(node -> GetLeft() != NULL) node -> SetLeft(MakeSimple(node -> GetLeft()));
  //else return node;

  //Bad----------------------------
  if((node -> GetType() == Types::MULT && 
     ((node -> GetRight() -> GetType() == Types::NUM && node -> GetRight() -> GetData() == 1) || 
     (node -> GetLeft() -> GetType() == Types::NUM && node -> GetLeft() -> GetData() == 0))) || 
     
     ((node -> GetType() == Types::PLUS || node -> GetType() == Types::MINUS) && 
      node -> GetRight() -> GetType() == Types::NUM && node -> GetRight() -> GetData() == 0) ||

     ((node -> GetType() == Types::UPPER) && (node -> GetRight() -> GetData() == 1))) {


    std::cout << "Hi, checker!\n"; 
    SyntaxNodeI* newnode = CopyTree(node -> GetLeft());
    node -> DeleteTree();
    return newnode;
  }


  else if((node -> GetType() == Types::MULT && 
     (node -> GetLeft() -> GetType() == Types::NUM && node -> GetLeft() -> GetData() == 1)) ||
		  
     (node -> GetType() == Types::PLUS && 
      node -> GetLeft() -> GetType() == Types::NUM && node -> GetLeft() -> GetData() == 0)) {
    //std::cout << "Hi, checker!\n"; 
    SyntaxNodeI* newnode = CopyTree(node -> GetRight());
    node -> DeleteTree();
    return newnode;
  }
   
  //----------------------------------

  else return node;
}

void Differenciator::Print(SyntaxNodeI * node) {
  assert(node != NULL);	
  Types type = node -> GetType();
  if(type == Types::PLUS || type == Types::MINUS || 
     type == Types::MULT || type == Types::DIV || 
     type == Types::UPPER) {
    
    if((/*(type == Types::MINUS || type == Types::PLUS) &&*/ GetTokenType(node -> GetLeft()) == Types::NUM || 
       GetTokenType(node -> GetLeft()) == VAR || GetTokenType(node -> GetLeft()) == Types::FUNC)) {} 
      
    else { if(((type == MULT) && node -> GetLeft() -> GetType() == Types::MULT)){}
    
           else std::cout << "(";}
  
    Print(node -> GetLeft());

    
    if((/*(type == Types::PLUS || type == Types::MINUS) &&*/ GetTokenType(node -> GetLeft()) == Types::NUM || 
       GetTokenType(node -> GetLeft()) == VAR || GetTokenType(node -> GetLeft()) == Types::FUNC)) {}
		    
    else {  if(((type == MULT) && node -> GetLeft() -> GetType() == Types::MULT)){}

    else std::cout << ")";}

    
    switch(type) {
      case Types::PLUS : {std::cout << " + "; break;}
      case Types::MINUS: {std::cout << " - "; break;}
      case Types::MULT : {std::cout << " * "; break;}
      case Types::DIV  : {std::cout << " / "; break;}
      case Types::UPPER: {std::cout << " ^ "; break;}
    }
    
    if((GetTokenType(node -> GetRight()) == Types::NUM || 
       GetTokenType(node -> GetRight()) == VAR || GetTokenType(node -> GetRight()) == Types::FUNC)) {}
       
    else {if(((type == MULT) && node -> GetRight() -> GetType() == Types::MULT)){}
    
    else std::cout << "(";}
    
    Print(node -> GetRight());

    if((/*(type == Types::MINUS || type == Types::PLUS) &&*/ GetTokenType(node -> GetRight()) == Types::NUM || 
       GetTokenType(node -> GetRight()) == VAR || GetTokenType(node -> GetRight()) == Types::FUNC)) {} 

    else {if(((type == MULT) && node -> GetRight() -> GetType() == Types::MULT)) {}
    
    else std::cout << ")";}
  }

  else if(type == Types::COS || type == Types::SIN || type == Types::LN ||
          type == Types::EXP || type == Types::CTG || type == Types::TG) {
    
    switch(type) {
      case Types::COS : {std::cout << "cos("; break;}
      case Types::SIN : {std::cout << "sin("; break;}
      case Types::LN :  {std::cout << "ln("; break;}
      case Types::TG :  {std::cout << "tg("; break;}
      case Types::EXP : {std::cout << "exp("; break;}
      case Types::CTG : {std::cout << "ctg("; break;}
    }

    Print(node -> GetLeft());
    std::cout << ")";
  }

  else if(type ==Types::NUM) {std::cout << node -> GetData();}
  else if(type == Types::VAR) {std::cout << "x";}
  else {std::cout << "Unexpected type in diff tree\n";
        std::abort();
  }
}

void Differenciator::StartDiff() {
  tree.root = MakeDiff(parser.tree.root);
}

void Differenciator::StartPrint() {
  tree.root = MakeSimple(tree.root);
  std::cout << "Hi, simple!\n";
  Print(tree.root);
}


/*void DeleteTree(SyntaxNodeI * node) {
  assert(node != NULL);
  if (node -> GetLeft() != NULL) DeleteTree(node -> GetLeft());
  if (node -> GetRight() != NULL) DeleteTree(node -> GetRight());
    
  delete node;
}*/

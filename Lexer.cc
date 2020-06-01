#include "Lexer.hpp"

void Lexer::Tokenisation() {
    std::cin >> std::noskipws;
    char c_in = '0';
    while(true){
      
      std::cin >> c_in;
      
      //std::cout << "c_in = " << c_in <<std::endl;  

      if(std::isdigit(c_in)) {
	do {
          buf.push_back(c_in);
	  std::cin >> c_in;
        } 
	while(std::isdigit(c_in));

        lexems.push_back(buf);
	buf.clear();
      }

      if(c_in == '\n') {break;}

      if(c_in == ' ') {continue;}
      
      switch(c_in) {
	case 'e': {
		    if(!buf.empty()) {
		      std::cout << "Wrong function " << buf << "e" << std::endl;
		      std::abort();
		    }

		    buf.push_back('e');
		    break;
		  }
	case 'x': {
	            if(buf == "e") {
		      buf.push_back('x');
		    }

		    else if(!buf.empty()) {
		      std::cout << "Wrong function " << buf << "x" << std::endl;
		      std::abort;
		    }

		    else {
		      lexems.push_back("x");}
		   
		    break;
		  }
	case 'p': {
		    if(buf == "ex"){
		      lexems.push_back("exp");
		      buf.clear();
		    }

		    else {
		      std::cout << "Wrong function " << buf << "p" << std::endl;
		      std::abort();
		    }
		  }
	case 'l':  {
		     if(!buf.empty()){ 
	               std::cout << "Wrong function " << buf << "l" << std::endl;
		       std::abort();
		     }
		     buf.push_back(c_in);
		     break;
                   }
	case 'n': {
		     if(buf == "l"){
		       lexems.push_back("ln");
		       buf.clear();
		     }

		     else if(buf == "si"){
		       lexems.push_back("sin");
		       buf.clear();
		     }

		     else {
		       std::cout << "Wrong function " << buf << "n" << std::endl;
		       std::abort();
		     }
		     break;
		   }

        case 'c': {
		     if(!buf.empty()) {
		       std::cout << "Wrong function " << buf << "l" << std::endl;
                       std::abort();
		     }
                     buf.push_back(c_in);
		     break;
		   }  
        case 'o':  {
		     if(buf == "c"){
		       buf.push_back(c_in);
		     }

		     else {
		       std::cout << "Wrong function " << buf << "o" << std::endl;
		       std::abort();
		     }
		     break;
		   }
        case 's':  {
		     if(buf == "co") {
		       lexems.push_back("cos");
		       buf.clear();
		     }

		     else if(buf.empty()) buf.push_back(c_in);

		     else {
		       std::cout << "Wrong function " << buf << "s" << std::endl;
		       std::abort();
		     }
		     break;
		   }
	case 'i':  {
	             if(buf == "s") buf.push_back(c_in);
		     else {
		       std::cout << "Wrong function " << buf << "i" << std::endl;
		     }
		     break;
	           }
	case 't':  {
	             if(buf == "c" || buf.empty()) buf.push_back(c_in);

		     else {
		       std::cout << "Wrong function " << buf << "t" << std::endl;
		       std::abort();
		     }
		     break;
	           }
	case 'g':  {
	             if(buf == "t") {
		       lexems.push_back("tg");
		       buf.clear();
		     }

		     else if(buf == "ct") {
		       lexems.push_back("ctg");
		       buf.clear();
		     }

		     else {
		      std::cout << "Wrong function " << buf << "g"<< std::endl;
		      std::abort();
		     }

		     break;
	           }
	case '+':  {lexems.push_back("+");break;}
	case '-':  {lexems.push_back("-");break;}
	case '*':  {lexems.push_back("*");break;}
	case '/':  {lexems.push_back("/");break;}
	case '(':  {lexems.push_back("(");break;}
	case ')':  {lexems.push_back(")");break;}
	case '^':  {lexems.push_back("^");break;}
	default :  {std::cout << "Wrong symbol\n";
		    std::abort();
		   }
      }
    }
}

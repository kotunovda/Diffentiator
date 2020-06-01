#pragma once

#include"Types.hpp"
#include<iostream>
#include<cassert>

class SyntaxNodeI {
  Tokens::Types type;

  void MessageAndAbort() const{
    std::cout << "You mustn't use this function in this scope\n";
    std::abort();
  }

public:
  SyntaxNodeI() = default;

  SyntaxNodeI(Tokens::Types type_) {
    type = type_;
  }

  Tokens::Types GetType() const{
    return type;
  }

  void SetType(Tokens::Types type_) {
    type = type_;
  }

  virtual void DeleteTree() {
    delete this;
  }

  virtual SyntaxNodeI* GetRight() const{
    return NULL;
  }
  virtual SyntaxNodeI* GetLeft() const{
    return NULL;
  };

  virtual void SetLeft(SyntaxNodeI* left_){
    MessageAndAbort();
  }

  virtual void SetRight(SyntaxNodeI* right_){
    MessageAndAbort();
  }

  virtual int GetData() const {
    MessageAndAbort();
  }

  virtual void SetData(int data_) {
    MessageAndAbort();
  }

  virtual ~SyntaxNodeI() {}
    
};

class SyntaxNodeUno : public SyntaxNodeI {
protected:
  SyntaxNodeI * left;

public:
  SyntaxNodeUno() = default;
  
  SyntaxNodeUno(Tokens::Types type_) : SyntaxNodeI(type_) {}
  
  SyntaxNodeUno(Tokens::Types type_, SyntaxNodeI* left_) : SyntaxNodeI(type_), left(left_) {}

  SyntaxNodeI* GetLeft() const override{
    return left;
  }

  void SetLeft(SyntaxNodeI * left_) override {
    left = left_;
  }

  virtual void DeleteTree() override{
    left -> DeleteTree();
    delete this;
  }

  virtual ~SyntaxNodeUno() {}
};

class SyntaxNodeBin final: public SyntaxNodeUno {
  
  SyntaxNodeI * right;

public:
  SyntaxNodeBin() = default;

  SyntaxNodeBin(Tokens::Types type_) : SyntaxNodeUno(type_) {}

  SyntaxNodeBin(Tokens::Types type_, SyntaxNodeI* left_, SyntaxNodeI* right_) : SyntaxNodeUno(type_, left_), right(right_) {}

  SyntaxNodeI* GetRight() const override{
    return right;
  }

  void SetRight(SyntaxNodeI * right_) override{
    right = right_;
  }

  void DeleteTree() override {
    left -> DeleteTree();
    right -> DeleteTree();
    delete this;
  }
};

class SyntaxNodeNum final: public SyntaxNodeI{
  int data;

public:
  SyntaxNodeNum() = default;

  SyntaxNodeNum(Tokens::Types type_) : SyntaxNodeI(type_) {}

  SyntaxNodeNum(Tokens::Types type_, int data_) : SyntaxNodeI(type_), data(data_) {}

  void SetData(int data_) override{
    data = data_;
  }

  int GetData() const override{
    return data;
  }
  
  void DeleteTree() {
    delete this;
  }
};

struct SyntaxTree {
  SyntaxNodeI * root;

  void DeleteTree(SyntaxNodeI * node) {
    assert(node != NULL);
    if (node -> GetLeft() != NULL) DeleteTree(node -> GetLeft());
    if (node -> GetRight() != NULL) DeleteTree(node -> GetRight());
    
    delete node;
  }

  ~SyntaxTree() {
    DeleteTree(root);
  }

};

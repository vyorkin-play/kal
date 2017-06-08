#ifndef __BASE_H__
#define __BASE_H__

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

class ASTNode;
class VariableNode;
class BinaryNode;
class CallNode;
class FunctionNode;
class NumberNode;
class PrototypeNode;

class Logger;
class Lexer;
class Parser;

static llvm::LLVMContext llvmContext;
static llvm::IRBuilder<> irBuilder(llvmContext);
static std::unique_ptr<llvm::Module> module;
static std::map<std::string, llvm::Value*> namedValues;

#endif

#include "AST.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

class CodeGenerator {
public:
    CodeGenerator();

    // Takes the root of the AST and generates code
    void generateCode(const ExprNode* root);

private:
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;
    llvm::IRBuilder<> builder;

    // Methods to handle different node types
    llvm::Value* generate(const ExprNode* node);
    llvm::Value* generate(const NumberNode* node);
    llvm::Value* generate(const BinaryExprNode* node);
    llvm::Value* generate(const UnaryExprNode* node);

    // Utility methods
};

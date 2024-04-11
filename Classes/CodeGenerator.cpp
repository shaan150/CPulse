#include "CodeGenerator.h"
#include "llvm/IR/Constants.h"

CodeGenerator::CodeGenerator()
    : builder(context), module(new llvm::Module("my cool jit", context)) {}

void CodeGenerator::generateCode(const ExprNode* root) {
    // This could be the entry point for generating code for a function or the whole program.
    // For simplicity, let's assume we're generating a single function that returns the evaluation of the expression.

    // Create the main function entry.
    llvm::FunctionType* funcType = llvm::FunctionType::get(builder.getDoubleTy(), false);
    llvm::Function* mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module.get());
    llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);

    // Generate the code for the AST and use its result as the return value.
    llvm::Value* retVal = generate(root);
    builder.CreateRet(retVal);

    // Complete the function and verify it
    llvm::verifyFunction(*mainFunc);

    // Create an ExecutionEngine
    std::string errStr;
    llvm::ExecutionEngine* EE = llvm::EngineBuilder(std::move(module))
        .setErrorStr(&errStr)
        .setEngineKind(llvm::EngineKind::JIT)
        .create();

    if (!EE) {
        std::cerr << "Failed to create ExecutionEngine: " << errStr << std::endl;
        return;
    }

    // Execute the `main` function
    std::vector<llvm::GenericValue> noargs;
    llvm::GenericValue gv = EE->runFunction(mainFunc, noargs);

    // Assuming main returns a double, print the result
    double result = gv.DoubleVal;
    std::cout << "Execution Result: " << result << std::endl;

    // Clean up
    delete EE;
    llvm::llvm_shutdown();
}

llvm::Value* CodeGenerator::generate(const ExprNode* node) {
    // Dispatch to the appropriate method based on the actual type of node.
    if (const auto numNode = dynamic_cast<const NumberNode*>(node)) {
        return generate(numNode);
    }
    else if (const auto binaryNode = dynamic_cast<const BinaryExprNode*>(node)) {
        return generate(binaryNode);
    }
    else if (const auto unaryNode = dynamic_cast<const UnaryExprNode*>(node)) {
        return generate(unaryNode);
    }
    // Handle other node types as needed.
    return nullptr;
}

llvm::Value* CodeGenerator::generate(const NumberNode* node) {
    return llvm::ConstantFP::get(context, llvm::APFloat(node->value));
}

llvm::Value* CodeGenerator::generate(const BinaryExprNode* node) {
    llvm::Value* left = generate(node->left.get());
    llvm::Value* right = generate(node->right.get());
    if (!left || !right) return nullptr;

    switch (node->op) {
    case '+':
        return builder.CreateFAdd(left, right, "addtmp");
    case '-':
        return builder.CreateFSub(left, right, "subtmp");
    case '*':
        return builder.CreateFMul(left, right, "multmp");
    case '/':
        return builder.CreateFDiv(left, right, "divtmp");
    default:
        // Handle errors or unsupported operations
        throw std::runtime_error("Unsupported binary operator");
    }
}

llvm::Value* CodeGenerator::generate(const UnaryExprNode* node) {
    llvm::Value* operand = generate(node->operand.get());
    if (!operand) return nullptr;

    switch (node->op) {
    case '-':
        // Creating a negation by subtracting from zero
        return builder.CreateFSub(llvm::ConstantFP::get(context, llvm::APFloat(0.0)), operand, "negtmp");
    default:
        // Handle errors or unsupported operations
        throw std::runtime_error("Unsupported unary operator");
    }
}

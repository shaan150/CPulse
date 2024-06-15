#pragma once
#include <CodeGenerator/CodeGenerator.h>
#include <Value/ValueHelper.h>
#include <AST/AST.h>


Value evaluateListInitNode(CodeGenerator& generator, const ListInitNode* listNode);
Value evaluateListAppendNode(CodeGenerator& generator, const ListAppendNode* listAppendNode);
Value evaluateListPopNode(CodeGenerator& generator, const ListPopNode* listPopNode);
Value evaluateListLengthNode(CodeGenerator& generator, const ListLengthNode* listLengthNode);
Value evaluateListIndexNode(CodeGenerator& generator, const ListIndexNode* listIndexNode);
Value evaluateListReplaceNode(CodeGenerator& generator, const ListReplaceNode* listReplaceNode);
Value getListValue(CodeGenerator& generator, const std::string& name, const Token& token);

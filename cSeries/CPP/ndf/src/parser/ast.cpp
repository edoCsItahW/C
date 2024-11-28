// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file ast.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/25 下午3:47
 * @brief
 * */
#include "ast.h"
#include <sstream>
#include <iostream>  // MSCV

namespace ast {
    std::string idt(int indent) { return std::string(indent * 4, ' '); }

    std::string Program::toString() const {
        std::ostringstream oss;

        for (const auto& stmt : statements) {
            oss << stmt->toString() << std::endl;
    }

        return oss.str();
    }

    std::vector<std::shared_ptr<AST>> Program::children() const {
        std::vector<std::shared_ptr<AST>> children;

        for (const auto& stmt : statements)
            children.push_back(stmt);

        return children;
    }

    void Program::accept(Visitor& v) {}

    void Statement::accept(ast::Visitor& v) {}

    std::vector<std::shared_ptr<AST>> Statement::children() const { return {}; }

    std::string Assignment::toString() const {
        return idt(indent) + identifier->toString() + " is " + expression->toString() + '\n';
    }

    void Assignment::accept(ast::Visitor& v) {
        v.visit(*this);
        if (expression)
            expression->accept(v);
    }

    std::vector<std::shared_ptr<AST>> Assignment::children() const {
        return {};
    }

    std::string ObjectDef::toString() const {
        std::ostringstream oss;

        oss << idt(indent) << identifier->toString() << " is " << type->toString() << "(" << std::endl;

        for (int i = 0; i < memberList.size(); i++)
            oss << idt(indent + 1) << memberList[i]->toString() << (i == memberList.size() - 1 ? "" : ",") << std::endl;

        oss << ")" << std::endl;

        return oss.str();
    }

    std::string MapDef::toString() const {
        std::ostringstream oss;

        oss << "MAP [" << std::endl;

        for (const auto& pair : pairList)
            oss << idt(indent + 1) << pair->toString() << "," << std::endl;

        oss << "]" << std::endl;

        return oss.str();
    }

    std::string Parameter::toString() const { return identifier->toString() + (type ? ": " + type->toString() : "") + (expression ? " = " + expression->toString() : ""); }

    std::string TemplateDef::toString() const {
        std::ostringstream oss;

        oss << idt(indent) << "template " << identifier->toString() << "[" << std::endl;

        for (int i = 0; i < parameterList.size(); i++)
            oss << idt(indent + 1) << parameterList[i]->toString() << (i == parameterList.size() - 1 ? "" : ",") << std::endl;

        oss << "] is " << type->toString() << "(" << std::endl;

        for (const auto& member : memberList)
            oss << idt(indent + 1) << member->toString() << std::endl;

        oss << idt(indent) << ")" << std::endl;

        return oss.str();
    }

    std::string Export::toString() const { return "export " + statement->toString(); }

    std::string Nil::toString() const { return "nil"; }

    std::string Member::toString() const {
        return identifier->toString() + " = " + expression->toString();
    }

    std::string GUID::toString() const { return "GUID:{" + value + "}"; }

    std::string Path::toString() const { return value; }

    std::string Pair::toString() const { return "(" + first->toString() + ", " + second->toString() + ")"; }

    std::string Boolean::toString() const { return value ? "true" : "false"; }

    std::string String::toString() const { return '"' + value + '"'; }

    std::string Integer::toString() const { return std::to_string(value); }

    std::string Float::toString() const { return std::to_string(value); }

    std::string Vector::toString() const {
        std::ostringstream oss;

        oss << "[" << std::endl;

        for (int i = 0; i < expressionList.size(); i++)
            oss << idt(indent + 1) << " " << expressionList[i]->toString() << (i == expressionList.size() - 1 ? "" : ", ");

        oss << idt(indent) << "]";

        return oss.str();
    }

    std::string Identifier::toString() const { return name; }

    std::string Operation::toString() const { return left->toString() + " " + operator_->toString() + " " + right->toString(); }

    std::string Operator::toString() const { return value; }

    std::string ObjectRef::toString() const { return "$/" + identifier->toString(); }

    std::string ObjectIns::toString() const {
        std::ostringstream oss;

        oss << idt(indent) << identifier->toString() << '(' << std::endl;

        for (const auto& member : memberList)
            oss << idt(indent + 1) << member->toString() << std::endl;

        oss << idt(indent) << ")" << std::endl;

        return oss.str();
    }

    std::string MapRef::toString() const {
        std::ostringstream oss;

        oss << "MAP [" << std::endl;

        for (int i = 0; i < pairList.size(); i++)
            oss << idt(indent + 1) << pairList[i]->toString() << (i == pairList.size() - 1 ? "" : ", \n");

        oss << idt(indent) << "]";

        return oss.str();
    }

    std::string TemplateRef::toString() const { return "template " + identifier->toString(); }

    std::string EnumRef::toString() const { return enumName->toString() + "/" + enumValue->toString(); }

    std::string TemplateParam::toString() const { return '<' + identifier->toString() + '>'; }

    Identifier::Identifier(std::string name)
        : name(std::move(name)) {}

    Operator::Operator(std::string value)
        : value(std::move(value)) {}

    Operation::Operation(std::shared_ptr<Expression> left, std::shared_ptr<Operator> operator_, std::shared_ptr<Expression> right)
        : left(std::move(left))
        , operator_(std::move(operator_))
        , right(std::move(right)) {}

    GUID::GUID(std::string value)
        : value(std::move(value)) {}

    Path::Path(std::string value)
        : value(std::move(value)) {}

}


// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file lexer.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/21 下午1:59
 * @brief 词法分析器
 * @copyright CC BY-NC-SA
 * */

/** @page Lexer 词法分析器
 *
 * @section VarLex语言词法规则
 * @code{.ebnf}
 *     symbol = "\", { letter }; (* 符号 *)
 *     letter = %x61-7A | %x41-5A; (* 字母a-zA-Z *)
 *     number = digit { digit }; (* 数字 *)
 *     digit = %x30-39; (* 数字0-9 *)
 *     comment = "%", { character }; (* 注释 *)
 *     character = digit | letter | whitespace | punctuation; (* 字符 *)
 *     punctuation = %x21-2F | %x3A-40 | %x5B-60 | %x7B-7E; (* 标点符号 *)
 *     whitespace = space | tab | newline; (* 空白字符 *)
 *     space = " "; (* 空格 *)
 *     tab = "\t"; (* 制表符 *)
 *     newline = "\n"; (* 换行符 *)
 *     ADD = "+"; (* 加号 *)
 *     SUB = "-"; (* 减号 *)
 *     MUL = "*"; (* 乘号 *)
 *     DIV = "/"; (* 除号 *)
 *     LPAREN = "("; (* 左括号 *)
 *     RPAREN = ")"; (* 右括号 *)
 *     LBRACKET = "["; (* 左中括号 *)
 *     RBRACKET = "]"; (* 右中括号 *)
 *     LBRACE = "{"; (* 左大括号 *)
 *     RBRACE = "}"; (* 右大括号 *)
 *     COMMA = ","; (* 逗号 *)
 *     SEMICOLON = ";"; (* 分号 *)
 *     COLON = ":"; (* 冒号 *)
 *     DOT = "."; (* 句号 *)
 *     EQ = "="; (* 等于号 *)
 *     NE = "<>"; (* 不等于号 *)
 *     LT = "<"; (* 小于号 *)
 *     LE = "<="; (* 小于等于号 *)
 *     GT = ">"; (* 大于号 *)
 *     GE = ">="; (* 大于等于号 *)
 *     INC = "++"; (* 自增 *)
 *     DEC = "--"; (* 自减 *)
 *     ADD_ASSIGN = "+="; (* 加等于号 *)
 *     SUB_ASSIGN = "-="; (* 减等于号 *)
 *     MUL_ASSIGN = "*="; (* 乘等于号 *)
 *     DIV_ASSIGN = "/="; (* 除等于号 *)
 * @endcode
 * */

#include "lexer.h"


std::string completePath(const std::string& _str) {
    std::filesystem::path path(_str);

    if (!path.is_absolute())  // 不是绝对路径,对于相对路径和文件名都可以转成绝对路径
        path = std::filesystem::absolute(path);

    if (!std::filesystem::exists(path))
        throw std::filesystem::filesystem_error("File not found: " + _str, std::make_error_code(std::errc::no_such_file_or_directory));

    return path.string();
}

std::string readFile(const std::string& _filePath) {
    const auto filePath = completePath(_filePath);

    if (filePath.ends_with(".vl")) {  // 必须为*.vl文件
        std::ifstream rscFile;
        rscFile.open(filePath, std::ios::in);

        if (rscFile.is_open()) {
            std::string content((std::istreambuf_iterator<char>(rscFile)), std::istreambuf_iterator<char>());
            rscFile.close();
            return content;
        }
        else {
            rscFile.close();
            throw std::runtime_error("Failed to open file: " + filePath);
        }
    }
    else
        throw std::invalid_argument("Invalid file extension. Only *.vl files are supported!");
}

Lexer::Lexer(std::string text) : text(std::move(text)), pos(0) {}

Token Lexer::operator*() {
    skipWhitespace();

    if (pos >= text.size()) return { TokenType::END, "" };
    else if (isdigit(text[pos]) || (text[pos] == '.' && isdigit(text[pos + 1]))) return extractNumber();
    else if (isalpha(text[pos]) || text[pos] == '_') return extractIdentifier();
    else if (text[pos] == '%') return extractComment();
    else if (text[pos] == '\\') return extractSymbol();
    else if (text[pos] == '\"' || text[pos] == '\'') return extractString();
    else if (!isalpha(text[pos]) && !isdigit(text[pos])) return extractOperator();
    return { TokenType::UNKNOWN, "<unknown>" };
}

Lexer& Lexer::operator++() { pos++; return *this; }

Lexer Lexer::operator++(int) { Lexer tmp(*this); pos++; return tmp; }

Lexer& Lexer::operator--() { pos--; return *this; }

Lexer Lexer::operator--(int) { Lexer tmp(*this); pos--; return tmp; }

bool Lexer::operator==(const char& c) const { return text[pos] == c; }

bool Lexer::operator!=(const char& c) const { return text[pos] != c; }

char Lexer::operator[](int idx) const { return text[idx]; }

void Lexer::skipWhitespace() {
    while (pos < text.size() && isspace(text[pos])) pos++;
}

Token Lexer::extractNumber() {
    std::string numStr;
    while (pos < text.size() && (isdigit(text[pos]) || text[pos] == '.')) numStr += text[pos++];
    return { TokenType::NUMBER, std::move(numStr) };
}

Token Lexer::extractComment() {
    std::string commentStr;
    pos++;  // 跳过'%'
    while (pos < text.size() && text[pos] != '\n') commentStr += text[pos++];
    return { TokenType::COMMENT, std::move(commentStr) };
}

Token Lexer::extractSymbol() {
    std::string symbolStr;
    pos++;  // 跳过'\'
    while (pos < text.size() && isalnum(text[pos])) symbolStr += text[pos++];
    return { TokenType::SYMBOL, std::string("\\") + std::move(symbolStr) };
}

Token Lexer::extractIdentifier() {
    std::string idStr;
    while (pos < text.size() && (isalpha(text[pos]) || isdigit(text[pos]) || text[pos] == '_')) idStr += text[pos++];
    pos--;  // 回退一个位置,因为上一个字符可能是符号
    return { TokenType::IDENTIFIER, std::move(idStr) };
}

Token Lexer::extractString() {
    std::string str;
    pos++;  // 跳过双引号或者单引号
    while (pos < text.size() && (text[pos] != '"' && text[pos] != '\'')) {
        if (text[pos] == '\\') {
            pos++;
            switch (text[pos]) {
                case 'n': str += '\n'; break;
                case 't': str += '\t'; break;
                case 'r': str += '\r'; break;
                case '0': str += '\0'; break;
                case '\\': str += '\\'; break;
                case '\'': str += '\''; break;
                case '\"': str += '\"'; break;
                default: throw std::invalid_argument(&"Invalid escape character: "[text[pos]]);
            }
        }
        else str += text[pos];
        pos++;
    }

    if (pos >= text.size()) throw std::invalid_argument("Unterminated string literal!");
    pos++;  // 跳过双引号或者单引号
    return { TokenType::STRING, std::move(str) };
}

Token Lexer::extractOperator() {
    std::string opStr;

    switch (text[pos]) {
        case '+':  // +
            switch (text[++pos]) {
                case '+': return { TokenType::INC, "++" };  // ++
                case '=': return { TokenType::ADD_ASSIGN, "+=" };  // +=
            }
            return { TokenType::ADD, "+" };
        case '-':  // -
            switch (text[++pos]) {
                case '-': return { TokenType::DEC, "--" };  // --
                case '=': return { TokenType::SUB_ASSIGN, "-=" };  // -=
                case '>': return { TokenType::RARROW, "->" };  // ->
            }
            return { TokenType::SUB, "-" };
        case '*':  // *
            switch (text[++pos]) {
                case '=': return { TokenType::MUL_ASSIGN, "*=" };  // *=
            }
            return { TokenType::MUL, "*" };
        case '/':  // /
            switch (text[++pos]) {
                case '=': return { TokenType::DIV_ASSIGN, "/=" };  // /=
            }
            return { TokenType::DIV, "/" };
        case '%': return { TokenType::MOD, "%" };  // %
        case '=': switch (text[++pos]) { case '=': return { TokenType::EQ, "==" }; }
            return { TokenType::ASSIGN, "=" };
        case '!': switch (text[++pos]) { case '=': return { TokenType::NE, "!=" }; }
            return { TokenType::NOT, "!" };
        case '<':  // <
            switch (text[++pos]) {
                case '=': return { TokenType::LE, "<=" };  // <=
                case '<': return { TokenType::LSHIFT, "<<" };  // <<
                case '-': return { TokenType::LARROW, "<-" };  // <-
            }
            return { TokenType::LT, "<" };
        case '>':  // >
            switch (text[++pos]) {
                case '=': return { TokenType::GE, ">=" };  // >=
                case '>': return { TokenType::RSHIFT, ">>" };  // >>
            }
            return { TokenType::GT, ">" };
        case '&': switch (text[++pos]) { case '&': return { TokenType::AND, "&&" }; }
            return { TokenType::BITAND, "&" };
        case '|': switch (text[++pos]) { case '|': return { TokenType::OR, "||" }; }
            return { TokenType::BITOR, "|" };
        case '^': return { TokenType::XOR, "^" };  // ^
        case '~': return { TokenType::BITNOT, "~" };  // ~
        case ',': return { TokenType::COMMA, "," };  // ,
        case ';': return { TokenType::SEMICOLON, ";" };  // ;
        case ':': return { TokenType::COLON, ":" };  // :
        case '{': return { TokenType::LBRACE, "{" };  // {
        case '}': return { TokenType::RBRACE, "}" };  // }
        case '(': return { TokenType::LPAREN, "(" };  // (
        case ')': return { TokenType::RPAREN, ")" };  // )
        case '[': return { TokenType::LBRACKET, "[" };  // [
        case ']': return { TokenType::RBRACKET, "]" };  // ]
        case '.':
            if (text[++pos] == '.' && text[++pos] == '.') return { TokenType::ELLIPSIS, "..." };  // ...
            pos--;
            return { TokenType::DOT, "." };  // .
        case '?': return { TokenType::QUESTION, "?" };  // ?
        case '@': return { TokenType::AT, "@" };  // @
        case '#': return { TokenType::HASH, "#" };  // #
        case '$': return { TokenType::DOLLAR, "$" };  // $
        default: return { TokenType::UNKNOWN, std::format("{}", text[pos]) };
    }
}

std::vector<std::unique_ptr<Token>> Lexer::tokenize(const std::string& text) {
    std::vector<std::unique_ptr<Token>> tokens;
    Lexer lexer(text);
    std::unique_ptr<Token> token;

    while ((token = std::make_unique<Token>(*lexer))->type != TokenType::END) {
        tokens.push_back(std::move(token));
        ++lexer;
    }
    return tokens;
}

bool Token::operator==(const Token& other) const {
    return type == other.type && value == other.value;
}

/**
 * @brief 输出Token信息
 * @details 输出类似于 `<NUMBER : '123'>` 的Token信息
 * @param os 输出流
 * @param token Token对象
 * @return 输出流
 * @see Token
 * @related Token
 * */
std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "<" << TokenName[static_cast<int>(token.type)] << " : '" << token.value << "'>";
    return os;
}


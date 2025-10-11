#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace std;

int fact(int n) {

    return (n == 0) || (n == 1) ? 1 : n * fact(n - 1);
}

enum class TokenType
{
    Number, Plus, Minus, Mul, Div, Pow, LParen, RParen, End,
    Sin, Cos, Tan, Cot, Mod, Round, Fact, Root

};
struct Token
{
    TokenType type{};
    double value{ 0.0 };

};
//////////////////////////////////lexer повертаэ рядок у послідовності токенів
class Lexer {
public:
    explicit Lexer(const string& s) :text(s), pos(0) {}

    Token next() {
        skipSpace();
        if (pos >= text.size())return{ TokenType::End, 0 };

        char c = text[pos];

        if (isdigit(c) || c == '.')
        {
            return readNumber();
        }
        switch (c)
        {
        case '+':
            ++pos;
            return { TokenType::Plus, 0 };
        case '!':
            ++pos;
            return { TokenType::Fact, 0 };
        case '-':
            ++pos;
            return { TokenType::Minus, 0 };
        case '/':
            ++pos;
            return { TokenType::Div, 0 };
        case '*':
            ++pos;
            return { TokenType::Mul, 0 };
        case '^':
            ++pos;
            return { TokenType::Pow, 0 };
        case '(':
            ++pos;
            return { TokenType::LParen,0 };
        case ')':
            ++pos;
            return { TokenType::RParen, 0 };
        case '|':
            ++pos;
            return { TokenType::Mod, 0 };
        case 'e':
            ++pos;
            return { TokenType::Number, M_E };
        case 'p':
            if (text[pos + 1] == 'i')
            {
                pos += 2;
                return { TokenType::Number, M_PI };
            }
            else
            {
                throw runtime_error(string("Unknown symbols after p: '") + text[pos + 1] + "', did you mean 'pi'?");
            }
        case 'r':
            if (text[pos + 1] == 'd')
            {
                pos += 2;
                return { TokenType::Round, 0 };
            }
            else if ((text[pos + 1] == 't'))
            {
                pos += 2;
                return { TokenType::Root, 0 };
            }
            else
            {
                throw runtime_error(string("Unknown symbols after r: '") + text[pos + 1] + "', did you mean 'rd' or 'rt'?");
            }

        case 'c':
            if (text[pos+1]=='o' && text[pos + 2] == 's')
            {
                pos += 3;
                return { TokenType::Cos, 0 };
            }
            else if (text[pos + 1] == 't' && text[pos + 2] == 'g')
            {
                pos += 3;
                return { TokenType::Cot, 0 };
            }
            else
            {
                throw runtime_error(string("Unknown symbols after c: '") + text[pos + 1] + text[pos + 2] + "', did you mean 'cos' or 'ctg'?");
            }
        case 't':
            if (text[pos + 1] == 'g')
            {
                pos += 2;
                return { TokenType::Tan, 0 };
            }
            else
            {
                throw runtime_error(string("Unknown symbols after t: '") + text[pos + 1] + "', did you mean 'tg'?");
            }
        case 's':
            if (text[pos + 1] == 'i' && text[pos + 2] == 'n')
            {
                pos += 3;
                return { TokenType::Sin, 0 };
            }
            else
            {
                throw runtime_error(string("Unknown symbols after s: '") + text[pos + 1] + text[pos + 2] + "', did you mean 'sin'?");
            }
        default:
            throw runtime_error(string("Unknown symbol: '") + c + "'");
        }

    }
    Token peek() {
        size_t saved = pos;
        Token t = next();
        pos = saved;
        return t;
    }
private:
    const string& text;
    size_t pos;

    void skipSpace() {
        while (pos < text.size() && isspace(static_cast<unsigned char>(text[pos]))) ++pos;
    }

    Token readNumber() {
        size_t start = pos;
        bool dot = false;
        while (pos < text.size())
        {
            char d = text[pos];
            if (isdigit(d)) { ++pos; }
            else if (d == '.' && !dot) { dot = true; ++pos; }
            else break;
        }
        //можливе навколо представлення 1.23e-4
        if (pos < text.size() && (text[pos] == 'e' || text[pos] == 'E'))
        {
            size_t epos = pos + 1;
            if (epos < text.size() && (text[epos] == '+' || text[epos] == '-')) ++epos;
            bool anyDigits = false;
            while (epos < text.size() && isdigit(static_cast<unsigned char>(text[epos])))
            {
                anyDigits = true;
                ++epos;
            }
            if (anyDigits) pos = epos;

        }
        double val = stod(text.substr(start, pos - start));
        return { TokenType::Number, val };
    }

    //   expr   := term (('+'|'-') term)*
    //   term   := power (('*'|'/') power)*
    //   power  := factor ('^' power)?        // права асоціативність
    //   factor := NUMBER | '(' expr ')' | ('+'|'-') factor |   cos || sin 
    //   
};
class Parser
{
public:
    explicit Parser(Lexer& lex) : lexer(lex), current(lexer.next()) {}
    double parseExpression() {
        return expr();
    }
private:
    Lexer& lexer;
    Token current;

    void eat(TokenType expected) {
        if (current.type != expected)
        {
            throw runtime_error("Syntax error: unexpected Token");
        }
        current = lexer.next();

    }
    double expr() {
        double value = term();
        while (current.type == TokenType::Plus || current.type == TokenType::Minus)
        {
            TokenType op = current.type;
            eat(op);
            double rhs = term();
            if (op == TokenType::Plus) value += rhs;
            else value -= rhs;
        }
        return value;
    }
    double term() {
        double value = power();
        while (current.type == TokenType::Mul || current.type == TokenType::Div)
        {
            TokenType op = current.type;
            eat(op);
            double rhs = power();
            if (op == TokenType::Mul) value *= rhs;
            else {
                if (rhs == 0.0)
                {
                    throw runtime_error("Invalid operation: divison by 0");

                }
                value /= rhs;
            }
        }
        return value;
    }
    double power() {
        double base = factor();
        if (current.type == TokenType::Pow)
        {
            eat(TokenType::Pow);
            double exponent = power();// a ^ b ^ c = a ^ (b ^ c) 
            return pow(base, exponent);
        }
        return base;
    }
    double factor() {

        switch (current.type) {
        case TokenType::Number: {
            double v = current.value;
            eat(TokenType::Number);
            if (current.type == TokenType::Fact)
            {
                if (fmod(v, 1.0) != 0.0)
                {
                    throw runtime_error("recieved a non-int number for factorial!");
                }
                eat(TokenType::Fact);
                return fact(v);
            }
            return v;
        }
        case TokenType::LParen: {
            eat(TokenType::LParen);
            double v = expr();
            if (current.type != TokenType::RParen)
                throw runtime_error("expected a right bracket \')\'");
            eat(TokenType::RParen);
            return v;
        }

        case TokenType::Plus: { // унітарний +
            eat(TokenType::Plus);
            return factor();
        }
        case TokenType::Minus: { // унітарний -
            eat(TokenType::Minus);
            return -factor();
        }


        case TokenType::Cos: {
            eat(TokenType::Cos);
            if (current.type != TokenType::LParen)
                throw runtime_error("expected a left bracket \'(\', after Cos");
            eat(TokenType::LParen);
            double v = expr();
            if (current.type != TokenType::RParen)
                throw runtime_error("expected a right bracket \')\'");
            eat(TokenType::RParen);
            return cos(v * M_PI / 180.0);

        }
        case TokenType::Sin: {
            eat(TokenType::Sin);
            if (current.type != TokenType::LParen)
                throw runtime_error("expected a left bracket \'(\', after Sin");
            eat(TokenType::LParen);
            double v = expr();
            if (current.type != TokenType::RParen)
                throw runtime_error("expected a right bracket \')\'");
            eat(TokenType::RParen);
            return sin(v * M_PI / 180.0);
        }
        case TokenType::Tan: {
            eat(TokenType::Tan);
            if (current.type != TokenType::LParen)
                throw runtime_error("expected a left bracket \'(\', after Tg");
            eat(TokenType::LParen);
            double v = expr();
            if (current.type != TokenType::RParen)
                throw runtime_error("expected a right bracket \')\'");
            eat(TokenType::RParen);
            return tan(v * M_PI / 180.0);
        }
        case TokenType::Cot: {
            eat(TokenType::Cot);
            if (current.type != TokenType::LParen)
                throw runtime_error("expected a left bracket \'(\', after Ctg");
            eat(TokenType::LParen);
            double v = expr();
            if (current.type != TokenType::RParen)
                throw runtime_error("expected a right bracket \')\'");
            eat(TokenType::RParen);
            double res = tan(v * M_PI / 180.0);
            if (res == 0.0)
                throw runtime_error("cot undefined for value");
            return 1.0/res;
        }
        case TokenType::Round: {
            eat(TokenType::Round);
            if (current.type != TokenType::LParen)
                throw runtime_error("expected a left bracket \'(\', after Rd");
            eat(TokenType::LParen);
            double v = expr();
            if (current.type != TokenType::RParen)
                throw runtime_error("expected a right bracket \')\'");
            eat(TokenType::RParen);
            return round(v);
        }
        case TokenType::Mod: {
            eat(TokenType::Mod);
            double v = expr();
            if (current.type != TokenType::Mod)
                throw runtime_error("expected a module close \'|\'");
            eat(TokenType::Mod);
            if (v >= 0)
            {
                return v;
            }
            else
            {
                return -v;
            }

        }
        case TokenType::Root: {
            eat(TokenType::Root);
            double pw = expr();
            if (current.type != TokenType::LParen)
                throw runtime_error("expected a left bracket \'(\', after Rt");
            eat(TokenType::LParen);
            double v = expr();
            if (current.type != TokenType::RParen)
                throw runtime_error("expected a right bracket \')\'");
            eat(TokenType::RParen);
            return pow(v, 1.0/pw);

        }
        default:
            throw runtime_error("expected: + - * / ^, barces, module, unitary +/-, cos, sin, tg , ctg, rounding->'rd()' and preset numbers : pi, e");
        }

    }
};


/// public interface calkilitor

class Calculator {
public:
    double evaluate(const string& expression) {
        Lexer lex(expression);
        Parser parser(lex);
        double result = parser.parseExpression();
        // Переконаємось, що вхід повністю розібрано
        Token rest = lex.peek();
        if (rest.type != TokenType::End) {
            throw runtime_error("redundant symbols in phrase");
        }
        return result;
    }
};



int main()
{
    cout.setf(ios::fixed);
    cout.precision(10);
    Calculator calc;
    cout << "OOP aclculator (supports + - * / ^, barces, module, unitary +/-, cos, sin, tg , ctg, !, rounding->'rd()', any root -> ex.'rt2(64)' and preset numbers : pi, e), use lowercase\n";
    cout << "Input expression 'exit' to exit.\n\n";
    string line;
    while (true) {
        cout << ">>> ";
        if (!getline(cin, line)) break;
        if (line == "exit" || line == "quit") break;
        if (line.empty()) continue;
        try {
            double ans = calc.evaluate(line);
            cout << "= " << ans << "\n";
        }
        catch (const exception& ex) {
            cout << "error: " << ex.what() << "\n";
        }
    }

    return 0;
}
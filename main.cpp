/********************************************
 * Main function that takes a postfix expression, applies the arithmetic, 
 * and determines whether or not an expression is valid. If not,
 * program outputs expression error
 *
 * Author: Wesley Johnson
 * Version: 03/28/2022
 *********************************************/

#include<iostream>
#include<vector>
#include<algorithm>
#include<cctype>
#include<string>
#include<sstream>
#include<stack>
#include<cmath>

using namespace std;

// 
bool operatorCheck(char token){
    if(token == '+' || token == '-' || token == '*' || token == '/'){
        return true;
    }
    return false;
};

bool operandCheck(char token){
    // Checks if element is an operand. isalnum incompatible with string.
    if(isalnum(token) != false){
        return true;
    }
    return false;
};

// Checks expression for open/close symbol balance.
// One open parenthesis for every close parenthesis, etc.
bool balanceCheck(string postFix){
    int openSymbol = 0;
    int closeSymbol = 0;
    
    for(int i = 0; i < postFix.size(); i++){
        if(postFix[i] == '(' || postFix[i] == '['){
            openSymbol++;
        };
        if(postFix[i] == ')' || postFix[i] == ']'){
            closeSymbol++;
        };
    };
    
    if(openSymbol == closeSymbol){
        return true;
    }
    else{
        return false;
    };
};

// Performs arithmetic when operator detected.
int operation(char a, char b, char op){

    // Convert string tokens to integers.
    int opA = a - '0';
    int opB = b - '0';

    switch(op){
        case '+': 
            return opA + opB;
            break;
        case '-':
            return opA - opB;
            break;
        case '*':
            return opA * opB;
            break;
        case '/':
            return round(opA / opB);
            break;
        case '%':
            return opA % opB;
            break;
        case '^':
            return pow(opA, opB);
            break;
        default:
            std::cout << "Unknown Operator. " << endl;
            return -1;
            break;
    };
};

// Removes all unused characters.
vector<char> remove(vector<char> tokens){

    tokens.erase(std::remove(tokens.begin(), tokens.end(),' '), tokens.end());
    tokens.erase(std::remove(tokens.begin(), tokens.end(),'('), tokens.end());
    tokens.erase(std::remove(tokens.begin(), tokens.end(),')'), tokens.end());
    tokens.erase(std::remove(tokens.begin(), tokens.end(),'['), tokens.end());
    tokens.erase(std::remove(tokens.begin(), tokens.end(),']'), tokens.end());
    tokens.erase(std::remove(tokens.begin(), tokens.end(),'{'), tokens.end());
    tokens.erase(std::remove(tokens.begin(), tokens.end(),'}'), tokens.end());

    return tokens;
};

int main(){

    string postFix;
    vector<char> stack;
    int result = 0;
    int operators = 0;
    int operands = 0;

    // Ask for expression. Repeats if not balanced.
    do{
        std::cout << "Enter postfix expression: " << endl;
        std::getline(cin, postFix);
    }while(!balanceCheck(postFix));
    
    vector<char> tokens(postFix.begin(), postFix.end());

    tokens = remove(tokens);

    while(!tokens.empty()){
        
        // Iterate through tokens vector.
        for(auto const &charHolder: tokens){
            // If operand, add to stack.

            if(operandCheck(charHolder)){
                stack.push_back(charHolder);
                tokens.pop_back();
                operands++;

                // Returns error message if operator missing.
                // if(stack.size() != 1 && tokens.empty()){
                //     std::cout << "Expression with an error - missing operator(s)." << endl;
                //     break;
                // };
            };
            
            // If operator, pop top two elements from stack and perform operation.
            if(operatorCheck(charHolder)){

                tokens.pop_back();

                char a = stack.back();
                stack.pop_back();

                // if(stack.size() != 1 && tokens.empty()){
                //     std::cout << "Expression with an error - missing operand."<< endl;
                //     break;
                // };

                char b = stack.back();
                stack.pop_back();
                operators++;

                result += operation(a, b, charHolder);
                stack.push_back(static_cast<char>(result));
            };

            // If expression is valid, output result
            // if(stack.size() == 1 && tokens.empty()){
            //     std::cout << "Valid expression. Result: " << result << endl;
            // };
            
        };

        if(operators == operands){
            cout << "Expression with an error - missing operand(s)." << endl;
        }else if(operators < operands - 1){
            cout << operands << " " << operators << endl;
            cout << "Expression with an error - missing operator(s)." << endl;
        }else{
            cout << "Valid expression\n";
            cout << "Result = " << result << endl;
        };

    };

};
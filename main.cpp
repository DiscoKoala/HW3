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
#include<cctype>
#include<string>
#include<sstream>
#include<stack>
#include<cmath>

using namespace std;

// 
bool operatorCheck(string& token){
    if(token == "+" || token == "-" || token == "*" || token == "/"){
        return true;
    }
    return false;
};

bool operandCheck(string token){
    // Checks if element is an operand. isalnum incompatible with string.
    if(isalnum(token[0]) != false){
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
int operation(string a, string b, const char* op){

    // Convert string tokens to integers.
    int opA = stoi(a);
    int opB = stoi(b);
    const char* operate = op;

    switch(operate){
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

int main(){

    string postFix;
    vector<string> tokens, stack;
    int count = 0;

    // Ask for expression. Repeats if not balanced.
    do{
        std::cout << "Enter postfix expression: " << endl;
        std::getline(cin, postFix);
    }while(!balanceCheck(postFix));
    
    // Create string stream
    stringstream expression(postFix);

    string temp;

    // Parsing expression.
    while(getline(expression, temp, ' ')){
        tokens.push_back(temp);
    };

    while(!tokens.empty()){
        
        // Iterate through tokens vector.
        for(auto &expression: tokens){
            // If operand, add to stack.
            if(operandCheck(expression)){
                stack.push_back(expression);
                tokens.pop_back();

                // Returns error message if operator missing.
                if(stack.size() != 1 && tokens.empty()){
                    std::cout << "Expression with an error - missing operator(s)." << endl;
                    break;
                };
            };
            
            // If operator, pop top two elements from stack and perform operation.
            if(operatorCheck(expression)){


                const char* expPtr = expression.c_str();

                // char exp = *expPtr;

                tokens.pop_back();

                string a = stack.back();
                stack.pop_back();

                string b = stack.back();
                stack.pop_back();

                if(stack.size() != 1 && tokens.empty()){
                    std::cout << "Expression with an error - missing operand."<< endl;
                    break;
                };

                int result = operation(a,b,expPtr);
                stack.push_back(to_string(result));
            };

            // If expression is valid, output result
            if(stack.size() == 1 && tokens.empty()){
                std::cout << "Valid expression. Result: " << stack.back() << endl;
            };
            
        };

    };

};
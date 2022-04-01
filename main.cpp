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
bool operatorCheck(string token){
    if(token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^"){
        return true;
    }
    return false;
};

bool operandCheck(string token){
    // Checks if element is an operand. isalnum incompatible with string.
    if(isalnum(token[0]) != false){
        return true;
    };
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
int operation(string a, string b, char op){

    // Convert string tokens to integers.
    int opA = stoi(a);
    int opB = stoi(b);

    switch(op){
        case '+': 
            return (opA + opB);
        case '-':
            return (opB - opA);
        case '*':
            return (opA * opB);
        case '/':
            return round(opA / opB);
        case '%':
            return (opA % opB);
        case '^':
            return pow(opA, opB);
        default:
            std::cout << "Unknown Operator. " << endl;
            return -1;
    };
};

int main(){

    string postFix;
    vector<string> stack, tokens;
    int result = 0;
    int operators = 0;
    int operands = 0;

    // Ask for expression. Repeats if not balanced.
    do{
        std::cout << "Enter postfix expression: " << endl;
        std::getline(cin, postFix);
    }while(!balanceCheck(postFix));

    stringstream expHolder(postFix);

    string temp;

    while(getline(expHolder, temp, ' ')){
        tokens.push_back(temp);
    };

    while(!tokens.empty()){
        
        // Iterate through tokens vector.
        for(string &charHolder: tokens){
            // If operand, add to stack.
            if(operandCheck(charHolder)){
                stack.push_back(charHolder);
                tokens.pop_back();
                operands++;
            };
            
            // If operator, pop top two elements from stack and perform operation.
            // Delete operator from token vector.
            if(operatorCheck(charHolder)){
                
                tokens.pop_back();

                string a = stack.back();
                stack.pop_back();

                string b = stack.back();
                stack.pop_back();
                operators++;

                const char * op = charHolder.c_str();
                char charHolder = *op;

                result = operation(a, b, charHolder);
                stack.push_back(to_string(result));
            };  
        };
    };
        if(operators == operands){
            cout << "Expression with an error - missing operand(s)." << endl;
        }else if(operators < operands - 1){
            cout << "Expression with an error - missing operator(s)." << endl;
        }else{
            cout << "Valid expression\n";
            cout << "Result = " << result << endl;
        };

};
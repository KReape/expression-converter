// Code written by Kateri Reape on 4/14/20

#include <iostream>
#include <string>
#include <stack>
using namespace std;

void convert();
string prefixToInfix(string s);
string postfixToInfix(string s);
string prefixToPostfix(string s);
string postfixToPrefix(string s);
string infixToPrefix(string s);
string infixToPostfix(string s);

int main() {
  convert();
  return 0;
}

void convert() {
  bool isRunning = true; // true if the program should still be running
  string nota; // holds the expression waiting to be converted
  string optionPicked; // the notation the user wants to convert to
  char yesNo;

  do {
    nota.clear();
    cout << "Please input an expression in prefix, postfix, or infix notation." << endl;
    cin >> nota;
    if (nota[0] == '(' && nota[nota.size() - 1] == ')') { // true the expression starts and ends with parentheses
      cout << "Would you like to convert it into prefix or postfix notation (pre/post)?" << endl;
      cin >> optionPicked;
      if (optionPicked == "pre") {
        cout << infixToPrefix(nota) << endl; // converts to prefix
      } else if (optionPicked == "post") {
        cout << infixToPostfix(nota) << endl; // converts to postfix
      } else {
        cout << "Invalid entry. Program restarting." << endl;
        continue;
      }
    } else if (nota[0] == '+' || nota[0] == '-' || nota[0] == '*' || nota[0] == '/') {
      cout << "Would you like to convert it into postfix or infix notation (post/in)?" << endl;
      cin >> optionPicked;
      if (optionPicked == "post") {
        cout << prefixToPostfix(nota) << endl; // converts to postfix
      } else if (optionPicked == "in") {
        cout << prefixToInfix(nota) << endl; // converts to infix
      } else {
        cout << "Invalid entry. Program restarting." << endl;
        continue;
      }
    } else if (nota[nota.size() - 1] == '+' || nota[nota.size() - 1] == '-' || nota[nota.size() - 1] == '*' || nota[nota.size() - 1] == '/') {
      cout << "Would you like to convert it into prefix or infix notation (pre/in)?" << endl;
      cin >> optionPicked;
      if (optionPicked == "pre") {
        cout << postfixToPrefix(nota) << endl; // converts to prefix
      } else if (optionPicked == "in") {
        cout << postfixToInfix(nota) << endl; // converts to infix
      } else {
        cout << "Invalid entry. Program restarting." << endl;
        continue;
      }
    } else {
      cout << "Invalid entry. Program restarting." << endl;
      continue;
    }
    cout << "Do you want to convert another expression (y/n)?" << endl;
    cin >> yesNo;
    if (yesNo == 'n') {
      isRunning = false;
    } else if (yesNo == 'y' || yesNo == 'Y') { // reruns the loop
      continue;
    } else {
      break;
    }
  } while (isRunning == true);
}


string prefixToInfix(string s) {
  stack<char> express; // holds the string, character by character
  for (size_t i = 0; i < s.size(); i++) {
    express.push(s[i]);
  }

  stack<string> num; // holds the digits/expressions as they're waiting to be evaluated
  string dummy = ""; // holds a temporary string before its placement in stack
  while(express.size() > 0) {
    if (express.top() == ')') { // puts digits in the stack
      express.pop();
      while(isalnum(express.top())) { // accounts for more than one digit
        dummy.insert(dummy.begin(), express.top());
        express.pop();
      }
      express.pop();
      num.push(dummy);
      dummy.clear();
    } else { // puts operators in between the digits/expressions that are in the stack
      dummy = dummy + '(' + num.top(); // first operand
      num.pop();
      dummy += express.top(); // operator
      express.pop();
      dummy = dummy + num.top() + ')'; // second operand
      num.pop();
      num.push(dummy);
      dummy.clear();
    }
  }

  s.clear();
  s = num.top(); // final expression
  return s;
}


string postfixToInfix(string s) {
  stack<char> express; // holds the string, character by character
  for (size_t i = s.size() - 1; i > 0; i--) {
    express.push(s[i]);
  }
  express.push(s[0]);

  stack<string> num; // holds the digits/expressions as they're waiting to be evaluated
  string dummy = ""; // holds a temporary string before placement in stack
  while(express.size() > 0) {
    if (express.top() == '(') { // puts digits in the stack
      express.pop();
      while(isalnum(express.top())) { // accounts for more than one digit
        dummy += express.top();
        express.pop();
      }
      express.pop();
      num.push(dummy);
      dummy.clear();
    } else { // puts operators in between the digits/expressions that are in the stack
      dummy = num.top() + ')' + dummy; // first operand
      num.pop();
      dummy = express.top() + dummy; // operator
      express.pop();
      dummy = '(' + num.top() + dummy; // second operand
      num.pop();
      num.push(dummy);
      dummy.clear();
    }
  }

  s.clear();
  s = num.top(); // final expression
  return s;
}


string prefixToPostfix(string s) {
  string str = prefixToInfix(s); // converts to infix
  return infixToPostfix(str); // converts to postfix
}


string postfixToPrefix(string s) {
  string str = postfixToInfix(s); // converts to infix
  return infixToPrefix(str); // converts to postfix
}


string infixToPrefix(string s) {
  stack<char> express; // holds the string, character by character
  for (size_t i = 0; i < s.size(); i++) {
    express.push(s[i]);
  }
  s.clear();
  while (!express.empty()) { // reverses the string
    s += express.top();
    express.pop();
  }

  string final = "";
  stack<char> op; // operator stack
  stack<char> paren; // parentheses stack
  for (size_t i = 0; i < s.size(); i++) { // iterates through the string
    if (s[i] == ')') { // puts right parentheses on the stack
      paren.push(s[i]);
    } else if (isalnum(s[i])) { // puts digits in the string
      final += ')';
      while (isalnum(s[i])) { // accounts for more than one digit
        final += s[i];
        i++;
      }
      final += '(';
      i--;
    } else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') { // puts operators on the stack
      op.push(s[i]);
    } else { // puts operators in the string
      final += op.top();
      op.pop();
      paren.pop();
    }
  }

  for (size_t i = 0; i < final.size(); i++) {
    express.push(final[i]);
  }
  final.clear();
  while (!express.empty()) { // reverse the string again
    final += express.top();
    express.pop();
  }

  return final; // final expression
}


string infixToPostfix(string s) {
  string final = "";
  stack<char> op; // operator stack
  stack<char> paren; // parentheses stack
  for (size_t i = 0; i < s.size(); i++) { // iterates through the string
    if (s[i] == '(') { // puts left parentheses on the stack
      paren.push(s[i]);
    } else if (isalnum(s[i])) { // puts digits in the string
      final += '(';
      while (isalnum(s[i])) { // accounts for more than one digit
        final += s[i];
        i++;
      }
      final += ')';
      i--;
    } else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') { // puts operators on the stack
      op.push(s[i]);
    } else { // puts operators in the string
      final += op.top();
      op.pop();
      paren.pop();
    }
  }

  return final; // final expression
}

/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2017.
*/

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include "scan.hpp"

using namespace std;
const vector<string> names = {"read", "write",
    "id", "literal", 
    "gets",
    "add", "sub", "mul", "div",
    "lparen", "rparen",
    "if", "fi",
    "do", "od", "check",
    "eof", "eq", "neq", "gt", "lt", "gte", "lte"
};

void error () {
    cout<< "syntax error\n";
    exit (1);
}

//return the FIRST(sym)
token* first_set(symbol sym) {
  switch(sym) {
    token* res;
    case nt_program:
      res = new token[8];
      res[0] = t_eof;
      res[1] = t_id;
      res[2] = t_read;
      res[3] = t_write;
      res[4] = t_if;
      res[5] = t_do;
      res[6] = t_check;
      res[7] = t_eps;
      return res;
    case nt_stmt_list:
    case nt_stmt:
      res = new token[7];
      res[0] = t_id;
      res[1] = t_read;
      res[2] = t_write;
      res[3] = t_if;
      res[4] = t_do;
      res[5] = t_check;
      res[6] = t_eps;
      return res;
    case nt_relation:
    case nt_expr:
    case nt_term:
    case nt_factor:
      res = new token[4];
      res[0] = t_lparen;
      res[1] = t_id;
      res[2] = t_literal;
      res[3] = t_eps;
      return res;
    case nt_expr_list:
    case nt_ro_op:
      res = new token[7];
      res[0] = t_eq;
      res[1] = t_neq;
      res[2] = t_lt;
      res[3] = t_gt;
      res[4] = t_lte;
      res[5] = t_gte;
      res[6] = t_eps;
      return res;
    case nt_term_list:
    case nt_add_op:
      res = new token[3];
      res[0] = t_add;
      res[1] = t_sub;
      res[2] = t_eps;
      return res;
    case nt_factor_list:
    case nt_mul_op:
      res = new token[3];
      res[0] = t_mul;
      res[1] = t_div;
      res[2] = t_eps;
      return res;
    default:
      cout << "fatal error\n";
      exit(1);
  }
}

//return true if sym can be empty string
bool epilson_set(symbol sym) {
  switch(sym) {
    case nt_program:
    case nt_stmt:
    case nt_relation:
    case nt_expr:
    case nt_term:
    case nt_factor:
    case nt_ro_op:
    case nt_add_op:
    case nt_mul_op:
      return false;
    case nt_stmt_list:
    case nt_expr_list:
    case nt_term_list:
    case nt_factor_list:
      return true;
    default:
      cout << "fatal error\n";
      exit(1);
  }
}

//return FOLLOW(sym)
token* follow_set(symbol sym) {
  token* res;
  switch(sym) {
    case nt_program:
      res = new token[0];
      return res;
    case nt_stmt_list:
      res = new token[4];
      res[0] = t_eof;
      res[1] = t_od;
      res[2] = t_fi;
      res[3] = t_eps;
      return res;
    case nt_stmt:
      res = new token[10];
      res[0] = t_eof;
      res[1] = t_id;
      res[2] = t_read;
      res[3] = t_write;
      res[4] = t_if;
      res[5] = t_do;
      res[6] = t_check;
      res[7] = t_od;
      res[8] = t_fi;
      res[9] = t_eps;
      return res;
    case nt_relation:
    case nt_expr_list:
      res = new token[11];
      res[0] = t_eof;
      res[1] = t_id;
      res[2] = t_read;
      res[3] = t_write;
      res[4] = t_if;
      res[5] = t_do;
      res[6] = t_check;
      res[7] = t_od;
      res[8] = t_fi;
      res[9] = t_rparen;
      res[10] = t_eps;
      return res;
    case nt_expr:
    case nt_term_list:
      res = new token[17];
      res[0] = t_eq;
      res[1] = t_neq;
      res[2] = t_lt;
      res[3] = t_gt;
      res[4] = t_lte;
      res[5] = t_gte;
      res[6] = t_eof;
      res[7] = t_id;
      res[8] = t_read;
      res[9] = t_write;
      res[10] = t_if;
      res[11] = t_do;
      res[12] = t_check;
      res[13] = t_od;
      res[14] = t_fi;
      res[15] = t_rparen;
      res[16] = t_eps;
      return res;
    case nt_term:
    case nt_factor_list:
      res = new token[19];
      res[0] = t_add;
      res[1] = t_sub;
      res[2] = t_eq;
      res[3] = t_neq;
      res[4] = t_lt;
      res[5] = t_gt;
      res[6] = t_lte;
      res[7] = t_gte;
      res[8] = t_eof;
      res[9] = t_id;
      res[10] = t_read;
      res[11] = t_write;
      res[12] = t_if;
      res[13] = t_do;
      res[14] = t_check;
      res[15] = t_od;
      res[16] = t_fi;
      res[17] = t_rparen;
      res[18] = t_eps;
      return res;
    case nt_factor:
      res = new token[21];
      res[0] = t_mul;
      res[1] = t_div;
      res[2] = t_add;
      res[3] = t_sub;
      res[4] = t_eq;
      res[5] = t_neq;
      res[6] = t_lt;
      res[7] = t_gt;
      res[8] = t_lte;
      res[9] = t_gte;
      res[10] = t_eof;
      res[11] = t_id;
      res[12] = t_read;
      res[13] = t_write;
      res[14] = t_if;
      res[15] = t_do;
      res[16] = t_check;
      res[17] = t_od;
      res[18] = t_fi;
      res[19] = t_rparen;
      res[20] = t_eps;
      return res;
    case nt_ro_op:
    case nt_add_op:
    case nt_mul_op:
      res = new token[4];
      res[0] = t_lparen;
      res[1] = t_id;
      res[2] = t_literal;
      res[3] = t_eps;
      return res;
    default:
      cout << "fatal error\n";
      exit(1);
  }
}

//check whether the current input_token is FIRST set and FOLLOW set
bool find_token(token* res) {
  int i = 0;
  while (res[i] != t_eps) {
    if(res[i] == input_token) {
      free(res);
      return true;
    }
    i++;
  }
  free(res);
  return false;
}
  



void match (token expected) {
    if (input_token == expected) {
        cout << "matched " << names[input_token];
        if (input_token == t_id || input_token == t_literal)
            cout << ": " << token_image;
        cout << "\n";
        input_token = scan ();
    }
    else error ();
}

void program ();
void stmt_list ();
void stmt ();
void expr ();
void term_tail ();
void term ();
void factor_tail ();
void factor ();
void add_op ();
void mul_op ();

void program () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict program --> stmt_list eof\n";
            stmt_list ();
            match (t_eof);
            break;
        default: error ();
    }
}

void stmt_list () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
            cout << "predict stmt_list --> stmt stmt_list\n";
            stmt ();
            stmt_list ();
            break;
        case t_eof:
            cout << "predict stmt_list --> epsilon\n";
            break;          /*  epsilon production */
        default: error ();
    }
}

void stmt () {
    switch (input_token) {
        case t_id:
            cout << "predict stmt --> id gets expr\n";
            match (t_id);
            match (t_gets);
            expr ();
            break;
        case t_read:
            cout << "predict stmt --> read id\n";
            match (t_read);
            match (t_id);
            break;
        case t_write:
            cout << "predict stmt --> write expr\n";
            match (t_write);
            expr ();
            break;
        default: error ();
    }
}

void expr () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            cout << "predict expr --> term term_tail\n";
            term ();
            term_tail ();
            break;
        default: error ();
    }
}

void term_tail () {
    switch (input_token) {
        case t_add:
        case t_sub:
            cout << "predict term_tail --> add_op term term_tail\n";
            add_op ();
            term ();
            term_tail ();
            break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict term_tail --> epsilon\n";
            break;          /*  epsilon production */
        default: error ();
    }
}

void term () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            cout << "predict term --> factor factor_tail\n";
            factor ();
            factor_tail ();
            break;
        default: error ();
    }
}

void factor_tail () {
    switch (input_token) {
        case t_mul:
        case t_div:
            cout << "predict factor_tail --> mul_op factor factor_tail\n";
            mul_op ();
            factor ();
            factor_tail ();
            break;
        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict factor_tail --> epsilon\n";
            break;          /*  epsilon production */
        default: error ();
    }
}

void factor () {
    switch (input_token) {
        case t_id :
            cout << "predict factor --> id\n";
            match (t_id);
            break;
        case t_literal:
            cout << "predict factor --> literal\n";
            match (t_literal);
            break;
        case t_lparen:
            cout << "predict factor --> lparen expr rparen\n";
            match (t_lparen);
            expr ();
            match (t_rparen);
            break;
        default: error ();
    }
}

void add_op () {
    switch (input_token) {
        case t_add:
            cout << "predict add_op --> add\n";
            match (t_add);
            break;
        case t_sub:
            cout << "predict add_op --> sub\n";
            match (t_sub);
            break;
        default: error ();
    }
}

void mul_op () {
    switch (input_token) {
        case t_mul:
            cout << "predict mul_op --> mul\n";
            match (t_mul);
            break;
        case t_div:
            cout << "predict mul_op --> div\n";
            match (t_div);
            break;
        default: error ();
    }
}

int main () {
    input_token = scan ();
    program ();
    return 0;
}

/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2017.
*/

#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "cctype"
#include <vector>
#include <iostream>
#include <string>
#include "scan.hpp"

using namespace std;

string token_image;
token_image.reserve(100);

token scan() {
    static int c = ' ';
    static char c_helper = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */

    /* skip white space */
    while (isspace(c)) {
        cin.get(c_helper); 
        c = (int) c_helper;    
    }
    //  Deal with eof
    if (c == EOF)
        return t_eof;


    if (isalpha(c)) {
        do {
            token_image[i++] = c;
            cin.get(c_helper); 
            c = (int) c_helper;
        } while (isalpha(c) || isdigit(c) || c == '_');
        token_image[i] = '\0';

        if (token_image == "read") {
            return t_read;
        } else if (token_image == "write") {
            return t_write;
        } else if (token_image == "do") {
            return t_do;
        } else if (token_image == "od") {
            return t_od;
        } else if (token_image == "if") {
            return t_if;
        } else if (token_image == "fi") {
            return t_fi;
        } else if (token_image == "check") {
            return t_check;
        }
        else return t_id;
    }
    else if (isdigit(c)) {
        do {
            token_image[i++] = c;
            cin.get(c_helper); 
            c = (int) c_helper;
        } while (isdigit(c));
        token_image[i] = '\0';
        return t_literal;
    } else switch (c) {
        case '$':
            cin.get(c_helper); 
            c = (int) c_helper;
            if (c != '$') {
                cerr << "error\n";
                exit(1);
            } else {
                cin.get(c_helper); 
                c = (int) c_helper;
                return t_eof;
            }
        case ':':
            cin.get(c_helper); 
            c = (int) c_helper;
            if (c != '=') {
                cerr << "error\n";
                exit(1);
            } else {
                cin.get(c_helper); 
                c = (int) c_helper;                
                return t_gets;
            }
            break;
        case '+': 
            cin.get(c_helper); 
            c = (int) c_helper; 
            return t_add;
        case '-': 
            cin.get(c_helper); 
            c = (int) c_helper;
            return t_sub;
        case '*': 
            cin.get(c_helper); 
            c = (int) c_helper;
            return t_mul;
        case '/': 
            cin.get(c_helper); 
            c = (int) c_helper;
            return t_div;
        case '(': 
            cin.get(c_helper); 
            c = (int) c_helper;
            return t_lparen;
        case ')':             
            cin.get(c_helper); 
            c = (int) c_helper; 
            return t_rparen;
        case '=':
            cin.get(c_helper); 
            c = (int) c_helper;
            if (c != '=') {
                cerr << "error\n";
                exit(1);
            } else {
                cin.get(c_helper); 
                c = (int) c_helper;
                return t_eq;
            }
        case '>' :
            cin.get(c_helper); 
            c = (int) c_helper;
            if (c != '=')
                return t_gt;
            else {
                cin.get(c_helper); 
                c = (int) c_helper;
                return t_gte;
            }
        case '<' :
            cin.get(c_helper); 
            c = (int) c_helper;
            if (c == '>') {
                cin.get(c_helper); 
                c = (int) c_helper;
                return t_neq;
            } else if (c == '=') {
                cin.get(c_helper); 
                c = (int) c_helper;
                return t_lte;
            } else {
                return t_lt;
            }
        default:
            cout << "error\n";
            exit(1);
    }
}

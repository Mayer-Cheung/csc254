/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2017.
*/
#ifndef SCAN_HPP
#define SCAN_HPP
#include <string>
typedef enum {
	t_read, t_write, 
	t_id, t_literal, 
	t_gets,
    t_add, t_sub, t_mul, t_div, 
    t_lparen, t_rparen, 
    t_eof,
    t_eq, t_neq, t_lte, t_gt, t_lt, t_gte,
    t_if, t_fi, t_do, t_od, t_check,
    t_eoa
} token;

typedef enum {
    nt_program, 
    nt_stmt_list, nt_stmt, 
    nt_relation, 
    nt_expr_list, nt_expr, 
    nt_term_list, nt_term, 
    nt_factor_list, nt_factor,
    nt_ro_op, nt_add_op, nt_mul_op
} symbol;

extern std::string token_image;
token_image.reserve(100);

extern token scan();
#endif
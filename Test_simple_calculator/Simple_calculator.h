#pragma once

#include <string>
#include <fstream>      // std::ofstream
#include "List.h"


using namespace std;

class Simple_calculator
{
public:
	Simple_calculator();
	~Simple_calculator();

	bool check_balance_symbols();
	void print_infix_expr();
	void print_postfix_expr();
	void print_result();
	void gen_infix_expr(int num_math_operators, bool balance_symbols = true);
	string gen_operand();

	void change_infix_to_postfix();
	void compute_postfix_expr();


private:

	void print_expr(const string& desc, const List<string>& expr);

	ofstream m_ofs;

	List<string> m_infix_expr;
	List<string> m_postfix_expr; // postfix 형태의 표현을 저장한다. m_infix_expr을 postfix_expr로 변환한다.
	long long m_result; // 계산 결과를 저장한다.

};




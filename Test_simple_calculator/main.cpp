// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>
#include "pch.h"
#include "Simple_calculator.h"


using namespace std;

/* ------------------------------------------------------------------------ */
// main()함수의 내용은 수정하지 마세요. 
// change_infix_to_postfix()와 compute_postfix_expr()를 위한 코드를 작성하시오.
// 실행 결과는 m_postfix_expr와 m_result에 저장하세요.
// 계산기는 정수(integer)를 사용하여 계산하시오. 실수(float)를 사용하여 계산하지 마세요. (예: 3 / 4 + 4 * 2 = 8 (0), 8.75 (X) ) 
// 피연산자: 양의 정수
// 연산자 (5개): +(덧셈), -(뺄셈), *(곱셈), /(나눗셈), ^(거듭제곱) (예: 3^2 = 9, 2^10 = 1024)
/* ------------------------------------------------------------------------ */

// 주의 : main 함수는 수정하지 마세요. 
int main()
{
	clock_t tStart = clock();

	srand(99);

	Simple_calculator my_calculator;

	// balance_symbols = false 이면, 괄호가 매칭되지 않을 수 있다. 
	my_calculator.gen_infix_expr(61, true); 
	my_calculator.print_infix_expr();
	
	/* 아래 3개의 메쏘드의 내용을 채우시오. */
	bool ret_val = my_calculator.check_balance_symbols(); // 문제 1 

	if (ret_val == false)
	{
		cerr << "We found some serious errors while checking balancing symbols in the math. expression" << endl;
		exit(0);
	}

	my_calculator.change_infix_to_postfix(); // 문제 2 
	my_calculator.compute_postfix_expr(); // 문제 3
	
	my_calculator.print_postfix_expr(); // postfix expr을 프린트한다.  
	my_calculator.print_result(); // 계산 결과를 프린트한다.  

	// 실행 시간을 측정합니다. 
	cout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " s" << endl;


	return 0;
}
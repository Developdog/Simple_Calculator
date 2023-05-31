// main.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

#include <iostream>
#include <time.h>
#include "pch.h"
#include "Simple_calculator.h"


using namespace std;

/* ------------------------------------------------------------------------ */
// main()�Լ��� ������ �������� ������. 
// change_infix_to_postfix()�� compute_postfix_expr()�� ���� �ڵ带 �ۼ��Ͻÿ�.
// ���� ����� m_postfix_expr�� m_result�� �����ϼ���.
// ����� ����(integer)�� ����Ͽ� ����Ͻÿ�. �Ǽ�(float)�� ����Ͽ� ������� ������. (��: 3 / 4 + 4 * 2 = 8 (0), 8.75 (X) ) 
// �ǿ�����: ���� ����
// ������ (5��): +(����), -(����), *(����), /(������), ^(�ŵ�����) (��: 3^2 = 9, 2^10 = 1024)
/* ------------------------------------------------------------------------ */

// ���� : main �Լ��� �������� ������. 
int main()
{
	clock_t tStart = clock();

	srand(99);

	Simple_calculator my_calculator;

	// balance_symbols = false �̸�, ��ȣ�� ��Ī���� ���� �� �ִ�. 
	my_calculator.gen_infix_expr(61, true); 
	my_calculator.print_infix_expr();
	
	/* �Ʒ� 3���� �޽���� ������ ä��ÿ�. */
	bool ret_val = my_calculator.check_balance_symbols(); // ���� 1 

	if (ret_val == false)
	{
		cerr << "We found some serious errors while checking balancing symbols in the math. expression" << endl;
		exit(0);
	}

	my_calculator.change_infix_to_postfix(); // ���� 2 
	my_calculator.compute_postfix_expr(); // ���� 3
	
	my_calculator.print_postfix_expr(); // postfix expr�� ����Ʈ�Ѵ�.  
	my_calculator.print_result(); // ��� ����� ����Ʈ�Ѵ�.  

	// ���� �ð��� �����մϴ�. 
	cout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " s" << endl;


	return 0;
}
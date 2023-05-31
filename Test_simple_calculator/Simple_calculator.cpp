#include "pch.h"
#include "Simple_calculator.h"
#include <iostream>
#include <time.h>
#include <sstream>
#include <iomanip>


/* -------------------------------------------------------- */
// ���� ��ȣ�� ������ ��ȣ�� ��Ī�Ǵ��� �˻��Ѵ�.
// ��Ī�� �°� �Ǹ�, true�� �����Ѵ�. �׷��� ������, false�� �����Ѵ�.
// ��: (()) , ()()	/* ��Ī O */
//     ((() , )(	    /* ��Ī X */
// 3�� 57�� �����̵� �����ϼ���.

// ���� 1
bool Simple_calculator::check_balance_symbols()
{
	List<string>::const_iterator pos;
	List<string> stack;

	for (List<string>::const_iterator pos = m_infix_expr.begin(); pos != m_infix_expr.end(); pos++)
	{
		if (*pos == "(") {
			stack.push_back("("); //(�� ���������� ���ÿ� �����ϱ�
		}
		if (*pos == ")" && *stack.begin() != "(") { // (�� �������� )�� ���� ��� 
			return false;
		}
		if (*pos == ")") {
			stack.pop_back();// )�� ���������� ���ÿ��� ������
		}

	}

	if (*stack.begin() == "(") { // (�� ���ÿ� ������ ���
		return false;
	}

	return true;
}

// ���� 2
void Simple_calculator::change_infix_to_postfix()
{
	/* ��ȯ ����� m_postfix_expr�� �����ϼ���. */
	List<string> stack;
	List<string> post_dummy; //���� �� ��ſ� �ϳ� �� �����
	List<string> post_dummytrans; // for�� ���� �� stack�� ����� ��


	for (List<string>::const_iterator pos = m_infix_expr.begin(); pos != m_infix_expr.end(); pos++)
	{
		if (*pos == "+" || *pos == "-") { // + Ȥ�� -�� ������
			if (stack.back() != "(" && stack.back() != "") { // ������ �� ���� ���� (�� NULL�� �ƴϸ� ��� ����Ѵ�.
				post_dummytrans = stack; // stack�� for���� �״�� ������ for�� ���� �� stack.end()�� ���� �ٲ� ����� ���������. ���� ������ stack�� ����� ���� �����.
				for (List<string>::const_iterator alpha = post_dummytrans.end(); alpha != post_dummytrans.begin(); alpha--)
				{
					if (stack.back() == "(" || stack.back() == "" ) break; // ���� ������ (�� NULL�� ������ Ż��
					else {
						post_dummy.push_back(stack.back());
						stack.pop_back();
					}
				}
			}
			stack.push_back(*pos); // ������ ���� ���κ��� ^ * / �� �ƴϸ� �׳� �Ѿ��.
		}
		// + -�� �ڽŰ� ������ + - �����ڸ� �������� ������, ���� ���� + - stack�� ����, ������ ���� stack�� �ִ´�. ���� * /�� ������ ��쿡�� (�� NULL�� ������ ������ stack�� ���� ����Ѵ�.

		else if (*pos == "*" || *pos == "/") { // * Ȥ�� / ������
			if ( stack.back() == "*" || stack.back() == "/" ) { // ������ �� ���� *�� /�� ������ �ش� ���� ����Ѵ�.
				post_dummytrans = stack;
				for (List<string>::const_iterator alpha = post_dummytrans.end(); alpha != post_dummytrans.begin(); alpha--)
				{
					if (stack.back() == "*" || stack.back() == "/") // *�� /�� ������ ���� ���� ��� Ż��
					{
						post_dummy.push_back(stack.back());
						stack.pop_back();
					}
					else {
						break;
					}
				}
			}
			stack.push_back(*pos); // ������ ���� ���κ��� ^�� �ƴϸ� �׳� �Ѿ��.
		}
		// * / �� �ڽŰ� ������ * / �����ڸ� �������� ������, ���� ���� * / stack�� ����, ������ ���� stack�� �ִ´�.���� �� �̿��� ���� ������ ��쿡�� �����Ѵ�.

		else if (*pos == "(") { stack.push_back(*pos); } //(�� ����.


		else if (*pos == ")") // (�� ���������� ������ �ִ� ��� ���� ��½�Ų��.
		{
			post_dummytrans = stack;
			for (List<string>::const_iterator alpha = post_dummytrans.end(); alpha != post_dummytrans.begin(); alpha--)
			{
				if (stack.back() == "(") {
					stack.pop_back();
					break; // ���� ������ (�� ������ ������ ���� ����� Ż��
				}
				else {
					post_dummy.push_back(stack.back()); //�� �̿��� ���� ������ ����� ���� ��½�Ų��.
					stack.pop_back();
				}

			}
			
		}

		else if (*pos == "^") { 
			stack.push_back(*pos);
			++pos;
			post_dummy.push_back(*pos);
			post_dummy.push_back(stack.back());
			stack.pop_back();
		} //^�̴�. ^�� ���ÿ� �����ϰ�, ���� ���� �ٷ� ��½�Ų ��, ^ �����ڸ� �ִ´�.

		else 
		{
			post_dummy.push_back(*pos);
		}
		// �ƹ��͵� �ƴ� ��� �׳� ���ڸ� ��½�Ų��.



		// ������ �� Ȯ�ο�
		/*
		cout << endl << "Post �� : " << *pos << endl;
		cout << "����Ʈ ���� �� : ";
		for (List<string>::const_iterator alpha = post_dummy.begin(); alpha != post_dummy.end(); alpha++)
		{
			cout << *alpha << " ";// �� ����ϰ� �ϱ�
		}
		cout << endl << "���� ���ο� ���� �� : ";
		for (List<string>::const_iterator alpha = stack.begin(); alpha != stack.end(); alpha++)
		{
			cout << *alpha; //���� ���ο� ���� �� Ȯ��
		}
		cout << endl << endl;
		*/
		
	}

	post_dummytrans = stack;
	for (List<string>::const_iterator alpha = post_dummytrans.end(); alpha != post_dummytrans.begin(); alpha--)
	{
			post_dummy.push_back(stack.back()); //���� ���ο� ���� ���� ��� ��½�Ű�� ������ ����.
			stack.pop_back();
	}

	m_postfix_expr = post_dummy;


	//������ �� Ȯ�ο� 
	/*
	for (List<string>::const_iterator alpha = m_postfix_expr.begin(); alpha != m_postfix_expr.end(); alpha++)
	{
		cout << *alpha << " ";// �� ����ϰ� �ϱ�
	}
	cout << endl << m_postfix_expr.size() << endl;
	cout << endl;
	*/
}

// ���� 3
void Simple_calculator::compute_postfix_expr()
{
	List<string> stack;
	long long Alpha, Beta, Ceta; // ������ long long �̻�

	for (List<string>::const_iterator pos = m_postfix_expr.begin(); pos != m_postfix_expr.end(); pos++) 
	{
		if (*pos == "+")
		{
			Alpha = stoll(stack.back());
			stack.pop_back();
			Beta = stoll(stack.back());
			stack.pop_back();
			Ceta = Beta + Alpha;
			stack.push_back(to_string(Ceta));
		}
		else if (*pos == "-")
		{
			Alpha = stoll(stack.back());
			stack.pop_back();
			Beta = stoll(stack.back());
			stack.pop_back();
			Ceta = Beta - Alpha;
			stack.push_back(to_string(Ceta));
		}
		else if (*pos == "*")
		{
			Alpha = stoll(stack.back());
			stack.pop_back();
			Beta = stoll(stack.back());
			stack.pop_back();
			Ceta = Beta * Alpha;
			stack.push_back(to_string(Ceta));
		}
		else if (*pos == "/")
		{
			if ("0" == stack.back()) Ceta = 0;//�и� 0�� ��� ���� ������ �ʱ� ������, ���� �������ش�.
			else {
				Alpha = stoll(stack.back());
				stack.pop_back();
				Beta = stoll(stack.back());
				stack.pop_back();
				Ceta = Beta / Alpha;
			}
			stack.push_back(to_string(Ceta));
		}
		else if (*pos == "^") //�ŵ�����
		{
			Alpha = stoll(stack.back());
			stack.pop_back();
			Beta = stoll(stack.back());
			stack.pop_back(); // Ceta�� ������ �����ϱ� ������ Delta�� 1�� �ٲ��ش�.
			Ceta = Beta;
			for (int Delta = 1; Delta < Alpha; Delta++ ) Ceta = Beta * Ceta;
			stack.push_back(to_string(Ceta));
		}
		else(stack.push_back(*pos));


		//Ȯ�ο� ��������
		/*
		cout << endl << "Post �� : " << *pos << endl;
		cout << "����Ʈ ���� �� : ";
		for (List<string>::const_iterator alpha = stack.begin(); alpha != stack.end(); alpha++)
		{
			cout << *alpha << " ";// �� ����ϰ� �ϱ�
		}
		cout << endl;
		*/
	}

	m_result = stol(stack.back());

	/* ��� ����� m_result�� �����ϼ���. */

}
/* -------------------------------------------------------- */


Simple_calculator::Simple_calculator()
{
	m_ofs.open("result.txt", ofstream::out | ofstream::trunc);
}


Simple_calculator::~Simple_calculator()
{
	m_ofs.close();
}


void Simple_calculator::print_expr(const string& desc, const List<string>& expr)// �޸��忡 ���� ��½�Ų��. ��� ����
{
	m_ofs << desc;
	for (List<string>::const_iterator pos = expr.begin(); pos != expr.end(); pos++)
	{
		m_ofs << *pos << " ";
	}
	m_ofs << endl;

}


void Simple_calculator::print_infix_expr()
{
	print_expr("infix_expr : ", m_infix_expr);
}

void Simple_calculator::print_postfix_expr()
{
	print_expr("postfix_expr : ", m_postfix_expr);
}

void Simple_calculator::print_result()
{
	m_ofs << "result is " << m_result << endl;
}


string Simple_calculator::gen_operand() // ������ �� ����
{
	int num = (rand() % 37) + 1; 

	stringstream ss;
	ss << setw(2) << num;
	string s = ss.str();

	return s;
}


void Simple_calculator::gen_infix_expr(int num_math_operators, bool balance_symbols)// ������ �� ���� 
{
	int cnt = 0;

	while (cnt++ < num_math_operators)
	{
		string op1, op2;
		string math_operator;

		int operator_id = rand() % 4;

		if (operator_id == 0) { math_operator = "+"; }
		else if (operator_id == 1) { math_operator = "-"; }
		else if (operator_id == 2) { math_operator = "*"; }
		else if (operator_id == 3) { math_operator = "/"; }

		// ���� ������(+, -, *, /)�� �߰��Ѵ�. 
		if (m_infix_expr.empty() == true)
		{
			op1 = gen_operand();
			op2 = gen_operand();

			m_infix_expr.push_back(op1);
			m_infix_expr.push_back(math_operator);
			m_infix_expr.push_back(op2);
		}
		else
		{
			op2 = gen_operand();

			m_infix_expr.push_back(math_operator);
			m_infix_expr.push_back(op2);
		}

		// ^ ���� ���� �����ڸ� �߰��Ѵ�.
		if (rand() % 5 == 0)
		{
			m_infix_expr.pop_back();

			op1 = gen_operand();


			int exponent = (rand() % 7) + 2;

			stringstream ss;
			ss << setw(1) << exponent;
			op2 = ss.str();



			math_operator = "^";

			m_infix_expr.push_back(op1);
			m_infix_expr.push_back(math_operator);
			m_infix_expr.push_back(op2);
		}



		if (rand() % 17 == 0)
		{
			const string open_paren		= (balance_symbols == false && (rand() % 3 == 0)) ? ")" : "(";
			const string close_paren	= (balance_symbols == false && (rand() % 3 == 0)) ? "(" : ")";

			m_infix_expr.push_front(open_paren);
			m_infix_expr.push_back(close_paren);
		}
	}
}
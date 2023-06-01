#include "pch.h"
#include "Simple_calculator.h"
#include <iostream>
#include <time.h>
#include <sstream>
#include <iomanip>


/* -------------------------------------------------------- */
// 왼쪽 괄호와 오른쪽 괄호가 매칭되는지 검사한다.
// 매칭이 맞게 되면, true를 리턴한다. 그렇지 않으면, false를 리턴한다.
// 예: (()) , ()()	/* 매칭 O */
//     ((() , )(	    /* 매칭 X */

// 문제 1
bool Simple_calculator::check_balance_symbols()
{
	List<string>::const_iterator pos;
	List<string> stack;

	for (List<string>::const_iterator pos = m_infix_expr.begin(); pos != m_infix_expr.end(); pos++)
	{
		if (*pos == "(") {
			stack.push_back("("); //(를 만날때마다 스택에 저장하기
		}
		if (*pos == ")" && *stack.begin() != "(") { // (가 없음에도 )를 만날 경우 
			return false;
		}
		if (*pos == ")") {
			stack.pop_back();// )를 만날때마다 스택에서 꺼내기
		}

	}

	if (*stack.begin() == "(") { // (가 스택에 남았을 경우
		return false;
	}

	return true;
}

// 문제 2
void Simple_calculator::change_infix_to_postfix()
{
	/* 변환 결과는 m_postfix_expr에 저장하세요. */
	List<string> stack;
	List<string> post_dummy; //원본 값 대신에 하나 더 만들기
	List<string> post_dummytrans; // for문 계산식 중 stack을 대신할 값


	for (List<string>::const_iterator pos = m_infix_expr.begin(); pos != m_infix_expr.end(); pos++)
	{
		if (*pos == "+" || *pos == "-") { // + 혹은 -을 넣을때
			if (stack.back() != "(" && stack.back() != "") { // 스택의 맨 위에 값이 (나 NULL이 아니면 계속 출력한다.
				post_dummytrans = stack; // stack을 for문에 그대로 넣으면 for문 실행 중 stack.end()의 값이 바꿔 계산이 어려워진다. 따라서 임의의 stack을 대신할 값을 만든다.
				for (List<string>::const_iterator alpha = post_dummytrans.end(); alpha != post_dummytrans.begin(); alpha--)
				{
					if (stack.back() == "(" || stack.back() == "" ) break; // 스택 내에서 (나 NULL을 만나면 탈출
					else {
						post_dummy.push_back(stack.back());
						stack.pop_back();
					}
				}
			}
			stack.push_back(*pos); // 스택의 가장 윗부분이 ^ * / 가 아니면 그냥 넘어간다.
		}
		// + -는 자신과 동일한 + - 연산자를 만나면을 만나면, 이전 값의 + - stack을 빼고, 본인의 값을 stack에 넣는다. 만약 * /을 만났을 경우에는 (나 NULL을 만나기 전까지 stack의 값을 출력한다.

		else if (*pos == "*" || *pos == "/") { // * 혹은 / 넣을때
			if ( stack.back() == "*" || stack.back() == "/" ) { // 스택의 맨 위에 *나 /가 있으면 해당 값을 출력한다.
				post_dummytrans = stack;
				for (List<string>::const_iterator alpha = post_dummytrans.end(); alpha != post_dummytrans.begin(); alpha--)
				{
					if (stack.back() == "*" || stack.back() == "/") // *나 /를 제외한 값을 만날 경우 탈출
					{
						post_dummy.push_back(stack.back());
						stack.pop_back();
					}
					else {
						break;
					}
				}
			}
			stack.push_back(*pos); // 스택의 가장 윗부분이 ^가 아니면 그냥 넘어간다.
		}
		// * / 는 자신과 동일한 * / 연산자를 만나면을 만나면, 이전 값의 * / stack을 빼고, 본인의 값을 stack에 넣는다.만약 그 이외의 값을 만났을 경우에는 종료한다.

		else if (*pos == "(") { stack.push_back(*pos); } //(의 시작.


		else if (*pos == ")") // (를 만날때까지 가지고 있는 모든 값을 출력시킨다.
		{
			post_dummytrans = stack;
			for (List<string>::const_iterator alpha = post_dummytrans.end(); alpha != post_dummytrans.begin(); alpha--)
			{
				if (stack.back() == "(") {
					stack.pop_back();
					break; // 스택 내에서 (를 만나면 스택의 값을 지우고 탈출
				}
				else {
					post_dummy.push_back(stack.back()); //그 이외의 값은 스택을 지우고 전부 출력시킨다.
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
		} //^이다. ^을 스택에 저장하고, 뒤의 값을 바로 출력시킨 뒤, ^ 연산자를 넣는다.

		else 
		{
			post_dummy.push_back(*pos);
		}
		// 아무것도 아닐 경우 그냥 숫자를 출력시킨다.



		// 지워도 됨 확인용
		/*
		cout << endl << "Post 값 : " << *pos << endl;
		cout << "포스트 더미 값 : ";
		for (List<string>::const_iterator alpha = post_dummy.begin(); alpha != post_dummy.end(); alpha++)
		{
			cout << *alpha << " ";// 값 출력하게 하기
		}
		cout << endl << "스택 내부에 남은 값 : ";
		for (List<string>::const_iterator alpha = stack.begin(); alpha != stack.end(); alpha++)
		{
			cout << *alpha; //스택 내부에 남은 값 확인
		}
		cout << endl << endl;
		*/
		
	}

	post_dummytrans = stack;
	for (List<string>::const_iterator alpha = post_dummytrans.end(); alpha != post_dummytrans.begin(); alpha--)
	{
			post_dummy.push_back(stack.back()); //스택 내부에 남은 값을 모두 출력시키고 스택은 비운다.
			stack.pop_back();
	}

	m_postfix_expr = post_dummy;


	//지워도 됨 확인용 
	/*
	for (List<string>::const_iterator alpha = m_postfix_expr.begin(); alpha != m_postfix_expr.end(); alpha++)
	{
		cout << *alpha << " ";// 값 출력하게 하기
	}
	cout << endl << m_postfix_expr.size() << endl;
	cout << endl;
	*/
}

// 문제 3
void Simple_calculator::compute_postfix_expr()
{
	List<string> stack;
	long long Alpha, Beta, Ceta; // 정수형 long long 이상

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
			if ("0" == stack.back()) Ceta = 0;//분모가 0일 경우 값이 나오지 않기 때문에, 따로 지정해준다.
			else {
				Alpha = stoll(stack.back());
				stack.pop_back();
				Beta = stoll(stack.back());
				stack.pop_back();
				Ceta = Beta / Alpha;
			}
			stack.push_back(to_string(Ceta));
		}
		else if (*pos == "^") //거듭제곱
		{
			Alpha = stoll(stack.back());
			stack.pop_back();
			Beta = stoll(stack.back());
			stack.pop_back(); // Ceta를 가지고 시작하기 때문에 Delta를 1로 바꿔준다.
			Ceta = Beta;
			for (int Delta = 1; Delta < Alpha; Delta++ ) Ceta = Beta * Ceta;
			stack.push_back(to_string(Ceta));
		}
		else(stack.push_back(*pos));


		//확인용 지워도됨
		/*
		cout << endl << "Post 값 : " << *pos << endl;
		cout << "포스트 더미 값 : ";
		for (List<string>::const_iterator alpha = stack.begin(); alpha != stack.end(); alpha++)
		{
			cout << *alpha << " ";// 값 출력하게 하기
		}
		cout << endl;
		*/
	}

	m_result = stol(stack.back());

	/* 계산 결과는 m_result에 저장하세요. */

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


void Simple_calculator::print_expr(const string& desc, const List<string>& expr)// 메모장에 값을 출력시킨다. 출력 가능
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


string Simple_calculator::gen_operand() // 무작위 식 생성
{
	int num = (rand() % 37) + 1; 

	stringstream ss;
	ss << setw(2) << num;
	string s = ss.str();

	return s;
}


void Simple_calculator::gen_infix_expr(int num_math_operators, bool balance_symbols)// 무작위 식 생성 
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

		// 이진 연산자(+, -, *, /)를 추가한다. 
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

		// ^ 단항 이진 연산자를 추가한다.
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

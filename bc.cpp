#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>


/*

E -> E + T | T

T -> F | T * F

F -> ( E ) | id

*/

const char* input_str = "a+b*(c+d)";
static char look_ahead;
char read_next() {
	static int pc = 0;
	return input_str[pc++];
}
void match_space(){
	if(look_ahead != ' ' && look_ahead != '\t'){
		look_ahead = read_next();
		return;
	}

	do{
		look_ahead = read_next();
	}while(look_ahead == ' ' || look_ahead == '\t');
}
void match(char c) {
	printf("try match %c == %c\n", look_ahead, c);
	assert(look_ahead == c);
	match_space();
}

std::string match_str(){
	char buf[128];

	assert(look_ahead == '\"');
	memset(buf, 0, sizeof(buf));
	int i = 0;
	do {
		look_ahead = read_next();
		buf[i++] = look_ahead;
	}while(look_ahead != '\"');
	buf[i-1] = 0;
	match_space();

	return std::string(buf);
}
std::string match_id(){
	char buf[128];
	assert(look_ahead <='z' && look_ahead >='a');
	memset(buf, 0, sizeof(buf));
	int i = 0;
	do {
		buf[i++] = look_ahead;
		look_ahead = read_next();

	}while(look_ahead <= 'z' && look_ahead >= 'a' ||
	look_ahead >='0' && look_ahead <= '9');

	buf[i] = 0;
	if(look_ahead == ' ' || look_ahead == '\t')
		match_space();
	printf("match_id:%s，%c\n", buf,look_ahead);
	return std::string(buf);
}
double match_digit(){
	char buf[128];
	int i = 0;
	do {
		look_ahead = read_next();
		buf[i++] = look_ahead;
	}while((look_ahead <='9' && look_ahead >='0') || look_ahead=='.');
	buf[i] = 0;
	match_space();

	return atof(buf);
}

/*
E -> T E_
E_ -> + T E_ | e

T -> F T_
T_ -> * F T_ | e

F -> ( E ) | id

*/
void T();
void T_();
void E();
void E_();
void F();

void E(){
	T(); E_();
}
void E_(){
	if(look_ahead == '+'){
		match('+');T();E_();
	}else
	;
}
void T(){
	F();T_();
	printf("get * or id\n");
}
void T_(){
	if (look_ahead == '*'){
		match('*');F();T_();
		/* code */
	}else
	;
}
void F(){
	if(look_ahead == '('){
		match('(');E();match(')');
	}else{
		std::string a = match_id();
		std::cout << a <<std::endl;
	}
}
int main() {
	look_ahead = read_next();
	E();
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

//const char *input = "A(B(,C(,)),D(,))";
const char *input = "(A (B))\0";
static int look_ahead ;
int read_next(){
	static  int i = 0;
	return input[i++];
}
void match(int t) {
	assert (look_ahead == t);
	do{
		look_ahead = read_next();
	}while(look_ahead == ' ');
}
struct node {
	struct node *left, *right;
	char c;
	node(char _c, struct node *l, struct node *r):
		c(_c),left(l),right(r) {}
};
struct node* N() {
	if (look_ahead <='Z' && look_ahead >= 'A') {
		struct node *l, *r;
		char c = look_ahead;
		match(look_ahead);
		match('(');
		l = N();match(',');
		r = N();match(')');
		return new struct node (c, l, r);
	}else {
		return NULL;
	}
}
void parse() {
	char look_ahead = 'c';
	switch(look_ahead) {
		case '(':
			break;
	}
}

void dump_node(struct node* root, int level) {
	char l,r ;
	int i = level*8;
	while(i--)
		printf(" ");
	std::cout << root->c <<std::endl;

}

/*

Lisp文法：
s-expr 	: 	atom 		| list ;
list	:	( members ) | () ;
members	:	s-expr		| s-expr members ;
members :   s-expr  G
G		:	members | e ;
atom	:	ID | NUM | STR |NIL | '+' | '-' | '*' | '/' ;

exprs -> expr exprs
list -> ( exprs )
expr -> atom | list
atom -> id| xxxx ;

*/
struct sexpr{};
struct slist{};
struct smember{};
struct atom{};
void expr();
void members();
void atom(){
	if(look_ahead <='Z' && look_ahead >= 'A')
		printf(" %c \n", look_ahead);
	match(look_ahead);
}
void G(){ // G -> Members | e
	// First(members)
	if(look_ahead == '(' || (look_ahead <='Z' && look_ahead >='A'))
		members();
	else
		;

}
void members() {
	printf("begin members \n");
	expr();	G();
}
void list() {
	printf("list()\n");
	match('(');
	if(look_ahead == ')')
		;
	else
		members();
}
void expr() {
	printf("expr(%c)\n",look_ahead);
	if(look_ahead == '(')
		list();
	else
		atom();
}

int main(int argc, char** argv) {
	look_ahead = read_next();
//	struct node* root =	N();
	expr();

}
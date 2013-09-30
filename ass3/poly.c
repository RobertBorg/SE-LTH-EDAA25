//Robert Borg 870906-3997
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "poly.h"

#define MAX_TERMS (10)

void error(const char* errMsg)
{
	printf("%s",errMsg);
	exit(1);
}

struct term_t {
	signed long long coefficient;
	signed long long exponent;
};

struct poly_t {
	int count;
	term_t* terms[MAX_TERMS];
};

void free_poly(poly_t* poly)
{
	for( int i = 0; i < poly->count; ++i) {
		free(poly->terms[i]);
		poly->terms[i] = 0;
	}
	poly->count = 0;
	free(poly);
}

poly_t* mul(poly_t* lhs, poly_t* rhs)
{
	poly_t* poly = malloc(sizeof(poly_t));
	if(poly == NULL)
		error("out of memory");
	poly->count = 0;
	for(int i = 0; i < lhs->count; ++i) {
		for(int j = 0; j < rhs->count; ++j) {
			signed long long coefficient = lhs->terms[i]->coefficient * rhs->terms[j]->coefficient;
			if(coefficient == 0)
				continue;
			signed long long exponent = lhs->terms[i]->exponent + rhs->terms[j]->exponent;
			bool match_found = false;
			for(int j = 0; j < poly->count; ++j) {
				if(poly->terms[j]->exponent == exponent){
					match_found = true;
					poly->terms[j]->coefficient += coefficient;
					break;
				}
			}
			if(!match_found) {
				term_t* term = malloc(sizeof(term_t));
				if(term == NULL){
					free_poly(poly);	
					error("not enough memory allocating a term");
				}
				poly->terms[poly->count++] = term;
				term->coefficient = coefficient;
				term->exponent = exponent;
			}
		}
	}
	return poly;
}


poly_t* new_poly_from_string(const char* in_string)
{
	poly_t* poly = malloc(sizeof(poly_t));
	if(poly == NULL)
		error("unable to allocate memory for poly");
	poly->count = 0;
	while(*in_string != 0) {
		term_t tmp;
		memset(&tmp, 0, sizeof(tmp));
		int n = 0;
		while(*in_string == ' ')
			++in_string;
		int multiplier = 1;
		if(*in_string == '-' || *in_string == '+') {
			if(*in_string++ == '-')
				multiplier = -1;

			while(*in_string == ' ')
				++in_string;

			if(isdigit(*in_string)) {
				sscanf(in_string, "%lld%n",&tmp.coefficient,&n);
				in_string += n;
			} else 
				tmp.coefficient = 1;

			tmp.coefficient *= multiplier;
		} else if(isdigit(*in_string)) {
			sscanf(in_string, "%lld%n",&tmp.coefficient,&n);
			in_string += n;
		} else
			tmp.coefficient = 1;
		if(*in_string == 'x' || *in_string == 'X') {
			if(*++in_string == '^') {
				sscanf(++in_string, "%lld%n", &tmp.exponent, &n);
				in_string += n;
			} else
				tmp.exponent = 1;
		} else {
			tmp.exponent = 0;
		}
		term_t* term = malloc(sizeof(term_t));
		if(term == NULL){
			free_poly(poly);
			error("unable to allocate memory for term");
		}
		memcpy(term, &tmp, sizeof(term_t));
		if(poly->count == MAX_TERMS){
			free(term);
			error("MAX_TERMS reached, unable to add more while parsing string");
		}
		poly->terms[poly->count++] = term;
	}
	return poly;
}

void print_poly(poly_t* poly)
{
	for(int i = 0; i < poly->count; ++i) {
		if(poly->terms[i]->coefficient < 0)
			printf("- ");
		else 
			if(i != 0)
				printf("+ ");
		if(poly->terms[i]->coefficient != 0) {
			if(poly->terms[i]->coefficient != 1 || poly->terms[i]->exponent == 0)
				printf("%lld", poly->terms[i]->coefficient < 0 ? poly->terms[i]->coefficient * -1 : poly->terms[i]->coefficient);
		} else
			continue;
		if(poly->terms[i]->exponent != 0) {
			printf("X");		
			if(poly->terms[i]->exponent != 1)
				printf("^%lld ", poly->terms[i]->exponent);
			else 
				printf(" ");
		} else {
			printf(" ");
		}
	}
	printf("\n");
}

static void poly_test(char* a, char* b)
{
	poly_t* p;
	poly_t* q;
	poly_t* r;
	printf("Begin polynomial test of (%s) * (%s)\n", a, b);
	p = new_poly_from_string(a);
	q = new_poly_from_string(b);
	print_poly(p);
	print_poly(q);
	r = mul(p, q);
	print_poly(r);
	free_poly(p);
	free_poly(q);
	free_poly(r);
	printf("End polynomial test of (%s) * (%s)\n\n\n", a, b);
}
int main(void)
{
	poly_test("x^2 - 7x + 1", "3x + 2");
	poly_test("x^10000000 + 2", "2x^2 + 3x + 4");
	return 0;
}
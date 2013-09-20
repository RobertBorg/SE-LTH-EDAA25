//870906-3997 Robert Borg
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_MAX (100)

void error(char* errMsg)
{
        printf("%s\n", errMsg);
        exit(1);
}

struct bigint {
        size_t count;
        unsigned int* numbers;
};

void bigint_init (struct bigint* bi, unsigned int num)
{
        bi->numbers = malloc(sizeof(unsigned int));
        if(bi->numbers == 0) {
                error("Unable to allocate memory for bigint.");
        }
        bi->numbers[0] = num;
        bi->count = 1;
}

void bigint_grow (struct bigint* bi) {
        bi->count *= 2;
        bi->numbers = realloc(bi->numbers, sizeof(unsigned int) * bi->count);
        if(bi->numbers == 0) {
                error("Unable to grow memory for bigint.");
        }
        unsigned int* numbers = bi->numbers;
        for(int i = bi->count / 2; i < bi->count; ++i) {
                numbers[i] = 0;
        }
}

void bigint_free (struct bigint* bi)
{
        if(bi->count != 0) {
                free(bi->numbers);
                bi->count = 0;
                bi->numbers = 0;
        }
}

void bigint_mul (struct bigint* bi, unsigned short num)
{
        unsigned int carry = 0;
        for(int i = 0; i < bi->count; ++i) {
                unsigned long long tmp = ((unsigned long long)bi->numbers[i]) * num + carry;
                if(tmp > 999999999) {
                        carry = tmp / 1000000000;
                        bi->numbers[i] = tmp % 1000000000;
                } else {
                        carry = 0;
                        bi->numbers[i] = tmp;
                }
        }
        if(carry != 0) {
                bigint_grow(bi);
                bi->numbers[bi->count/2] = carry;
        }
}

void bigint_print (struct bigint* bi)
{
        bool found_first = false;
        for(int i = bi->count-1; i >= 0; --i) {
                if(bi->numbers[i] != 0) {
                        found_first = true;
                        printf("%u", bi->numbers[i]);
                } else if(found_first)
                        printf("000000000");
        }
        printf("\n");
}

int main (int argc, const char* argv[])
{
        if(argc < 2)
                error("n was not supplied");
        unsigned short n = 0;
        const char* number = argv[1];
        while(*number != 0){
                n *= 10;
                n += *number - '0';
                ++number;
        }
        if(n > N_MAX)
                error("n > N_MAX");
        struct bigint bi;
        bigint_init(&bi, 1);
        for(int i = 1; i <= n; ++i)
                bigint_mul(&bi, i);
        bigint_print(&bi);
        bigint_free(&bi);
        return 0;
}
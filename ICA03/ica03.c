#include <stdio.h>

int main()
{
    unsigned int q_1 = 5632 & 0x321 >> 3;

    printf("%d\n", q_1);

    unsigned int q_2 = (unsigned char)5632 | 0x321 >> 3;

    printf("%d\n", q_2);

    unsigned char q_3 = (unsigned char)(5632 & 0xF371 >> 3);

    printf("%d\n", q_3);

    unsigned int q_4 = (unsigned char)(0x12345678ul / 4);

    printf("%d\n", q_4);

    //Using short type to try to convert number to 16 bits

    unsigned short int q_5 = 0b10101010001001000101001100101010 >> 2 & 0xF5A56832u;

    printf("%d\n", q_5);

    unsigned int q_6 = 8 * 0x34 + 0b1101010011 << 4 & 0b110011001100 >> 2;

    printf("%d", q_6);
    
    return 0;
}

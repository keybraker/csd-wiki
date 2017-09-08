/*
Alexandros Marantos
csd3329@csd.uoc.gr
Assignment 1
HY 255    */

#include <stdio.h>

/*-------dilosi-pinakon-ellinikon--------------
---kefalaia-ellinika---*/
int kef_ell[22] = {193, 194, 195, 196, 197, 198, 199, 200, 201,
                    202, 203, 204, 205, 207, 208, 209, 211,
                    212, 213, 214, 215, 217};        /*ALPHA-OMEGA xoris ks kai ps
---mikra-ellinika-----*/
int mikra_ell[23] = {225, 226, 227, 228, 229, 230, 231, 232, 233,
                    234, 235, 236, 237, 239, 240, 241, 242,
                    243, 244, 245, 246, 247, 249};
                    /* a-omega / ta 242 kai 243 einai kai ta dio s
                    to 242 to teliko s kai to 243 to klasiko
-----telos-dilosis-pinakon-ellinikon-----------
-------------------------------------------------------------------------------------
------dilosi-pinakon-agglikon-----------------*/
int cap_eng[22] = {65, 86, 71, 68, 69, 90, 72, 56, 73, 75, 76,
                    77, 78, 79, 80, 82, 83, 84, 89, 70, 88,
                    87};    /*A-V-G-D-E... xoris ks & ps*/

int small_eng[22] = {97, 118, 103, 100, 101, 122, 104, 56, 105,
                    107, 108, 109, 110, 111, 112, 114,
                    115, 116, 121, 102, 120, 119};    /*a-v-g-d-e... xoris ks ps
---------telos-dilosis-pinakon-aggLikon-----------*/
int kef_mikra_tonos[20] = {182, 184, 185, 186, 188, 191, 190, 220, 221, 222, 223, 252, 254, 253, 250, 251, 218, 219, 192, 224};

int tran_chars[20] = {65,69,72,73,79,87,89,97,101,104,105,111,119,121, 105, 121, 73, 89, 105, 121};

void Capitals(int letter)
{
    int i;
    for(i = 0; i < 22; i++)
    {
        if(kef_ell[i] == letter)
        {
            putchar(cap_eng[i]);
            break;
        }
    }
}
void Small(int letter)
{
    int i;
    for(i = 0; i < 23; i++)
    {
        if(mikra_ell[i] == letter)
        {
            if(i<17)                        /*logo ton 2 s*/
            {
                putchar(small_eng[i]);
            }
            else
            {
               putchar(small_eng[i-1]);
            }

            break;
        }
    }

}
void tonoi_dialytika( int letter )
{
    int i;
    for(i=0; i<20; i++)
    {
        if(kef_mikra_tonos[i] == letter)
        {
            if(i<7)                     /*kefalaia tonoi*/
            {
                putchar('\'');
                putchar(tran_chars[i]);
            }
            else if(i>=7 && i<14)           /*mikra tonoi*/
            {
                putchar(tran_chars[i]);
                putchar('\'');
            }
            else if(i>=14 && i<17)          /*dialytika*/
            {
                putchar(tran_chars[i]);
                putchar('\"');
            }
            else                            /*dialytika tonos*/
            {
                putchar(tran_chars[i]);
                putchar('\"');
                putchar('\'');
            }
            break;
        }
    }
}

int StateMachine(int letter, int state)
{
int prob=0,prob2=0;
/*----------------kefalaia--------------------------------------------------------------*/
    if((letter == 244 && state == 205) || (letter == 240 && state == 204) )
    {
        prob = 1;

    }
    else if( (letter == 208 && state == 236) || (letter == 212 && state == 237))
    {
        prob2 = 1;
    }

    if( ((letter>=193 && letter<=217 && letter != 206 && letter != 216 && letter != 210) || (prob == 1)) && ( prob2 == 0) )
    {
        if(letter == 204)
        {
            if(state == 204)        /*polla M sinexomena*/
            {
                putchar('M');
            }
            return 204;
        }
        else if(state == 204 && ( letter == 208 || letter == 240 ))  /*prin m tora p*/
        {
            putchar('B');
            return 0;
        }
        else if(state == 204 && letter == 240)
        {
            putchar('b');
            return 0;
        }
        else if(state == 204 && letter != 208)
        {
            putchar('M');
            Capitals(letter);
            return 0;
        }
        else if(letter == 205)
        {
            if(state == 205)            /*polla N sinexomena*/
            {
                putchar('N');
            }
            return 205;
        }
        else if(state == 205 && ( letter == 212 || letter == 244 ) )
        {
            putchar('D');
            return 0;
        }
        else if(state == 205 && letter != 212)
        {
            putchar('N');
            Capitals(letter);
            return 0;
        }
        else
        {
            if(state == 204)
            {
                putchar('M');
            }
            else if(state == 237)
            {
                putchar('N');
            }
            Capitals(letter);
        }
        prob=0;
    }
    else if (letter == 206)
    {
        if(state == 0)
        {
            putchar('K');
            return 1;
        }
        else
        {
            putchar('S');
        }
    }
    else if (letter == 216)
    {
        if(state == 0)
        {
            putchar('P');
            return 1;
        }
        else
        {
            putchar('S');
        }
    }
/*---------------mikra----------------------------------------------------------------*/
    else if ((letter>=225 && letter<=249 && letter != 238 && letter != 248) || (prob2 == 1))
    {
        if(letter == 236)
        {
            if(state == 236)            /*polla m sinexomena*/
            {
                putchar('m');
            }
            else if(state == 237)       /*polla n sinexomena*/
            {
                putchar('n');
            }
            return 236;
        }
        else if(state == 236 && (letter == 240 || letter == 208))  /*prin m tora p*/
        {
            putchar('b');
            return 0;
        }
        else if(state == 236 && letter != 240)
        {
            putchar('m');
            Small(letter);
            return 0;
        }
        else if(letter == 237)
        {
            return 237;
        }
        else if(state == 237 && (letter == 244 || letter == 212))
        {
            putchar('d');
            return 0;
        }
        else if(state == 237 && letter != 244)
        {
            putchar('n');
            Small(letter);
            return 0;
        }
        else if(state == 236 || state == 237)          /*an eixe prohgithei m or n typose to*/
        {
            if(state == 236)
            {
                putchar('m');
                Small(letter);
            }
            else
            {
                putchar('n');
                Small(letter);
            }
        }
        else
        {
            Small(letter);
        }
        prob2=0;
    }
    else if (letter == 238)
    {
        if(state == 0)
        {
            putchar('k');           /*gia to mikro ks*/
            return 1;
        }
        else
        {
            putchar('s');
        }
    }
    else if (letter == 248)
    {
        if(state == 0)              /*ps*/
        {
            putchar('p');
            return 1;
        }
        else
        {
            putchar('s');
        }
    }
/*----------tonoi kefalaia--------------------------------------------------------------*/
    else if(letter == 182 || (letter>=184 && letter<=186) || letter == 188 || (letter>=190 && letter<=192) || (letter>=218 && letter<=224) || (letter>=250 && letter<=254) )
    {
        if(state == 236)
        {
            putchar('m');
        }
        else if(state == 237)
        {
            putchar('n');
        }
        tonoi_dialytika(letter);

    }
    else
    {
        if(state == 236)
        {
            putchar('m');
        }
        else if(state == 237)
        {
            putchar('n');
        }
        putchar(letter);
    }
    return 0;
}


int main(void)
{
    int state = 0;        /*0=kanonika|1= ks or ps|#of letter = dealing with it*/

    int letter;

    while ((letter = getchar()) != EOF)
	{		
        state = StateMachine(letter, state);

        if(state == 1)              /*to xrisimopoioyn ta ks kai ps*/
        {
            state = StateMachine(letter, state);
        }

    }
    return 0;
}
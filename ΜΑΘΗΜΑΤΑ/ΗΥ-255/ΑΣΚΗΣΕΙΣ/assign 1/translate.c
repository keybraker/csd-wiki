/*
* translate.c
* John Rambo
* rambo@csd.uoc.gr
* hy255
* as1
*/

#include <stdio.h>

#define SET_SIZE		255

#define M_CAP_GR		204
#define M_SMALL_GR		236
#define N_CAP_GR		205
#define N_SMALL_GR		237
#define P_CAP_GR		208
#define P_SMALL_GR		240
#define T_CAP_GR		212
#define T_SMALL_GR		244

#define M_CAP_EN		78
#define M_SMALL_EN		109
#define N_CAP_EN		79
#define N_SMALL_EN		110
#define B_CAP_EN		66
#define B_SMALL_EN		98
#define D_CAP_EN		68
#define D_SMALL_EN		100

#define	TONOS			39
#define	DIALYTIKA		34


/* enumeration constants for automaton states */
enum state { ANY = 0, M_UPPER, M_LOWER, N_UPPER, N_LOWER };

/* structure representing a character map between two encodings */
struct {
	char rep[3];
} cmap[SET_SIZE];

/*
* initializes the character map
*/
void initialize_c_map(void) {
	cmap[168].rep[0] = DIALYTIKA;
	cmap[180].rep[0] = TONOS;
	cmap[181].rep[0] = TONOS; cmap[181].rep[1] = DIALYTIKA;
	cmap[182].rep[0] = TONOS; cmap[182].rep[1] = 65;
	cmap[184].rep[0] = TONOS; cmap[184].rep[1] = 69;
	cmap[185].rep[0] = TONOS; cmap[185].rep[1] = 72;
	cmap[186].rep[0] = TONOS; cmap[186].rep[1] = 73;
	cmap[188].rep[0] = TONOS; cmap[188].rep[1] = 79;
	cmap[190].rep[0] = TONOS; cmap[190].rep[1] = 89;
	cmap[191].rep[0] = TONOS; cmap[191].rep[1] = 87;
	cmap[192].rep[0] = 105; cmap[192].rep[1] = DIALYTIKA;
							cmap[192].rep[2] = TONOS;
	cmap[193].rep[0] = 65;
	cmap[194].rep[0] = 86;
	cmap[195].rep[0] = 71;
	cmap[196].rep[0] = 68;
	cmap[197].rep[0] = 69;
	cmap[198].rep[0] = 90;
	cmap[199].rep[0] = 72;
	cmap[200].rep[0] = 56;
	cmap[201].rep[0] = 73;
	cmap[202].rep[0] = 75;
	cmap[203].rep[0] = 76;
	cmap[204].rep[0] = 77;
	cmap[205].rep[0] = 78;
	cmap[206].rep[0] = 75; cmap[206].rep[1] = 83;
	cmap[207].rep[0] = 79;
	cmap[208].rep[0] = 80;
	cmap[209].rep[0] = 82;
	cmap[211].rep[0] = 83;
	cmap[212].rep[0] = 84;
	cmap[213].rep[0] = 89;
	cmap[214].rep[0] = 70;
	cmap[215].rep[0] = 88;
	cmap[216].rep[0] = 80; cmap[216].rep[1] = 83;
	cmap[217].rep[0] = 87;
	cmap[218].rep[0] = DIALYTIKA; cmap[218].rep[1] = 73;
	cmap[219].rep[0] = DIALYTIKA; cmap[218].rep[1] = 89;
	cmap[220].rep[0] = 97; cmap[220].rep[1] = TONOS;
	cmap[221].rep[0] = 101; cmap[221].rep[1] = TONOS;
	cmap[222].rep[0] = 104; cmap[222].rep[1] = TONOS;
	cmap[223].rep[0] = 105; cmap[223].rep[1] = TONOS;
	cmap[224].rep[0] = 121; cmap[224].rep[1] = DIALYTIKA;
							cmap[224].rep[2] = TONOS;
	cmap[225].rep[0] = 97;
	cmap[226].rep[0] = 118;
	cmap[227].rep[0] = 103;
	cmap[228].rep[0] = 100;
	cmap[229].rep[0] = 101;
	cmap[230].rep[0] = 122;
	cmap[231].rep[0] = 104;
	cmap[232].rep[0] = 56;
	cmap[233].rep[0] = 105;
	cmap[234].rep[0] = 107;
	cmap[235].rep[0] = 108;
	cmap[236].rep[0] = 109;
	cmap[237].rep[0] = 110;
	cmap[238].rep[0] = 107; cmap[238].rep[1] = 115;
	cmap[239].rep[0] = 111;
	cmap[240].rep[0] = 112;
	cmap[241].rep[0] = 114;
	cmap[242].rep[0] = 115;
	cmap[243].rep[0] = 115;
	cmap[244].rep[0] = 116;
	cmap[245].rep[0] = 121;
	cmap[246].rep[0] = 102;
	cmap[247].rep[0] = 120;
	cmap[248].rep[0] = 112; cmap[248].rep[1] = 115;
	cmap[249].rep[0] = 119;
	cmap[250].rep[0] = 105; cmap[250].rep[1] = DIALYTIKA;
	cmap[251].rep[0] = 121; cmap[251].rep[1] = DIALYTIKA;
	cmap[252].rep[0] = 111; cmap[252].rep[1] = TONOS;
	cmap[253].rep[0] = 121; cmap[253].rep[1] = TONOS;
	cmap[254].rep[0] = 119; cmap[254].rep[1] = TONOS;
}

/*
* prints the corresponding latin character based on the map
*/
void print_simple(int c) {
	int i = 0;
	if (cmap[c].rep[i] == NULL)
		putchar(c);
	else while (cmap[c].rep[i] != NULL && i < 3)
		putchar(cmap[c].rep[i++]);
}

enum state action_any(int c) {
	switch (c) {
		case M_CAP_GR:
			return M_UPPER;
		case M_SMALL_GR:
			return M_LOWER;
		case N_CAP_GR:
			return N_UPPER;
		case N_SMALL_GR:
			return N_LOWER;
		default:
			print_simple(c);
			return ANY;
	}
}

enum state action_m_upper(int c) {
	switch (c) {
		case M_CAP_GR:
			putchar(M_CAP_EN);
			return M_UPPER;
		case M_SMALL_GR:
			putchar(M_CAP_EN);
			return M_LOWER;
		case N_CAP_GR:
			putchar(M_CAP_EN);
			return N_UPPER;
		case N_SMALL_GR:
			putchar(M_CAP_EN);
			return N_LOWER;
		case P_CAP_GR:
			putchar(B_CAP_EN);
			return ANY;
		case P_SMALL_GR:
			putchar(B_CAP_EN);
			return ANY;
		default:
			putchar(M_CAP_EN);
			print_simple(c);
			return ANY;
	}
}

enum state action_m_lower(int c) {
	switch (c) {
		case M_CAP_GR:
			putchar(M_SMALL_EN);
			return M_UPPER;
		case M_SMALL_GR:
			putchar(M_SMALL_EN);
			return M_LOWER;
		case N_CAP_GR:
			putchar(M_SMALL_EN);
			return N_UPPER;
		case N_SMALL_GR:
			putchar(M_SMALL_EN);
			return N_LOWER;
		case P_CAP_GR:
			putchar(B_SMALL_EN);
			return ANY;
		case P_SMALL_GR:
			putchar(B_SMALL_EN);
			return ANY;
		default:
			putchar(M_SMALL_EN);
			print_simple(c);
			return ANY;
	}
}

enum state action_n_upper(int c) {
	switch (c) {
		case M_CAP_GR:
			putchar(N_CAP_EN);
			return M_UPPER;
		case M_SMALL_GR:
			putchar(N_CAP_EN);
			return M_LOWER;
		case N_CAP_GR:
			putchar(N_CAP_EN);
			return N_UPPER;
		case N_SMALL_GR:
			putchar(N_CAP_EN);
			return N_LOWER;
		case T_CAP_GR:
			putchar(D_CAP_EN);
			return ANY;
		case T_SMALL_GR:
			putchar(D_CAP_EN);
			return ANY;
		default:
			putchar(N_CAP_EN);
			print_simple(c);
			return ANY;
	}
}

enum state action_n_lower(int c) {
	switch (c) {
		case M_CAP_GR:
			putchar(N_SMALL_EN);
			return M_UPPER;
		case M_SMALL_GR:
			putchar(N_SMALL_EN);
			return M_LOWER;
		case N_CAP_GR:
			putchar(N_SMALL_EN);
			return N_UPPER;
		case N_SMALL_GR:
			putchar(N_SMALL_EN);
			return N_LOWER;
		case T_CAP_GR:
			putchar(D_SMALL_EN);
			return ANY;
		case T_SMALL_GR:
			putchar(D_SMALL_EN);
			return ANY;
		default:
			putchar(N_SMALL_EN);
			print_simple(c);
			return ANY;
	}
}

enum state (*action[])(int c) = 	{ action_any,
									action_m_upper, action_m_lower,
									action_n_upper, action_n_lower };

int main(void) {
	
	int 		c;
	enum state 	cur_state;
	
	initialize_c_map();
	
	cur_state = ANY;
	while ((c = getchar()) != EOF) {
		cur_state = (action[cur_state])(c);
	}
	
	return 0;
}

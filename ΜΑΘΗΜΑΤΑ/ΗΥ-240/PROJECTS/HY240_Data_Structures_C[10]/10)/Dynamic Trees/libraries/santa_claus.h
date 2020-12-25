/**********************************************************************
 * @file   santa_claus.h                                              *
 * @author Papaioannou Antonis <papaioan@csd.uoc.gr>				  *
 *                                                                    *
 * @brief  Header file with the structures and function prototypes    *
 * for the needs of the Data Structures (HY-240a) project (Fall 2015) *
 * Computer Science Department, University of Crete, Greece           *
**********************************************************************/

#define M 3 /*Number of child's preferences*/
#define N 4 /*Number of children's age categories*/

extern int primes_g[160];

/*Needed structs definition*/

/*Structure defining a node of the children tree*/
struct child {
	int cid; /*The identifier of the child.*/
	int age; /*The age of the child.*/
	int did; /*The identifier of the child.*/
	int present_choices[M]; /*The array in which the preferences of the child for presents are stored*/
	struct child *lc; /* left child */
	struct child *rc; /* right child */
};

/*Structure defining a node of the presents tree*/
struct present {
	int pid; /*The identifier of the present*/
	int stock_cnt; /*The counter of available presents in stock*/
	int request_cnt; /*The counter of requested presents in stock*/
	struct present *parent; /* parent node */
	struct present *lc; /* left child */
	struct present *rc; /* right child */
};

/*Structure defining a record of the present assignments (used in present assignments hash table) */
struct present_assign {
	int cid; /*The identifier of the child that the present assigned to*/
	int pid; /*The identifier of the present assigned to the child*/
	int s_degree; /*The degree of satisfaction of the child who received the present*/
	struct present_assign *next; /* Create chains in hash table */
};

/*Structure defining a node of the districts list*/
struct district {
	int did; /*The identifier of the district that the child lives in*/
	int children_cnt; /* no. of children live in this district */
	struct present_assign *assignHT; /* the hash table of present assignments of this district*/
	struct district *next; /* Singly-linked list */
};

extern struct child *Age_categories[N]; /*The array of the children's age categories*/

extern struct present *stock_tree; /* global variable pointing to the root of the stock tree */
extern struct present *stock_sentinel; /* global variable pointing to the sentinel node of the stock tree */

extern struct district* DistrictsL;

/*Needed function protypes definition*/

/**
 * @brief Create a new present and add it to the stock
 *
 * @param pid The new present's id
 * @param stock_cnt The instances of the new present to be stored at the stock
 *
 * @return 1 on success
 *         0 on failure
 */
int buy_present(int pid, int stock_cnt);

/**
 * @brief Create a new request for present from the child  and handle the counters about the stock
 *
 * @param cid The id of the child who sent the letter
 * @param age The age of the child
 * @param did The id of the district in which the child lives
 * @param pid1 The id of the present of the 1st preference of the child
 * @param pid2 The id of the present of the 2nd preference of the child
 * @param pid3 The id of the present of the 3rd preference of the child
 *
 * @return 1 on success
 *         0 on failure
 */
int letter_received(int cid, int age, int did, int pid1, int pid2, int pid3);

/**
 * @brief Assign presents to children taking into consideration their preference and stock availability 
 *
 * @return 1 on success
 *         0 on failure
 */
int prepare_presents(void);

/**
 * @brief Assign a satisfaction degree to the present received by the child
 *
 * @param cid The id of the child who gives feedback
 * @param did The id of the district where the child lives
 * @param s_degree The number of the satisfaction degree of the child
 *
 * @return 1 on success
 *         0 on failure
 */
int give_feedback(int cid, int did, int s_degree);

/**
 * @brief Sort the stock list of presents
 *
 * @return 1 on success
 *         0 on failure
 */
int analytics(int k);

/**
 * @brief Change the year of presents dispatch
 *
 * @return 1 on success
 *         0 on failure
 */
int new_season(void);

/**
 * @brief Remove children who did not send a letter to Santa Claus
 *
 * @return 1 on success
 *         0 on failure
 */
int clear_list_of_children(void);

/**
 * @brief Search for a specific present in stock list of presents
 *
 * @param pid The id of the present searched
 *
 * @return 1 on success
 *         0 on failure
 */
int search_present(int pid);

/**
 * @brief Print the children lists of all age categories
 *
 * @return 1 on success
 *         0 on failure
 */
int print_child(void);

/**
 * @brief Print the children id and presents id of all districts
 *
 * @return 1 on success
 *         0 on failure
 */
int print_district(void);

/**
 * @brief Print the id of available presents of the stock
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stock(void);


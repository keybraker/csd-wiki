#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

 int give_feedback(int cid, int s_degree) {

     struct district* districts = district_head;
     struct present_assign* ass;

     while (districts != NULL) {
         ass = districts->assignL;
         while (ass != NULL) {
             
             if (ass->cid == cid) {
                 if (ass->pid == -2) {
                     ass->s_degree = 1;
                     printf("F <%d> <%d> <%d> \n\nDONE\n\n",cid,s_degree,ass->pid);
                     return 1;
                 }else{
                     ass->s_degree = s_degree;
                     printf("F <%d> <%d> <%d> \n\nDONE\n\n",cid,s_degree,ass->pid);
                     return 1;
                 }
             }
             ass = ass->next;
         }
         districts = districts->next;
     
     }
     return 1;
 }


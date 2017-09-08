#include <stdio.h>
#include <stdlib.h>

char *Word_Translator ( int c ){
    
    int i;
    
    /*ΠΙΝΑΚΕΣ ΚΑΤ'ΑΝΤΙΣΤΟΙΧΙΑ, ΤΟΥ ΕΛΛΗΝΙΚΟΥ ΜΕ ΤΟΝ ΑΓΓΛΙΚΟ*/
    int GREEK_ORIGINAL[24] = { 193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,211,212,213,214,215,216,217};
    char *GREEK_ENGLISH[24] = {"A","V","G","D","E","Z","H","8","I","K","L","M","N","KS","O","P","R","S","T","Y","F","X","PS","W"};
    
    int GREEK_ORIGINAL_SMALL[25] = { 225 , 226 , 227 , 228 , 229 , 230 , 231 , 232 , 233 , 234 , 235 , 236 , 237 , 238 , 239 , 240 , 241 , 242 , 243 , 244 , 245 , 246 , 247 , 248 , 249 };
    char *GREEK_ENGLISH_SMALL[25] = {"a","v","g","d","e","z","h","8","i","k","l","m","n","ks","o","p","r","s","s","t","y","f","x","ps","w"};
    
    int GREEK_ACUTE[14] = { 182 , 184 , 185 , 186 , 188 , 190 , 191 , 220 , 221 , 222 , 223 , 252 , 253 , 254 };
    char *ENGLISH_ACUTE[14] = {"\'A","\'E","\'H","\'I","\'O","\'Y","\'W","a\'","e\'","h\'","i\'","o\'","y\'","w\'"};
    
    int GREEK_EXTRAS[4] = { 250 , 251 , 192 , 224 };
    char *ENGLISH_EXTRAS[4]= {"i\'","y\'","i\'\"","y\'\""};
    
    int NUMBERS[10] = { 48,49,50,51,52,53,54,55,56,57 };
    char *NUMBERS_REAL[10]= { "0","1","2","3","4","5","6","7","8","9" };
    
    int SYMBOLS[4] = { 33,44,46,63 };
    char *SYMBOLS_REAL[4] = { "!",",",".","?" };
    
    if ( c == 32 ) {
        return " ";
    }
    
    /*ΕΛΕΓΧΟΣ ΧΑΡΑΚΤΗΡΑ ΚΑΙ ΕΠΙΣΤΡΟΦΗ ΤΟΥ ΣΩΣΤΟΥ ΑΓΓΛΙΚΟΥ*/
    for ( i=0 ; i<24 ; i++ ){
        if ( GREEK_ORIGINAL[i] == c ){
            return GREEK_ENGLISH[i];
        }
    }
    for ( i=0 ; i<24 ; i++ ){
        if ( GREEK_ORIGINAL_SMALL[i] == c ){
            return GREEK_ENGLISH_SMALL[i];
        }
    }
    for ( i=0 ; i<14 ; i++ ){
        if ( GREEK_ACUTE[i] == c ){
            return ENGLISH_ACUTE[i];
        }
    }
    for ( i=0 ; i<4 ; i++ ){
        if ( GREEK_EXTRAS[i] == c ){
            return ENGLISH_EXTRAS[i];
        }
    }
    for ( i=0 ; i<10 ; i++ ){
        if ( NUMBERS[i] == c ){
            return NUMBERS_REAL[i];
        }
    }
    for ( i=0 ; i<22 ; i++ ){
        if ( SYMBOLS[i] == c ){
            return SYMBOLS_REAL[i];
        }
    }
    
    return "";
}

int main() {
    
    int c,memo;
    char *ct = NULL;
    
    memo = 0;
    /*ΛΟΥΠΑ ΓΙΑ ΤΗΝ ΕΙΣΑΓΩΓΗ ΧΑΡΑΚΤΗΡΩΝ*/
    while ( (c = getchar() ) != EOF ) {
        
        /*ΕΛΕΓΧΟΣ ΓΙΑ ΤΟ Ντ και το Μπ*/
        if ( c == 204 ){ memo =1;
            c = getchar();
            if ( c == 240 || c == 208 ) {
                putchar('B');
                memo =6;
            }
        }else if ( c == 205 ){ memo = 2;
            c = getchar();
            if ( c == 244 || c == 212 ) {
                putchar('D');
                memo =6;
            }
        }else if ( c == 236 ){ memo = 3;
            c = getchar();
            if ( c == 240 || c == 208 ) {
                putchar('b');
                memo =6;
            }
        }else if ( c == 237 ){ memo = 4;
            c = getchar();
            if ( c == 244 || c == 212 ) {
                putchar('d');
                memo =6;
            }
        }
        
        /*ΕΚΤΥΠΩΣΗ ΤΩΝ ΚΑΤΑΛΛΗΛΩΝ ΧΑΡΑΚΤΗΡΩΝ ΜΕ ΤΗ ΒΟΗΘΕΙΑ 
         ΜΕΤΑΒΛΗΤΩΝ ΣΤΗ ΡΟΗ ΤΟΥ ΠΡΟΓΡΑΜΜΑΤΟΣ*/
        if ( memo == 6 ) {
            /*ΔΕΝ ΠΡΕΠΕΙ ΝΑ ΤΥΠΩΣΕΙ ΤΙΠΟΤΑ ΔΙΟΤΙ ΕΧΕΙ ΗΔΗ 
             ΤΥΠΩΣΕΙ ΤΟ B Η ΤΟ D ΚΑΙ ΠΡΕΠΕΙ ΝΑ ΠΑΕΙ ΝΑ ΠΑΡΕΙ 
             ΝΕΟ ΧΑΡΑΚΤΗΡΑ ΓΙΑ ΤΗ ΣΥΝΕΧΙΑ ΤΗΣ ΕΚΤΕΛΕΣΗΣ*/
        }else{
            if (memo == 1) {
                putchar('M');
            }else if (memo == 2) {
                putchar('N');
            }else if (memo == 3) {
                putchar('m');
            }else if (memo == 4) {
                putchar('n');
            }
            /*ΜΕ ΤΥΠΩΜΕΝΟ ΤΟΝ ΧΑΡΑΚΤΗΡΑ ΠΟΥ ΔΕΝ ΚΑΤΑΦΕΡΕ 
             ΝΑ ΓΙΝΕΙ B Ή D ΠΑΕΙ ΝΑ ΒΡΕΙ ΤΟΝ ΕΠΟΜΕΝΟ ΚΑΙ 
             ΝΑ ΤΟΝ ΕΚΤΥΠΩΣΕΙ*/
            ct = Word_Translator(c);
            printf("%s",ct);
        }
        
        /*ΤΟ memo ΠΟΥ ΕΙΝΑΙ Η ΜΝΗΜΗ ΕΠΑΝΕΡΧΕΤΑΙ ΣΤΗ ΚΑΝΟ-
         ΝΙΚΗ ΚΑΤΑΣΤΑΣΗ ΚΑΙ ΞΕΚΙΝΑΕΙ Η ΕΠΟΜΕΝΗ ΛΟΥΠΑ*/
        memo = 0;
    
    }
    return 0;
}


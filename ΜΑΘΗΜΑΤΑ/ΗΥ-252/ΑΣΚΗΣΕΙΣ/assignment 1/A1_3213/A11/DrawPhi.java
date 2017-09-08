import java.util.Scanner;

public class DrawPhi {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        
        System.out.print("Enter an integer: ");
        int L = keyboard.nextInt();
        int odd = 1;int spaces = 0;
        if ( L%2 == 0 ){
            odd = 0;//even
            spaces = ((L-1)/2)+1;
        }else{
            spaces = L/2;//odd
        }
        //System.out.println("spaces="+spaces+", odd="+odd);
        
        int i=0,j=0;
        int sp=spaces;
        if (L<4){
            System.out.println("L<4 prints nothing");
        }else{
            
            if(odd == 0){//System.out.println(L+", odd == 0");
                
                while (i<L/2){//first part of
                    
                    //prints the spaces before the Phi
                    for(j=0;j<sp;j++){
                        System.out.print(" ");
                    }
                    if(i==0){sp--;}
                    //prints the stars "*" and the spaces
                    if(i==0){
                        System.out.println("*");
                    }else{
                        System.out.print("*");
                        int k=0;
                        while(k<i){
                            System.out.print(" ");
                            k++;
                        }
                        System.out.print("*");
                        k=0;
                        while(k<i){
                            System.out.print(" ");
                            k++;
                        }
                        System.out.println("*");
                    }
                    sp=sp-1;
                    i++;
                }
                
                sp=0;
                i=L/2;
                while (i>0){//second part of Phi
                    
                    if(i==1){
                        for(j=0;j<((L-1)/2)+1;j++){
                            System.out.print(" ");
                        }
                    }else{
                        //prints the spaces before the Phi
                        for(j=0;j<sp;j++){
                            System.out.print(" ");
                        }
                    }
                    //prints the stars "*" and the spaces
                    if(i==1){
                        System.out.println("*");
                    }else{
                        System.out.print("*");
                        int k=0;
                        while(k<i-1){
                            System.out.print(" ");
                            k++;
                        }
                        System.out.print("*");
                        k=0;
                        while(k<i-1){
                            System.out.print(" ");
                            k++;
                        }
                        System.out.println("*");
                    }
                    sp=sp+1;
                    i--;
                }
                
            }else if ( odd == 1){
                sp=spaces+1;
                while (i<(L/2)+1){//first part of Phi
                    
                    //prints the spaces before the f
                    for(j=0;j<sp;j++){
                        System.out.print(" ");
                    }
                    if(i==0){sp--;}
                    //prints the stars "*" and the spaces
                    if(i==0){
                        System.out.println("*");
                    }else{
                        System.out.print("*");
                        int k=0;
                        while(k<i){
                            System.out.print(" ");//prints spaces after the first *
                            k++;
                        }
                        System.out.print("*");//prints the second *
                        k=0;
                        while(k<i){
                            System.out.print(" ");//prints spaces after the second *
                            k++;
                        }
                        System.out.println("*");//prints the third *
                    }
                    sp=sp-1;
                    i++;//System.out.println("i="+i);
                }
                
                sp=1;
                i=L/2;
                while (i>0){//second part of Phi
                    
                    if(i==1){
                        for(j=0;j<((L-1)/2)+1;j++){
                            System.out.print(" ");
                        }
                    }else{
                        //prints the spaces before the Phi
                        for(j=0;j<sp;j++){
                            System.out.print(" ");
                        }
                    }
                    //prints the stars "*" and the spaces
                    if(i==1){
                        System.out.println("*");
                    }else{
                        System.out.print("*");
                        int k=0;
                        while(k<i-1){
                            System.out.print(" ");
                            k++;
                        }
                        System.out.print("*");
                        k=0;
                        while(k<i-1){
                            System.out.print(" ");
                            k++;
                        }
                        System.out.println("*");
                    }
                    sp=sp+1;
                    i--;
                }
            }
        }
    }
}




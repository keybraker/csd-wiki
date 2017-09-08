import java.util.Scanner;

public class DrawPhiB {
    private static Scanner keyboard;
    
    public static void main(String[] args) {
        keyboard = new Scanner(System.in);
        
        System.out.print("Enter an integer: ");
        int L = keyboard.nextInt();
        int odd,spaces;
        
        while(L>=4 && L<=30){
            
            odd = 1;spaces = 0;
            if ( L%2 == 0 ){
                odd = 0;//even
                spaces = ((L-1)/2)+1;
                
            }else{
                spaces = L/2;
            }
            
            int i=0,j=0;
            int sp=spaces;
            
            if(odd == 0){
                
                while (i<L/2){//first part of Phi
                    
                    //prints the spaces before the first *
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
                        //prints the spaces before the first *
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
                    
                    //prints the spaces before the first *
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
                
                sp=1;
                i=L/2;
                while (i>0){//second part of Phi
                    
                    if(i==1){
                        for(j=0;j<((L-1)/2)+1;j++){
                            System.out.print(" ");
                        }
                    }else{
                        //prints the spaces before the first *
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
            
            System.out.print("Enter an integer: ");
            L = keyboard.nextInt();
            
        }
    }
}






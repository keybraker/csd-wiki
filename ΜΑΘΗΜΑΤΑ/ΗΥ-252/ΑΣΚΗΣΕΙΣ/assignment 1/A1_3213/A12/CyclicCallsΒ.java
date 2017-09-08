package CyclicCallsB;
import java.util.Random;

public class CyclicCallsB {
    public static void main(String[] args) {
        
        m1(10);
        
    }
    
    public static void m1(int Number){
        
        System.out.println("m1 called with argument "+ Number);
        
        double random = new Random().nextDouble();
        System.out.println(random);
        
        double number = Number * random;
        double numbererase = number;
        
        while(numbererase>=0){
            numbererase--;
        }
        numbererase++;System.out.println("numbererase="+numbererase);
        
        if(numbererase>0.5){
            number++;
        }
        number -= numbererase;
        
        Number = (int) number;System.out.println("Number="+Number);
        if(Number == 9){
            System.out.println("ᕕ( ՞ ᗜ ՞ )ᕗ Bingo!");
            System.exit(0);
        }
        try {
            m2(Number);
        }catch (StackOverflowError e){
            System.out.println("\n ໒( • ͜ʖ • )७ : Error caught: "+e);
        }
        
    }
    
    public static void m2(int Number){
        
        System.out.println("m2 called with argument "+ Number);
        
        double random = new Random().nextDouble();
        System.out.println(random);
        
        double number = Number * random;
        double numbererase = number;
        
        while(numbererase>=0){
            numbererase--;
        }
        numbererase++;
        
        if(numbererase>0.5){
            number++;
        }
        number -= numbererase;
        
        Number = (int) number;
        if(Number == 9){
            System.out.println("ᕕ( ՞ ᗜ ՞ )ᕗ Bingo!");
            System.exit(0);
        }
        try {
            m1(10);
        }catch (StackOverflowError e){
            System.out.println("\n ໒( • ͜ʖ • )७ : Error caught: "+e);
        }
        
    }
}

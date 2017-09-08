package CyclicCalls;
import java.util.Random;

public class CyclicCalls {
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
        numbererase++;
        
        if(numbererase>0.5){
            number++;
        }
        number -= numbererase;
        
        Number = (int) number;
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
        try {
            m1(10);
        }catch (StackOverflowError e){
            System.out.println("\n ໒( • ͜ʖ • )७ : Error caught: "+e);
        }
    }
}

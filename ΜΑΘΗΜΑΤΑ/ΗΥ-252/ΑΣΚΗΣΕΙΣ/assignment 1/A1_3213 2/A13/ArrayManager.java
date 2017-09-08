package ArrayManager;

import org.jfugue.Player;

public class ArrayManager {
    
    public static void main(String[] args){
        
        int[] p1 =new int[20] ;
        int[] p2 =new int[20] ;
        
        fillRandom(50,120,p1);
        fillFrom(p2,p1);
        playMusic(p2);
        
    }
    
    static void fillRandom(int min, int max, int[] ar) {
        
        for (int i=0;i<ar.length;i++){
            
            //Random rand = new Random();
            //int n = rand.nextInt(max) + min;
            
            int n = min + (int)(Math.random() * ((max - min) + 1));
            
            ar[i]=n;
            
        }
        
    }
    
    static void fillFrom(int[] ar, int[] fromArr){
        
        if(ar.length != fromArr.length){
            System.out.println("Size of arrays is diffrent");
        }else{
            for (int i=0;i<ar.length;i++){
                ar[i] = fromArr[i];
            }
        }
        
    }
    
    static void playMusic(int[] ar){
        
        String music = "";
        Player player = new Player();
        for (int i=0;i<ar.length;i++){
            music += "["+ ar[i] +"] ";
        }
        player.play(music);
    }
    
}


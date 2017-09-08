/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gr.uoc.csd.hy252.a1.ask3;

import java.util.Random;
import org.jfugue.Player;

/**
 *
 * @author athineou
 */
public class ArrayManager {

    void fillRandom(int min, int max, int[] ar) {
        for (int i = 0; i < ar.length; i++) {
            Random rand = new Random();
            int n = rand.nextInt(max);
            if (n < min) {
                n = n + min;
            }
            ar[i] = n;
        }
    }

    void fillFrom(int[] ar, int[] fromArr) {
        if (ar.length != fromArr.length) {
            System.out.println("Error. Cannot fillFrom from arrays with different length.");
        } else {
            for (int i = 0; i < fromArr.length; i++) {
                ar[i] = fromArr[i];
            }
        }
    }

    void playMusic(int[] ar) {
        Player p = new Player();
        String par = "";
        for (int i = 0; i < ar.length; i++) {
            par = par + "[" + ar[i] + "] ";
        }
        //System.out.println("par = "+par);
        p.play(par);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        ArrayManager am = new ArrayManager();
        int[] p1 = new int[20];
        int[] p2 = new int[20];
        am.fillRandom(50, 120, p1);
        am.fillFrom(p2, p1);
        am.playMusic(p2);
    }
}

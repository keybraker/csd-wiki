/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gr.uoc.csd.hy252.a1.ask2;

import java.util.Random;

/**
 *
 * @author mbaritak
 */
public class CyclicCalls {

    public static void main(String[] args) {
        m1(10);
    }

    public static void m1(int i) {

        if (i == 9) {
            System.out.println("Bingo!");
            System.exit(0);
        }
        System.out.println("m1 called with argument " + i);
        int random = (int) Math.round(new Random().nextDouble() * 10);
        m2(random);

    }

    public static void m2(int i) {
        if (i == 9) {
            System.out.println("Bingo!");
            System.exit(0);
        }
        System.out.println("m2 called with argument " + i);
        m1(10);
    }
}

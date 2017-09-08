package gr.uoc.csd.hy252.a1.ask1;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import javax.swing.JOptionPane;

/**
 *
 * @author mbaritak
 */
public class DrawPhiwin2 {

    public static void main(String[] args) {

        int L = Integer.parseInt(JOptionPane.showInputDialog("Give me a number ", 4));

        int mid = (L / 2) + 1;
        String newl = "\n", phi = newl, sp = "  ";

        if (L >= 4 && L <= 30) {

            for (int j = 0; j < mid - 1; j++) {
                phi += sp;
            }

            phi += "1";
            phi += newl;

            int a = mid, b = L;


            if (L % 2 == 0) {
                a = mid - 1;
                b = L + 1;
            }


            for (int j = 2; j < a; j++) {
                for (int k = 0; k < mid - j; k++) {
                    phi += sp;
                }
                phi += j;

                for (int i = 0; i < j - 2; i++) {
                    phi += sp;
                }
                phi += j;

                for (int i = 0; i < j - 2; i++) {
                    phi += sp;
                }
                phi += j;

                phi += newl;
            }


            // ====

            if (L % 2 == 1) {
                for (int k = 0; k < 0; k++) {
                    phi += sp;
                }
                phi += mid;

                for (int i = 0; i < mid - 2; i++) {
                    phi += sp;
                }
                phi += mid;

                for (int i = 0; i < mid - 2; i++) {
                    phi += sp;
                }
                phi += mid;

                phi += newl;
            } else {

                for (int k = 0; k < 1; k++) {
                    phi += sp;
                }
                phi += mid;

                for (int i = mid; i > 3; i--) {
                    phi += sp;
                }
                phi += mid;

                for (int i = mid; i > 3; i--) {
                    phi += sp;
                }
                phi += mid;


                phi += newl;

            }


            // ====


            for (int j = mid + 1; j < b; j++) {
                for (int k = 0; k < j - mid; k++) {
                    phi += sp;
                }
                phi += j;

                for (int i = mid; i > j - mid + 2; i--) {
                    phi += sp;
                }
                phi += j;

                for (int i = mid; i > j - mid + 2; i--) {
                    phi += sp;
                }
                phi += j;


                phi += newl;
            }



            for (int j = 0; j < mid - 1; j++) {
                phi += sp;
            }

            phi += L;
            phi += newl;


        }

        JOptionPane.showMessageDialog(null, phi, "Output", JOptionPane.INFORMATION_MESSAGE);
    }
}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gr.uoc.csd.hy252.a1.ask5;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import javax.swing.JOptionPane;

/**
 *
 * @author Pavlos Fafalios
 */
public class encrypt {

    private static String filename;
    private static int K;

    public static void main(String[] args) throws FileNotFoundException, IOException {

        String number = null;
        if (args.length == 2) {
            filename = args[0];
            number = args[1];
        } else {
            File f = GraphicalFileLoaderSaver.openFile();
            filename = f.getAbsolutePath();
            number = JOptionPane.showInputDialog("Give a number", "");
        }

        try {
            K = Integer.parseInt(number);
        } catch (Exception e) {
            System.out.println("H deuterh parametros prepei na einai arithmos!");
            return;
        }

        System.out.println("# File: " + filename);
        System.out.println("# Number: " + K);

        boolean testResult = test();
        if (!testResult) {
            System.out.println("# The encryption has been aborted due to error in testing!");
            return;
        }


        System.out.println("# Start encrypting...");
        long startTimeB = System.nanoTime();
        Transform(filename, "Encrypted" + new File(filename).getName(), K);
        long endTimeB = System.nanoTime();
        long timeB = endTimeB - startTimeB;
        System.out.println("# Time for encryption: " + (double) timeB / 1000000 + " ms.");

    }

    private static boolean test() throws FileNotFoundException, IOException {

        String encrypted = "TEST_ENCRYPTED_" + new File(filename).getName();
        String decrypted = "TEST_DECRYPTED_" + new File(filename).getName();
        Transform(filename, encrypted, K);
        Transform(encrypted, decrypted, -K);

        /* 
         * Twra prepei na elenksoume ta periexomena tou arxikou arxeiou (filename) 
         * me ayta toy decrypted. 
         * Tha to kanoume auto swzontas ta bytes kathe arxeiou se diaforetika Strings
         * kai elegxontas sto telos an auta ta 2 strings einai idia.
         */

        /* READ BYTES OF INITIAL FILE */
        StringBuilder bytes1 = new StringBuilder();
        FileInputStream fis1 = new FileInputStream(filename);
        int b;
        while ((b = fis1.read()) != -1) {
            bytes1.append(b);
        }
        fis1.close();

        /* READ BYTES OF DECRYPTED FILE */
        StringBuilder bytes2 = new StringBuilder();
        FileInputStream fis2 = new FileInputStream(decrypted);
        int b2;
        while ((b2 = fis2.read()) != -1) {
            bytes2.append(b2);
        }
        fis2.close();

        /* DELETE THE TEST FILES */
        File file2del1 = new File(encrypted);
        file2del1.delete();
        File file2del2 = new File(decrypted);
        file2del2.delete();

        if (bytes1.toString().equals(bytes2.toString())) {
            System.out.println("# Testing was executed successfully! ");
            return true;
        } else {
            System.out.println("# Error in testing! The bytes of the decrypted file are not the same to those of the initial file! ");
            return false;
        }
    }

    static void Transform(String inputFileName, String outputFileName, int inputK) throws FileNotFoundException, IOException {
        Transform(new File(inputFileName), new File(outputFileName), inputK);
    }

    static void Transform(File inputFile, File outputFile, int inputK) throws FileNotFoundException, IOException {
        FileInputStream fis = new FileInputStream(inputFile);
        FileOutputStream fop = new FileOutputStream(outputFile);

        int content;
        while ((content = fis.read()) != -1) {
            fop.write(content + inputK);
        }

        fis.close();
        fop.flush();
        fop.close();
    }
}

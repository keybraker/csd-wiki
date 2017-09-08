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

/**
 *
 * @author Pavlos Fafalios
 */
public class encrypt_folder {

    public static void main(String[] args) throws FileNotFoundException, IOException {

        String folder = null;
        String number = null;

        if (args.length == 2) {
            folder = args[0];
            number = args[1];
        } else {
            System.out.println("Wrong number of arguments!");
            return;
        }

        int K;
        try {
            K = Integer.parseInt(number);
        } catch (Exception e) {
            System.out.println("H deuterh parametros prepei na einai arithmos!");
            return;
        }

        System.out.println("# Folder: " + folder);
        System.out.println("# Number: " + K);
        System.out.println("");

        encryptFolder(folder, K);



    }

    static void encryptFolder(String folderPath, int K) throws FileNotFoundException, IOException {
        for (File fileEntry : new File(folderPath).listFiles()) {
            if (fileEntry.isDirectory()) {
                encryptFolder(fileEntry.getAbsolutePath(), K);
            } else {
                System.out.println("# Start encrypting file: " + fileEntry.getAbsolutePath());
                long startTimeB = System.nanoTime();
                Transform(fileEntry.getAbsolutePath(), fileEntry.getParent() + "/Encrypted" + fileEntry.getName(), K);
                long endTimeB = System.nanoTime();
                long timeB = endTimeB - startTimeB;
                System.out.println("# Time for encryption: " + (double) timeB / 1000000 + " ms.");
                System.out.println("--------");
            }
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

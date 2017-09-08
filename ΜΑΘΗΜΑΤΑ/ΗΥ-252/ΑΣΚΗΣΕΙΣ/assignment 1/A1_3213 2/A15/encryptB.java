package encrypt;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;

public class encrypt {
	
	private static Scanner keyboard;
	public static void main(String[] args) throws IOException {
		
		//Reads file name
		keyboard = new Scanner(System.in);
		System.out.print("encrypt\nEnter an file name : ");
		String FileName = keyboard.next();
	
	    //Reads int K
		System.out.print("Enter an integer : ");
		int K = keyboard.nextInt();
		
		long startTime = System.nanoTime();
		
		//Creation of new file
		String NewFileName = "Encryptedmy"+FileName;
				
		//endryption class called
		System.out.println("\nTest, ended with: "+test(FileName, NewFileName, K));
		long endTime = System.nanoTime();
		long timeInNanosecs = endTime - startTime;

		System.out.println("Runtime : "+timeInNanosecs+" (ns)");
		
	}
	
	static void Transform(String inputFileName, String outputFileName, int inputK) throws IOException{
		
		FileInputStream in = null;
        FileOutputStream out = null;
        
        try {
            in = new FileInputStream(inputFileName);
            out = new FileOutputStream(outputFileName);
            int c;

            while ((c = in.read()) != -1) {
                out.write(c+inputK);
            }
        } finally {
            if (in != null) {
                in.close();
            }
            if (out != null) {
                out.close();
            }
        }
	}

	static boolean test(String inputFileName, String outputFileName, int inputK) throws IOException{
		
		//Creation of new fileName
		String decryptedoutputFileName = "Encryptedmy"+outputFileName;
		
		Transform(inputFileName, outputFileName, inputK);
		Transform(outputFileName, decryptedoutputFileName, -inputK);
		
		FileInputStream one = null;
		FileInputStream two = null;
		
        try {
        	
            one = new FileInputStream(inputFileName);
            two = new FileInputStream(decryptedoutputFileName);
            int c1,c2;
            String str1="",str2="";
            
            while ((c1 = one.read()) != -1) {
                str1 += c1;
            }
            while ((c2 = two.read()) != -1) {
            	str2 += c2;
            }
            if (str1.equals(str2)){
        		return(true);
            }
            
        } finally {
            if (one != null) {
                one.close();
            }
            if (two != null) {
                two.close();
            }
        }
        return(false);
	}
	
}

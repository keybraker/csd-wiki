package encrypt;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
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
		
		//Creation of new file Name
		String NewFileName = "Encryptedmy"+FileName;
				
		//endryption class called
		Transform(FileName, NewFileName, K);
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

            if (in != null) {
                in.close();
            }
            if (out != null) {
                out.close();
            }
        }
            catch(FileNotFoundException ex) {
                System.out.println(ex);
            }
            catch(IOException ex) {
                System.out.println(ex);
                // Or we could just do this:
                // ex.printStackTrace();
            }
            
        }
        
    }

}

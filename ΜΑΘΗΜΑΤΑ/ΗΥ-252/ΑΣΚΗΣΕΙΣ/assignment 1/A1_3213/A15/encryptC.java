package encrypt;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class encrypt {
	static File file;
	public static void main(String[] args) throws IOException {

		int K = 0;

		String FilePath = null;
		String FileName = null;
		String AbsoluteFilePath = null;
		String EncryptedFilePath = null;
		
		JFileChooser fileChooser = new JFileChooser(); 
		fileChooser.setDialogTitle("Select a file");
		int userSelection = fileChooser.showSaveDialog(null); 
		if (userSelection == JFileChooser.APPROVE_OPTION) {
			
			file = fileChooser.getSelectedFile();
			
			AbsoluteFilePath = file.getAbsolutePath(); 
			FilePath = file.getParent();
			FileName = file.getName();
					
		 	EncryptedFilePath = FilePath+FileName;
		 	
		}
		
	    JOptionPane.showMessageDialog(null,
			"Enter integer: ", "inp ut window",
			JOptionPane.INFORMATION_MESSAGE);
	    K = Integer.parseInt(JOptionPane.showInputDialog(
			"Enter an integer : ",""));
	    
	    long startTime = System.nanoTime();
	    
		System.out.println("Test, ended with: "+test(FilePath,FileName,K));
		
		long endTime = System.nanoTime();
		long timeInNanosecs = endTime - startTime;

		System.out.println("Runtime : "+timeInNanosecs+" (ns)");
		
	}
	
	static void Transform(String inputFilePath, String outputFilePath, int inputK) throws IOException{

		File inputFileTypePath = new File(inputFilePath);
		File outputFileTypePath = new File(outputFilePath);

		Transform2(inputFileTypePath,outputFileTypePath,inputK);
		
	}

	static void Transform2(File inputFilePath, File outputFilePath, int inputK) throws IOException{
			
			FileInputStream in = null;
	        FileOutputStream out = null;
	        
	        try {
	            in = new FileInputStream(inputFilePath);
	            out = new FileOutputStream(outputFilePath);
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

	static boolean test(String inputFilePath, String outputFilePath, int inputK)throws IOException{
		
		//Creation of new FilePath
		String encryptionoutputFilePath = inputFilePath+"/Encryptedmy"+outputFilePath;
		String decryptedoutputFilePath = inputFilePath+"/EncryptedmyEncryptedmy"+outputFilePath;
		String Filename = inputFilePath+"/"+outputFilePath;
		
		Transform(Filename, encryptionoutputFilePath, inputK);
		Transform(encryptionoutputFilePath, decryptedoutputFilePath, -inputK);
		
		FileInputStream one = null;
		FileInputStream two = null;
		
        try {
        	
            one = new FileInputStream(Filename);
            two = new FileInputStream(decryptedoutputFilePath);
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

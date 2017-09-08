package TextFiletoWebpage;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Scanner;

public class TextFiletoWebpage {
    
    private static Scanner keyboard;
    private static String line = "";
    
    public static void main(String[] args) {
        
        keyboard = new Scanner(System.in);
        System.out.print("Enter an file name : ");
        String name = keyboard.next();
        
        String fileName = name;
        int lengthOfname = name.length();
        char[] namenew = name.toCharArray();
        name ="";
        
        for(int i=0;i<lengthOfname-4;i++){
            name += namenew[i];
        }
        
        try {
            
            FileReader fileReader = new FileReader(fileName);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            System.out.println("\nfile, " + fileName + " found. ");
            System.out.println("file opened : " + fileName + "\n");
            
            //-------------------------------
            
            File file = new File(name+".html");
            System.out.println("file created : "+name+".html");
            
            FileOutputStream fos = new FileOutputStream(file);
            BufferedWriter new_file = new BufferedWriter(new OutputStreamWriter(fos));
            
            //-------------------------------
            
            new_file.write("<!DOCTYPE html> <html>\n<head>\n<meta http-equiv="
                           + "\"content-type\" content=\"text/html;charset=utf-8\" /> "
                           + "<title>\n"+name+".html"+"\n</title>\n</head>\n<body>");
            
            String data = "";
            long startTime = System.nanoTime();
            while((line = bufferedReader.readLine()) != null) {
                data += line;
           	}
            int length = data.length() ;
            
            char[] charArray = data.toCharArray();
            for(int i=0;i<length;i++){
                
                if(if_greek(charArray[i]) != null){
                    new_file.write(if_greek(charArray[i]));
                }else{
                    if (charArray[i] == '\n'){
                        new_file.write("<br />");
                    }else if(charArray[i] == '\t'){
                        new_file.write("￼&nbsp;￼￼");
                    }else if(charArray[i] == '>'){
                        new_file.write("￼&gt;￼￼");
                    }else if(charArray[i] == '<'){
                        new_file.write("￼ltt;￼￼");
                    }else if(charArray[i] == '&'){
                        new_file.write("￼&amp;￼￼");
                    }else{
                        new_file.write(charArray[i]);
                    }
                }
            }
            new_file.write("</body>\n</html>");
            System.out.println("file, "+name+".html" + ", filled.");
            
            long endTime = System.nanoTime();
            long timeInNanosecs = endTime-startTime;
            
            System.out.println("file, "+name+".html" + ", filled.\n");
            System.out.println("Conversion took: "+timeInNanosecs+" (ns)\n");
            
            bufferedReader.close();  System.out.println("file closed : "+fileName);
            new_file.close();  System.out.println("file closed : "+name+".html");
            
        }
        catch(FileNotFoundException ex) {
            System.out.println(
                               "Unable to open file '" +
                               fileName + "'");
        }
        catch(IOException ex) {
            System.out.println(
                               "Error reading file '"
                               + fileName + "'");
            // Or we could just do this:
            // ex.printStackTrace();
        }
        
    }
    
    private static String if_greek(char c) {
        
        char[] GREEK_GREEK = {'Α','Β','Γ','Δ','Ε','Ζ','Η','Θ','Ι','Κ',
            'Λ','Μ','Ν','Ξ','Ο','Π','Ρ','Σ','Τ','Υ','Φ','Χ','Ψ','Ω'};
        String[] GREEK_ENGLISH = {"A","V","G","D","E","Z","H","8","I","K",
            "L","M","N","KS","O","P","R","S","T","Y","F","X","PS","W"};
        
        char[] GREEK_GREEK_SMALL = {'α','β','γ','δ','ε','ζ','η','θ','ι','κ',
            'λ','μ','ν','ξ','ο','π','ρ','σ','ς','τ','υ','φ','χ','ψ','ω'};
        String[] GREEK_ENGLISH_SMALL = {"a","v","g","d","e","z","h","8","i",
            "k","l","m","n","ks","o","p","r","s","s","t","y","f","x","ps","w"};
        
        char[] GREEK_EXTRAS = {'ά','έ','ύ','ί','ό','Ά','Έ','Ύ','Ί','Ό'};
        String[] ENGLISH_EXTRAS = {"a'","e'","u'","i'","o'","A'","E'","Y'","I'","O'"};
        
        for (int i=0 ; i<24 ; i++ ){
            if ( GREEK_GREEK[i] == c ){
                return GREEK_ENGLISH[i];
            }
        }
        for (int  i=0 ; i<24 ; i++ ){
            if ( GREEK_GREEK[i] == c ){
                return GREEK_ENGLISH[i];
            }
        }
        for (int i=0 ; i<24 ; i++ ){
            if ( GREEK_GREEK_SMALL[i] == c ){
                return GREEK_ENGLISH_SMALL[i];
            }
        }
        for (int  i=0 ; i<24 ; i++ ){
            if ( GREEK_GREEK_SMALL[i] == c ){
                return GREEK_ENGLISH_SMALL[i];
            }
        }
        for (int  i=0 ; i<10 ; i++ ){
            if ( GREEK_EXTRAS[i] == c ){
                return ENGLISH_EXTRAS[i];
            }
        }
        return null;
        
        
    }
    
}

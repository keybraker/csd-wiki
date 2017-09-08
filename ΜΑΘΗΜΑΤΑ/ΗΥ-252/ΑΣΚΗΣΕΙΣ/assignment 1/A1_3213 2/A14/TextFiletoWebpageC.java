package TextFiletoWebpage;//http://users.ics.forth.gr/~fafalios/Lysistrata.txt

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.util.Scanner;

public class TextFiletoWebpage {
    
    private static Scanner keyboard;
    //private static String line = "";
    
    public static void main(String[] args) throws UnsupportedEncodingException, IOException {
        
        keyboard = new Scanner(System.in);
        System.out.print("Enter an URL : ");
        String name = keyboard.next();
        System.out.println("name: "+name);
        try {
            
            File file = new File("UrlOutput.html");
            System.out.println("file created : UrlOutput.html");
            
            FileOutputStream fos = new FileOutputStream(file);
            BufferedWriter new_file = new BufferedWriter(new OutputStreamWriter(fos));
            
            long startTime = System.nanoTime();
            
            new_file.write("<!DOCTYPE html> <html>\n<head>\n<meta http-equiv="
                           + "\"content-type\" content=\"text/html;charset=utf-8\" /> "
                           + "<title>\nUrlOutput.html\n</title>\n</head>\n<body>");
            
            URL url = new URL(name);
            BufferedReader in = new BufferedReader(new InputStreamReader(url.openStream(), "UTF-8"));
            int c = in.read();
            
            
            while (c != -1) {
                
                if(if_greek((char) c) != null){
                    new_file.write(if_greek((char) c));
                }else{
                    if (c == '\n'){
                        new_file.write("<br />");
                    }else if(c == '\t'){
                        new_file.write("￼&nbsp;￼￼");
                    }else if(c == '>'){
                        new_file.write("￼&gt;￼￼");
                    }else if(c == '<'){
                        new_file.write("￼ltt;￼￼");
                    }else if(c == '&'){
                        new_file.write("￼&amp;￼￼");
               	   	}else{
                        new_file.write(c);
               	   	}
                }
                
                c = in.read();
            }
            in.close();
            new_file.write("</body>\n</html>");
            System.out.println("file, "+name+".html" + ", filled.");
            
            long endTime = System.nanoTime();
            long timeInNanosecs = endTime-startTime;
            
            System.out.println("file, "+name+".html" + ", filled.\n");
            System.out.println("Conversion took: "+timeInNanosecs+" (ns)\n");
            
            //bufferedReader.close();  System.out.println("file closed : "+fileName);
            new_file.close();  System.out.println("file closed : "+name+".html");
            
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

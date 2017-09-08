import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.BufferedWriter;

public class DrawPhiHtml {
    public static void main(String[] args) {
        
        String text = "<!DOCTYPE html>\n"+"<html>\n"+"<head>\n"+"<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />\n"+"</head>\n"+"<body>\n"
        +"<p style=\"font-size:K*10%\" align=\"center\">Φ</p>\n"+"</body>\n"+"</html>\n";
        
        try {
            
            File file = new File("PhiK.html");
            FileOutputStream fos = new FileOutputStream(file);
            
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
            
            bw.write(text);
            bw.close();
            
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }
}






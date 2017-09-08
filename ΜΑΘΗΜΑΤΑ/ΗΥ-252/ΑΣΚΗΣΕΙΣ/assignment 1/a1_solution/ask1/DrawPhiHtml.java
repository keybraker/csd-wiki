package gr.uoc.csd.hy252.a1.ask1;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author mbaritak
 */
public class DrawPhiHtml {

    public static void main(String[] args) throws IOException {

        int L = Integer.parseInt(args[0]);

        String text = "<!DOCTYPE html>\n"
                + "<html>\n"
                + "<head>\n"
                + "<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />\n"
                + "</head\n"
                + "<body>\n"
                + "\n"
                + "<p style=\"font-size:" + (L * 10) + "%\" align=\"center\">Φ</p>\n"
                + "\n"
                + "</body>\n"
                + "</html>";


        File html = new File("PhiK.html");
        FileWriter fw = new FileWriter(html);
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write(text);
        bw.close();

    }
}

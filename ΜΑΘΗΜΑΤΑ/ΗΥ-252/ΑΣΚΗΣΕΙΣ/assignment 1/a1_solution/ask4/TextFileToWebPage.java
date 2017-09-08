/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gr.uoc.csd.hy252.a1.ask4;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.io.Writer;
import java.net.URL;

/**
 *
 * @author Pavlos Fafalios
 */
public class TextFileToWebPage {

    private static StringBuilder html1;
    private static StringBuilder html2;
    private static StringBuilder html3;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws UnsupportedEncodingException, FileNotFoundException, IOException {

        long startTime = System.nanoTime();
        /* Initialize the HTML template parts */
        html1 = new StringBuilder();
        html1.append("<!DOCTYPE html>\n");
        html1.append("<html>\n");
        html1.append("  <head>\n");
        html1.append("    <meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />\n");
        html1.append("    <title>\n");

        html2 = new StringBuilder();
        html2.append("    </title>\n");
        html2.append("  </head>\n");
        html2.append("  <body>\n");

        html3 = new StringBuilder();
        html3.append("  </body>\n");
        html3.append("</html>");

        //String path = "Lysistrata.txt";
        String path = "http://users.ics.forth.gr/~fafalios/Lysistrata.txt";
        if (args.length == 1) { // If argument is given, use it
            path = args[0];
        }


        if (path.toLowerCase().startsWith("http://") || path.toLowerCase().startsWith("https://")) {
            URL u = new URL(path);
            BufferedReader in = new BufferedReader(new InputStreamReader(u.openStream(), "UTF-8"));
            String fileName = path.substring(path.lastIndexOf("/") + 1);
            createHTML(in, fileName);
        } else {
            BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(path), "UTF8"));
            String fileName = new File(path).getName();
            createHTML(in, fileName);
        }

        long endTime = System.nanoTime();
        long timeInNanosecs = endTime - startTime;
        double timeInMilliseconds = (double) timeInNanosecs / 1000000.0;
        System.out.println("Time creating the HTML file (in ms): " + timeInMilliseconds);

    }

    public static void createHTML(BufferedReader in, String filename) throws UnsupportedEncodingException, FileNotFoundException, IOException {
        File fileToWrite = new File(filename + ".html");
        Writer out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(fileToWrite), "UTF8"));


        out.append(html1);
        out.append(filename);
        out.append(html2);

        int c = in.read();
        while (c != -1) {
            out.append(getMatching((char) c));
            c = in.read();
        }
        out.append(html3);
        out.flush();
        out.close();
        in.close();
    }

    private static String getMatching(char c) {
        if (c == '\n') {
            return "<br />";
        } else if (c == ' ' || c == '\t') {
            return "&nbsp;";
        } else if (c == '>') {
            return "&gt;";
        } else if (c == '<') {
            return "&lt;";
        } else if (c == '&') {
            return "&amp;";
        } else if (c == 'α') {
            return "a";
        } else if (c == 'ά') {
            return "a";
        } else if (c == 'β') {
            return "b";
        } else if (c == 'γ') {
            return "g";
        } else if (c == 'δ') {
            return "d";
        } else if (c == 'ε') {
            return "e";
        } else if (c == 'έ') {
            return "e";
        } else if (c == 'ζ') {
            return "z";
        } else if (c == 'η') {
            return "h";
        } else if (c == 'ή') {
            return "h";
        } else if (c == 'θ') {
            return "th";
        } else if (c == 'ι') {
            return "i";
        } else if (c == 'ί') {
            return "i";
        } else if (c == 'κ') {
            return "k";
        } else if (c == 'λ') {
            return "l";
        } else if (c == 'μ') {
            return "m";
        } else if (c == 'ν') {
            return "n";
        } else if (c == 'ξ') {
            return "ks";
        } else if (c == 'ο') {
            return "o";
        } else if (c == 'ό') {
            return "o";
        } else if (c == 'π') {
            return "p";
        } else if (c == 'ρ') {
            return "r";
        } else if (c == 'σ') {
            return "s";
        } else if (c == 'ς') {
            return "s";
        } else if (c == 'τ') {
            return "t";
        } else if (c == 'υ') {
            return "u";
        } else if (c == 'ύ') {
            return "u";
        } else if (c == 'φ') {
            return "f";
        } else if (c == 'χ') {
            return "ch";
        } else if (c == 'ψ') {
            return "ps";
        } else if (c == 'ω') {
            return "w";
        } else if (c == 'ώ') {
            return "w";
        } else if (c == 'Α') {
            return "A";
        } else if (c == 'Β') {
            return "B";
        } else if (c == 'Γ') {
            return "G";
        } else if (c == 'Δ') {
            return "D";
        } else if (c == 'Ε') {
            return "E";
        } else if (c == 'Ζ') {
            return "Z";
        } else if (c == 'Η') {
            return "H";
        } else if (c == 'Θ') {
            return "TH";
        } else if (c == 'Ι') {
            return "I";
        } else if (c == 'Κ') {
            return "K";
        } else if (c == 'Λ') {
            return "L";
        } else if (c == 'Μ') {
            return "M";
        } else if (c == 'Ν') {
            return "N";
        } else if (c == 'Ξ') {
            return "KS";
        } else if (c == 'Ο') {
            return "O";
        } else if (c == 'Π') {
            return "P";
        } else if (c == 'Ρ') {
            return "R";
        } else if (c == 'Σ') {
            return "S";
        } else if (c == 'Τ') {
            return "T";
        } else if (c == 'Υ') {
            return "Y";
        } else if (c == 'Φ') {
            return "F";
        } else if (c == 'Χ') {
            return "CH";
        } else if (c == 'Ψ') {
            return "PS";
        } else if (c == 'Ω') {
            return "W";
        } else {
            return String.valueOf((char) c);
        }

    }
}

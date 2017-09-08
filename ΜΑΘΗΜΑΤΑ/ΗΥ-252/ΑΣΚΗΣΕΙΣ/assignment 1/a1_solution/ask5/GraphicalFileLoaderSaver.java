/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gr.uoc.csd.hy252.a1.ask5;

import javax.swing.JFileChooser;
import java.io.File;
import javax.swing.*;

public class GraphicalFileLoaderSaver {

    static final JFileChooser fc = new JFileChooser();

    public static File openFile() {
        File fileToreturn = null;

        fc.setAcceptAllFileFilterUsed(true);
        //fc.addChoosableFileFilter(new MyFileSlectionFilter());

        int returnVal = fc.showOpenDialog(null);

        String statusStr;
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            fileToreturn = fc.getSelectedFile();
            //This is where a real application would open the file.
            //log.append("Opening: " + file.getName() + "." + newline);
            statusStr = "Opening: " + fileToreturn.getName();
        } else {
            //log.append("Open command cancelled by user." + newline);
            statusStr = "Open command cancelled by user.";
        }

        System.out.println(statusStr);
        return fileToreturn;

    }

    static public File saveFile() {
        int rVal = fc.showSaveDialog(null);
        if (rVal == JFileChooser.APPROVE_OPTION) {
            //filename.setText(c.getSelectedFile().getName());
            //dir.setText(c.getCurrentDirectory().toString());
            File fileToreturn = fc.getSelectedFile();
            //return fileToreturn; // Xwris comment auth h grammh einai ok apla den elegxei an yparxei


            if ((fileToreturn != null) && fileToreturn.exists()) {
                int response = JOptionPane.showConfirmDialog(null,
                        "The file " + fileToreturn.getName()
                        + " already exists. Do you want to replace the existing file?",
                        "Ovewrite file", JOptionPane.YES_NO_OPTION,
                        JOptionPane.WARNING_MESSAGE);
                if (response != JOptionPane.YES_OPTION) {
                    return null;
                }
            }
            return fileToreturn;


            //This is where a real application would open the file.
            //log.append("Opening: " + file.getName() + "." + newline);
            //statusStr = "Opening: " + fileToreturn.getName();
        }
        if (rVal == JFileChooser.CANCEL_OPTION) {
            //filename.setText("You pressed cancel");
            //dir.setText("");
        }
        return null;
    }

    // voithitiki
    public static String getExtension(File f) {
        String ext = null;
        String s = f.getName();
        int i = s.lastIndexOf('.');

        if (i > 0 && i < s.length() - 1) {
            ext = s.substring(i + 1).toLowerCase();
        }
        return ext;
    }
}
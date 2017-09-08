import javax.swing.JOptionPane;

public class DrawPhiwin {
    public static void main(String[] args) {
        
        JOptionPane.showMessageDialog(null,
                                      "Enter integer: ", "input window",
                                      JOptionPane.INFORMATION_MESSAGE);
        int L = Integer.parseInt(JOptionPane.showInputDialog(
                                                             "Give me a number ",4));
        
        int odd,sp;
        
        while(L>=4 && L<=30){
            
            String line1="";
            odd = 1;sp = 0;
            if ( L%2 == 0 ){
                odd = 0;//even
                sp = L/2;
                
            }else{
                odd = 1;
                sp = L/2;
            }
            //System.out.println("L="+L+",odd= "+odd);
            int i=0,j=0;
            
            if(odd == 0){
                
                while (i<L/2){//first part of Phi
                    
                    //prints the sp before the first *
                    for(j=0;j<sp;j++){
                        line1+=" ";
                    }
                    if(i==0){sp--;}
                    //prints the stars "*" and the sp
                    if(i==0){
                        line1+="*\n";
                    }else{
                        line1+="*";
                        int k=0;
                        while(k<i){
                            line1+=" ";
                            k++;
                        }
                        line1+="*";
                        k=0;
                        while(k<i){
                            line1+=" ";
                            k++;
                        }
                        line1+="*\n";
                    }
                    sp=sp-1;
                    i++;//System.out.println("i="+i);
                }
                
                sp=0;
                i=L/2;
                while (i>0){//second part of Phi
                    
                    if(i==1){
                        for(j=0;j<((L-1)/2)+1;j++){
                            line1+=" ";
                        }
                    }else{
                        //prints the sp before the first *
                        for(j=0;j<sp;j++){
                            line1+=" ";
                        }
                    }
                    //prints the stars "*" and the sp
                    if(i==1){
                        line1+="*\n";
                    }else{
                        line1+="*";
                        int k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+="*";
                        k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+="*\n";
                    }
                    sp=sp+1;
                    i--;
                }
                
            }else if ( odd == 1){//even
                
                sp=sp+1;
                while (i<(L/2)+1){//first part of Phi
                    
                    //prints the sp before the first *
                    for(j=0;j<sp;j++){
                        line1+=" ";
                    }
                    if(i==0){sp--;}
                    //prints the stars "*" and the sp
                    if(i==0){
                        line1+="*\n";
                    }else{
                        line1+="*";
                        int k=0;
                        while(k<i){
                            line1+=" ";
                            k++;
                        }
                        line1+="*";
                        k=0;
                        while(k<i){
                            line1+=" ";
                            k++;
                        }
                        line1+="*\n";
                    }
                    sp=sp-1;
                    i++;//System.out.println("i="+i);
                }
                
                sp=1;
                i=L/2;
                while (i>0){//second part of Phi
                    
                    if(i==1){
                        for(j=0;j<((L-1)/2)+1;j++){
                            line1+=" ";
                        }
                    }else{
                        //prints the sp before the first *
                        for(j=0;j<sp;j++){
                            line1+=" ";
                        }
                    }
                    //prints the stars "*" and the sp
                    if(i==1){
                        line1+="*\n";
                    }else{
                        line1+="*";
                        int k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+="*";
                        k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+="*\n";
                    }
                    sp=sp+1;
                    i--;
                }
            }
            
            JOptionPane.showMessageDialog(null,
                                          line1, "output",
                                          JOptionPane.INFORMATION_MESSAGE);
            
            JOptionPane.showMessageDialog(null,
                                          "Enter integer: ", "input window",
                                          JOptionPane.INFORMATION_MESSAGE);
            L = Integer.parseInt(JOptionPane.showInputDialog(
                                                             "Give me a number ",4));
            
        }
    }
}






import javax.swing.JOptionPane;

public class DrawPhiwin2 {
    public static void main(String[] args) {
        
        JOptionPane.showMessageDialog(null,
                                      "Enter integer: ", "input window",
                                      JOptionPane.INFORMATION_MESSAGE);
        int L = Integer.parseInt(JOptionPane.showInputDialog(
                                                             "Give me a number ",4));
        System.out.println(L+"/2 = "+L/2);
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
            int i=0,j=0,number=1;
            
            if(odd == 0){//even
                
                while (i<L/2){//first part of Phi
                    
                    //prints the sp before the first *
                	if(i==0){
                		for(j=0;j<sp+4;j++){
                            line1+=" ";
                        }
                	}else{
	                    for(j=0;j<sp+1;j++){
	                        line1+=" ";
	                    }
                	}
                    if(i==0){sp--;}
                    //prints the stars "*" and the sp
                    if(i==0){
                        line1+=number+"\n";
                    }else if(number<10){//////////////////////////////////
                    	line1+=number;
                        int k=0;
                        while(k<i+2){
                            line1+=" ";
                            k++;
                        }
                        line1+=number;
                        k=0;
                        while(k<i+2){
                            line1+=" ";
                            k++;
                        }
                        line1+=number+"\n";
                    }else{///////////////////////////////////////////////
                        line1+=number;
                        int k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+=number;
                        k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+=number+"\n";
                    }
                    sp=sp-1; number++;
                    i++;//System.out.println("i="+i);
                }
                
                sp=0;
                i=L/2;
                while (i>0){//second part of Phi
                    
                    if(i==1){
                        for(j=0;j<((L-1)/2)+4;j++){
                            line1+=" ";
                        }
                    }else if(number>9){
                    	for(j=0;j<sp;j++){
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
                        line1+=number+"\n";
                    }else if(number<10){//////////////////////////////////
                    	line1+=number;
                        int k=0;
                        while(k<i+2){
                            line1+=" ";
                            k++;
                        }
                        line1+=number;
                        k=0;
                        while(k<i+2){
                            line1+=" ";
                            k++;
                        }
                        line1+=number+"\n";
                    }else{///////////////////////////////////////////////
                        line1+=number;
                        int k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+=number;
                        k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+=number+"\n";
                    }
                    sp=sp+1; number++;
                    i--;
                }
                
            }else if ( odd == 1){//odd
                
                sp=sp+1;
                while (i<(L/2)+1){//first part of Phi
                    
                    //prints the sp before the first *
                	if(i==0){
                		for(j=0;j<sp+4;j++){
                            line1+=" ";
                        }
                	}else{
	                    for(j=0;j<sp+1;j++){
	                        line1+=" ";
	                    }
                	}
                    if(i==0){sp--;}
                    //prints the stars "*" and the sp
                    if(i==0){
                        line1+=number+"\n";
                    }else if(number<10){//////////////////////////////////
                    	line1+=number;
                        int k=0;
                        while(k<i+2){
                            line1+=" ";
                            k++;
                        }
                        line1+=number;
                        k=0;
                        while(k<i+2){
                            line1+=" ";
                            k++;
                        }
                        line1+=number+"\n";
                    }else{///////////////////////////////////////////////
                        line1+=number;
                        int k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+=number;
                        k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+=number+"\n";
                    }
                    sp=sp-1; number++;
                    i++;//System.out.println("i="+i);
                }
                
                sp=1;
                i=L/2;
                while (i>0){//second part of Phi
                    
                    if(i==1){
                        for(j=0;j<((L-1)/2)+4;j++){
                            line1+=" ";
                        }
                    }else if(number>9){
                    	for(j=0;j<sp;j++){
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
                        line1+=number+"\n";
                    }else if(number<10){//////////////////////////////////
                    	line1+=number;
                        int k=0;
                        while(k<i+2){
                            line1+=" ";
                            k++;
                        }
                        line1+=number;
                        k=0;
                        while(k<i+2){
                            line1+=" ";
                            k++;
                        }
                        line1+=number+"\n";
                    }else{///////////////////////////////////////////////
                        line1+=number;
                        int k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+=number;
                        k=0;
                        while(k<i-1){
                            line1+=" ";
                            k++;
                        }
                        line1+=number+"\n";
                    }
                    sp=sp+1; number++;
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






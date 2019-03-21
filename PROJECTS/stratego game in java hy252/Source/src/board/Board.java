package board;

public class Board {
	
    private int[][] board;

    public Board(){
    	this.board = new int[8][10];
    }
    
    public int getValue(int x, int y){
		return this.board[x][y];
    }
    
    public void add(int x, int y, int value){
	    this.board[x][y] = value;
    }
    
    public void printBoard(){
    	System.out.print("   ");
    	for(int p=0;p<10;p++){	
    		System.out.print(" "+p+") ");
    	}
    	System.out.print("\n");
    	for(int i=0;i<8;i++){	
    		System.out.print(i+") ");
        	for(int p=0;p<10;p++){	
        		System.out.print("["+this.board[i][p]+"]");
        	}
        	System.out.println();
    	}
    	System.out.println();
    }
    
}

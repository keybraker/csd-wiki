package deck;

/**
 * This class creates a new Collection of this.cards.
 * @version 1.0
 * @author Ioannis Tsiakkas
 */
public class Deck 
{
    private int[][] cards;
    
    public Deck(String color)
    {
        
    	this.cards = new int[12][2];
        
        if(color == "BLUE"){
        	
    		this.cards[0][0] = 30;
    		this.cards[1][0] = 31;
    	    this.cards[2][0] = 32;
    	    this.cards[3][0] = 33;
    	    this.cards[4][0] = 34;
    	    this.cards[5][0] = 35;
    	    this.cards[6][0] = 36;
    	    this.cards[7][0] = 37;
    	    this.cards[8][0] = 38;
    	    this.cards[9][0] = 39;
    	    this.cards[10][0] = 40;
    	    this.cards[11][0] = 41;
        	    
    	    this.cards[0][1] = 7;
    		this.cards[1][1] = 10;
    	    this.cards[2][1] = 3;
    	    this.cards[3][1] = 4;
    	    this.cards[4][1] = 0;
    	    this.cards[5][1] = 8;
    	    this.cards[6][1] = 5;
    	    this.cards[7][1] = 9;
    	    this.cards[8][1] = 2;
    	    this.cards[9][1] = 1;
    	    this.cards[10][1] = 6;
    	    this.cards[11][1] = 11;
    	    
    	}else{
    		
    		this.cards[0][0] = 10;
    		this.cards[1][0] = 11;
    	    this.cards[2][0] = 12;
    	    this.cards[3][0] = 13;
    	    this.cards[4][0] = 14;
    	    this.cards[5][0] = 15;
    	    this.cards[6][0] = 16;
    	    this.cards[7][0] = 17;
    	    this.cards[8][0] = 18;
    	    this.cards[9][0] = 19;
    	    this.cards[10][0] = 20;
    	    this.cards[11][0] = 21;
    	    
    	    this.cards[0][1] = 7;
    		this.cards[1][1] = 10;
    	    this.cards[2][1] = 3;
    	    this.cards[3][1] = 4;
    	    this.cards[4][1] = 0;
    	    this.cards[5][1] = 8;
    	    this.cards[6][1] = 5;
    	    this.cards[7][1] = 9;
    	    this.cards[8][1] = 2;
    	    this.cards[9][1] = 1;
    	    this.cards[10][1] = 6;
    	    this.cards[11][1] = 11;
    	    
    	}
    }   
    
    public int getValue(int Character){
    	for(int i = 0; i< 12; i++){
			if (this.cards[i][0] == Character){
				return this.cards[i][1];
			}
		}
    	return -2;
    }
    
    public boolean isEmpty()
    {
    	int i = 0;
    	while(i<12){
    		if(this.cards[i][0] != 0){
            	return false;
    		}
    	}
        return true;
    }
    
    public void addCard(int i)
    {
    	this.cards[i][1]++;
    }   
    
    public void removeCard(int i)
    {
    	if(this.cards[i][1] != 0){
    		this.cards[i][1]--;
    	}
    }
    
    public int size()
    {
    	int i = 0,count=0;
    	while(i<12){
    		if(this.cards[i][0] != 0){
    			count++;
    		}
    	}
    	return count;
    }
   
}
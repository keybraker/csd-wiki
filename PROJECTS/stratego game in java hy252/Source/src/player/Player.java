package player;

import deck.Deck;

/**
 * Player class describes the characteristics of a player
 * and provides modification methods. 
 * @author Ioannis Tsiakkas
 */
public class Player 
{
	private int ID;
		
	private Deck charactersAlive,charactersDead;
    
    private boolean hasPlayed;
   
    public Player(int ID)
    { 
		this.ID = ID;
    	
    	this.charactersAlive = new Deck("BLUE");
        this.charactersDead  = new Deck("BLUE");
                
        this.hasPlayed = false;
    }
   
    public void setID(int ID) {
		this.ID = ID;
    }
    
    public int getID(){
		return ID;
	}
	
    public void reviveCharacter(int i)
    {
        this.charactersAlive.addCard(i);
        this.charactersDead.removeCard(i);
    }
    
    public void removeCharacter(int i)
    {
        this.charactersAlive.removeCard(i);
        this.charactersDead.addCard(i);
    }
  
    public boolean getPlayed()
    {
 	   return this.hasPlayed;
    }
    
    public void setPlayed()
    {
    	this.hasPlayed = true;
    }

    public boolean isDead()
    {
	   if(this.charactersAlive.isEmpty() == true){
		   return true;
	   }else{
		   return false;
	   }
    }

}


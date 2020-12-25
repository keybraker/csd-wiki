package turn;

/**
 * This class represents the turn of the game
 * @author Ioannis Tsiakkas
 */
public class Turn 
{
    private int currentID;
    private int numberOfRounds;
    
    public Turn()
    {
        this.currentID = 0;
        this.numberOfRounds = 0;
    }
   
    public void setID(int ID)
    {
       this.currentID = ID;
    }
    
    public int getID()
    {    
        this.numberOfRounds ++ ;
        return this.currentID;
    }
    
    public void printNumOfRounds(){
    	System.out.println("Number of rounds = "+numberOfRounds);
    }
}

package controller;

import player.Player;
import turn.Turn;

/**
 * Controller is the master of the game and controls all 
 * of the operations executed
 * @author Ioannis Tsiakkas
 */
public class Controller 
{
    private Player BLUE,RED;
    private boolean hasPlayed;

    private Turn turn;
    
    public Controller()
    {
        RED = new Player(0);
        BLUE = new Player(1);
        turn = new Turn();
        this.hasPlayed = false;
    }
    
    public void setTurn(int ID)
    {
        turn.setID(ID);
    }
    
    public int getTurn()
    {
        return turn.getID();
    }
    
    public void nextRound()
    {
        if(turn.getID() == 0){
            turn.setID(1);
        }else{
            turn.setID(0);
        }
    }
    
    public void playerHasPlayed()
    {
        hasPlayed = true;
    }
    
    public void endOfRound()
    {
        hasPlayed = false;
    }
}


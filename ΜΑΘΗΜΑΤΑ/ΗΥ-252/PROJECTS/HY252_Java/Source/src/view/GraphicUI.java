package view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.IOException;

import controller.Controller;
import deck.Deck;
import board.Board;

import java.util.Random;

import javax.imageio.ImageIO;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;

        
/**
 * @version 1.0
 * @author ioannis tsiakkas
 */
public class GraphicUI extends JFrame  {
  	
	private Controller game;
	private Board gameBoard;
	private Deck valueDeckBLUE;
	private Deck valueDeckRED;
	
	private JFrame frame;
	
	private JButton buttons[] = new JButton[60];
	private JButton gamebuttons[] = new JButton[12];
	private JButton next_round;
	
	private JTextPane infoo;
	private JTextPane infot;
    
    private JPanel[] area = new JPanel[80];
    
    private boolean canChange = true;
    
    private String character;
    
    private int currentPlacementX = -1;
    private int currentPlacementY = -1;
    
    private int futurePlacementX = -1;
    private int futurePlacementY = -1;
    
    private int currentCharacter = -1;
    private int futureCharacter = -1;

    /**
	 * <b>constructor</b>: Creates a new Window and initializes some buttons and panels <br />
	 * <b>postconditions</b>: Creates a new Window and initializes some buttons and panels
	 * starting a new game.
     * @throws IOException 
	 */
    public GraphicUI() throws IOException {
	
		gameBoard = new Board();
    	game = new Controller();
		valueDeckBLUE = new Deck("BLUE");
		valueDeckRED = new Deck("RED");
		
    	infoWindow();
    	initializeComponents();
    	initializeButtons();
    	initializeDeck();
    }
    
    private void infoWindow(){
    	
    	frame = new JFrame("INFORMATION");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);      
        frame.setLocationByPlatform(true);
        frame.setSize(350, 750);
   		frame.setLayout(new GridLayout(3, 1, 0 ,0));
        frame.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
        frame.setBackground(Color.ORANGE);
        frame.setResizable(false);
        
        infot = new JTextPane();							
        infoo = new JTextPane();

        next_round = new JButton();
        
    	infot.setForeground(Color.RED);
        infot.setText(" Volcandria (RED) player is now playing.\n"
        		+ " You must click one Volcandria (RED) card,\n to begin your round.");
        infoo.setText(" You can click a character to make a move or an attack "
        		+ " all the rules are as follows:\n"
        		+ "1) In every round only one character can be played.\n"
        		+ "2) All characters can move up-down-left-right.\n"
        		+ "3) No character can go to the yellow areas.\n"
        		+ "4) Only a Dwarf can destroy a trap.\n"
        		+ "5) If a Slayer attacks a Dragon fist he terminates it.\n"
        		+ "6) The Scout can move as many free squares as he wants.\n\n"
        		+ " Left click the card you want to play,\n and then right click\n"
        		+ " where you want to move or what card\n you want to attack.\n"
        		+ "\n If you want to move another character press right click and "
        		+ " start all over again.");
        
        next_round.setFont(new Font("Arial",Font.PLAIN, 40));
        next_round.setText("Next Round");
                
        infot.setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
        infoo.setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
        next_round.setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
        next_round.setForeground(Color.BLACK);	

        infot.setEditable(false);
        infoo.setEditable(false);
        
        next_round.addActionListener(new CardListener());
        next_round.addMouseListener(new CardListener());

        frame.add(infot);
        frame.add(infoo);
        frame.add(next_round);
        frame.setVisible(true);
    
    }
    
    private void initializeComponents(){
    	
    	// creates the frame
		this.setTitle("STRATEGO");
   		this.setVisible(true);
   		this.setSize(1000, 1000);
   		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
   		this.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
   		this.setLayout(new GridLayout(8, 10, 0 ,0));
   		
   		for(int i=0;i<80;i++){
			area[i] = new JPanel();
		}
   		for(int i=0;i<12;i++){
   			gamebuttons[i] = new JButton();
		}
   		int m=0;
   		int l = 0;
  		for(int i=0; i < 80; i++){
	   		
  			if( i>31 && i<34 || i>35 && i<38 || i>41 && i<44 || i>45 && i<48 ){
				area[l].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.YELLOW));
				area[l].setOpaque(true);
				area[l].setForeground(Color.YELLOW);
				area[l].setBackground(Color.YELLOW);
				this.add(area[l]);
			}else if( i>29 && i<32 || i>33 && i<36 || i>37 && i<40 || i>47 && i<50 || i>39 && i<42 || i>43 && i<46 ){
				gamebuttons[m].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				gamebuttons[m].setOpaque(true);
				gamebuttons[m].setBackground(Color.WHITE);
				
				gamebuttons[m].addActionListener(new CardListener());
				gamebuttons[m].addMouseListener(new CardListener());  
				
				this.add(gamebuttons[m]);
				m++;
			}else{
				area[l].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				area[l].setOpaque(true);
				area[l].setForeground(Color.WHITE);
				area[l].setBackground(Color.WHITE);
				this.add(area[l]);
			}
			l++;
  		}
   		this.setVisible(true);
	}

    private void initializeButtons() throws IOException{
	    
	    int[] Availability = new int[12];
	    									
	    Random rand = new Random(); 
    	int value,j=0,k=0;
    	
    	for(int i=0;i<60;i++){ 
    		buttons[i] = new JButton();
    	}
    	
	    Availability[0] = 3; // BeastRider 
    	Availability[1] = 1; // Dragon
	    Availability[2] = 5; // Dwarf
	    Availability[3] = 2; // Elf
	    Availability[4] = 1; // Flag
	    Availability[5] = 2; // Knight
	    Availability[6] = 2; // Lava
	    Availability[7] = 1; // Mage
	    Availability[8] = 4; // Scout
	    Availability[9] = 1; // Slayer
	    Availability[10] = 2; // Sorceress
	    Availability[11] = 6; // Trap
    	
    	for(int i=0;i<30;i++){ //RED
    		
    		value = rand.nextInt(12)+10;
    	    while(Availability[value-10] == 0  ){
        	    value = rand.nextInt(12)+10;
    	    }
	    	Availability[value-10] --;
    	    buttons[i].setIcon(getImage("/"+value+".png")); //image
    	    if(k == 10){ j++;k=0; }
    	    //board[j][k] = value;
    	    gameBoard.add(j,k,value);
    	   
    	    k++;
    	    //buttons[i].setIcon(new ImageIcon((Main.class.getResource("/"+value+".png"))));
    	    
   			buttons[i].addActionListener(new CardListener());
			buttons[i].addMouseListener(new CardListener());  

    	}
    	
    	Availability[0] = 3; // BeastRider 
    	Availability[1] = 1; // Dragon
	    Availability[2] = 5; // Dwarf
	    Availability[3] = 2; // Elf
	    Availability[4] = 1; // Flag
	    Availability[5] = 2; // Knight
	    Availability[6] = 2; // Yeti
	    Availability[7] = 1; // Mage
	    Availability[8] = 4; // Scout
	    Availability[9] = 1; // Slayer
	    Availability[10] = 2; // Sorceress
	    Availability[11] = 6; // Trap

	    j+=2; // so that there are two lines free
    	for(int i=3;i<5;i++){	
    		for(int l=0;l<10;l++){	

    			if(l>1 && l<4 || l>5 && l<8){
    				gameBoard.add(i,l,-1);
    			}
    		}
    	}
    	for(int i=30;i<60;i++){	//BLUE
    		
    		value = rand.nextInt(12)+30;
    	    while(Availability[value-30] == 0  ){
        	    value = rand.nextInt(12)+30;
    	    }
	    	Availability[value-30] --;
    	    
    	    buttons[i].setIcon(getImage("/"+value+".png")); //image
    	    if(k == 10){ j++;k=0; }
    	    //board[j][k] = value;
    	    gameBoard.add(j,k,value);

    	    k++;
   			//buttons[i].setIcon(new ImageIcon((Main.class.getResource("/"+value+".png")))); 
   		
   			buttons[i].addActionListener(new CardListener());
			buttons[i].addMouseListener(new CardListener());   
    	}
    	ImageChange();
    	for(int i=0;i<20;i++){	//BLUE
    		
    		
    		 
    	}
    	
	}
    
    private void initializeDeck(){
    	
    	for(int i=0; i < 60; i++){ 
   			if( i < 30 ){
   				buttons[i].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.RED));
   			}else{
   				buttons[i].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLUE));	
   			}
   			if(i >= 30){
   				area[20+i].add(buttons[i]);
   			}else{
   				area[i].add(buttons[i]);
   			}
		} 			
    	playSound("moirasma.wav");
   		this.setVisible(true);
    }   
    
    private class CardListener implements ActionListener,MouseListener {
    	
    	public void mouseClicked(MouseEvent e) {	    	
    		
    		if(e.getButton() == 1){ playSound("click.wav");
    			
    				for( int j=0; j<60 ; j++){
            			if (e.getSource() == buttons[j]){ 
            				if(j>29){j+=20;}
            				String value = String.valueOf(j);
            				
            				if(currentCharacter == -1){
            					
            					if(findID(value) != -1){
                					currentCharacter = findID(value);
                					infoScreenYourCard(findID(value));
            	    			}
            					
            				}else if(futureCharacter == -1){   
            					
            					int loop;
            					if((loop = findID(value)) != -1){  
            						
            	    				if( futurePlacementX != -1 && futurePlacementY != -1 ){	
                    					futureCharacter = loop;
                    					infoScreenEnemyCard(loop);
            	    				}
            	    				
            	    			}
            					 
            				}
            				break;
            			}
            		}
    				
    				for( int j=0; j<12 ; j++){
            			if (e.getSource() == gamebuttons[j]){
            				
            				String value = null;
            				
            				switch(j){
            				case 0: 
                				value = "30";
            					break;
            				case 1: 
                				value = "31";
                				break;
            				case 2: 
            					value = "34";
            					break;
            				case 3: 
            					value = "35";
            					break;
            				case 4: 
            					value = "38";
            					break;
            				case 5: 
            					value = "39";
            					break;
            				case 6: 
            					value = "40";
            					break;
            				case 7: 
            					value = "41";
            					break;
            				case 8: 
            					value = "44";
            					break;
            				case 9: 
            					value = "45";
            					break;
            				case 10: 
            					value = "48";
            					break;
            				case 11: 
                				value = "49";
            					break;
            				}
            				
            				if(currentCharacter == -1){
            					
            					if(findID(value) != -1){
                					
            						currentCharacter = findID(value);
                					infoScreenYourCard(findID(value));
            	    			
            					}
            					
            				}if(futureCharacter == -1){   
            					
            					int loop;
            					if((loop = findID(value)) != -1){  
            						
            	    				if( futurePlacementX != -1 && futurePlacementY != -1 ){	
                    		
            	    					futureCharacter = loop;
                    					infoScreenEnemyCard(loop);
                    		
                            			break;
            	    				}
            	    				
            	    			}
            					 
            				}
            			}
    				}
    				
    				if (e.getSource() == next_round){ 
    					
    					if(currentCharacter != -1 && futureCharacter == -1){
    						
    						String color;
    						
    						if(game.getTurn() == 0){
    				    		infot.setForeground(Color.RED);
    				    		color = "Volcandria (RED)";
    				    	}else{
    				    		infot.setForeground(Color.BLUE);
    				    		color = "Everwinter (BLUE)";
    				    	}
    						infot.setText(" "+color+" player is now playing.\n"
    								+ " You must click one "+color+" card,\n to begin your round.\n\n "
    								+ character+" is Selected."
        							+ "\n Select enemy character to attack or place to move !");
    						
    					}else if(currentCharacter == -1 && futureCharacter == -1){
    						
    						if(game.getTurn() == 0){
    				    		infot.setForeground(Color.RED);
            					infot.setText(" Volcandria (RED) player is now playing.\n"
            			        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n"
            							+ " Select your character !");
            				}else{
    				    		infot.setForeground(Color.BLUE);
            					infot.setText(" Everwinter (BLUE) player is now playing.\n"
            							+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n"
            							+ " Select your character !");
            				}
    						
    					}else if(currentCharacter != -1 && futureCharacter != -1){
    						
    						if(canChange == false && futureCharacter == 0 
    								&& (currentCharacter == 18 ||  currentCharacter == 38)){ 
    			        	    
    			        		playSound("again.wav");

    			        	    futureCharacter = -1;
    			        	    futurePlacementX = -1;
    			        	    futurePlacementY = -1;
    							
    			        	    String color;
								if(game.getTurn() == 0){
	    				    		infot.setForeground(Color.RED);
	    				    		color = "Volcandria (RED)";
	    				    	}else{
	    				    		infot.setForeground(Color.BLUE);
	    				    		color = "Everwinter (BLUE)";
	    				    	}
								infot.setText(" "+color+" player is now playing.\n"
	    								+ " You must click one "+color+" card,\n to begin your round.\n\n "
	    								+ character+" has moved and now can attack."
	        							+ "\n Select enemy character to attack\n"
	        							+ " or press Next Round to not attack.\n"
	        							+ " * You cannot move again !");
								
    						}else if(canChange == false && futureCharacter != 0 && 
    								(currentCharacter == 18 ||  currentCharacter == 38)){
    							
    							if(checkIfMoveIsReady() == true && isCharMovable() == true){

    								if(makeMoveOrAttack() == true){

    									canChange = true;
        								game.endOfRound();
                        				game.nextRound();
                        				nextRound();
                        				if(GameOver() == true){
                        					if(game.getTurn() == 0){
                        						playSound("win2.wav");
                            					JOptionPane.showMessageDialog(null, "BLUE HAS WON\nEND OF GAME");
                            					System.exit(0);
            	    				    	}else{
                        						playSound("win2.wav");
                            					JOptionPane.showMessageDialog(null, "RED HAS WON\nEND OF GAME");
                            					System.exit(0);
            	    				    	}
                        				}
            							ImageChange();
            							
                						if(game.getTurn() == 0){
                				    		infot.setForeground(Color.RED);
                        					infot.setText(" Volcandria (RED) player is now playing.\n"
                        			        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n");
                        				}else{
                				    		infot.setForeground(Color.BLUE);
                        					infot.setText(" Everwinter (BLUE) player is now playing.\n"
                        							+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n");
                        				}
    								}
    							}
    						}else if(checkIfMoveIsReady() == true && isCharMovable() == true){
    							
    							if(makeMoveOrAttack() == false && currentCharacter != 18 && currentCharacter != 38){ // attacked

    								game.endOfRound();
                    				game.nextRound();
                    				nextRound();
                    				if(GameOver() == true){
                    					if(game.getTurn() == 0){
                    						playSound("win2.wav");
                        					JOptionPane.showMessageDialog(null, "BLUE HAS WON\nEND OF GAME");
                        					System.exit(0);
        	    				    	}else{
                    						playSound("win2.wav");
                        					JOptionPane.showMessageDialog(null, "RED HAS WON\nEND OF GAME");
                        					System.exit(0);
        	    				    	}
                    				}
        							ImageChange();
        							
            						if(game.getTurn() == 0){
            				    		infot.setForeground(Color.RED);
                    					infot.setText(" Volcandria (RED) player is now playing.\n"
                    			        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n");
                    				}else{
            				    		infot.setForeground(Color.BLUE);
                    					infot.setText(" Everwinter (BLUE) player is now playing.\n"
                    							+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n");
                    				}
            						
    							}else{
    								
    								String color;
    								if(game.getTurn() == 0){
    	    				    		infot.setForeground(Color.RED);
    	    				    		color = "Volcandria (RED)";
    	    				    	}else{
    	    				    		infot.setForeground(Color.BLUE);
    	    				    		color = "Everwinter (BLUE)";
    	    				    	}
    								canChange = false;
    								infot.setText(" "+color+" player is now playing.\n"
    	    								+ " You must click one "+color+" card,\n to begin your round.\n\n "
    	    								+ character+" has moved and now can attack."
    	        							+ "\n Select enemy character to attack\n"
    	        							+ " or press right click to end round.");
    								
    								futureCharacter = -1;
        			        	    futurePlacementX = -1;
        			        	    futurePlacementY = -1;
    							}    							
        						
    						}else if(isCharMovable() == false){
    							if(game.getTurn() == 0){
    					    		infot.setForeground(Color.RED);
    					    		infot.setText(" Volcandria (RED) player is now playing.\n"
    						        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n"
    										+ " * Trap and Flag cannot be moved.\n\n"
    						        		+ " Choose a character and make a move/attack");
    							}else{
    					    		infot.setForeground(Color.BLUE);
    								infot.setText(" Everwinter (BLUE) player is now playing.\n"
    										+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n"
    										+ " * Trap and Flag cannot be moved.\n\n"
    						        		+ " Choose a character and make a move/attack");
    			    			}
    							playSound("again.wav");
    			        		
    			        		currentCharacter = -1;
    			        		currentPlacementX = -1;
    			        	    currentPlacementY = -1;
    			        	    
    			        	    futureCharacter = -1;
    			        	    futurePlacementX = -1;
    			        	    futurePlacementY = -1;
    			        	    
    						}else{
    							
    							if(game.getTurn() == 0){
    					    		infot.setForeground(Color.RED);
    					    		infot.setText(" Volcandria (RED) player is now playing.\n"
    						        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n"
    										+ " * Your charachter can only move\n"
    										+ " * one brick up, down, left or right.\n\n"
    						        		+ " Choose a character and make a move/attack");
    							}else{
    					    		infot.setForeground(Color.BLUE);
    								infot.setText(" Everwinter (BLUE) player is now playing.\n"
    										+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n"
    										+ " * Your charachter can only move\n"
    										+ " * one brick up, down, left or right.\n\n"
    						        		+ " Choose a character and make a move/attack");
    			    			}
    			        		playSound("again.wav");
    			        		
    			        		currentCharacter = -1;
    			        		currentPlacementX = -1;
    			        	    currentPlacementY = -1;
    			        	    
    			        	    futureCharacter = -1;
    			        	    futurePlacementX = -1;
    			        	    futurePlacementY = -1;
    						}
    						
    					}
        			}

    		}else if(e.getButton() == 3){
    			
    			if(canChange == true){
    				
	    			if(game.getTurn() == 0){
			    		infot.setForeground(Color.RED);
			    		infot.setText(" Volcandria (RED) player is now playing.\n"
				        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n"
				        		+ " Choose a character and make a move/attack");
					}else{
			    		infot.setForeground(Color.BLUE);
						infot.setText(" Everwinter (BLUE) player is now playing.\n"
								+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n"
				        		+ " Choose a character and make a move/attack");
	    			}
	        		playSound("again.wav");
	        		
	        		currentCharacter = -1;
	        		currentPlacementX = -1;
	        	    currentPlacementY = -1;
	        	    
	        	    futureCharacter = -1;
	        	    futurePlacementX = -1;
	        	    futurePlacementY = -1;
	        	    
    			}else{
    			
    				canChange = true;
    				game.endOfRound();
    				game.nextRound();
    				nextRound();
					ImageChange();
					
					if(game.getTurn() == 0){
			    		infot.setForeground(Color.RED);
    					infot.setText(" Volcandria (RED) player is now playing.\n"
    			        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n");
    				}else{
			    		infot.setForeground(Color.BLUE);
    					infot.setText(" Everwinter (BLUE) player is now playing.\n"
    							+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n");
    				}
    			}
    			
    		}else if(e.getButton() == 2){
    			gameBoard.printBoard();
    		}
    		    		
    	}
    	
		public void mouseEntered(MouseEvent e) {		
    	}
    	public void mouseExited(MouseEvent e) {
    	}
    	public void mousePressed(MouseEvent e) {
    	}
    	public void mouseReleased(MouseEvent e) {		
    	}
    	public void actionPerformed(ActionEvent e) {
    		//
    	}
    	
    }
    
    private int findID(String number){ 
    	
    	if(game.getTurn() == 0){ // RED
    		
    		if(number.length() == 1){						

    			int y = Integer.parseInt(number);

    			if(gameBoard.getValue(0, y) > 9 && gameBoard.getValue(0, y) < 22){

    				if( currentPlacementX == -1 && currentPlacementY == -1 ){
        				currentPlacementX = 0;
        			    currentPlacementY = y;
        			}else if(gameBoard.getValue(0, y) > 29 && gameBoard.getValue(0, y) < 42){ 
        				futurePlacementX = 0;
        				futurePlacementY = y;
        			}
    				
    				return gameBoard.getValue(0, y);
    				
    			}else if(gameBoard.getValue(0, y) > 29 && gameBoard.getValue(0, y) < 42){	
    			
    				if( currentCharacter != -1 ){
    					
    					futurePlacementX = 0;
        				futurePlacementY = y;
    					
        				return gameBoard.getValue(0, y);
    				}else{
    					return -1;
    				}
    				
    			}else{ // an einai sth mesh
    				
    				if( currentCharacter != -1 ){ 
    					
    					futurePlacementX = 0;
        				futurePlacementY = y;
    					
        				return gameBoard.getValue(0, y);
    				
    				}else{
    					return -1;
    				}
    				
    			}
    			
    		}else{	
    			
    			int x = Integer.parseInt(number.substring(0, 1));
    			int y = Integer.parseInt(number.substring(1, 2));

    			if(gameBoard.getValue(x, y) > 9 && gameBoard.getValue(x, y) < 22){
    				
    				if( currentPlacementX == -1 && currentPlacementY == -1 ){
        				currentPlacementX = x;
        			    currentPlacementY = y;
        			}else if(gameBoard.getValue(x, y) > 29 && gameBoard.getValue(x, y) < 42){ 
        				futurePlacementX = x;
        				futurePlacementY = y;
        			}
    				
    				return gameBoard.getValue(x, y);
    			
    			}else if(gameBoard.getValue(x, y) > 29 && gameBoard.getValue(x, y) < 42){	
        			
    				if( currentCharacter != -1 ){ 
    					
    					futurePlacementX = x;
        				futurePlacementY = y;
    					
        				return gameBoard.getValue(x, y);
    				}else{
    					return -1;
    				}
    				
    			}else{ // an einai sth mesh
    				
    				if( currentCharacter != -1 ){
    					
    					futurePlacementX = x;
        				futurePlacementY = y;
    					
        				return gameBoard.getValue(x, y);
    				
    				}else{
    					return -1;
    				}
    			}
    		}
    		
    	}else{ // BLUE
    		
    		if(number.length() == 1){						

    			int y = Integer.parseInt(number);

    			if(gameBoard.getValue(0, y) > 29 && gameBoard.getValue(0, y) < 42){
    				
    				if( currentPlacementX == -1 && currentPlacementY == -1 ){
        				currentPlacementX = 0;
        			    currentPlacementY = y;
        			}else if(gameBoard.getValue(0, y) > 9 && gameBoard.getValue(0, y) < 22){
        				futurePlacementX = 0;
        				futurePlacementY = y;
        			}
    				
    				return gameBoard.getValue(0, y);
    				
    			}else if(gameBoard.getValue(0, y) > 9 && gameBoard.getValue(0, y) < 12){	
        			
    				if( currentCharacter != -1 ){ 
    					
    					futurePlacementX = 0;
        				futurePlacementY = y;
    					
        				return gameBoard.getValue(0, y);
    				}else{
    					return -1;
    				}
    				
    			}else{ // an einai sth mesh
    				
    				if( currentCharacter != -1 ){
    					
    					futurePlacementX = 0;
        				futurePlacementY = y;
    					
        				return gameBoard.getValue(0, y);
    				
    				}else{
    					return -1;
    				}
    			}
    			
    		}else{	
    			
    			int x = Integer.parseInt(number.substring(0, 1));
    			int y = Integer.parseInt(number.substring(1, 2));

    			if(gameBoard.getValue(x, y) > 29 && gameBoard.getValue(x, y) < 42){
    				
    				if( currentPlacementX == -1 && currentPlacementY == -1 ){
        				currentPlacementX = x;
        			    currentPlacementY = y;
        			}else if(gameBoard.getValue(x, y) > 9 && gameBoard.getValue(x, y) < 22){
        				futurePlacementX = x;
        				futurePlacementY = y;
        			}
    				
    				return gameBoard.getValue(x, y);
    			
    			}else if(gameBoard.getValue(x, y) > 9 && gameBoard.getValue(x, y) < 12){	
        			
    				if( currentCharacter != -1 ){ 
    					
    					futurePlacementX = x;
        				futurePlacementY = y;
    					
        				return gameBoard.getValue(x, y);
    				}else{
    					return -1;
    				}
    				
    			}else{ // an einai sth mesh
    				
    				if( currentCharacter != -1 ){ 
    					
    					futurePlacementX = x;
        				futurePlacementY = y;
    					
        				return gameBoard.getValue(x, y);
    				
    				}else{
    					return -1;
    				}
    			}
    		}		
    	}
    }
    
    private boolean checkIfMoveIsReady() {
		if(currentPlacementX != -1 ){
    		if(currentPlacementY != -1 ){
    			if(futurePlacementX != -1 ){
    				if(futurePlacementX != -1 ){
    					if(currentCharacter != -1 ){
    						if(futureCharacter != -1 ){
    							if(currentCharacter == 18 || currentCharacter == 38){ // scout
    								if(currentPlacementX == futurePlacementX || currentPlacementY == futurePlacementY){
    									return true;
    								}else{
    									return false;
    								}
    							}
    							if(currentPlacementX-1 == futurePlacementX && currentPlacementY == futurePlacementY){
    								return true;
    							}else if(currentPlacementX+1 == futurePlacementX && currentPlacementY == futurePlacementY){
    								return true;
    							}else if(currentPlacementX == futurePlacementX && currentPlacementY-1 == futurePlacementY){
    								return true;
    							}else if(currentPlacementX == futurePlacementX && currentPlacementY+1 == futurePlacementY){
    								return true;
    							}else{
    								return false;
    							}
        			    	}
    			    	}
    		    	}
    	    	}	
        	}
    	}
    	return false;
	}
    
	private boolean makeMoveOrAttack(){
		
		if(futureCharacter == 0){ // move

			if(currentCharacter == 18 || currentCharacter == 38){
				
				if(currentPlacementX == futurePlacementX && canChange == true){
					int Y,Distance;
					if(currentPlacementY < futurePlacementY){
						Y = currentPlacementY+1;
						Distance = futurePlacementY-currentPlacementY;
					}else{
						Y = futurePlacementY;
						Distance = currentPlacementY-futurePlacementY;
					}

					while(Distance != 0 ){
						if(gameBoard.getValue(currentPlacementX, Y) != 0){
							return false;
						}
						Y++;
						Distance--;
					}
					gameBoard.add(futurePlacementX, futurePlacementY, currentCharacter);
					gameBoard.add(currentPlacementX, currentPlacementY, 0);
					
					String oldc = ""+currentPlacementX+currentPlacementY;
					String newc = ""+futurePlacementX+futurePlacementY;
							
					UIchangeAdd(newc,currentCharacter);
					UIchangeRemove(oldc);
					
					canChange = false;
					currentPlacementX = futurePlacementX;
					currentPlacementY = futurePlacementY;
					futurePlacementX = -1;
					futurePlacementY = -1;
					
					return true;
					
				}else if(currentPlacementY == futurePlacementY && canChange == true){
					
					int X,Distance;
					if(currentPlacementX < futurePlacementX){
						X = currentPlacementX+1;
						Distance = futurePlacementX-currentPlacementX;
					}else{
						X = futurePlacementX;
						Distance = currentPlacementX-futurePlacementX;
					}

					while(Distance != 0 ){
						if(gameBoard.getValue(X, currentPlacementY) != 0){
							return false;
						}
						X++;
						Distance--;
					}
					gameBoard.add(futurePlacementX, futurePlacementY, currentCharacter);
					gameBoard.add(currentPlacementX, currentPlacementY, 0);
					
					String oldc = ""+currentPlacementX+currentPlacementY;
					String newc = ""+futurePlacementX+futurePlacementY;
							
					UIchangeAdd(newc,currentCharacter);
					UIchangeRemove(oldc);
					
					canChange = false;
					currentPlacementX = futurePlacementX;
					currentPlacementY = futurePlacementY;
					futurePlacementX = -1;
					futurePlacementY = -1;
					return true;
				
				}
				
				
				
			}
			
			if(currentPlacementX-1 == futurePlacementX && currentPlacementY == futurePlacementY){
				//pano
				
				gameBoard.add(futurePlacementX, futurePlacementY, currentCharacter);
				gameBoard.add(currentPlacementX, currentPlacementY, 0);
				
				String oldc = ""+currentPlacementX+currentPlacementY;
				String newc = ""+futurePlacementX+futurePlacementY;
						
				UIchangeAdd(newc,currentCharacter);
				UIchangeRemove(oldc);
				
			}else if(currentPlacementX+1 == futurePlacementX && currentPlacementY == futurePlacementY){
				//kato
				
				gameBoard.add(futurePlacementX, futurePlacementY, currentCharacter);
				gameBoard.add(currentPlacementX, currentPlacementY, 0);

				String oldc = ""+currentPlacementX+currentPlacementY;
				String newc = ""+futurePlacementX+futurePlacementY;
						
				UIchangeAdd(newc,currentCharacter);
				UIchangeRemove(oldc);
				
			}else if(currentPlacementX == futurePlacementX && currentPlacementY-1 == futurePlacementY){
				//aristera
				
				gameBoard.add(futurePlacementX, futurePlacementY, currentCharacter);
				gameBoard.add(currentPlacementX, currentPlacementY, 0);
				
				String oldc = ""+currentPlacementX+currentPlacementY;
				String newc = ""+futurePlacementX+futurePlacementY;
						
				UIchangeAdd(newc,currentCharacter);
				UIchangeRemove(oldc);
				
			}else if(currentPlacementX == futurePlacementX && currentPlacementY+1 == futurePlacementY){
				//deksia
				
				gameBoard.add(futurePlacementX, futurePlacementY, currentCharacter);
				gameBoard.add(currentPlacementX, currentPlacementY, 0);
				
				String oldc = ""+currentPlacementX+currentPlacementY;
				String newc = ""+futurePlacementX+futurePlacementY;
						
				UIchangeAdd(newc,currentCharacter);
				UIchangeRemove(oldc);
				
			}else{
				// cannot move
			}
			
		}else{ // attack
			
			boolean doIt = false;
			
			if(currentPlacementX-1 == futurePlacementX && currentPlacementY == futurePlacementY){
				//pano
				doIt = true;
			}else if(currentPlacementX+1 == futurePlacementX && currentPlacementY == futurePlacementY){
				//kato
				doIt = true;
			}else if(currentPlacementX == futurePlacementX && currentPlacementY-1 == futurePlacementY){
				//aristera		
				doIt = true;
			}else if(currentPlacementX == futurePlacementX && currentPlacementY+1 == futurePlacementY){
				//deksia
				doIt = true;
			}else{
				// cannot attack
				doIt = false;
			}

			if(doIt == true){

				int cValue,fValue;
				
				if(game.getTurn() == 0){
		    		cValue = valueDeckRED.getValue(currentCharacter);
		    		fValue = valueDeckBLUE.getValue(futureCharacter);
				}else{
					cValue = valueDeckBLUE.getValue(currentCharacter);
		    		fValue = valueDeckRED.getValue(futureCharacter);
				}
				
				//Dwarf special Trap power
				if(currentCharacter == 12 || currentCharacter == 32){ // dwarf
					if(futureCharacter == 21 || futureCharacter == 41){ // trap
						cValue = fValue + 1;
					}
				}
				//Slayer special Dragon power
				if(currentCharacter == 19 || currentCharacter == 39){ // slayer
					if(futureCharacter == 11 || futureCharacter == 31){ // dragon
						cValue = fValue + 1;
					}
				}
				
				if ( cValue > fValue){ 
					
					gameBoard.add(futurePlacementX, futurePlacementY, currentCharacter);
					gameBoard.add(currentPlacementX, currentPlacementY, 0);
					
					String oldc = ""+currentPlacementX+currentPlacementY;
					String newc = ""+futurePlacementX+futurePlacementY;
							
					UIchangeAdd(newc, currentCharacter);
					UIchangeRemove(oldc);
					
				}else if ( cValue < fValue){ 
					
					gameBoard.add(currentPlacementX, currentPlacementY, 0);
					
					String oldc = ""+currentPlacementX+currentPlacementY;
							
					UIchangeRemove(oldc);
					
				}else if ( cValue == fValue){ 
					
					gameBoard.add(futurePlacementX, futurePlacementY, 0);
					gameBoard.add(currentPlacementX, currentPlacementY, 0);
					
					String oldc = ""+currentPlacementX+currentPlacementY;
					String newc = ""+futurePlacementX+futurePlacementY;
							
					UIchangeRemove(newc);
					UIchangeRemove(oldc);
					
				}
			}
			
			if(currentCharacter == 18 || currentCharacter == 38 || currentCharacter == 0){
				game.endOfRound();
				if(canChange == false){game.nextRound();}
				nextRound();
				if(GameOver() == true){
					if(game.getTurn() == 0){
						playSound("win2.wav");
    					JOptionPane.showMessageDialog(null, "BLUE HAS WON\nEND OF GAME");
    					System.exit(0);
			    	}else{
						playSound("win2.wav");
    					JOptionPane.showMessageDialog(null, "RED HAS WON\nEND OF GAME");
    					System.exit(0);
			    	}
				}
				ImageChange();
				canChange = true;

				if(game.getTurn() == 0){
					infot.setForeground(Color.RED);
					infot.setText(" Volcandria (RED) player is now playing.\n"
			        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n");
				}else{
					infot.setForeground(Color.BLUE);
					infot.setText(" Everwinter (BLUE) player is now playing.\n"
							+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n");
				}	
				return false;
			}
			
		}
		
			
		if(currentCharacter == 2 || currentCharacter == 32){ // dwarf
			
		}else if(currentCharacter == 8 || currentCharacter == 38){ // scout
			// move and attack
		}else if(currentCharacter == 9 || currentCharacter == 39){ // slayer
			
		}
		
		return false;
		
	}
	
	private boolean isCharMovable(){
		
		if(currentCharacter == 14 || currentCharacter == 34){  
			//flag
			if(game.getTurn() == 0){
	    		infot.setForeground(Color.RED);
	    		infot.setText(" Volcandria (RED) player is now playing.\n"
		        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n"
						+ " * Flags cannot move.\n\n"
		        		+ " Choose a character and make a move/attack");
			}else{
	    		infot.setForeground(Color.BLUE);
				infot.setText(" Everwinter (BLUE) player is now playing.\n"
						+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n"
						+ " * Flags cannot move.\n\n"
		        		+ " Choose a character and make a move/attack");
			}
			return false;
		}
		if(currentCharacter == 21 || currentCharacter == 41){ 
			// trap
			if(game.getTurn() == 0){
	    		infot.setForeground(Color.RED);
	    		infot.setText(" Volcandria (RED) player is now playing.\n"
		        		+ " You must click one Volcandria (RED) card,\n to begin your round.\n\n"
						+ " * Traps cannot move.\n\n"
		        		+ " Choose a character and make a move/attack");
			}else{
	    		infot.setForeground(Color.BLUE);
				infot.setText(" Everwinter (BLUE) player is now playing.\n"
						+ " You must click one Everwinter (BLUE) card,\n to begin your round.\n\n"
						+ " * Traps cannot move.\n\n"
		        		+ " Choose a character and make a move/attack");
			}
			return false;
		}
		return true;
	}
	
	private boolean GameOver(){
		
		int charCountCanMove = 0;
		boolean flagExists = false;
		
		if(game.getTurn() == 0){ // RED
			
    		for(int i = 0; i<8 ; i++){
            	for(int j = 0; j<10 ; j++){
            		
            		if(gameBoard.getValue(i, j) > 9 && gameBoard.getValue(i, j) < 22){
            			charCountCanMove = 0;
            			
            			if(gameBoard.getValue(i, j) == 14){
            				flagExists = true;
            			}
            			
            			int up=1,down=1,left=1,right=1;
            			
            			if(i == 0){ 
            				up = 0;
            			}
            			if(i == 7){
            				down = 0;
            			}
            			if(j == 0){
            				left = 0;
            			}
            			if(j == 9){
            				right = 0;
            			}
            			
            			if(up == 1){
            				if((gameBoard.getValue(i-1, j) > 9 && gameBoard.getValue(i-1, j) < 22) || gameBoard.getValue(i-1, j) == -1){
    	            			// cannot move
                			}else{charCountCanMove++;}
            			}
            			if(down == 1){
            				if((gameBoard.getValue(i+1, j) > 9 && gameBoard.getValue(i+1, j) < 22) || gameBoard.getValue(i+1, j) == -1){
    	            			// cannot move
                			}else{charCountCanMove++;}
            			}
            			if(left == 1){
            				if((gameBoard.getValue(i, j-1) > 9 && gameBoard.getValue(i, j-1) < 22) || gameBoard.getValue(i, j-1) == -1){
    	            			// cannot move
                			}else{charCountCanMove++;}
            			}
            			if(right == 1){
            				if((gameBoard.getValue(i, j+1) > 9 && gameBoard.getValue(i, j+1) < 22) || gameBoard.getValue(i, j+1) == -1){
    	            			// cannot move
                			}else{charCountCanMove++;}
            			}
            			
            			if(gameBoard.getValue(i, j) == 14 || gameBoard.getValue(i, j) < 21 || gameBoard.getValue(i, j) == 34 || gameBoard.getValue(i, j) == 41){
            				up = 0;down =0;right=0;left=0;
            			}
            			
            		}
            	}
    		}
            		
            if(flagExists == true){
    			if(charCountCanMove == 0){
        			return true;
        		}else{
        			charCountCanMove = 0;
        			return false;
        		}
    		}else{
    			return true;
    		}    		
    		
    	}else{ // BLUE
    		
    		for(int i = 0; i<8 ; i++){
            	for(int j = 0; j<10 ; j++){
            		
            		if(gameBoard.getValue(i, j) > 29 && gameBoard.getValue(i, j) < 42){
            			
            			charCountCanMove = 0;
            			
            			if(gameBoard.getValue(i, j) == 34){
            				flagExists = true;
            			}

            			int up=1,down=1,left=1,right=1;
            			
            			if(i == 0){
            				up = 0;
            			}
            			if(i == 7){
            				down = 0;
            			}
            			if(j == 0){
            				left = 0;
            			}
            			if(j == 9){
            				right = 0;
            			}
            			
            			if(up == 1){
            				if((gameBoard.getValue(i-1, j) > 9 && gameBoard.getValue(i-1, j) < 22) || gameBoard.getValue(i-1, j) == -1){
    	            			// cannot move
                			}else{charCountCanMove++;}
            			}
            			if(down == 1){
            				if((gameBoard.getValue(i+1, j) > 9 && gameBoard.getValue(i+1, j) < 22) || gameBoard.getValue(i+1, j) == -1){
    	            			// cannot move
                			}else{charCountCanMove++;}
            			}
            			if(left == 1){
            				if((gameBoard.getValue(i, j-1) > 9 && gameBoard.getValue(i, j-1) < 22) || gameBoard.getValue(i, j-1) == -1){
    	            			// cannot move
                			}else{charCountCanMove++;}
            			}
            			if(right == 1){
            				if((gameBoard.getValue(i, j+1) > 9 && gameBoard.getValue(i, j+1) < 22) || gameBoard.getValue(i, j+1) == -1){
    	            			// cannot move
                			}else{charCountCanMove++;}
            			}
            			if(gameBoard.getValue(i, j) == 14 || gameBoard.getValue(i, j) < 21 || gameBoard.getValue(i, j) == 34 || gameBoard.getValue(i, j) == 41){
            				up = 0;down =0;right=0;left=0;
            			}
            			
            		}
            	}
        	}
    		
    		if(flagExists == true){
    			if(charCountCanMove == 0){
        			return true;
        		}else{
        			charCountCanMove = 0;
        			return false;
        		}
    		}else{
    			return true;
    		}
    	}
	}
	
	private void UIchangeAdd(String str_value, int image){
		
		int value = Integer.parseInt(str_value);
		Color colour;
		if(game.getTurn() == 0){ // RED
			colour = Color.RED;
		}else{
			colour = Color.BLUE;
		}
		
		if(value > 29 && value < 50){ // mid
		
			switch(value){
			case 30:
				gamebuttons[0].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[0].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 31: 
				gamebuttons[1].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[1].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 34: 
				gamebuttons[2].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[2].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 35:
				gamebuttons[3].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[3].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 38: 
				gamebuttons[4].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[4].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 39: 
				gamebuttons[5].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[5].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 40:
				gamebuttons[6].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[6].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 41: 
				gamebuttons[7].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[7].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 44:
				gamebuttons[8].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[8].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 45: 
				gamebuttons[9].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[9].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 48: 
				gamebuttons[10].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[10].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			case 49: 
				gamebuttons[11].setIcon(getImage("/"+image+".png")); //image
				gamebuttons[11].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
				break;
			}
		}else if(value > 49){ // mid
			buttons[value-20].setIcon(getImage("/"+image+".png")); //image
			buttons[value-20].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
		}else{
			buttons[value].setIcon(getImage("/"+image+".png")); //image
			buttons[value].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, colour));
		}
		
	}
	
	
	private void UIchangeRemove(String str_value){
	
		int value = Integer.parseInt(str_value);
	
		if(value > 29 && value < 50){ // mid
			switch(value){
			case 30:
				gamebuttons[0].setIcon(getImage("/white.png")); //image
				gamebuttons[0].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 31:
				gamebuttons[1].setIcon(getImage("/white.png")); //image
				gamebuttons[1].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 34: 
				gamebuttons[2].setIcon(getImage("/white.png")); //image
				gamebuttons[2].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 35: 
				gamebuttons[3].setIcon(getImage("/white.png")); //image
				gamebuttons[3].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 38: 
				gamebuttons[4].setIcon(getImage("/white.png")); //image
				gamebuttons[4].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 39:
				gamebuttons[5].setIcon(getImage("/white.png")); //image
				gamebuttons[5].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 40: 
				gamebuttons[6].setIcon(getImage("/white.png")); //image
				gamebuttons[6].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 41: 
				gamebuttons[7].setIcon(getImage("/white.png")); //image
				gamebuttons[7].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 44: 
				gamebuttons[8].setIcon(getImage("/white.png")); //image
				gamebuttons[8].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 45: 
				gamebuttons[9].setIcon(getImage("/white.png")); //image
				gamebuttons[9].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 48: 
				gamebuttons[10].setIcon(getImage("/white.png")); //image
				gamebuttons[10].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			case 49:
				gamebuttons[11].setIcon(getImage("/white.png")); //image
				gamebuttons[11].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
				break;
			}
		}else if(value > 49){ // mid
			buttons[value-20].setIcon(getImage("/white.png")); //image
			buttons[value-20].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
		}else{
			buttons[value].setIcon(getImage("/white.png")); //image
			buttons[value].setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.BLACK));
		}
		
	}
	
	
	private void infoScreenYourCard(int i){

    	String color;
    	int num;
    	if(game.getTurn() == 0){
    		infot.setForeground(Color.RED);
    		color = "Volcandria (RED)";
    		num = 10;
    	}else{
    		infot.setForeground(Color.BLUE);
    		color = "Everwinter (BLUE)";
    		num = 30;
    	}
    	
    	switch(i-num){
		
		case 0:	character = "Beast Rider";
				infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Beast Rider is Selected");
				break;	
		case 1:	character = "Dragon";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Dragon is Selected");
		break;
		case 2:	character = "Dwarf";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Dwarf is Selected");
		break;
		case 3:	character = "Elf";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Elf is Selected");
		break;
		case 4:	character = "Flag";	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Flag is Selected");
		break;
		case 5:	character = "Knight";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Knight is Selected");
		break;
		case 6:
			if(game.getTurn() == 0){
				character = "Lava Beast";
	    	}else{
	    		character = "Yeti";
	    	}
			
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ character+" is Selected");
		break;	
		case 7:	character = "Mage";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Mage is Selected");
		break;
		case 8:	character = "Scout";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Scout is Selected");
		break;
		case 9:	character = "Slayer";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Slayer is Selected");
		break;
		case 10:	character = "Sorceress";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Sorceress is Selected");
		break;
		case 11: 	character = "Trap";
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n"
				+ " Trap is Selected");
		break;
    	}	
	
    }
    
	
	private void infoScreenEnemyCard(int i){

    	String color;
    	int num;
    	if(game.getTurn() == 0){
    		infot.setForeground(Color.RED);
    		color = "Volcandria (RED)";
    		num = 30;
    	}else{
    		infot.setForeground(Color.BLUE);
    		color = "Everwinter (BLUE)";
    		num = 10;
    	}
    	
    	if(i == 0){
    		infot.setText(" "+color+" player is now playing.\n "
    				+ "You must click one "+color+" card,\n to begin your round.\n\n "
    				+ character+" is Selected to move.");
    		return;
    	}
    	
    	switch(i-num){
		
		case 0:	
				infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Beast Rider.");
				break;	
		case 1:	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Dragon.");
		break;
		case 2:	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Dwarf.");
		break;
		case 3:	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Elf.");
		break;
		case 4:	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Flag.");
		break;
		case 5:
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Knight.");
		break;
		case 6:
			String chara;
			if(game.getTurn() == 0){
	    		chara = "Yeti.";
	    	}else{
				chara = "Lava Beast.";
	    	}
			
			infot.setText(" "+color+" player is now playing.\n "
					+ "You must click one "+color+" card,\n to begin your round.\n\n "
					+ character+" is Selected to attack "+chara);
		break;
		case 7:	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Mage.");
		break;
		case 8:	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Scout.");
		break;
		case 9:	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Slayer.");
		break;
		case 10:	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Sorceress.");
		break;
		case 11: 	
		infot.setText(" "+color+" player is now playing.\n "
				+ "You must click one "+color+" card,\n to begin your round.\n\n "
				+ character+" is Selected to attack "
				+ " Trap.");
		break;
    	}	
	
    }
    
   
	private void ImageChange(){
    	
    	if(game.getTurn() == 0){ // RED
    		for(int i = 0; i<8 ; i++){
            	for(int j = 0; j<10 ; j++){
    				// VANISH BLUE
            		if(gameBoard.getValue(i, j) > 29 && gameBoard.getValue(i, j) < 42){
            			if(i>2 && i<5){
            				switch(Integer.parseInt(""+i+j)){ 
            				case 30: 
            					gamebuttons[0].setIcon(getImage("/42.png")); //image
            					break;
            				case 31: 
            					gamebuttons[1].setIcon(getImage("/42.png")); //image
            					break;
            				case 34: 
            					gamebuttons[2].setIcon(getImage("/42.png")); //image
            					break;
            				case 35: 
            					gamebuttons[3].setIcon(getImage("/42.png")); //image
            					break;
            				case 38: 
            					gamebuttons[4].setIcon(getImage("/42.png")); //image
            					break;
            				case 39: 
            					gamebuttons[5].setIcon(getImage("/42.png")); //image
            					break;
            				case 40: 
            					gamebuttons[6].setIcon(getImage("/42.png")); //image
            					break;
            				case 41: 
            					gamebuttons[7].setIcon(getImage("/42.png")); //image
            					break;
            				case 44: 
            					gamebuttons[8].setIcon(getImage("/42.png")); //image
            					break;
            				case 45: 
            					gamebuttons[9].setIcon(getImage("/42.png")); //image
            					break;
            				case 48: 
            					gamebuttons[10].setIcon(getImage("/42.png")); //image
            					break;
            				case 49: 
            					gamebuttons[11].setIcon(getImage("/42.png")); //image
            					break;
            				}
            			}else{
            				if(i>4){
            					buttons[Integer.parseInt(""+i+j)-20].setIcon(getImage("/42.png")); //image
            				}else{
            					buttons[Integer.parseInt(""+i+j)].setIcon(getImage("/42.png")); //image
            				}
            			}
            		}
        			// MAKE RED VISIBLE
            		if(gameBoard.getValue(i, j) > 9 && gameBoard.getValue(i, j) < 22){
            			if(i>2 && i<5){
            				switch(Integer.parseInt(""+i+j)){
            				case 30: 
            					gamebuttons[0].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 31: 
            					gamebuttons[1].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 34: 
            					gamebuttons[2].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 35: 
            					gamebuttons[3].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 38: 
            					gamebuttons[4].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 39: 
            					gamebuttons[5].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 40: 
            					gamebuttons[6].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 41: 
            					gamebuttons[7].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 44: 
            					gamebuttons[8].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 45: 
            					gamebuttons[9].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 48: 
            					gamebuttons[10].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 49: 
            					gamebuttons[11].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				}
            			}else{
            				if(i>4){
            					buttons[Integer.parseInt(""+i+j)-20].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            				}else{
            					buttons[Integer.parseInt(""+i+j)].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            				}
            			}
            		}
            	}
        	}
    		
    	}else{
    		
    		for(int i = 0; i<8 ; i++){
            	for(int j = 0; j<10 ; j++){
            		// VANISH RED
            		if(gameBoard.getValue(i, j) > 9 && gameBoard.getValue(i, j) < 22){
            			if(i>2 && i<5){
            				switch(Integer.parseInt(""+i+j)){
            				case 30: 
            					gamebuttons[0].setIcon(getImage("/22.png")); //image
            					break;
            				case 31: 
            					gamebuttons[1].setIcon(getImage("/22.png")); //image
            					break;
            				case 34: 
            					gamebuttons[2].setIcon(getImage("/22.png")); //image
            					break;
            				case 35: 
            					gamebuttons[3].setIcon(getImage("/22.png")); //image
            					break;
            				case 38: 
            					gamebuttons[4].setIcon(getImage("/22.png")); //image
            					break;
            				case 39: 
            					gamebuttons[5].setIcon(getImage("/22.png")); //image
            					break;
            				case 40: 
            					gamebuttons[6].setIcon(getImage("/22.png")); //image
            					break;
            				case 41: 
            					gamebuttons[7].setIcon(getImage("/22.png")); //image
            					break;
            				case 44: 
            					gamebuttons[8].setIcon(getImage("/22.png")); //image
            					break;
            				case 45: 
            					gamebuttons[9].setIcon(getImage("/22.png")); //image
            					break;
            				case 48: 
            					gamebuttons[10].setIcon(getImage("/22.png")); //image
            					break;
            				case 49: 
            					gamebuttons[11].setIcon(getImage("/22.png")); //image
            					break;
            				}
            			}else{
            				if(i>4){
            					buttons[Integer.parseInt(""+i+j)-20].setIcon(getImage("/22.png")); //image
            				}else{
            					buttons[Integer.parseInt(""+i+j)].setIcon(getImage("/22.png")); //image
            				}
            			}
            		}
                	// MAKE BLUE VISIBLE
            		if(gameBoard.getValue(i, j) > 29 && gameBoard.getValue(i, j) < 42){
            			if(i>2 && i<5){
            				switch(Integer.parseInt(""+i+j)){
            				case 30: 
            					gamebuttons[0].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 31: 
            					gamebuttons[1].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 34: 
            					gamebuttons[2].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 35: 
            					gamebuttons[3].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 38: 
            					gamebuttons[4].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 39: 
            					gamebuttons[5].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 40: 
            					gamebuttons[6].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 41: 
            					gamebuttons[7].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 44: 
            					gamebuttons[8].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 45: 
            					gamebuttons[9].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 48: 
            					gamebuttons[10].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				case 49: 
            					gamebuttons[11].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            					break;
            				}
            			}else{
            				if(i>4){
            					buttons[Integer.parseInt(""+i+j)-20].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            				}else{
            					buttons[Integer.parseInt(""+i+j)].setIcon(getImage("/"+gameBoard.getValue(i, j)+".png")); //image
            				}
            			}
            		}
            	}
        	}
    	}
    }
    
   
	private void nextRound(){
    	currentCharacter = -1;
		currentPlacementX = -1;
	    currentPlacementY = -1;
	    
	    futureCharacter = -1;
	    futurePlacementX = -1;
	    futurePlacementY = -1;
    }
    
    
	private ImageIcon getImage(String image){ //image for background
        try{
            return new ImageIcon(ImageIO.read(getClass().getResource(image)).getScaledInstance(120, 120, Image.SCALE_SMOOTH));
        }catch(IOException e){
            e.printStackTrace();
        }
        return null;
    }
    
    
	public void playSound(String soundName){
		try{
			
			File soundFile = new File("sounds/"+soundName);
		    AudioInputStream sound = AudioSystem.getAudioInputStream(soundFile);

		    // load the sound into memory (a Clip)
		    DataLine.Info info = new DataLine.Info(Clip.class, sound.getFormat());
		    Clip clip = (Clip) AudioSystem.getLine(info);
		    clip.open(sound);
			clip.start( );
			
		}catch(Exception ex){
			System.out.println("Error with playing sound.");
			ex.printStackTrace( );
		}
	}

}


/*
if(i == 0 && j == 0){
	if((gameBoard.getValue(i, j+1) > 29 && gameBoard.getValue(i, j+1) < 42) || gameBoard.getValue(i, j+1) == -1){
		if((gameBoard.getValue(i+1, j) > 29 && gameBoard.getValue(i+1, j) < 42) || gameBoard.getValue(i+1, j) == -1){
			// cannot move
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 7 && j == 9){
	if((gameBoard.getValue(i, j-1) > 29 && gameBoard.getValue(i, j-1) < 42) || gameBoard.getValue(i, j-1) == -1){
		if((gameBoard.getValue(i-1, j) > 29 && gameBoard.getValue(i-1, j) < 42) || gameBoard.getValue(i-1, j) == -1){
			// cannot move
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 0 && j == 9){
	if((gameBoard.getValue(i, j-1) > 29 && gameBoard.getValue(i, j-1) < 42) || gameBoard.getValue(i, j-1) == -1){
		if((gameBoard.getValue(i+1, j) > 29 && gameBoard.getValue(i+1, j) < 42) || gameBoard.getValue(i+1, j) == -1){
			// cannot move
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 7 && j == 0){
	if((gameBoard.getValue(i, j+1) > 29 && gameBoard.getValue(i, j+1) < 42) || gameBoard.getValue(i, j+1) == -1){
		if((gameBoard.getValue(i-1, j) > 29 && gameBoard.getValue(i-1, j) < 42) || gameBoard.getValue(i-1, j) == -1){
			// cannot move
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 0){
	if((gameBoard.getValue(i, j+1) > 29 && gameBoard.getValue(i, j+1) < 42) || gameBoard.getValue(i, j+1) == -1){
		if((gameBoard.getValue(i+1, j) > 29 && gameBoard.getValue(i+1, j) < 42) || gameBoard.getValue(i+1, j) == -1){
			if((gameBoard.getValue(i, j-1) > 29 && gameBoard.getValue(i, j-1) < 42) || gameBoard.getValue(i, j-1) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 7){
	if((gameBoard.getValue(i, j-1) > 29 && gameBoard.getValue(i, j-1) < 42) || gameBoard.getValue(i, j-1) == -1){
		if((gameBoard.getValue(i, j+1) > 29 && gameBoard.getValue(i, j+1) < 42) || gameBoard.getValue(i, j+1) == -1){
			if((gameBoard.getValue(i-1, j) > 29 && gameBoard.getValue(i-1, j) < 42) || gameBoard.getValue(i-1, j) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(j == 0){
	if((gameBoard.getValue(i+1, j) > 29 && gameBoard.getValue(i+1, j) < 42) || gameBoard.getValue(i+1, j) == -1){
		if((gameBoard.getValue(1, j+1) > 29 && gameBoard.getValue(i, j+1) < 42) || gameBoard.getValue(i, j+1) == -1){
			if((gameBoard.getValue(i-1, j) > 29 && gameBoard.getValue(i-1, j) < 42) || gameBoard.getValue(i-1, j) == -1){            	            			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(j == 9){
	if((gameBoard.getValue(i, j-1) > 29 && gameBoard.getValue(i, j-1) < 42) || gameBoard.getValue(i, j-1) == -1){
		if((gameBoard.getValue(1-1, j) > 29 && gameBoard.getValue(i-1, j) < 42) || gameBoard.getValue(i-1, j) == -1){
			if((gameBoard.getValue(i+1, j) > 29 && gameBoard.getValue(i+1, j) < 42) || gameBoard.getValue(i+1, j) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if((gameBoard.getValue(i, j+1) > 29 && gameBoard.getValue(i, j+1) < 42) || gameBoard.getValue(i, j) == -1){
	if((gameBoard.getValue(i, j-1) > 29 && gameBoard.getValue(i, j-1) < 42) || gameBoard.getValue(i, j) == -1){
		if((gameBoard.getValue(i+1, j) > 29 && gameBoard.getValue(i+1, j) < 42) || gameBoard.getValue(i, j) == -1){
			if((gameBoard.getValue(i-1, j) > 29 && gameBoard.getValue(i-1, j) < 42) || gameBoard.getValue(i, j) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else{charCountCanMove++;}
*/
/*
if(i == 0 && j == 0){
	if((gameBoard.getValue(i, j+1) > 9 && gameBoard.getValue(i, j+1) < 22) || gameBoard.getValue(i, j+1) == -1){
		if((gameBoard.getValue(i+1, j) > 9 && gameBoard.getValue(i+1, j) < 22) || gameBoard.getValue(i+1, j) == -1){
			// cannot move
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 7 && j == 9){
	if((gameBoard.getValue(i, j-1) > 9 && gameBoard.getValue(i, j-1) < 22) || gameBoard.getValue(i, j-1) == -1){
		if((gameBoard.getValue(i-1, j) > 9 && gameBoard.getValue(i-1, j) < 22) || gameBoard.getValue(i-1, j) == -1){
			// cannot move
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 0 && j == 9){
	if((gameBoard.getValue(i, j-1) > 9 && gameBoard.getValue(i, j-1) < 22) || gameBoard.getValue(i, j-1) == -1){
		if((gameBoard.getValue(i+1, j) > 9 && gameBoard.getValue(i+1, j) < 22) || gameBoard.getValue(i+1, j) == -1){
			// cannot move
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 7 && j == 0){
	if((gameBoard.getValue(i, j+1) > 9 && gameBoard.getValue(i, j+1) < 22) || gameBoard.getValue(i, j+1) == -1){
		if((gameBoard.getValue(i-1, j) > 9 && gameBoard.getValue(i-1, j) < 22) || gameBoard.getValue(i-1, j) == -1){
			// cannot move
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 0){
	if((gameBoard.getValue(i, j+1) > 9 && gameBoard.getValue(i, j+1) < 22) || gameBoard.getValue(i, j+1) == -1){
		if((gameBoard.getValue(i+1, j) > 9 && gameBoard.getValue(i+1, j) < 22) || gameBoard.getValue(i+1, j) == -1){
			if((gameBoard.getValue(i, j-1) > 9 && gameBoard.getValue(i, j-1) < 22) || gameBoard.getValue(i, j-1) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(i == 7){
	if((gameBoard.getValue(i, j-1) > 9 && gameBoard.getValue(i, j-1) < 22) || gameBoard.getValue(i, j-1) == -1){
		if((gameBoard.getValue(i, j+1) > 9 && gameBoard.getValue(i, j+1) < 22) || gameBoard.getValue(i, j+1) == -1){
			if((gameBoard.getValue(i-1, j) > 9 && gameBoard.getValue(i-1, j) < 22) || gameBoard.getValue(i-1, j) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(j == 0){
	if((gameBoard.getValue(i+1, j) > 9 && gameBoard.getValue(i+1, j) < 22) || gameBoard.getValue(i+1, j) == -1){
		if((gameBoard.getValue(1, j+1) > 9 && gameBoard.getValue(i, j+1) < 22) || gameBoard.getValue(i, j+1) == -1){
			if((gameBoard.getValue(i-1, j) > 9 && gameBoard.getValue(i-1, j) < 22) || gameBoard.getValue(i-1, j) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else if(j == 9){
	if((gameBoard.getValue(i, j-1) > 9 && gameBoard.getValue(i, j-1) < 22) || gameBoard.getValue(i, j-1) == -1){
		if((gameBoard.getValue(i-1, j) > 9 && gameBoard.getValue(i-1, j) < 22) || gameBoard.getValue(i-1, j) == -1){
			if((gameBoard.getValue(i+1, j) > 9 && gameBoard.getValue(i+1, j) < 22) || gameBoard.getValue(i+1, j) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
	}else if((gameBoard.getValue(i, j+1) > 9 && gameBoard.getValue(i, j+1) < 22) || gameBoard.getValue(i, j) == -1){
	if((gameBoard.getValue(i, j-1) > 9 && gameBoard.getValue(i, j-1) < 22) || gameBoard.getValue(i, j) == -1){
		if((gameBoard.getValue(i+1, j) > 9 && gameBoard.getValue(i+1, j) < 22) || gameBoard.getValue(i, j) == -1){
			if((gameBoard.getValue(i-1, j) > 9 && gameBoard.getValue(i-1, j) < 22) || gameBoard.getValue(i, j) == -1){
    			// cannot move
			}else{charCountCanMove++;}
		}else{charCountCanMove++;}
	}else{charCountCanMove++;}
}else{charCountCanMove++;}
*/

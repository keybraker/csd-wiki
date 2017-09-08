package Game;

public class Jedi extends Humanoid implements Combatant{

	private String firstName;
	private String lastName;
	private int health;
	
	private int force_level;
	private enum RANK { 
		YOUNGLING,PADAWAN,KNIGHT,
		MASTER,GRAND_MASTER 
	}
	RANK rank;
	
	public Jedi(String firstName, String lastName){
		super(firstName, lastName);

		this.firstName =  firstName;
		this.lastName =  lastName;
		this.health = 10;

		force_level = (int) (Math.random() * 100 + 1);

		if (force_level >= 1 && force_level < 10) {
			rank = RANK.YOUNGLING;
		} else if (force_level >= 10 && force_level < 30) {
			rank = RANK.PADAWAN;
		} else if (force_level >= 30 && force_level < 70) {
			rank = RANK.KNIGHT;
		} else if (force_level >= 70 && force_level < 90) {
			rank = RANK.MASTER;
		} else if (force_level >= 90 && force_level <= 100) {
			rank = RANK.GRAND_MASTER;
		}
	}

	public int getForceLevel() {
		return force_level;
	}

	public RANK getRank() {
		return rank;
	}

	public void attack(Object adversary) {
		if( (adversary instanceof Sith) ){
			if(this.hasWeapon()){/*pos 8a anafertho sto stoixeio pou eimai dhladh Jedi?*/
				switch (rank) {
	            case YOUNGLING:
	            	((Sith) adversary).setHealth(((Sith) adversary).getHealth()-this.getWeapon().getPower());
	            	break;
	            case PADAWAN:
	                ((Sith) adversary).setHealth(((Sith) adversary).getHealth()-this.getWeapon().getPower()-1);
	            	break;         
	            case KNIGHT: 
	            	((Sith) adversary).setHealth(((Sith) adversary).getHealth()-this.getWeapon().getPower()-2);
	            	break;
	            case MASTER:
	            	((Sith) adversary).setHealth(((Sith) adversary).getHealth()-this.getWeapon().getPower()-3);
	            	break;
	            case GRAND_MASTER:
	            	((Sith) adversary).setHealth(((Sith) adversary).getHealth()-this.getWeapon().getPower()-4);
	            	break;
				}
			}else{
				switch (rank) {
	            case YOUNGLING:
	            	break;
	            case PADAWAN:
	                ((Sith) adversary).setHealth(((Sith) adversary).getHealth()-1);
	            	break;         
	            case KNIGHT: 
	            	((Sith) adversary).setHealth(((Sith) adversary).getHealth()-2);
	            	break;
	            case MASTER:
	            	((Sith) adversary).setHealth(((Sith) adversary).getHealth()-3);
	            	break;
	            case GRAND_MASTER:
	            	((Sith) adversary).setHealth(((Sith) adversary).getHealth()-4);
	            	break;
				}
			}
		}else if( (adversary instanceof BattleDroid) ){
			if(this.hasWeapon()){
				switch (rank) {/*pos 8a anafertho sto stoixeio pou eimai dhladh Jedi?*/
	            case YOUNGLING:
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-this.getWeapon().getPower());
	            	break;
	            case PADAWAN:
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-this.getWeapon().getPower()-1);
	            	break;         
	            case KNIGHT: 
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-this.getWeapon().getPower()-2);
	            	break;
	            case MASTER:
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-this.getWeapon().getPower()-3);
	            	break;
	            case GRAND_MASTER:
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-this.getWeapon().getPower()-4);
	            	break;
				}
			}else{
				switch (rank) {
	            case YOUNGLING:
	            	break;
	            case PADAWAN:
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-1);
	            	break;         
	            case KNIGHT: 
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-2);
	            	break;
	            case MASTER:
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-3);
	            	break;
	            case GRAND_MASTER:
	            	((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-4);
	            	break;
				}
			}
		}
	}
		
	public String toString() {
		if(this.hasWeapon() == true){
			return "Jedi:\n"+this.firstName+" "+this.lastName+"\nRank: "+this.rank+"\nWeapon: "+this.getWeapon()+"\n"; 
		}else{
			return "Jedi:\n"+this.firstName+" "+this.lastName+"\nRank: "+this.rank+"\n"; 
		}
	}


}


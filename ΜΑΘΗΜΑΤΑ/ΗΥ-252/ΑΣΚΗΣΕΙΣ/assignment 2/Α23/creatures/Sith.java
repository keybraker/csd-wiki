package Game;

public class Sith extends Humanoid implements Combatant{

	private String firstName;
	private String lastName;
	private int health;
	
	public Sith(String lastName){
		super("Darth", lastName, 10);

		this.firstName =  "Darth";
		this.lastName =  lastName;
		this.health = 10;
	
	}
	
	public void attack(Object adversary) {
		if( (adversary instanceof Jedi) ){
			if(this.hasWeapon()){
	            ((Jedi) adversary).setHealth(((Jedi) adversary).getHealth()-this.getWeapon().getPower());
			}else{
				((Jedi) adversary).setHealth(((Jedi) adversary).getHealth()-1);
			}
		}else if((adversary instanceof BattleDroid)){
			if(this.hasWeapon()){
	            ((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-this.getWeapon().getPower());
			}else{
				((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-1);
			}
		}
	}
	
	public String toString() {
		if(this.hasWeapon() == true){
			return "Sith:\n"+this.firstName+" "+this.lastName+"\nWeapon: "+this.getWeapon()+"\n"; 
		}else{
			return "Sith:\n"+this.firstName+" "+this.lastName;
		}
	}
}

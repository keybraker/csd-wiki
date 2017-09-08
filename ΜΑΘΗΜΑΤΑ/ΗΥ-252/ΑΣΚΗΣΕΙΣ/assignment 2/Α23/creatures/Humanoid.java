package Game;

public abstract class Humanoid extends WeaponCarrier{

	private String firstName;
	private String lastName;
	private int health;
	
	public Humanoid (String firstName, String lastName,int health){
		this.firstName =  firstName;
		this.lastName =  lastName;
		this.health = health;
	}
	
	public Humanoid (String firstName, String lastName){
		this.firstName =  firstName;
		this.lastName =  lastName;
		this.health = 10;
	}
	
	public void setHealth(int health){
		if(health <=0 ){
			this.health = health;
		}else{
			this.health =  health;
		}
	}
	public int getHealth(){
		return health;
	}
	
	public void setCondition(int cond){
		if(cond <=0 ){
			this.health = cond;
		}else{
			this.health =  cond;
		}
	}
	
	public int getCondition(){
		return health;
	}
	
	public boolean isDefeated(){
		if (health <= 0){
			return true;
		} else { 
			return false;
		}
	}
	
	public String getCallSign(){
		return (this.firstName+" "+this.lastName);
	}
	
	public abstract String toString();
	
}


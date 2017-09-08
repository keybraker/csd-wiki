package Game;

public class Lightsaber extends Weapon{

	private enum COLOUR { 
		BLUE,RED
	}
	COLOUR colour;
		
	Lightsaber(){
		super();
		this.power = (int )(Math. random() * 5 + 1);
		//if(this.power == 1){this.power=1;}else{this.power=5;}
	}

	public int getColor(){
		if (colour == COLOUR.BLUE){
			return 1; 
		}else{
			return 0;
		}
	}

	public void setHolder(Object holder){
		this.holder = (WeaponCarrier) holder;
		if(this.holder instanceof Jedi){
			colour = COLOUR.BLUE;			
		}else if( holder instanceof Sith ){
			colour = COLOUR.RED;
		}
	}

	public String toString(){
		return this.colour+" lightsaber, of power "+this.power;
	}
}


package Game;

public class BattleDroid extends Droid implements Combatant {

	int condition = 0;

	public BattleDroid() {

		for (int i = 0; i < 2; i++) {
			name += (int) (Math.random() * 9 + 1);
			name += (char) (Math.random() * 25 + 65);
		}
		condition = 10;
	}

	public BattleDroid(Humanoid master) {

		for (int i = 0; i < 2; i++) {
			name += (int) (Math.random() * 9 + 1);
			name += (char) (Math.random() * 25 + 65);
		}
		condition = 10;
		this.master = master;
	}

	public int getCondition() {
		return condition;
	}

	public void setCondition(int condition) {
		this.condition = condition;
	}

	public String getCallSign() {
		return name;
	}

	public void attack(Object adversary) {
		if (adversary instanceof Sith) {
			((Sith) adversary).setHealth(((Sith) adversary).getHealth()-1);
		}else if(adversary instanceof Jedi){
			((Jedi) adversary).setHealth(((Jedi) adversary).getHealth()-1);
		}else if(adversary instanceof BattleDroid){
			((BattleDroid) adversary).setCondition(((BattleDroid) adversary).getCondition()-1);
		}
	}

	public boolean isDefeated() {
		if (condition <= 0) {
			return true;
		} else {
			return false;
		}
	}

	public void protectMasterFrom(Object adversary) {
		if(master.isDefeated() == false){
			if( ! (master instanceof Jedi && adversary instanceof Jedi || master instanceof Sith && adversary instanceof Sith) ){
				attack(adversary);
			}
		}
	}
	
}

package Game;

public abstract class Droid {

	String name;
	Humanoid master;

	public Droid() {
		name ="";
		this.master = null;
	}

	public Droid(Humanoid master) {
		this.name = "";
		for (int i = 0; i < 2; i++) {
			this.name += (int) (Math.random() * 9 + 1);
			this.name += (char) (Math.random() * 25 + 65);
		}
		this.master = master;
	}

	public void setMaster(Object master) {
		if(master instanceof Jedi){
			this.master = (Jedi) master;
		}else if(master instanceof Sith){
			this.master = (Sith) master;
		}
	}

	public Humanoid getMaster() {
		if (master == null) {
			return null;
		} else {
			return master;
		}
	}

	public String getName() {
		return name;
	}

	public boolean isFree() {
		if (this.master == null) {
			return true;
		} else {
			return false;
		}
	}

	public String toString() {
		if(isFree() == false){
			return ("Droid:\n"+this.name+"\nMaster : "+master.getCallSign()+"\n");
		}else{
			return ("Droid:\n"+this.name+"\nDroid is free\n");
		}
	}

}

package Game;

public abstract class WeaponCarrier {

	//prepei na do an prepei na ta orizo 
	//ola pali h an xanetai h plhroforia 
	//otan ta ksana orizo 
	
	private Weapon weapon;// = new Weapon();

	public WeaponCarrier(){
		 this.weapon = null;
	}

	public Weapon getWeapon() {
		return this.weapon;
	}

	public boolean hasWeapon() {
		if (this.weapon == null) {
			return false;
		} else {
			return true;
		}
	}

	public void setWeapon(Weapon weapon) {
		this.weapon = weapon;
		weapon.setHolder(this);
	}

}

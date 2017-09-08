package Game;

public abstract class Weapon {

	protected int power;
	protected WeaponCarrier holder;// = new WeaponCarrier();

	public Weapon() {

		
		power = (int) (Math.random() * 2 + 1);

		if (power == 1) {
			power = 1;
		} else {
			power = 5;
		}

	}

	public int getPower() {
		return power;
	}

	public abstract void setHolder(Object holder);

	public WeaponCarrier getHolder() {
		if (holder.getWeapon() != null) {
			return holder;
		} else {
			return null;
		}
	}

	public abstract String toString();
}

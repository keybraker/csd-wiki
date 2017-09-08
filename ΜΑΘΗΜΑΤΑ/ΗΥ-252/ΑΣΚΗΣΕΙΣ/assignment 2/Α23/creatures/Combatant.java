package Game;

public interface Combatant {
	
	void attack(Object adversary);
	
	boolean isDefeated();
	
	int getCondition();
	
	void setCondition(int condition);
	
	String getCallSign();
	
}

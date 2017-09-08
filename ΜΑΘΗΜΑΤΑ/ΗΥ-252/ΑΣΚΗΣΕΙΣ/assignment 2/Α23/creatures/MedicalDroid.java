package Game;

public class MedicalDroid extends Droid {

	int medicalSkills;

	public MedicalDroid() {

		medicalSkills = (int) (Math.random() * 2 + 1);
		if (medicalSkills == 1) {
			medicalSkills = 1;
		} else {
			medicalSkills = 3;
		}

		for (int i = 0; i < 2; i++) {
			name += (int) (Math.random() * 9 + 1);
			name += (char) (Math.random() * 25 + 65);
		}

	}

	public MedicalDroid(Humanoid master) {

		this.master = master;

		medicalSkills = (int) (Math.random() * 2 + 1);
		if (medicalSkills == 1) {
			medicalSkills = 1;
		} else {
			medicalSkills = 3;
		}

		for (int i = 0; i < 2; i++) {
			name += (int) (Math.random() * 9 + 1);
			name += (char) (Math.random() * 25 + 65);
		}
	}

	public int getMedicalSkills() {
		return medicalSkills;
	}

	public String getName() {
		return name;
	}

	public void healMaster() {
		if (master != null) {
			master.setHealth(master.getHealth() + medicalSkills);
		}
	}

}

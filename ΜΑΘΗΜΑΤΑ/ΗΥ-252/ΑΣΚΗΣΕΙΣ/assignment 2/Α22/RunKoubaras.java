package ADT;

public class RunKoubaras implements Koubaras{

	public void addKerma(KoubarasMoney koubaras, float K) {
		
		koubaras.setKerma(koubaras.getKerma()+K);
		
	}

	public void addXarti(KoubarasMoney koubaras,int X) {

		koubaras.setXarti(koubaras.getXarti()+X);
		
	}

	public boolean isFull(KoubarasMoney Koubaras) {
		
		if((Koubaras.getKerma() > Koubaras.getMaxKerma() ) || (Koubaras.getXarti() > Koubaras.getMaxXarti() )){
			return true;
		}else{
			return false;
		}
		
	}

	public void breaκ_Koubaras(KoubarasMoney Koubaras) {

		System.out.println(Value(Koubaras));
		
		Koubaras.setKerma(-1);
		Koubaras.setXarti(-1);

	}

	public float Value(KoubarasMoney Koubaras) {

		float all = 0;

		all += Koubaras.getKerma();
		all += Koubaras.getXarti();
		
		return all;
	}

	public boolean isBroken(KoubarasMoney Koubaras) {

		if(Koubaras.getKerma() == -1 && Koubaras.getXarti() == -1){
			return true;
		}else{
			return false;
		}

	}

}

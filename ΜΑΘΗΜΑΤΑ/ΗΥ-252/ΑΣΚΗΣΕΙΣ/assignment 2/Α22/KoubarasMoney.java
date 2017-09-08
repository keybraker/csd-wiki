package ADT;

public class KoubarasMoney {

	private float Kerma = 0;
	private int Xarti = 0;
	
	private float MaxKerma = 0;
	private int MaxXarti = 0;

	
	public KoubarasMoney(float K ,int X){
		MaxKerma = K;
		MaxXarti = X;
	}
	
	public float getKerma(){
		return Kerma;
	}
	public int getXarti(){
		return Xarti;
	}
	
	public void setKerma(float K){
		Kerma = K;
	}
	public void setXarti(int X){
		Xarti = X;
	}
	
	public float getMaxKerma(){
		return MaxKerma;
	}
	public int getMaxXarti(){
		return MaxXarti;
	}
	
}

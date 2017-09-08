package ADT;



public class Execute {
	public static void main(String[] args) {
		
		KoubarasMoney K = new KoubarasMoney(30,30);	
		RunKoubaras Koubaras = new RunKoubaras();
		
		System.out.println("Kerma = "+K.getKerma());
		System.out.println("Xarti = "+K.getXarti());
		
		System.out.println("\nMaxKerma = "+K.getMaxKerma());
		System.out.println("MaxXarti = "+K.getMaxXarti());
		
		Koubaras.addKerma(K,10);
        Koubaras.addKerma(K,2);
        
        Koubaras.addXarti(K,5);
        Koubaras.addXarti(K,20);

        System.out.println("isFull = "+Koubaras.isFull(K));
        System.out.println("Value = "+Koubaras.Value(K));
        System.out.println("isBroken = "+Koubaras.isBroken(K));
        
        System.out.println("\n");
        Koubaras.addKerma(K,10);
        Koubaras.addKerma(K,2);
        
        Koubaras.addXarti(K,5);
        Koubaras.addXarti(K,20);

        System.out.println("isFull = "+Koubaras.isFull(K));
        System.out.println("Value = "+Koubaras.Value(K));
        System.out.println("isBroken = "+Koubaras.isBroken(K));
        System.out.println("\n");
        
        System.out.println("is broken = "+Koubaras.isBroken(K));
        if(Koubaras.isFull(K) == true ){
        	Koubaras.breaκ_Koubaras(K);
        }
        System.out.println("is broken = "+Koubaras.isBroken(K));
        
	}
}

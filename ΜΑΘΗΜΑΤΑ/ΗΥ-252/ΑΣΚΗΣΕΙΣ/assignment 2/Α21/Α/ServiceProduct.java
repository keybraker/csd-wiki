package Store;

class ServiceProduct extends Product{
	
	private String name;
	private String barCode;
	private float price;
	private int numOfCus ;
	 
	public ServiceProduct(String orderName, String orederBarCode, float orderPrice) {
		super(orderName, orederBarCode, orderPrice);
							
		name = "κουβερ";
		barCode = "b001";
		price = 0;
		//numOfCus = getNumofCustomers(); 	
		
	}	 
	 
	 public String toString(){
			
			String product = " "+name+" | Barcode: "+barCode+" | Price: "+price;
			return product;  
			
	 }
	 
	 public float getPrice(){
			return (price*numOfCus);
	}

}

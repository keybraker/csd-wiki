package Store;

public class Product{
	
	  private String name;
	  private String barCode;
	  private float price;

	//Constructor
	public Product(String orderName, String orederBarCode, float orderPrice) {
			
		name = orderName;
		barCode = orederBarCode;
		price = orderPrice;
		
	}
	
	public String toString(){
		
		int lengthName = name.length();
		int lengthBarcode = barCode.length();
		int i = 0;
		
		String product = "| "+name;
		while(i<10-lengthName){product += " ";i++;}
		product += "| "+barCode;
		i=0;
		while(i<8-lengthBarcode){product += " ";i++;}
		product += "| "+price+"€";
		
		return product;  
		
	}
	
	public float getPrice(){
		return price;
	}
	
	public String getBarcode(){
		return barCode;
	}
	
	public String getName(){
		return name;
	}

}

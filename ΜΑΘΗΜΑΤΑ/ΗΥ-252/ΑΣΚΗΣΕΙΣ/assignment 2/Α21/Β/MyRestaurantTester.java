package Store;

import java.util.Date;

public class MyRestaurantTester {
	public static void main(String[] args) {
		
		//System.out.println("kappa\n");
		
		Product salad = new Product("salad", "0b01", 7);
		Product snitchel = new Product("snitchel","0b01",8);
		Product beer = new Product("beer","0b03",3);
		
		Date date1 = new Date( );
		
		Paraggelia p = new Paraggelia(date1, "one");
		p.setNumOfpeople(2);
		
		p.addProduct(salad);
		
		p.addProduct(snitchel);
		p.addProduct(snitchel);

		p.addProduct(beer);
		p.addProduct(beer);

		System.out.println(p.getReceipt());
		
		Date date2 = new Date( );
		
		Paraggelia p2 = new Paraggelia(date2, "two");
		p2.setNumOfpeople(3);
		
		p2.addProduct(snitchel);
		p2.addProduct(snitchel);

		p2.addProduct(beer);
		p2.addProduct(beer);
		
		System.out.println("\n");
		System.out.println(p2.getReceipt());
		
    }
}

	

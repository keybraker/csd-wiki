package Store;

import java.util.ArrayList;
import java.util.Date;

public class Paraggelia{

	//Three fields
	private Date date;
	private String NumberOfTable;
	private int NumberOfCustomers;
	
	//Dynamic Array to store Names,NumberTemaxia,barcode,price
	ArrayList<Product> allProduct = new ArrayList<Product>();
	ArrayList<Integer> ammount = new ArrayList<Integer>();
	
	//Constructor
	public Paraggelia(Date orderDate, String numTables) {
		
		date = orderDate;
		NumberOfTable = numTables;
		
	}
	
	//Methods
	
	//Gets date
	public void setDate(Date inpuntDate){
		date = inpuntDate;
	}
	
	//Gets number of Table
	public void setNumOfTable(String numTable){
		NumberOfTable = numTable;
	}
	
	//Gets number of Customers
	public void setNumOfpeople(int numCustomers){
		NumberOfCustomers = numCustomers;
	}
	
	//Adds Product
	public void addProduct(Product p){
		if(allProduct.indexOf(p) == -1){
			allProduct.add(p);
			ammount.add(1);
		}else{
			ammount.set(allProduct.indexOf(p),ammount.get(allProduct.indexOf(p))+1);
		}
	}
	
	//Removes Product
	public void deleteProduct(Product p){
		int memOfp = allProduct.indexOf(p);
		if(memOfp == -1){
			//Does Nothing
		}else{
			if(ammount.get(memOfp) == 1){
				ammount.remove(ammount.get(memOfp));
				allProduct.remove(allProduct.get(memOfp));
			}else{
				ammount.set(allProduct.indexOf(p),ammount.get(allProduct.indexOf(p))-1);
			}
		}
	}
	
	//Returns Total Price
	public float getTotalPrice(){

		float fPrice=0;		
		
		int i=0;
		while(i < allProduct.size()){
			fPrice += ammount.get(i)*allProduct.get(i).getPrice();
			i++;
		}
		return fPrice;
	}
	
	//Returns Receipt
	public String getReceipt(){

		String fString = "" ;
		
		fString += "                WELCOME TO                 \n";
		fString += "                YOUR LOCAL                 \n";
		fString += "                  STORE                    \n";
		fString += "----------------------------------------\n";

		fString += "Date : "+date.toString();
		fString += "\nTable Number : "+NumberOfTable;
		fString += "\nNumber of Customers : "+NumberOfCustomers+"\n\n";
		fString +=  " Countity | Name      | Barcode | Price\n";
		fString += "-----------------------------------------\n";

		int i=0;
		while(i < allProduct.size()){

			fString += "|   "+ammount.get(i)+"x    "+allProduct.get(i).toString()+"  |\n";
			i++;
			
		}

		fString += "-----------------------------------------\n";
		fString += "                          Total: "+getTotalPrice()+"€\n\n";
		fString += "               THANK YOU!                 \n";


		return fString;
	}

	public int getNumofCustomers(){
		return NumberOfCustomers;
	}
	
	public String getNumofTable(){
		return NumberOfTable;
	}
	
}

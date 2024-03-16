

import java.util.Random;

public class stranicenje {
	static int N=2;
	static int M=1;
	static int disk[][] = new int[N][16];
	static int tablica[][] = new int[N][16];
	static int okvir[] = new int[M];
	static int t;
	
 public static void main (String[] args) throws InterruptedException {
		
		
		for(int i=0; i<N; i++) {
			  for(int j=0; j<16; j++) {
				  disk[i][j]= 0;
			  }
			  for(int j=0; j<16; j++) {
				  tablica[i][j]= 0;
			  }
			
	    }
		
	
	for(int i=0; i<M; i++) {
		okvir[i]= 0;
	 }
	
	
	t=0;
	int x;
	int r;
	int p;
	int q=0;
	
	
 while(true) {
		for(int k=0; k<N; k++) {
			System.out.printf("Proces: ");
			System.out.println(k);
			System.out.printf("t:");
			System.out.println(t);
			Random ra = new Random();
			x= ra.nextInt(65536);
			
			x = x&0X3FE;
			//x=0x01FE;
			p = x&0b111111;
			r= x&0b1111000000;
			r = r>>6;
		    System.out.printf("Logička adresa:");
			//System.out.println(" x= "+ Integer. toBinaryString(x));
		     // System.out.println(" p= "+ Integer. toBinaryString(p));
		     // System.out.println(" r= "+ Integer. toBinaryString(r));
		    System.out.println(String.format(" x= "+"0x%04X", x));
		    
		    
		    String broj= Integer.toBinaryString(x);
		    String brojp= Integer.toBinaryString(p);
		    String brojr= Integer.toBinaryString(r);
		    
		    int mjesto = 0;
		    int pun=0;
		      if(tablica[k][r]==0) {
		    	  
		          System.out.println("promašaj!");
		    	
		    	  for(int l=0; l<M; l++) {
		    		  if(okvir[l]==0) {
		    			  mjesto = l;
		    			  okvir[l] = disk[k][r];
		    			  System.out.printf("Dodijeljen okvir: ");
		    			  System.out.println(mjesto);
		    			  pun=0;
		    			  break;
		    		  }
		    		  pun =1;
		    	  } 
		    	  
		    	  if (pun==1) {
		    		  int min=9999999;
		    		  int minokvir;
		    		  int mini=0, minj=0;
		    		  int uokviru=0;
		    		  int adresautab =0;
		    		  
		    		  for(int i=0; i<N; i++) {
		    			  for(int j=0;j<16;j++) {
		    				   adresautab = tablica[i][j]&0b1111000000 ;
		    				   adresautab = adresautab>>6;
		    			       int prisutnost = tablica[i][j]&0b100000;
		    			       prisutnost = prisutnost >>5;
		    	               int lru = tablica[i][j]&0b11111;
		    	              
		    	              if(prisutnost==1) {
		    	                if(lru<min) {
		    	            	  min = lru;
		    	            	  minokvir = adresautab;
		    	            	  mini=i;
		    	            	  minj=j;
			    				  uokviru = okvir[adresautab];
			    				  mjesto = adresautab;
		    	                }
		    				
		    	              }  
		    		}
		    			  
		    			  
		    			  
		    			  
		    		  }
	System.out.printf(String.format("Izbacujem stranicu " + "0x%04X", minj<<6));  
	System.out.println(String.format(" iz procesa " + "%d", mini));
	System.out.println(String.format("lru izbacene stranice " + "0x%04X", min)); 
	
	                  okvir[mjesto]=0;
		    		  tablica[mini][minj]=0;
		    		  disk[mini][minj]= uokviru;
	    			  //System.out.println(adresautab);
		    		  //System.out.println(min);
		    		  System.out.printf("Dodijeljen okvir: ");
	    			  System.out.println(mjesto);
		    		  
		    	  }
		    	  
		    	  
		    	 String mjestost = Integer.toBinaryString(mjesto);
		    	 int len = mjestost.length();
		    	 int dodaj = 4-len;
		    	 String s = "";
		    	 for(int i=0;i<dodaj;i++) {
		    		s= s+"0";
		    		// System.out.println(s);
		    	 }
		    	 
		    	 
		    	 String tst = Integer.toBinaryString(t);
		    	 int len2 = tst.length();
		    	 int dodaj2 = 5-len2;
		    	 String s2 = "";
		    	 
		    	 for(int i=0;i<dodaj2;i++) {
		    		s2= s2 + "0";
		    	 }
		    	 
		    	 
		    	String adresa = "000000"+ s + mjestost + "1" + s2 + tst  ;
		    	//System.out.println(adresa);
		    	int adresaint = Integer.parseInt(adresa,2);
		    	tablica[k][r]= adresaint;
		    	//System.out.println("zapis tablice: "+Integer.toHexString(tablica[k][r]));
		    	// System.out.println(Integer.toBinaryString(adresaint));
		    	System.out.printf("fizička adresa: ");
	   			int fizicka = tablica[k][r]&0b1111111111000000;
	   			fizicka = fizicka | p;
	   			System.out.println(String.format("0x%04X", fizicka));
		    	System.out.println(String.format("zapis tablice: "+"0x%04X", tablica[k][r]));
		    	  
		           } else {
		        	   
		    	 mjesto = tablica[k][r]&0b1111000000;
		    	 mjesto = mjesto>>6;
		    	 //System.out.println(tablica[k][r]);
		    	 tablica[k][r] = tablica[k][r]&0b1111111111100000;
		    	 // System.out.println(tablica[k][r]);
		    	 tablica[k][r]  = tablica[k][r] | t;
		    	 System.out.println(tablica[k][r]);
		    	 System.out.printf("Dodijeljen okvir: ");
   			     System.out.println(mjesto);
   			     //System.out.println("zapis tablice: "+ Integer.toHexString(tablica[k][r]));
		    	//okvir[mjestookvira]++;
   			    System.out.printf("fizička adresa: ");
   			    int fizicka = tablica[k][r]&0b1111111111000000;
   			    fizicka = fizicka | p;
   			    System.out.println(String.format("0x%04X", fizicka));
   			    System.out.println(String.format("zapis tablice: "+"0x%04X", tablica[k][r]));
		      }
			
			
			  if(t==31) {
				   t=0;
				for (int t=0; t<N;t++) {
					for(int j=0;j<16;j++) {
						tablica[t][j] = tablica[t][j]&0b100000;
					}
				}
			}
			  
			  
			t++;
			okvir[mjesto] = okvir[mjesto]+1;
			//System.out.println(okvir[mjesto]);
			System.out.printf("sadrzaj adrese: ");
			System.out.println(disk[k][r]);
			System.out.println();
			Thread.sleep(4000);
		}
		
		
	}
	
	
	
 }
}

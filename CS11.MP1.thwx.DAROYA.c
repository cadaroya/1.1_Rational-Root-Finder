/**


Name: 				DAROYA, Carlos Adrian A.
Student #:  		2015-07397
Section:			thwx

Description: 		The following code is Rational Root Finder. Given user-inputted degree and coefficients
					that corresponds to a polynomial, the program can solve for its rational roots. It uses
					the idea of Remainder theorem such that in:
					
					P(x) = (x - r) q(x) + R
					if P(p/q) = 0, then p/q is a root of the polynomial. 
					
					The code solves for the remainder of the whole polynomial by continuous "substitution"
					of the p/q values for every term. 
					
					To prevent floating point precision errors, the program utilizes solely int data types in
					solving for the remainder. It uses operations on separated numerators and denominators in
					the function getremainder().
					
					If the solved numerator (which is the remainder) equals to zero, then p/q will be stored as root.
					
					The program will then sort the roots stored in an array in ascending order and finally print them
					out as fractions OR whole numbers as necessary.
					
					Additional Notes:
					*The program prints the roots in its lowest terms
					*User-input is validated through the return value of sscanf 
					*Input validation allows space in appropriate cases (Allows inputs such as: 1, 2, 2 ,1 BUT not in: 1 1)
					*The program detects constant inputs
					
					
**/


//Including libraries

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main(); // Declaration of main 




int findgcf(int num1, int num2)	     //function that finds the gcf of two numbers: p and q
{
    int i, hcf;						 //declaration

    for(i=1; i<=num1 || i<=num2; ++i)
    {
        if(num1%i==0 && num2%i==0)   // Checking whether i is a factor of both number
            hcf=i;					 // defines hcf with value i
    }

    return hcf;   // The function will return hcf
}

int getremainder(int p, int q, int degree, int coeff[])
{
	coeff[degree+1]=0;  //initializes the EXCESS last index as zero
	int i,j;			//counters
	int a,b,c,d,e,f;    //variables to be used for operations
	
	e=0;f=1;			//initialize


	for(i=0;i<degree+1;i+=2) 		// code block that "converts" the operation to fractions; separating numerator and denominator as it solves
	{
									// solves per term starting from the lowest degree term

		a = (coeff[i])*pow(p, i);	// coefficient * (p/q)^i   is equal to (coeff * p^i) / q^i
		b = pow(q, i);				
	
		a = a*f + e*b;				// adds (a/b) to the solved (e/f) from the previous iteration
		b = b*f;					// the answer will be the new (a/b)

		for(j=i+1;j<=i+1;j+=2)		// loop that adds (a/b) to the next term
		{
			if(i<degree+1)			// stops at the last term
			{

				c = (coeff[j])*(pow(p, j));	// solves for (c/d)
				d = pow(q, j);
				
			}
			
		}
		
		e = a*d + b*c;				// (a/b) + (c/d) is added and redefined as (e/f)
		f = b*d;
	}
	
	
	
	if(e==0)
	{
		return 0;					//returns zero as remainder if the numerator e is zero
	}
	
	else
	{
		return 1;					//returns 1 to falsify the catching statement and not record p/q as a root
	}
		
}

int getroots(int p, int q, int dsize,int coeff[])
{
	
	/*****FACTORING p AND q ******/ 
	//gets the factors of p and q

	int i,z;
	
	int pfactor[10000]; 				//array pfactor will be storing all factors of p
	int k=0; 							//counter for pfactor array
		
			for(i=1;i<=sqrt(p);i++) 	//factoring code block
			{
				if(p%i==0)
				{
					pfactor[k++]=i; 
			
					if(i!=(p/i))
					{
						pfactor[k++]=p/i;
				
					}
				}
			}
			
	int qfactor[10000]; 				//array qfactor will be storing all factors of q
	int j=0; 							//counter for qfactor array
			
			for(i=1;i<=sqrt(q);i++)
			{
				if(q%i==0)
				{
					qfactor[j++]=i;
					if(i!=(q/i))
					{
						qfactor[j++]=q/i;
					}
				}
			}
			
	/*****END OF FACTORING SEGMENT******/ 


	int ctr; 						// counter declaration
	int h=0;						// index counter
	int count=0; 					// index counter for roots array
	
	float PQarray; 					// variable storing p/q
	float roots[100000]; 			// stores the decimal roots
	float sum; 						// the remainder to be checked for each run 
	
	int p2[1000]; 					//stores a root's numerator
	int q2[1000]; 					//stores a corresponding denominator
	
	
	
		if((getremainder(0, 1, dsize, coeff)==0)) 	// starts getting remainder for (p/q) = 0
					{
						roots[h] = 0;
						p2[h]= 0; 					//assigns zero to numerator if statement is true
						q2[h] = 1; 					//assigns 1 to denominator if statement is true
						h++; 						//increments h to move to the next index
					}
		
	/*****ROOT SOLVING SEGMENT******/ 
	
			for(i=0;i<k;i++) // for loop the gets all the p/q factors
			{
				for(ctr=0;ctr<j;ctr++)
				{
					PQarray=((float)pfactor[i])/((float)qfactor[ctr]); 				//casting of p and q to float to get decimal version of p/q
					if((getremainder(pfactor[i], qfactor[ctr], dsize, coeff)==0))
					{
						roots[h] = PQarray;			//assignment of values
						p2[h]= pfactor[i];
						q2[h] = qfactor[ctr];
						h++;						//increments counter h
					
					}				
					
					PQarray=((float)pfactor[i])/((float)(qfactor[ctr]*-1));			//solves for  negative factors
					if((getremainder(pfactor[i]*-1, qfactor[ctr], dsize, coeff))==0)
					{
						roots[h] = PQarray;
						p2[h]= pfactor[i]*-1;
						q2[h] = qfactor[ctr];
						h++;
						
					}	
				}
			}
			
			
		/*****DELETING SEGMENT******/ 
		// Repeated roots are deleted from the roots[] array
			
		for(i=0;i<h;i++)
		{ 
			for(j=i+1;j<h;j++)
			{ 
				if(roots[i] == roots[j])
				{  
					
					for(k=j;k<h;k++)
					{

						roots[k] = roots[k+1];
						p2[k] = p2[k+1];
						q2[k] = q2[k+1];
						
					}
					 j--; //backtrack
					 h=h-1;
				}
			}
			
	}
	
	/*****GETTING THE LOWEST TERMS OF ROOTS******/ 

	int gcf;

	for(i=0;i<h;i++)
		{	
				gcf = findgcf(p2[i],q2[i]);		// sends p and q to findgcf function to get the gcf
				
				if(gcf == 1)					//if gcf is 1, the loop continues
				continue;
				
				else if(gcf != 0)
				{
					p2[i] = p2[i] / gcf;		//dividing the p and q by its lowest terms
					q2[i] = q2[i] / gcf;	
				}	
		}
		

			
	/*****SORTING OF ROOTS******/ 

		float temp;
	
	//Bubble sorting
	
		for(i=0;i<h-1;i++)
		{
			for(ctr=0;ctr<(h-i-1);ctr++)
			{
				if(roots[ctr]>roots[ctr+1])
				{
					//basis decimal root array
					//swapping
					
					temp = roots[ctr];
					roots[ctr] = roots[ctr+1];
					roots[ctr+1] = temp;
					
					temp = p2[ctr];
					p2[ctr] = p2[ctr+1];
					p2[ctr+1] = temp;
					
					temp = q2[ctr];
					q2[ctr] = q2[ctr+1];
					q2[ctr+1] = temp;
					
				}
			}
		}
		
	/*****PRINTING OF SORTED ROOTS******/ 
	
			if(h>0) 									//if roots are present
			{	
				printf("\nThe rational root/s of the polynomial is/are: ");
				for(i=0;i<h;i++)
				{
					if(q2[i]==1) 						//if denominator is 1, it prints just the numerator
					{
						printf("%d", p2[i]);
					}
					
					else								//else, it prints the fraction
					{	
					
						printf("%d/%d", p2[i],q2[i]);
					}
					
					if(i<h-1)							//prints commas until the last root
						printf(",");
			
				}
			}
			
			else 										//else, there are no roots
			printf("\nThe polynomial has no rational roots");
			
			return 0;
}

int getpq(int coeff[], int maxx)
{
	int i,x;		 //counters
	int p=0,q=0; 	 //p and q initialized as zero
	
		for(i=maxx;i>=0;i--) 		//starts checking from the coeff of highest degree
			{
				if(coeff[i]!=0) 	// if statement that assigns the value of coefficient to q if it's not equal to 0
				{
				
					q=coeff[i]; 
					break; 			// breaks the loop once q is assigned
				}
				
				else 				// continues to the coefficient of the next term 
				continue;
			}
	
		for(x=0;x<i;x++) 			// starts checking from the coeff of term with lowest degree UNTIL before where the q assigning loop stopped
			{
				if(coeff[x]!=0) 	// if statement that assigns the value of coefficient to p if it's not equal to 0
				{
				
					p=coeff[x];
					break; 			// breaks the loop once p is assigned
				}
				
				else 				// continues to the coefficient of the next term
				continue;
			}
	
	
	if(p<0) // gets the positive p
	p=p*-1;
	
	
	if(q<0) // gets the positive q
	q=q*-1;
		
	//INITIAL CASES (Prevent dividing by zero)
	
		if(p==0 && q==0) 		//When all inputs are zero
			{
				printf("\nThere are no rational for a constant input.");
			}
	

		else if(p==0 && q!=0) 	//When user only input one term which is not the constant
			{
				printf("\nThe rational roots of the polynomial is: 0");
			}
			
		else if(p!=0 && q!=0) 	//When there are nonzero inputs for p and q
			{
				getroots(p,q,maxx,coeff);
			}
			
		else
				printf("\nThe polynomial has no rational roots");
				
				return 0;
}

int coeffparsevalidate(int max) 	//reassigns degree as int max
{
	char tokenstring[1000]; 		// inputted string
	char delims[] = ","; 			// comma as delimiter
	char* token; 					// token pointer
	
	
	int input[1000]; 				// array that will be storing parsed inputs
	int num,n; 
	
	int count=0,flag=0,i;			 // declaration of counters
	char* cp,badc;					 // badc is for detecting extraneous chars in the input
	
	
	/*****INPUT VALIDATION PER PARSED TOKEN******/ 
	
	while(flag==0) // outer loop
	{
		cp = fgets(tokenstring, sizeof(tokenstring), stdin); 	//reads user-input as tokenstring using fgets
		token = strtok (tokenstring, delims);					// first tokenizing step
		
		if (cp == tokenstring)
        {
			while (token != NULL)
				{
				    n = sscanf(token, "%d %c", &num, &badc); 	//re-scans the tokenized string as integer and character
		
				    if(n!=1) 		//the return value "n" is only equal to 1 when sscanf scanned an integer
					    
						{
					    	printf("\nInvalid Input! Try again: ");
					    	count = 0; 				//resets count to allow overwriting of input array
					    	flag = 0; 				//falsifies the flag to re-enter the outer while-loop
					    	break; 					//breaks the inner while-loop
						}
						
					else
						{
					
							input[count++] = num;				//assigning the validated,parsed integer input to input[count++]
							token = strtok (NULL, delims); 		//tokenizing code block						
							flag = 1; 							//escape the outer while loop when inputs are correct
						}
				}
				
			if(count>(max+1)||count<(max+1)) 					// Checks if the number of coefficients are wrong
				{
					printf("\nInvalid number of coefficients! Try again: ");
				   	count = 0; 		//resets count to allow overwriting of input array
				   	flag = 0; 		//falsifies the flag to re-enter the outer while-loop
				}
		}
		
	}
	
	getpq(input,max); //sends coefficients (input) and degree (max) to getpq()
	
	return 0;
}



int getdegreevalidate()
{
	int num;
	int flag=0;
    char input[1000]; // arbitrary size buffer
    char* cp, badc; // badc is for detecting extraneous chars in the input
    int n;
    
    
   	/*****INPUT VALIDATION OF DEGREE******/ 
   	
    while(flag == 0)
    {
	
        cp = fgets(input, sizeof(input), stdin);		//reads user-input as tokenstring using fgets
        if (cp == input)
        {
            n = sscanf(input, "%d %c", &num, &badc);	//re-scans the string as integer and character
            if (n != 1) 								//the return value "n" is only equal to 1 when sscanf scanned an integer
            {
                printf("Error! Enter a new degree: ");
                flag = 0;								//falsifies the flag to re-enter the outer while-loop
            }
            
            else if(num < 0)							//negative inputs validation
            {
            	printf("Error! Input a Positive degree: ");
            	flag = 0;								//falsifies the flag to re-enter the outer while-loop
			}
			
            else
                flag = 1;
            
        }
    }

    return num;
}

int main()
{
	int DEGREE;
	
	printf("Enter the highest degree of the polynomial: ");
	
	DEGREE=getdegreevalidate(); 				// Calls getdegreevaliaate() and have its return value assigned to DEGREE
	
	
	printf("\nEnter %d integer coefficients starting from the 0th degree.\nSeparate each input with a comma: ", DEGREE+1);
	
	
	coeffparsevalidate(DEGREE); 			 	// Calls coeffparsevalidate() to prompt user to input coefficients
	
	//ASKING FOR NEW POLYNOMIAL
	
	char string[100];
	char ask[100];
	int flag = 0; 
    
	printf("\nInput new polynomial? ");
	
	/*****INPUT VALIDATION OF RESTART ANSWER******/ 
	while(flag == 0)
		{		
					fgets(string, sizeof(string), stdin);
					sscanf(string, "%[^\n]s", ask);
			
					if(strcasecmp(ask, "yes")==0)
					{
					flag = 1;
					main();
					}
					
					else if(strcasecmp(ask, "no")==0)
					{
					return 0;	
					}
					
					else
					{
					printf("\nInvalid Input. Try again: ");
					flag = 0;
					}
					
		}
}



#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <ctime>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtoull */

using namespace std;

string divisionStr(string value,int from,int to){
	return value.substr(from,to);
}
unsigned long long int power(unsigned long long int value,unsigned long long int powerValue){
	unsigned long long int sum=1;
	
	int i=0;
	while(i<powerValue){
		sum = sum*value;
		i++;
	}
	return sum;

}
/*For Running Time Calculation*/
int frequency_of_primes (int n) {
  int i,j;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}


 unsigned long long int binaryToDecimalStr(string inresult){
 	
	unsigned long long int value = 0;
	int indexCounter = 0;
	for(int i= inresult.length()-1;i>=0;i--){

    	if(inresult[i]=='1'){
        	//value += pow(2, indexCounter);
    		value += (2<<indexCounter-1);
		}
    	indexCounter++;
	}
	
    return value;
}

int maxLength(string bstr1,string bstr2)
{
	return ( bstr1.size() > bstr2.size() ? bstr1.size() : bstr2.size() );
}
int findLength(string &bstr1, string &bstr2)
{
    int len1 = bstr1.size();
    int len2 = bstr2.size();
    
	if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            bstr1 = '0' + bstr1;
        return len2;
    }
    if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            bstr2 = '0' + bstr2;
    }
    return len1; 
}

string  addBitStrings( string first, string second )
{
    string result;  

    // make the lengths same before adding
    int length = findLength(first, second);
    int carry = 0;  // Initialize carry

    // Add all bits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';

        // 	XOR for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';

        result = (char) sum + result;

        // boolean expression for 3-bit addition
        carry = (firstBit&secondBit) | (secondBit&carry) | (firstBit&carry);
    }

    // if overflow, then add a leading 1
    if (carry)  result = '1' + result;

    return result;
}



 unsigned long long int multiply(string X, string Y)
{
    // Find the maximum of lengths of x and Y and make length
    // of smaller string same as that of larger string
    int n = findLength(X, Y);
    
    if (n == 1) 
	return (X[0] - '0')*(Y[0] - '0');

    int firstpart = n/2;   // First half of string, floor(n/2)
    int secondpart = n - firstpart ; 

    
   
    string xL = divisionStr(X,0,firstpart);
    string xR = divisionStr(X,firstpart,secondpart);

    string yL = divisionStr(Y,0,firstpart);
    string yR = divisionStr(Y,firstpart,secondpart);
    // Recursively divide the numbers and then find bit by bit result
    unsigned long long int P1 = multiply(xL, yL);
    unsigned long long int P2 = multiply(xR, yR);
    unsigned long long int P3 = multiply(addBitStrings(xL, xR), addBitStrings(yL, yR))-(P2+P1);
	
	return P1*(1<<(2*secondpart)) + P3*(1<<secondpart) + P2; ; 
}

string classicalMultiply(string X, string Y) 
{ 
	int n = maxLength(X, Y);
    int n1 = X.size(); 
    int n2 = Y.size(); 
    string preresult;
    
	if (n == 1){
		preresult+=(X[0]-'0')*(Y[0]-'0')+'0';
		return preresult;
	}

   
    
    vector<int> result(n1 + n2);
	fill(result.begin(),result.end(),0);
   
    // Below two indexes are used to find positions 
    // in result.  
    int i_n1 = 0;  
    int i_n2 = 0;  
	
	//Start at last index of string
    for (int i=n1-1; i>=0; i--) 
    { 
        int carry = 0; 
        int n1 = X[i] - '0'; 
   		i_n2 = 0;  
           
        //Shifting the other number       
        for (int j=n2-1; j >= 0; j--) 
        { 
            int n2 = Y[j] - '0';  
            int sum = n1*n2 + result[i_n1 + i_n2] + carry; 
   
            // Carry operation for the next 
            carry = sum/2; 

            result[i_n1 + i_n2] = sum % 2; 
   
            i_n2++; 
        } 
   
        // store carry in next cell 
        if (carry > 0) 
            result[i_n1 + i_n2] += carry; 
   
        // To shift position to left after every operation
        i_n1++; 
    } 

    int i = result.size() - 1; 
    // generate the result string 
    string s = ""; 
  	while (i >= 0) 
        s += result[i--]+'0'; 
    return s; 
} 

int main(int argc,char **argv)
{
	
	string firststr, secondstr;
	char selection;
	unsigned long long int result;
	string classicalResult;
	clock_t t;
 	int f;
 	
    cout<<"First Binary Number:";
    //cin>>firststr;
    firststr="1010101010101010101010101010101010101010101010101010101010101010";
	
	cout<<"Second Binary Number:";
	//cin>>secondstr;	
	secondstr="1000100010001000100010001000100010001000100010001000100010001000";
    cout<<"Select multiply type if Classical Method press 'C'/'c' or Given Algorithm press 'G'/'g':"<<endl;
	cin>>selection;
		    
	cout<<"First String:"<<firststr<<endl;
	cout<<"Second String:"<<secondstr<<endl;
	cout<<"First Decimal:"<<binaryToDecimalStr(firststr)<<endl;
	cout<<"Second Decimal:"<<binaryToDecimalStr(secondstr)<<endl;
	
	t = clock();
	if( selection == 'G' || selection=='g')
	{	
	
		result = multiply(firststr,secondstr) ;
		f = frequency_of_primes (999999);
 		t = clock() - t;
  		cout<<"Running time:"<<t<<" clicks seconds:"<< ((float)t)/CLOCKS_PER_SEC<<endl;
		cout<<"Product of given algorithm result:"<<result<<endl;
		
	}
	
	if( selection == 'C' || selection=='c')
	{
	
	classicalResult = classicalMultiply(firststr,secondstr);
	f = frequency_of_primes (999999);
 	t = clock() - t;
  	cout<<"Running time:"<<t<<" clicks seconds:"<< ((float)t)/CLOCKS_PER_SEC<<endl;
	cout<<"Product of classical algorithm binary result:"<<classicalResult<<endl;

	cout<<"Product of classical algorithm decimal result:"<<binaryToDecimalStr(classicalResult)<<endl;

	}
	
	return 0;
}


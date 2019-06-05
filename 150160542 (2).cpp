#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <limits>
#include <algorithm>
#include <fstream>


using  namespace std;
//For clock time operation
int frequency_of_primes (int n) {
    int i,j;
    int freq=n-1;
    for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
    return freq;
}
//just find max length
int maxLength(string bstr1,string bstr2)
{
    return ( bstr1.size() > bstr2.size() ? bstr1.size() : bstr2.size() );
}
// the convertor binary string to decimal
unsigned long long int binaryToDecimalStr(string inresult){

    unsigned long long int value = 0;
    int indexCounter = 0;
    for(int i= inresult.length()-1;i>=0;i--){

        if(inresult[i]=='1'){
            value += pow(2, indexCounter);
            //value += (2<<indexCounter-1);
        }
        indexCounter++;
    }

    return value;
}

//Classical Multiply
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



    vector<unsigned long long int> result(n1 + n2);
    fill(result.begin(),result.end(),0);

    // Below two indexes are used to find positions
    // in result.
    unsigned long int i_n1 = 0;
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
//Find greater lenght and maniputate each of them if neccessary add '0'
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
// adding operation for P3
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
string divisionStr(string value,int from,int to){
    return value.substr(from,to);
}
//string adding operation
string addBinary(string a, string b)
{
    string result = ""; // Initialize result
    int s = 0;          // Initialize digit sum

    // Travers both strings starting from last
    // characters
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1)
    {
        // Comput sum of last digits and carry
        s += ((i >= 0)? a[i] - '0': 0);
        s += ((j >= 0)? b[j] - '0': 0);

        // If current digit sum is 1 or 3, add 1 to result
        result = char(s % 2 + '0') + result;

        // Compute carry
        s /= 2;

        // Move to next digits
        i--; j--;
    }
    return result;
}

//String subtraction operation
string sub2(string a, string b,string output)
{
    int lena = a.size();
    int lenb = b.size();

    //assert(lena >= lenb);

    int toSub = 0;
    for (int inda = lena - 1, indb = lenb - 1; inda >= 0; --inda, --indb)
    {
        int x = a[inda] - '0';
        int y = indb >= 0 ? b[indb] - '0' : 0;

        if (toSub == 1)
        {
            x--;
        }
        int cur;
        if (x < y)
        {
            cur = x + 2 - y;
            toSub = 1;
        }
        else
        {
            cur = x - y;
            toSub = 0;
        }

        output[inda] = cur + '0';

    }
    return output;
}
//for handle shifting to multiply 2 or another
string mult2 (string a, int n)
{
    int lena = a.size();
    string ret;
    if (lena == 1 && a[0] == '0')
    {
        ret = a;
        return ret;
    }

    for (int i = 0; i < lena ; ++i)
        ret += a[i];

    for (int i = lena; i < lena + n; ++i)
    {
        ret  += '0';
    }
    ret[lena + n]=0;


    return ret;
}
//The given algorithm
string  multiply(string X, string Y)
{
    // Find the maximum of lengths of x and Y and make length
    // of smaller string same as that of larger string
    int n = findLength(X, Y);
    //n = maxLength(X, Y);
    string preresult;
    if (n == 1) {

        preresult += (X[0]-'0')*(Y[0]-'0')+'0';
        return preresult;


    }
    int firstpart = n/2;   // First half of string, floor(n/2)
    int secondpart = (n - firstpart) ;



    string xL = divisionStr(X,0,firstpart);
    string xR = divisionStr(X,firstpart,secondpart);

    string yL = divisionStr(Y,0,firstpart);
    string yR = divisionStr(Y,firstpart,secondpart);
    // Recursively divide the numbers and then find bit by bit result
    string P1 = multiply(xL, yL);
    string P2 = multiply(xR, yR);
    string P3 = multiply(addBitStrings(xL, xR), addBitStrings(yL, yR));
    //The process of algorithms operations is done for string.
    string P4 = sub2(P3,P2,P3);
    string P5 = sub2(P4,P1,P4);
    string P6 = mult2(P5,secondpart);
    string P7 = mult2(P1,2*secondpart);

    string P8 = addBinary(P6,P7);
    string P9 = addBinary(P8,P2);

    return P9;
}
//Binary string generator
int randomGenerator(){

    double num = ((double)rand()) / RAND_MAX; // num between 0 and 1

    if(num>0.5) return 1; // heads

    else return 0; // tails

}

int main(int argc,char **argv) {


    string firststr, secondstr;
    char selection;
    unsigned long long int result;
    string classicalResult;
    clock_t t;
    int f;
    string test;
    ofstream myfile;
    myfile.open ("output.txt");


    cout<<"Please create a 1.string randomly to multiply and write this numbers or else 2,4,8,16,32,64 bit:"<<endl;
    int firstNumber;
    cin>>firstNumber;
    cout<<"Please create a 2.string randomly to multiply and write this numbers or else 2,4,8,16,32,64 bit:"<<endl;
    int secondNumber;
    cin>>secondNumber;

    srand(time(NULL)); // set random seed from clock

    //Binary String Generator
    for(int i=0;i<firstNumber;i++){
        firststr += to_string(randomGenerator());
    }

    for(int i=0;i<secondNumber;i++){
        secondstr+=to_string(randomGenerator());
    }

    cout<<"Select multiply type if Classical Method press 'C'/'c' or Given Algorithm press 'G'/'g':"<<endl;
    cin>>selection;

    cout<<"First String:"<<firststr<<endl;
    cout<<"Second String:"<<secondstr<<endl;
    cout<<"First Decimal:"<<binaryToDecimalStr(firststr)<<endl;
    cout<<"Second Decimal:"<<binaryToDecimalStr(secondstr)<<endl;


    myfile<<firststr.size()<<" bit first number:"<<firststr<<endl;
    myfile<<firststr.size()<<" bit second number:"<<secondstr<<endl;
    t = clock();
    if( selection == 'G' || selection=='g')
    {
        //This frequency of prime could be changed.
        f = frequency_of_primes (999999);
        test = multiply(firststr,secondstr) ;
        t = clock() - t;
        cout<<"Running time:"<<t<<" clicks seconds:"<< ((float)t)/CLOCKS_PER_SEC<<endl;
        cout<<"Product of given algorithm result:"<<test<<endl;
        cout<<"Product of given algorithm decimal result:"<<binaryToDecimalStr(test)<<endl;

        myfile<<"Running time:"<<t<<" clicks seconds:"<< ((float)t)/CLOCKS_PER_SEC<<endl;
        myfile<<"Product of given algorithm binary result"<<test<<endl;
        myfile<<"Product of given algorithm decimal result"<<binaryToDecimalStr(test)<<endl;

    }

    if( selection == 'C' || selection=='c')
    {

        classicalResult = classicalMultiply(firststr,secondstr);
        f = frequency_of_primes (999999);
        t = clock() - t;
        cout<<"Running time:"<<t<<" clicks seconds:"<< ((float)t)/CLOCKS_PER_SEC<<endl;
        cout<<"Product of classical algorithm binary result:"<<classicalResult<<endl;
        cout<<"Product of classical algorithm decimal result:"<<binaryToDecimalStr(classicalResult)<<endl;

        myfile<<"Running time:"<<t<<" clicks seconds:"<< ((float)t)/CLOCKS_PER_SEC<<endl;
        myfile<<"Product of classical algorithm binary result"<<classicalResult<<endl;
        myfile<<"Product of classical algorithm decimal result"<<binaryToDecimalStr(classicalResult)<<endl;
    }
    cout <<"This is the limit of unsigned  long long int bound for decimal output:"<< numeric_limits<unsigned long long int>::max() <<endl;
    myfile <<"This is the limit of unsigned  long long int bound for decimal output otherwise it shows '0':" << numeric_limits<unsigned long long int>::max() <<endl;

    myfile.close();
    return 0;
}
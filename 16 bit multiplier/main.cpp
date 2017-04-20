//
//  16-Bit_Multiplier.cpp
// 
//  A simulation program for the 16-bit unsigned number multiplier in C++
//  In this program use 16-bit operands for the multiplication. 
//  16 bit mutliplicand, 16 bit mutliplier and product is 32 bit
//  This simulation program uses basic logic gates, MUX , Adder , Decoder , 1 bit ALU ,
//  1 Bit ALU with overflow checking , 16 Bit ALU 
//  This program gets input for multiplier in Array of 16 elements each for MD and MQ.
//  The result of this program is in Array of 32 elements.
//  This program shows the content of MD, MQ and AC at each step and each iteration.  
//
//  Created by Harkaranjeet Singh on 4/11/17.
//  Copyright © 2017 Harkaranjeet Singh. All rights reserved.
//



#include <iostream>

using namespace std;

//---------------------------------------------------------------------------------------
//------------------------------------- AND gate ----------------------------------------
//---------------------------------------------------------------------------------------
// function for AND gate

int  AND_gate (int x, int y )
{
    
    if (x == 1 && y == 1 )
        return 1;
    else
        return 0 ;
}

//---------------------------------------------------------------------------------------
//------------------------------------- OR gate -----------------------------------------
//---------------------------------------------------------------------------------------
// function for OR gate

int  OR_gate (int x, int y )
{
    if (x ==  1|| y == 1)
    {
        return 1;
    }
    else
        return 0;
    
}

//---------------------------------------------------------------------------------------
//------------------------------------- XOR gate ----------------------------------------
//---------------------------------------------------------------------------------------
// function for XOR gate

int XOR_gate (int x, int y )
{
    if (x==y)
    {
        return 0 ;
        
    }
    else {
        return 1;
    }
}

//---------------------------------------------------------------------------------------
//------------------------------------- NOT gate ----------------------------------------
//---------------------------------------------------------------------------------------
// function for not gate to negate the value

int NOT_gate (int x)
{
    
    if (x==1)
        return 0 ;
    else
        return 1;
    
}

//---------------------------------------------------------------------------------------
//------------------------------- Full Adder gate ---------------------------------------
//---------------------------------------------------------------------------------------
// void function for 1 bit full adder with 3 inputs (x1,x2,x3(carry in)) two outputs (Sum ,cout)

void full_Adder_1Bit (int x1, int x2, int x3, int& sum, int& cout)
{
    int temp1, temp2, temp3;                  // temp variables
    temp1 = XOR_gate (x1,x2);                // calling XOR gate with parameter x1 and x2, result of this stores in temp1
    sum   = XOR_gate (temp1,x3);            // calling XOR gate with parameter temp1 and x3, result of this stores in sum
    temp2 = AND_gate (temp1,x3);           // calling AND gate with parameter temp1 and x3, result of this stores in temp2
    temp3 = AND_gate (x1,x2);             // calling AND gate with parameter temp1 and x3, result of this stores in temp3
    cout  = OR_gate (temp2,temp3);       // calling OR gate with parameter temp2 and temp3, result of this stores in cout (carry out)
    
}


//----------------------------------------------------------------------------------------
//------------------------------------ Decoder -------------------------------------------
//----------------------------------------------------------------------------------------
// void function for decoder
// calling NOT ,AND to perform functions
// it is part of 4x1 mux , it is called from MUX_4x1


void DECODER(int x1,int x2, int& d1, int& d2, int& d3 , int& d4 )
{
    
    int temp0, temp1, temp2, temp3;                   // temp variables
    
    temp0 = NOT_gate (x1);                           // calling NOT gate to negate the x1 and stores in temp0
    temp1 = NOT_gate (x2);                          // calling NOT gate to negate the x2 and stores in temp1
    temp2 = NOT_gate (x1);                         // calling NOT gate to negate the x1 and stores in temp2
    temp3 = NOT_gate (x2);                        // calling NOT gate to negate the x2 and stores in temp3
    
    d1 = AND_gate( temp0, temp1);         // calling AND gate with parameter temp0 (negate) and temp1 (negate), result of this stores in d1
    d2 = AND_gate( temp2, x2);           // calling AND gate with parameter temp2 (negate) and x2 (opcode), result of this stores in d2
    d3 = AND_gate( x1, temp3);          // calling AND gate with parameter x1(opcode) and temp3 (negate), result of this stores in d3
    d4 = AND_gate( x1, x2);            // calling AND gate with parameter x1(opcode) and x2 (opcode), result of this stores in d4
}


//-----------------------------------------------------------------------------------------
//----------------------------- MUX_4x1 ---------------------------------------------------
//-----------------------------------------------------------------------------------------
// void function for Mux_4x1 with 6 input and 1 output
// it calls decoder,AND ,OR gate to perform functions

void MUX_4x1(int y1, int y2, int y3, int y4 , int x1, int x2, int&z)
{
    
    int tempd1, tempd2, tempd3, tempd4 , tand1, tand2 ,tand3, tand4, tor1,tor2;    // temp variables
    
    DECODER (x1, x2, tempd1, tempd2 , tempd3, tempd4);           // calling the Decoder with two bit signal opcode getting 4 bit output
    
    tand1 = AND_gate(tempd1,y1);    // calling AND gate parameter temp1 (1st out decoder),y1 (from ALU), result is tand1
    tand2 = AND_gate(tempd2,y2);   // calling AND gate parameter temp2 (2nd out decoder),y2 (from ALU), result is tand2
    tand3 = AND_gate(tempd3,y3);  // calling AND gate parameter temp3 (3rd out decoder),y3 (from ALU), result is tand3
    tand4 = AND_gate(tempd4,y4); // calling AND gate parameter temp4 (4th out decoder),y4 (from ALU), result is tand4
    
    tor1 = OR_gate(tand1,tand2);     // calling OR gate parameter tand1,tand2, result is tor1
    tor2 = OR_gate(tand3,tand4);    // calling OR gate parameter tand3,tand4, result is tor2
    z = OR_gate(tor1,tor2);        // calling OR gate parameter tor1,tor2 result is z

    
}

//-------------------------------------------------------------------------------------------
//--------------------------- One Bit ALU gate ----------------------------------------------
//-------------------------------------------------------------------------------------------
// void function for one bit ALU getting parameter a,b 2 bit each
// 2 bit opcode( defined separately)
// it call AND, OR , full Adder , MUX_4x1 to perform functions
// gives output cout(carryout), ovf(overflow), z(result)

void OneBitALU(int a, int b, int cin,int op1, int op0, int &cout, int& z)
{
    int tand1,tor1,tbit1;                               // temp variables
    tand1 = AND_gate (a,b);                            // calling AND gate with parameter a and b, result of this stores in tand1
    tor1  = OR_gate (a,b);                            // calling OR gate with parameter a and b, result of this stores in tor1
    full_Adder_1Bit (a,b,cin,tbit1,cout);            // calling Adder
    MUX_4x1( tand1,tor1,tbit1,0,op1,op0,z);         // calling mux_4x1
}


//--------------------------------------------------------------------------------------------
//------------------------------- One Bit ALU overflow checking ------------------------------
//--------------------------------------------------------------------------------------------
// void function for one bit ALU getting parameter a,b 2 bit each
// 2 bit opcode( defined separately)
// it call AND, OR , full Adder , MUX_4x1 and XOR gate to perform functions
// gives output cout(carryout), ovf(overflow), z(result)


void OneBitALU_OF(int a, int b,int cin,int op1, int op0 , int&cout, int& ovf , int& z)
{
    int tand1,tor1,tbit1;                        // temp variables
    tand1 = AND_gate (a,b);                     // calling AND gate with parameter a and b, result of this stores in tand1
    tor1  = OR_gate (a,b);                     // calling OR gate with parameter a and b, result of this stores in tor1
    full_Adder_1Bit (a,b,cin,tbit1,cout);     // calling Adder
    MUX_4x1(tand1,tor1,tbit1,0,op1,op0,z);   // calling Mux_4x1 given
    ovf   = XOR_gate(cin,cout);             // calling the XOR gate to checking overflow
}

//-------------------------------------------------------------------------------------------
// ------------------------------------- Sixteen Bit ALU ------------------------------------
//-------------------------------------------------------------------------------------------
//void function Sixteen bit ALU getting parameter of a,b,op and giving the result
// calling the one bit alu 15 times and at last calling the one bit alu with overflow checking
// passing the parameter to one bit alu each elemts of array at time.
// tcout is used for caary out and used as carryin in next ALU
// Result is stored as element of array

void SixteenBitALU (int a[],int b[],int op[],int* result)
{
    
    int tcout[16];  // temmp array of elelments to store the value of cout from each one bit alu
    int ovf;       // variable to store overflow
    int cin = 0;  // intial carry
    
    OneBitALU  (a[15],  b[15],       cin,  op[0], op[1], tcout[15],  result[15]);      //calling and passing the last element of array to 1st bit ALU to give a binary notation
    OneBitALU  (a[14],  b[14],  tcout[15], op[0], op[1], tcout[14],  result[14]);
    OneBitALU  (a[13],  b[13],  tcout[14], op[0], op[1], tcout[13],  result[13]);
    OneBitALU  (a[12],  b[12],  tcout[13], op[0], op[1], tcout[12],  result[12]);
    OneBitALU  (a[11],  b[11],  tcout[12], op[0], op[1], tcout[11],  result[11]);
    OneBitALU  (a[10],  b[10],  tcout[11], op[0], op[1], tcout[10],  result[10]);
    OneBitALU   (a[9],  b[9],   tcout[10], op[0], op[1], tcout[9],   result[9]);
    OneBitALU   (a[8],  b[8],   tcout[9],  op[0], op[1], tcout[8],   result[8]);
    OneBitALU   (a[7],  b[7],   tcout[8],  op[0], op[1], tcout[7],   result[7]);
    OneBitALU   (a[6],  b[6],   tcout[7],  op[0], op[1], tcout[6],   result[6]);
    OneBitALU   (a[5],  b[5],   tcout[6],  op[0], op[1], tcout[5],   result[5]);
    OneBitALU   (a[4],  b[4],   tcout[5],  op[0], op[1], tcout[4],   result[4]);
    OneBitALU   (a[3],  b[3],   tcout[4],  op[0], op[1], tcout[3],   result[3]);
    OneBitALU   (a[2],  b[2],   tcout[3],  op[0], op[1], tcout[2],   result[2]);
    OneBitALU   (a[1],  b[1],   tcout[2],  op[0], op[1], tcout[1],   result[1]);
    OneBitALU_OF(a[0],  b[0],   tcout[1],  op[0], op[1], tcout[0], ovf, result[0]);     // calling the one bit alu with over flow checking
    
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------- Array Merge ----------------------------------------------
//---------------------------------------------------------------------------------------------------
// Array Merge is void function which is getting parameter of array AC and MQ each 16 element
// it performs the merge of two 16 element array into 32 element array

void ArrayMerge (int AC[16],int MQ[16],int MERGED[32])
{
    int i;
    for(i=0;i<16;i++)
    {
        MERGED[i]=AC[i];
        MERGED[i+16]=MQ[i];
    }
}



//---------------------------------------------------------------------------------------------------
//------------------------------------- Array Shifter ----------------------------------------------
//---------------------------------------------------------------------------------------------------
// Array Shifter is void function which is getting parameter of array SHIFTED
// it performs the logical right shift to 32 element array and add a 0 to the 0th element place

void ArrayShifter(int *SHIFTED)
{
    int array_size = 32;
    
    for (int i = array_size - 1; i > 0; i--)
    {
        SHIFTED[i] = SHIFTED[i - 1];
    }
    SHIFTED[0] = 0;
}

//---------------------------------------------------------------------------------------------------
//------------------------------------- Array Splitter ----------------------------------------------
//---------------------------------------------------------------------------------------------------
// Array Splitter is void function which is getting parameter of array SHIFTED and gives two 16 element array
// it performs the spliiting of 32 element array into two 16 element array


void ArraySplitter(int SHIFTED[], int AC[],int *MQ)

{
    for(int i=0;i<16;i++)
    {
        AC[i]= SHIFTED[i];
        MQ[i]=SHIFTED[i+16];
    }
}



//-------------------------------------------------------------------------------------------------
//--------------------------------------- Sixteen Bit Multiplier ----------------------------------
//-------------------------------------------------------------------------------------------------
// Sixteen Bit multiplier is void function which is getting the parameter of array MD and MQ.
// it will multiply two 16 bit number and displays the result
// Both the parameter are holding 16 elements (16 bit)
// Multiplier checks the conditions required to perform itr
// call the 16 bit ALU to perform addition
// after performing the addition it will do the logically shift right by calling  function ArrayShifter
// Arraymerge is called to perform array merge to 32 elements from 16 elemets each
// ArraySplitter is called to perform array split into 16 elements each from 32 elements
// Multilpier displys the value of AC,MD and MQ at initial and every itr steps


void SixteenBitMultiplier(int MD[],int MQ[], int RESULT[])
{
    int op[2] = {1,0};                                    // op code control for add
    int ACMQ[32];                                        // 32 element array
    int ZERO[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    // 16 element array used for ading zero
    int AC[16]=   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   // 16 element array used for AC
    int i,counter;                                    // variables
    
    
    
    cout<<"================================     INITIAL VALUES     ================================"<<endl<<endl;
    
    cout<<"                   MD                     AC                   MQ           "<<endl;
    cout<<"             ";
    for(i=0;i<16;i++)                                  // to display the content of MD at intial
    {
        cout<<MD[i];
    }
    cout<<"      ";
    
                           // to display the content of AC at intial
    for(i=0;i<16;i++)
    {
        cout<<AC[i];
    }
    cout<<"      ";
    
                            // to display the content of MQ at intial
    for(i=0;i<16;i++)
    {
        cout<<MQ[i];
    }
    
    cout<<endl<<endl;
    
    
    
    
    for (counter=16; counter>=1;counter--)                                        // for loop which runs 16 times
    {
        
        cout<<"============================     CYCLE COUNTER = "<<counter<< "     ==========================="<<endl<<endl;
       
        
        // Checking the condition which are required to perform the itr
        
        if (MQ[15] == 1)                                                 // if MQ's 0th value is == 1 , add AC + MD
        {
            SixteenBitALU(AC,MD,op,AC);                                 // calling the sixteen bit ALU to perform addition
        }
        else                                                           // if MQ's 0th value is == 0 , add AC + ZERO
        {
            SixteenBitALU(AC,ZERO,op,AC);                             // calling the sixteen bit ALU to perform addition
        }
        
         cout<<"                    MD                     AC                   MQ           "<<endl;
        cout<<"STEP-1       ";
        for(i=0;i<16;i++)                                         // to display the content of MD  at Step 1
        {
            cout<<MD[i];
        }
        cout<<"      ";

        for(i=0;i<16;i++)                                           // to display the content of AC at Step 1
        {
            cout<<AC[i];
        }
        cout<<"      ";
        
        for(i=0;i<16;i++)                                         // to display the content of MQ  at Step 1
        {
            cout<<MQ[i];
        }
        cout<<endl;
        
        
        
        
        // Calling the function to merge two array which are holding the values of AC And MQ.
       // get the 32 elements array in ACMQ.
        
        ArrayMerge(AC, MQ, ACMQ);                                 // merge two array
        
        
        
        // calling the function to logicall right Shift By One
       // parameter of array ACMQ
        
        ArrayShifter(ACMQ);                                      // logicall right Shift
        
        
        // Calling the function to Split the 32 element array into two 16 element array
       // paramenter of 32 element is ACMQ and get back AC and MQ in 16 elements each
        
        ArraySplitter(ACMQ, AC, MQ);                              // Split 32 element array to two 16 elemenet array
        
         cout<<"STEP-2       ";
        for(i=0;i<16;i++)                                      // to display the content of MD  at Step 2
        {
            cout<<MD[i];
        }
        cout<<"      ";
        
        for (int i = 0; i < 16; i++)                            // to display the content of AC at Step 2
        {
            cout << AC[i];
        }
        cout<<"      ";
        
        for (int i = 0; i < 16; i++)                           // to display the content of MQ at Step 2
        {
            cout << MQ[i];
        }
        cout<<endl;
        
        
        //calling Merge function again to display the 32 bit result of each itr
        
        ArrayMerge(AC, MQ, RESULT);
           cout<<endl;
        
    }
    
    
}

int main (){
    
   int RESULT [32] ;  
    
    // Test cases in array for each
    
     int MD[16] = {0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1};
     int MQ[16] = {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0};
     //int MD[16] = {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0};
    // int MQ[16] = {0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1};
    // int MD[16] = {1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0};
    // int MQ[16] = {0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1};
    // int MD[16] = {0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1};
    // int MQ[16] = {1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0};
    
    
    SixteenBitMultiplier(MD, MQ, RESULT);          // calling 16 Bit multiplier with given parameters
    
    cout<<"        RESULT     = ";
    for (int i = 0; i < 32; i++)                        // to display the Result
    {
        cout << RESULT[i];                             
    }
    cout<<endl<<endl;
    

int MD0[16] = {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0};
 int MQ0[16] = {0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1};

SixteenBitMultiplier(MD0, MQ0, RESULT);          // calling 16 Bit multiplier with given parameters
    
    cout<<"        RESULT     = ";
    for (int i = 0; i < 32; i++)                        // to display the Result
    {
        cout << RESULT[i];                             
    }
    cout<<endl<<endl;


 int MD1[16] = {1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0};
 int MQ1[16] = {0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1};


SixteenBitMultiplier(MD1, MQ1, RESULT);          // calling 16 Bit multiplier with given parameters
    
    cout<<"        RESULT     = ";
    for (int i = 0; i < 32; i++)                        // to display the Result
    {
        cout << RESULT[i];                             
    }
    cout<<endl<<endl;


 int MD2[16] = {0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1};
 int MQ2[16] = {1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0};

SixteenBitMultiplier(MD2, MQ2, RESULT);          // calling 16 Bit multiplier with given parameters
    
    cout<<"        RESULT     = ";
    for (int i = 0; i < 32; i++)                        // to display the Result
    {
        cout << RESULT[i];                             
    }
    cout<<endl<<endl;

    return 0;
    
}

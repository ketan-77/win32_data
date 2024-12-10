using System;
using System.Runtime.InteropServices;
using AutomationServerDotUnderstandableDLL;

public class CSharAutomation 
{
    public static void Main() 
    {
        CMyMathClass objCMyMathClass = new CMyMathClass();
        IMyMath objIMyMath = (IMyMath)objCMyMathClass;

        int num1 = 10;
        int num2 = 100;
        int sum = 0, subtract = 0;

        sum = objIMyMath.SumOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum of " + num1 + " and " + num2 + " is " + sum);
        
        subtract = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
        Console.WriteLine("Subtraction of " + num1 + " and " + num2 + " is " + sum);
    }
}



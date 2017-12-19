using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace no2_1
{
    class Program
    {
        static void Main(string[] args)
        {
            BigInteger a = 85;
            BigInteger b = 97;
            BigInteger t = 1234567891234567890;
            /*a = BigInteger.Parse(Console.ReadLine());
            b = BigInteger.Parse(Console.ReadLine());
            t = BigInteger.Parse(Console.ReadLine());
            */

            BigInteger divide = BigInteger.Pow(10, 9) + 7;
            
            BigInteger resultA = a * Pow(b, t);
            BigInteger resultDivide = BigInteger.Divide(resultA, divide);
            BigInteger temp = resultDivide * divide;
            BigInteger result = resultA - temp;
            
            Console.WriteLine(result);
        }

        public static BigInteger Pow(BigInteger b, BigInteger power)
        {

            if (b == null)
            {
                throw new ArgumentNullException("b");
            }

            if (power == null)
            {
                throw new ArgumentNullException("power");
            }

            if (power < 0)
            {
                throw new ArgumentOutOfRangeException("power", "Currently negative exponents are not supported");
            }


            BigInteger result = 1;
            while (power != 0)
            {

                if ((power & 1) != 0)
                    result *= b;
                power >>= 1;
                b *= b;
            }

            return result;
        }
    }
}

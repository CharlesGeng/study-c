// Charles Geng
// 2013-01-30

using System;
using System.Collections;

namespace IteratorPattern
{
    public class MainClass
    {
        public static int Main()
        {
            DinerMenu dinerMenu = new DinerMenu();
            PancakeHouseMenu pancakeMenu = new PancakeHouseMenu();
            CafeMenu cafeMenu = new CafeMenu();

            Console.WriteLine("Start Test!");
            Waitress waitress = new Waitress(dinerMenu, pancakeMenu, cafeMenu);
            waitress.PrintMenu();
            Console.WriteLine("Test finished!");
            return 0;
        }
    }
}

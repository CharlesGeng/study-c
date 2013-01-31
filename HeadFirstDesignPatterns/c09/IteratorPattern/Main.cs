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
            Console.WriteLine("Start Test!");
            Waitress waitress = new Waitress();
            waitress.ShowAllMenuItems();
            Console.WriteLine("Test finished!");
            return 0;
        }
    }
}

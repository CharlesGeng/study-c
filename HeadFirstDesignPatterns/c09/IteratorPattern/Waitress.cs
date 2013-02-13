// Charles Geng
// 2013-01-30

using System;
using System.Collections;

namespace IteratorPattern
{
    public class Waitress
    {
        private IMenu _dinerMenu = null;
        private IMenu _pancakeMenu = null;
        private IMenu _cafeMenu = null;

        public Waitress(IMenu dinerMenu, IMenu pancakeMenu, IMenu cafeMenu)
        {
            _dinerMenu = dinerMenu;
            _pancakeMenu = pancakeMenu;
            _cafeMenu = cafeMenu;
        }

        public void PrintMenu()
        {
            IMenuIterator dinerIterator = _dinerMenu.CreateIterator();
            IMenuIterator pancakeIterator = _pancakeMenu.CreateIterator();
            IMenuIterator cafeIterator = _cafeMenu.CreateIterator();

            Console.WriteLine("Diner Menu:");
            PrintMenu(dinerIterator);

            Console.WriteLine("Breakfast Menu:");
            PrintMenu(pancakeIterator);

            Console.WriteLine("Cafe Menu:");
            PrintMenu(cafeIterator);
        }

        public void PrintMenu(IMenuIterator iterator)
        {
            while (iterator.HasNext())
            {
                MenuItem item = (MenuItem)iterator.Next();
                Console.WriteLine(string.Format("\tName: {0} \r\n\tDescription: {1}", item.GetName, item.GetDescription));
                Console.WriteLine("");
            }
        }
    }
}

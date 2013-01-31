// Charles Geng
// 2013-01-30

using System;
using System.Collections;

namespace IteratorPattern
{
    public class Waitress
    {
        private DinerMenu _dinerMenu = null;
        private PancakeHouseMenu _pancakeMenu = null;

        public Waitress()
        {
            _dinerMenu = new DinerMenu();
            _pancakeMenu = new PancakeHouseMenu();
        }

        public void ShowAllMenuItems()
        {
            IMenuIterator dinerIterator = _dinerMenu.CreateIterator();
            IMenuIterator pancakeIterator = _pancakeMenu.CreateIterator();
            while (dinerIterator.HasNext())
            {
                MenuItem item = (MenuItem)dinerIterator.Next();
                Console.WriteLine(string.Format("Name:{0} \r\nDescription:{1}", item.GetName, item.GetDescription));
                Console.WriteLine("");
            }

            while (pancakeIterator.HasNext())
            {
                MenuItem item = (MenuItem)pancakeIterator.Next();
                Console.WriteLine(string.Format("Name:{0} \r\nDescription:{1}", item.GetName, item.GetDescription));
                Console.WriteLine("");
            }
        }
    }
}

// Charles Geng
// 28/01/13 06:04:42

using System;
using System.Collections;

namespace IteratorPattern
{
    //Use ArrayList to store menuitem
    public class PancakeHouseMenu : IMenu
    {
        private ArrayList menuItems = null;

        public PancakeHouseMenu()
        {
            menuItems = new ArrayList();
            AddMenuItem("Big Meat Pie", "Large cake with meat and vegetable", false, 12.1);
            AddMenuItem("Small Meat Pie", "Small cake with meat and vegetable", false, 9.11);
            AddMenuItem("Beaf Pie", "A lot of Beaf on it, also some vegetable", false, 22.21);
            AddMenuItem("Vege Pie", "A pie only with Vegetable", true, 6.71);
        }

        public IMenuIterator CreateIterator()
        {
            return new PancakeMenuIterator(menuItems);
        }

        public void AddMenuItem(string name, string description, bool vegetarian, double price)
        {
            MenuItem item = new MenuItem(name, description, vegetarian, price);
            menuItems.Add(item);
        }

        public ArrayList GetItems()
        {
            return menuItems;
        }
    }
}

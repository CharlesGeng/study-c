// Charles Geng
// 28/01/13 06:04:42

using System;
using System.Collections;

namespace IteratorPattern
{
    //Use Array to store menuitem
    public class DinerMenu : IMenu
    {
        private const int count = 4;
        private int index = 0;
        private MenuItem[] menuItems = new MenuItem[count];

        public DinerMenu()
        {
            AddMenuItem("Big Beef Rice", "Large Beef with rice and vegetable", false, 12.1);
            AddMenuItem("Small Beef Rice", "Small Beef with meat and vegetable", false, 9.11);
            AddMenuItem("Pork Bread", "A piece of pork in a bread, also some vegetable", false, 8.21);
            AddMenuItem("Vege Bread", "Some Vegetable in a bread", true, 6.71);
        }

        public IMenuIterator CreateIterator()
        {
            return new DinerMenuIterator(menuItems);
        }

        public void AddMenuItem(string name, string description, bool vegetarian, double price)
        {
            MenuItem item = new MenuItem(name, description, vegetarian, price);
            menuItems[index++] = item;
        }

        public MenuItem[] GetItems()
        {
            return menuItems;
        }
    }
}

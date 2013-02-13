using System;
using System.Collections;

namespace IteratorPattern
{
    public class CafeMenu : IMenu
    {
        Hashtable _menuItems = null;
        public CafeMenu()
        {
            _menuItems = new Hashtable();

            AddItem("Veggie Burger and Air Fries",
                    "Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
                    true,3.99,1);
            AddItem("Soup of the Day",
                    "A cup of the soup of the day, with a side salad",
                    false, 3.69,2);
            AddItem("Burrito",
                    "A large burrito, with whole pinto beans, salsa, guacamole",
                    true, 4.29,3);
        }

        public void AddItem(string name, string description, bool vegetarian, double price, int index)
        {
            MenuItem menuItem = new MenuItem(name, description, vegetarian, price);
            _menuItems.Add(index, menuItem);
        }

        public IMenuIterator CreateIterator()
        {
            return new CafeMenuIterator(_menuItems);
        }
    }
}

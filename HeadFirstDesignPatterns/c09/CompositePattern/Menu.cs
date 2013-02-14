using System;
using System.Collections;

namespace CompositePattern
{
    public class Menu : MenuComponent
    {
        private string _name = string.Empty;
        private string _description = string.Empty;
        private ArrayList _menu = null;

        public Menu(string name, string description)
        {
            _name = name;
            _description = description;
            _menu = new ArrayList();
        }

        public override string GetName()
        {
            return _name;
        }

        public override void Print()
        {
            Console.WriteLine("{0}, {1}", _name, _description);
            Console.WriteLine("------------------------------");
            foreach (MenuComponent menu in _menu)
            {
                menu.Print();
            }
        }

        public override void Add(MenuComponent menuComponent)
        {
            _menu.Add(menuComponent);
        }

        public override void Remove(MenuComponent menuComponent)
        {
            _menu.Remove(menuComponent);
        }

        public override MenuComponent GetClient(int i)
        {
            if (i < _menu.Count)
            {
                return (MenuComponent)_menu[i];
            }
            else
            {
                return null;
            }
        }
     }
}

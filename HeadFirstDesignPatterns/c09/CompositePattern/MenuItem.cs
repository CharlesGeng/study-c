using System;

namespace CompositePattern
{
    public class MenuItem : MenuComponent
    {
        private string _name = string.Empty;
        private string _description = string.Empty;
        private double _price = 0.0d;
        private bool _isVegetarian = false;

        public MenuItem(string name, string description, bool isVegetarian, double price)
        {
            _name = name;
            _description = description;
            _price = price;
            _isVegetarian = isVegetarian;
        }

        public override string GetName()
        {
            return _name;
        }

        public override string GetDescription()
        {
            return _description;
        }

        public override double GetPrice()
        {
            return _price;
        }

        public override bool IsVegetarian()
        {
            return _isVegetarian;
        }

        public override void Print()
        {
            Console.WriteLine("\tName: {0}, Price: {1}", _name, _price);
            Console.WriteLine("\tDescription: {0}", _description);
        }
    }
}

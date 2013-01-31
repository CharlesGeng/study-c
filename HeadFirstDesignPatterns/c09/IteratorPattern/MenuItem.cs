// Charles Geng
// 28/01/13 06:04:42

using System;

namespace IteratorPattern
{

    public class MenuItem
    {
        private string Name;
        private string Description;
        private bool Vegetarian;
        private double Price;
        public MenuItem(string name, string description, bool vegetarian, double price)
        {
            this.Name = name;
            this.Description = description;
            this.Vegetarian = vegetarian;
            this.Price = price;
        }

        public string GetName
        {get{return Name;}set{Name=value;}}

        public string GetDescription
        {get{return Description;}set{Description=value;}}

        public bool IsVegetarian
        {get{return Vegetarian;}set{Vegetarian=value;}}

        public double GetPrice
        {get{return Price;}set{Price=value;}}
    }
}

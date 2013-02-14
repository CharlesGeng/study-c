using System;

namespace CompositePattern
{
    public abstract class MenuComponent
    {
        public virtual string GetName()
        {
            throw new Exception("Unsupport Method!");
        }

        public virtual string GetDescription()
        {
            throw new Exception("Unsupport Method!");
        }

        public virtual bool IsVegetarian()
        {
            throw new Exception("Unsupport Method!");
        }

        public virtual double GetPrice()
        {
            throw new Exception("Unsupport Method!");
        }

        public virtual void Print()
        {
            throw new Exception("Unsupport Method!");
        }

        public virtual void Add(MenuComponent component)
        {
            throw new Exception("Unsupport Method!");
        }

        public virtual void Remove(MenuComponent component)
        {
            throw new Exception("Unsupport Method!");
        }

        public virtual MenuComponent GetClient(int i)
        {
            throw new Exception("Unsupport Method!");
        }
    }
}

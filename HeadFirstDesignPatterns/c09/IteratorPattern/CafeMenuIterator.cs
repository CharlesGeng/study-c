using System;
using System.Collections;

namespace IteratorPattern
{
    public class CafeMenuIterator : IMenuIterator
    {
        Hashtable _menuItems = null;
        int _index = 1;

        public CafeMenuIterator(Hashtable menuItems)
        {
            _menuItems = menuItems;
        }

        public bool HasNext()
        {
            if (_menuItems.Values.Count >= _index)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public object Next()
        {
            if (HasNext())
            {
                return _menuItems[_index++];
            }
            else
            {
                return null;
            }
        }
    }
}

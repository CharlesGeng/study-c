//Charles Geng
//2013-01-31

using System;
using System.Collections;

namespace IteratorPattern
{
    public class PancakeMenuIterator : IMenuIterator
    {
        private ArrayList _menuItems = null;
        private int _i = 0;

        public PancakeMenuIterator(ArrayList menuItems)
        {
            _menuItems = new ArrayList();
            _menuItems = menuItems.Clone() as ArrayList;
        }

        public bool HasNext()
        {
            if (_i < _menuItems.Count)
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
                return _menuItems[_i++];
            }
            return null;
        }
    }
}

//Charles Geng
//2013-01-31

using System;
using System.Collections;

namespace IteratorPattern
{
    public class DinerMenuIterator : IMenuIterator
    {
        private MenuItem[] _menuItems = null;
        private int _i = 0 ;

        public DinerMenuIterator (MenuItem[] menuItems)
        {
            _menuItems = menuItems;
        }

        public bool HasNext()
        {
            if (_i < _menuItems.Length)
            {
                return true;
            }
            return false;
        }

        public object Next()
        {
            if (HasNext())
            {
                return _menuItems[_i++];
            }
            else
            {
                return null;
            }
        }
    }
}

//GengQi
//2013-02-12

using System;
using System.Collections;

namespace IteratorPattern
{
    public interface IMenu
    {
        IMenuIterator CreateIterator();
    }
}

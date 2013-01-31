// Charles Geng
// 2013-01-30

using System;
using System.Collections;

namespace IteratorPattern
{
    public interface IMenuIterator
    {
        bool HasNext();
        object Next();
    }
}

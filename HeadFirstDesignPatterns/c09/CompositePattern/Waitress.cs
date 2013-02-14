namespace CompositePattern
{
    public class Waitress
    {
        private MenuComponent _allMenu = null;

        public Waitress(MenuComponent allMenu)
        {
            _allMenu = allMenu;
        }

        public void PrintAllMenuItem()
        {
            _allMenu.Print();
        }
    }
}

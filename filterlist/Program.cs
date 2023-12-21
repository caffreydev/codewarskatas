using System.Collections;
using System.Collections.Generic;

namespace filterlist{
class Program {

public static void Main (string[] args)
{
    Console.WriteLine(ListFilterer.GetIntegersFromList(new List<object>{1 , 2, "fish", "chips", 5, "sausage", 3}).ElementAt(2));
}
}
}



public class ListFilterer
{
   public static IEnumerable<int> GetIntegersFromList(List<object> listOfItems)
   {
     return listOfItems.OfType<int>();
      
   }
}
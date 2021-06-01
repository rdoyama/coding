public class Part3
{
    public boolean twoOccurrences(String stringa, String stringb)
    {
        int index1 = stringb.indexOf(stringa);

        if (index1 == -1)
            return false;
        
        int index2 = stringb.substring(index1 + 1).indexOf(stringa);
        
        if (index2 == -1)
            return false;
        
        return true;
    }

    public String lastPart(String stringa, String stringb)
    {
        int idx1 = stringb.indexOf(stringa);
        
        if (idx1 == -1)
            return stringb;
        
        return stringb.substring(idx1 + stringa.length());
    }

    public void testing()
    {
        String str = "banana";
        System.out.println("True");
        System.out.println(twoOccurrences("an", str));

        str = "earphones";
        System.out.println("False");
        System.out.println(twoOccurrences("an", str));

        str = "banana";
        System.out.println("Should print 'ana'");
        System.out.println(lastPart("an", str));

        str = "forest";
        System.out.println("Should print 'forest'");
        System.out.println(lastPart("zoo", str));

        str = "forest";
        System.out.println("Should print ''");
        System.out.println(lastPart("st", str));
    }

    public static void main(String args[])
    {
        Part3 pt3 = new Part3();
        pt3.testing();
    }
}
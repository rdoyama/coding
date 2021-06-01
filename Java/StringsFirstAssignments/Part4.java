import edu.duke.*;

public class Part4
{
    public void printLinks(String url, String sign)
    {
        URLResource ur = new URLResource(url);
        String lowerSign = sign.toLowerCase();

        for (String word : ur.words())
        {
            //System.out.println(word);
            String lowerWord = word.toLowerCase();
            int idx = lowerWord.indexOf(lowerSign);
            if (idx != -1)
            {
                int quotLeft = lowerWord.indexOf("\"");
                int quotRight = lowerWord.lastIndexOf("\"");
                if (quotLeft != -1 && quotRight != -1)
                    System.out.println(word.substring(quotLeft, quotRight + 1));
            }
        }
    }

    public static void main(String args[])
    {
        Part4 run = new Part4();

        run.printLinks("https://www.dukelearntoprogram.com//course2/data/manylinks.html", "youtube.com");
    }
}
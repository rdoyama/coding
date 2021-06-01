public class Part1
{
    public String findSimpleGene(String dna)
    {
        int start = dna.indexOf("ATG");
        if (start == -1)
            return "";
        
        int end = dna.indexOf("TAA");
        if (end == -1 || (end + 3 - start) % 3 != 0)
            return "";
        
        return dna.substring(start, end + 3);
    }

    public void testSimpleGene()
    {
        // Without ATG, with TAA
        String dna = "GTACGTAGATCGGCTATCTAGATAA";
        System.out.println("Without ATG, with TAA");
        System.out.println(findSimpleGene(dna));

        // With ATG, without TAA
        dna = "GTACGTAGATGGGCTATCTAGATGA";
        System.out.println("With ATG, without TAA");
        System.out.println(findSimpleGene(dna));

        // Without ATG, without TAA
        dna = "GTACGTAGATCGGCTATCTAGATGA";
        System.out.println("Without ATG, without TAA");
        System.out.println(findSimpleGene(dna));

        // With ATG, with TAA, multiple of 3
        dna = "GTACGTAGATGGGCTAGATCTGATAAGT";
        System.out.println("With ATG, with TAA, multiple of 3");
        System.out.println(findSimpleGene(dna));

        // With ATG, with TAA, not multiple of 3
        dna = "GTACGTAGATGGGCTATCTAGATAAGT";
        System.out.println("With ATG, with TAA, not multiple of 3");
        System.out.println(findSimpleGene(dna));
    }

    public static void main(String args[])
    {
        Part1 test = new Part1();
        test.testSimpleGene();
    }
}


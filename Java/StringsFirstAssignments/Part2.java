public class Part2
{
    public String findSimpleGene(String dna, String startCodon, String endCodon)
    {
        String sub_dna = dna.toUpperCase();
        int start = sub_dna.indexOf(startCodon.toUpperCase());
        if (start == -1)
            return "";
        
        int end = sub_dna.indexOf(endCodon.toUpperCase());
        if (end == -1 || (end + 3 - start) % 3 != 0)
            return "";
        
        return dna.substring(start, end + 3);
    }

    public void testSimpleGene()
    {
        // Without ATG, with TAA
        String dna = "GTACGTAGATCGGCTATCTAGATAA";
        System.out.println("Without ATG, with TAA");
        System.out.println(findSimpleGene(dna, "ATG", "TAA"));

        // With ATG, without TAA
        dna = "GTACGTAGATGGGCTATCTAGATGA";
        System.out.println("With ATG, without TAA");
        System.out.println(findSimpleGene(dna, "ATG", "TAA"));

        // Without ATG, without TAA
        dna = "GTACGTAGATCGGCTATCTAGATGA";
        System.out.println("Without ATG, without TAA");
        System.out.println(findSimpleGene(dna, "ATG", "TAA"));

        // With ATG, with TAA, multiple of 3
        dna = "gtacgtagatgggctagatctgataagt";
        System.out.println("With ATG, with TAA, multiple of 3");
        System.out.println(findSimpleGene(dna, "ATG", "TAA"));

        // With ATG, with TAA, not multiple of 3
        dna = "GTACGTAGATGGGCTATCTAGATAAGT";
        System.out.println("With ATG, with TAA, not multiple of 3");
        System.out.println(findSimpleGene(dna, "ATG", "TAA"));
    }

    public static void main(String args[])
    {
        Part2 test = new Part2();
        test.testSimpleGene();
    }
}


import java.math.BigInteger;

public class Euler57
{
    static boolean is_z_longer_n(final BigInteger z, final BigInteger n, final int iteration)
    {
        BigInteger summed_z = z.add(n);

        final String strZ = summed_z.toString();
        final String strN = n.toString();
        
        System.out.printf("#%d\t%s/%s\n"
            , iteration
            , strZ
            , strN);

        return strZ.length() > strN.length();
    }

    public static void main(String[] args)
    {
        final int iterations = 9;

        int iteration  = 1;
        BigInteger z = new BigInteger("1");
        BigInteger n = new BigInteger("2");

        int found = 0;

        for (;;) {

            if ( is_z_longer_n(z,n,iteration) ) {
                found += 1;
            }

            if ( iteration == iterations ) {
                break;
            }
            iteration += 1;

            // 2 + ...
            z = n.add(n).add(z);

            // 1 / ...
            BigInteger tmp = z;
            z = n;
            n = tmp;

        }

        System.out.printf("%d\n", found);
    }
}
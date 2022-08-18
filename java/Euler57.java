import java.math.BigDecimal;
import java.math.BigInteger;

public class Euler57
{
    static void print_z_n(final BigInteger z, final BigInteger n, final int iteration)
    {
        System.out.printf("#%d\t%s/%s\n"
            , iteration
            , z.toString()
            , n.toString());
    }

    static long run(final long iterations) 
    {
        BigInteger z = new BigInteger("1");
        BigInteger n = new BigInteger("2");

        int found = 0;

        for (int iteration  = 1;; ++iteration) {

            z = z.add(n);

            if ( z.toString().length() > n.toString().length() ) {
                found += 1;
            }

            if ( iteration == iterations ) {
                break;
            }

            // 2 + ...
            z = z.add(n);

            // 1 / ...
            BigInteger tmp = z;
            z = n;
            n = tmp;

        }

        return found;

    }

    static int integerDigits(BigDecimal n) {
        BigDecimal stripped = n.stripTrailingZeros();
        return stripped.precision() - stripped.scale();
    }

    static long runDecimal(final long iterations) 
    {
        BigDecimal z = new BigDecimal("1");
        BigDecimal n = new BigDecimal("2");

        int found = 0;

        for (int iteration  = 1;; ++iteration) {

            z = z.add(n);

            if ( integerDigits(z) > integerDigits(n) ) {
                found += 1;
            }

            if ( iteration == iterations ) {
                break;
            }

            // 2 + ...
            z = z.add(n);

            // 1 / ...
            BigDecimal tmp = z;
            z = n;
            n = tmp;

        }

        return found;

    }

    public static void main(String[] args)
    {
        long iterations;
        if ( args.length == 1)
        {
            iterations = Long.parseLong(args[0]);
        }
        else
        {
            iterations = 1000;
        }

        System.out.printf("iterations: %d\n", iterations);
        long found = runDecimal(iterations);
        System.out.printf("%d\n", found);
    }
}
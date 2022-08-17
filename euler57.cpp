#include <stdio.h>

#include <vector>
#include <string>

struct BigUInt {
    std::vector<char> buf;

    BigUInt(char number)
    {
        buf.push_back( number );
    }

    void clear()
    {
        buf.clear();
    }

    std::string toString() const {
        std::string s;

        for ( auto riter=buf.rbegin(); riter != buf.rend(); ++riter)
        {
            s.push_back( *riter + '0' );
        }

        return s;
    }

    void add(const BigUInt& rhs, BigUInt *result) const
    {
        result->clear();

        auto a = this->buf.begin();
        auto b =   rhs.buf.begin();

        char carry = 0;

        for (;;)
        {
            if ( a == this->buf.end() && b == rhs.buf.end() )
            {
                if ( carry == 1 )
                {
                    result->buf.push_back(1);
                }
                break;
            }

            char val_a = a == this->buf.end() ? 0 : *a++;
            char val_b = b ==   rhs.buf.end() ? 0 : *b++;
            char sum = carry + val_a + val_b;

            if ( sum < 10 ) 
            {
                result->buf.push_back(sum);
                carry = 0;
            }
            else
            {
                result->buf.push_back(sum - 10);
                carry = 1;
            }
        }
    }
};

void print_iteration_result(const BigUInt& z, const BigUInt& n, int iteration)
{
    printf("#%d\t%s/%s\n"
        , iteration
        , z.toString().c_str()
        , n.toString().c_str()
        );
}

int main() {

    const int iterations = 1000;

    int iteration  = 1;
    BigUInt _z(1);
    BigUInt _n(2);
    BigUInt _z_sum(0);

    BigUInt& z     = _z;
    BigUInt& z_sum = _z_sum;
    BigUInt& n     = _n;

    int found = 0;

    for (;;) {

        z.add(n, &z_sum);

        if ( z_sum.buf.size() > n.buf.size() )
        {
            ++found;
        }

        if ( iteration == iterations ) {
            break;
        }

        iteration += 1;
        
        z_sum.add(n, &z);   // 2 + ...
        std::swap(z,n);     // 1 / ...
    }

    printf("%d\n", found);
}
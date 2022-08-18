#include <cstdio>
#include <cstdint>

#include <vector>
#include <string>

struct BigUInt {
    std::vector<uint8_t> buf;

    BigUInt(uint8_t number)
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

        uint8_t carry = 0;

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

            uint8_t val_a = a == this->buf.end() ? 0 : *a++;
            uint8_t val_b = b ==   rhs.buf.end() ? 0 : *b++;
            uint8_t sum = carry + val_a + val_b;

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
    void add(const BigUInt& rhs)
    {
        const auto orig_a_end = this->buf.end();

        auto a_read = this->buf.begin();
        auto b_read =   rhs.buf.begin();

        auto a_write = this->buf.begin();

        uint8_t carry = 0;

        for (;;)
        {
            const bool a_ended = a_read == orig_a_end;
            const bool b_ended = b_read == rhs.buf.end();

            if ( a_ended && b_ended )
            {
                if ( carry == 1 )
                {
                    this->buf.push_back(1);
                }
                break;
            }

            const uint8_t val_a = a_ended ? 0 : *a_read++;
            const uint8_t val_b = b_ended ? 0 : *b_read++;
            const uint8_t sum   = carry + val_a + val_b;

            uint8_t sum_digit;
            if ( sum < 10 ) 
            {
                sum_digit = sum;
                carry = 0;
            }
            else
            {
                sum_digit = sum - 10;
                carry = 1;
            }

            if ( a_write == orig_a_end )
            {
                this->buf.push_back(sum_digit);
            }
            else
            {
                *a_write = sum_digit;
                ++a_write;
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

void v1()
{
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

size_t v2(const size_t iterations)
{
    BigUInt _z(1);
    BigUInt _n(2);

    BigUInt& z     = _z;
    BigUInt& n     = _n;

    size_t found = 0;

    for (int iteration  = 1; ;++iteration) {

        z.add(n);

        if ( z.buf.size() > n.buf.size() )
        {
            ++found;
        }

        if ( iteration == iterations ) {
            break;
        }

        z.add(n);           // 2 + ...
        std::swap(z,n);     // 1 / ...
    }

    return found;    

}

int main(int argc, char* argv[]) {

    size_t iterations;

    if ( argc == 2 ) {
        sscanf(argv[1], "%zu", &iterations);
    }
    else
    {
        iterations = 1000;
    }
    printf("iterations: %zu\n", iterations);
    size_t found = v2(iterations);
    printf("%zu\n", found);
}
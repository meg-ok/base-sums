#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

void print_vector(const vector<int>& A)
{
    for (const auto& a : A)
    {
        cout << to_string(a);
    }
    cout << endl;
}

int num_at(const vector<int>& A, int i)
{
    try
    {
        return A.at(i);
    }
    catch (const std::out_of_range)
    {
        return 0;
    }
}

/*
* Converts from vector of ints in base -2 to an int in base 10.
*/
int convert_from_base_neg2(const vector<int>& A)
{
    int base10 = 0;
    int base = 2;
    int exp = 0;
    for (const auto& a : A)
    {
        base10 += a * pow(-2, exp);
        exp++;
    }
    return base10;
}

/*
 * Converts from an int in base 10 to a vector of ints in base -2.
 */
vector<int> convert_to_base_neg2(int a)
{
    if (a == 0) return {0};

    int base = -2;
    int remainder = 0;
    vector<int> baseNeg2;

    while (a != 0)
    {
        remainder = a % base;
        a /= base;
        // if remainder is negative, then add 2
        // (remainder will only ever be -1, 0, or 1)
        if (remainder == -1)
        {
            remainder += abs(base);
            a += 1;
        }
        baseNeg2.push_back(remainder);
    }
    return baseNeg2;
}

/*
 * Takes two vectors of ints in base -2 and returns the sum.
 */
vector<int> sum(const vector<int>& A, const vector<int>& B)
{
    if (A.empty()) return B;
    if (B.empty()) return A;

    int a_base10 = convert_from_base_neg2(A);
    int b_base10 = convert_from_base_neg2(B);
    
    int sum = a_base10 + b_base10;
    return convert_to_base_neg2(sum);
}

int main()
{
    // tests
    
    vector<int> A = {1}; // 1
    vector<int> B = {0, 1, 1, 1}; // -6
    vector<int> answer = {1, 1, 1, 1}; // -5
    vector<int> calculated_answer = sum(A, B);
    assert(answer == calculated_answer);

    A = {1, 1, 0, 1}; // -9
    B = {0, 1, 1, 1}; // -6
    answer = {1, 0, 0, 0, 1, 1}; // -15
    calculated_answer = sum(A, B);
    assert(answer == calculated_answer);
    
    A = {}; // 0
    B = {0, 1, 1, 1}; // -6
    answer = {0, 1, 1, 1}; // -6
    calculated_answer = sum(A, B);
    assert(answer == calculated_answer);
    
    A = {1, 1, 0, 1}; // -9
    B = {}; // 0
    answer = {1, 1, 0, 1}; // -9
    calculated_answer = sum(A, B);
    assert(answer == calculated_answer);
    
    A = {}; // 0
    B = {}; // 0
    answer = {}; // 0
    calculated_answer = sum(A, B);
    assert(answer == calculated_answer);
    
    A = {1}; // 1
    B = {1}; // 1
    vector<int> Z = {1}; // 1
    answer = {1, 1, 1}; // 0
    calculated_answer = sum(sum(A, B), Z);
    assert(answer == calculated_answer);
    
    A = {0, 1, 1, 1}; // -6
    B = {1}; // 1
    Z = {1}; // 1
    answer = {0, 0, 1, 1}; // -4
    calculated_answer = sum(sum(A, B), Z);
    assert(answer == calculated_answer);

    A = {0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1}; // 5730
    B = {0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1}; // -2396
    answer = {0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1}; // 3334
    calculated_answer = sum(A, B);
    //cout << "A: "; print_vector(A);
    //cout << "B: "; print_vector(B);
    //cout << "C: "; print_vector(calculated_answer);
    //cout << "R: "; print_vector(answer);
    assert(answer == calculated_answer);
    
    cout << "All tests passed." << endl;

    return 0;
}


#if __has_include(<benchmark/benchmark.h>)
#pragma comment ( lib, "Shlwapi.lib" )
#include <benchmark/benchmark.h>     // https://github.com/google/benchmark 
#endif

#if __has_include(<gtest/gtest.h>)
#include <gtest/gtest.h>        // https://google.github.io/googletest
#endif

#include "Matrix.h"


#ifdef BENCHMARK_BENCHMARK_H_

static void Gauss_JordanElimination_BM(benchmark::State & state)
{
    Matrix matrix(state.range(0), state.range(0));

    // Міряємо час роботи алгоритму 
    for (auto _ : state)
    {
        state.PauseTiming();
        matrix.SetRandom(state.range(0) * -1, state.range(0));
        state.ResumeTiming();

        try
        {
            benchmark::DoNotOptimize(Matrix::Gauss_JordanElimination(matrix));
            // benchmark::ClobberMemory();
        }
        catch (const std::overflow_error& e) {}

    }
    state.SetComplexityN(pow(state.range(0), 3));
}
BENCHMARK(Gauss_JordanElimination_BM)->Unit(benchmark::kMillisecond)->RangeMultiplier(2)->Range(2, 2 << 9);

#endif // BENCHMARK_BENCHMARK_H_



#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_

TEST(MatrixInversion, Gauss_JordanMethod)
{
    for (size_t i = 2; i < 2 << 9; i*=2)
    {
        Matrix identity_matrix(i, i); identity_matrix.MakeIndentityMatrix();
        Matrix matrix(i, i), inversed(i, i);

        ASSERT_EQ(identity_matrix * matrix, matrix);

        for (size_t j = i; j < 2 << 4; ++j)
        {
            matrix.SetRandom(i * -1, i);
            try
            {
                inversed = Matrix::Gauss_JordanElimination(matrix);
            }
            catch (const std::overflow_error& e) {
                std::cout << "Overflow exception: " << e.what() << std::endl;
            }

            // std::cout << inversed << "\n";
            EXPECT_EQ(inversed * matrix, identity_matrix);
        }
    }

    Matrix matrix(10, 10); matrix.setToZero();
    try
    {
        Matrix::Gauss_JordanElimination(matrix);
    }
    catch (const std::overflow_error& e)
    {
        EXPECT_STREQ("Determinant = 0", e.what());
        std::cout << "Overflow exception: " << e.what() << std::endl;
    }
}

#endif // GOOGLETEST_INCLUDE_GTEST_GTEST_H_

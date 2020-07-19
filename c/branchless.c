#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <string.h>

clock_t start, end;
double cpu_time_used;
int testCount = 100000;

char BRIGHTRED[] = "\033[31;1m";
char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";

void ToUpper_Branchless(char* d, int count)
{
    for (int i = 0; i < count; i++)
    {
        d[i] = (d[i] * !(d[i] >= 'a' && d[i] <= 'z')) +
               (d[i] - 32) * (d[i] >= 'a' && d[i] <= 'z');
    }
}

void ToUpper_Branchless2(char* d, int count)
{
    for (int i = 0; i < count; i++)
    {
        d[i] -= 32 * (d[i] >= 'a' && d[i] <= 'z');
    }
}

void ToUpper(char* d, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (d[i] >= 'a' && d[i] <= 'z')
        {
            d[i] -= 32;
        }
    }
}

char randomString[] = "E3rzRGj0qANuVaKITixjPV10MWHecDea9kLSRtXDwxsfSSSjTs8TELVuTZgNr2BZFyLxZrQyHyVgt2CeanzkhlwNRNy9wfz3LH9WArREMQShdWx1DUM5UFn7nyBpsc9UiysamsA38tG7xzI42HlPx1aMlOOZ0foAvUKAvmXV0hpy1Roh7ZKz044g1otF41yiA0PuT2Khr6VmQJDa1NQTHc7Yiid5IUnrCrvEKGdbivzUNegU4d3VKFKTPqT1RHoKyXNOJg7eWzUB1Bvmgyoi3fvORO6HEQo00iznmQeupTFK0H8q0KcJRv6hQiL0OxFKXKaXozPRyAOok70kTPF1BExdNC0owIaXmL8xJxtrWkOOgbbHlLrS9dJmHFZO5Ry3RfAcJKaXHRLNmqplqgvImeLzqhTV6lbPwrL4m0WHxBnrEArD3mo2yOFVciXcdPlBDBy0kE0YW5cUZvqzqdp9sfZ70ZvTHBzM5xAoR8WH4U6kO5VTiks9pHdcHvAYbXnafOqTKiPwNm1E92jldi9xkBOJE7ENfPvFU4cA5Onx6hIQYkh6JuFVAq6Gcdu3s08eBQauDwuJTTcEEEUAQwlUAjj7CkaKEkkhPkpL4xHGcij9jGRGn2elAA4dBDisjLHTW2MdPooN6z9dFbtvG2yhLdKFfscyTJpvJIBr0mUAMeG4QeXKqpQ9vCmdfxN972x9M6oQPeLLRCGPfzXnRLaFMeDs9z3mpVFvJaRGd2ojwKdMmhJWVhhHc37CHjL2WE5jBLpKck2XvpoWbMcLA2RvkQZbJ3ZARFGNXfBU8uMmldMiwmUhQdxegFFJ79uG2V1BoezMqRnOacUpABe60tBOpNANGvCyWVntu6OQD3tefWwlccpstZdSvpJlVceClt3yjkNLAR2YcoHvlBzbeWBRsJr8XcGQRfE0OTMIyafALLZd7NztGNr7ByPeS0Jmzk7oYEpdOVwHqDwJwIadt4bmPudX2MsN4FNa727GPt5c3CiABHoTgsVFdQbh2QSrUTkv";

void Test_ToUpper()
{
    for (int i = 0; i < testCount; i++)
    {
        ToUpper(randomString, strlen(randomString));
    }
}

void Test_ToUpper_Branchless()
{
    for (int i = 0; i < testCount; i++)
    {
        ToUpper_Branchless(randomString, strlen(randomString));
    }
}

void Test_ToUpper_Branchless2()
{
    for (int i = 0; i < testCount; i++)
    {
        ToUpper_Branchless2(randomString, strlen(randomString));
    }
}

int main(int argc, char *argv[])
{
  printf("%s *** C *** %s\n", INVERSE, RESET);

  printf("Starting ToUpper\n");
  start = clock();
  Test_ToUpper();
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, cpu_time_used, RESET);

  printf("\n");

  printf("Starting ToUpper_Branchless\n");
  start = clock();
  Test_ToUpper_Branchless();
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, cpu_time_used, RESET);

  printf("\n");

  printf("Starting ToUpper_Branchless2\n");
  start = clock();
  Test_ToUpper_Branchless2();
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, cpu_time_used, RESET);
}

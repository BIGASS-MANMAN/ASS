#include "/usr/local/Auto_Scoring_System/Assignment/Ass1/2012722060_KYJ/4.h"
#include "gtest/gtest.h"

class UnitTest4 : public testing::Test{
	protected:
		virtual void SetUp(){}
		virtual void TearDown(){}
};
int arr[5] = {-1,5,100,2,3};

TEST_F(UnitTest4,Min){EXPECT_EQ(-1,Min(arr,5));}
TEST_F(UnitTest4,Max){EXPECT_EQ(100,Max(arr,5));}
TEST_F(UnitTest4,Average){EXPECT_EQ(21.8,Average(arr));}
TEST_F(UnitTest4,Variance){EXPECT_EQ(3,Variance(arr));}

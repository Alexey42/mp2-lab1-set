#include <gtest.h>
#include <conio.h>
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
	_getch();
	return 1;
}

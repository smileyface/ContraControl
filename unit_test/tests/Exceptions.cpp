#include "../test_utilities/system_utilities.h"
#include "../test_utilities/test_utilities.h"

#include "../test_utilities/pch.h"

#include "../../Utilities/Utilities/exceptions.h"

namespace
{
	class Exceptions_Test : public ::testing::Test
	{
		virtual void SetUp()
		{
		}
		virtual void TearDown()
		{
		}
	};
}

TEST_F(Exceptions_Test, Description_Test)
{
	DeviceNotFoundException dnfe;
	NodeNotFoundException nnfe;
	IncorrectStateTypeException iste;
	InvalidCommandException ice;
	InvalidDeviceException ide;
	UnimplementedFunctionException ufe;
	NetworkErrorException nee;
	EXPECT_STREQ(dnfe.what(), "Device is not on node");
	EXPECT_STREQ(nnfe.what(), "Node is unknown");
	EXPECT_STREQ(iste.what(), "Incorrect state attempting to be mangled");
	EXPECT_STREQ(dnfe.what(), "Invalid command given");
	EXPECT_STREQ(dnfe.what(), "Device is of an invalid type");
	EXPECT_STREQ(dnfe.what(), "Function not implemented");
}

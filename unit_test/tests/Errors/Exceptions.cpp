#include "../../test_utilities/system_utilities.h"
#include "../../test_utilities/test_utilities.h"

#include "../../test_utilities/pch.h"

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
	NodeNotFoundException nnfe;
	IncorrectStateTypeException iste;
	InvalidCommandException ice;
	InvalidDeviceException ide;
	UnimplementedFunctionException ufe;
	NetworkErrorException nee;
	EXPECT_STREQ(nnfe.what(), "Node is unknown");
	EXPECT_STREQ(iste.what(), "Incorrect state attempting to be mangled");
	EXPECT_STREQ(ice.what(), "Invalid command given");
	EXPECT_STREQ(ide.what(), "Device is of an invalid type");
	EXPECT_STREQ(ufe.what(), "Function not implemented");
	EXPECT_STREQ(nee.what(), "Network Error");
}

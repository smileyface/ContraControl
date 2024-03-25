#include "../../test_utilities/test_utilities.h"
#include "../../test_utilities/system_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/View/view_main.h"
#include "../../dev/View/format/console.h"
#include "../../dev/View/format/file.h"

namespace
{
	class View_Format_Test : public ::testing::Test
	{
	public:
		View_Handle display_handle = 0;
		virtual void SetUp()
		{
			system_utilities::setup();
			system_utilities::start_system();
		}
		virtual void TearDown()
		{
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
}

TEST_F(View_Format_Test, Add_Console_Format)
{
	display_handle = view->add_display(DISPLAY_TYPES::CONSOLE);
	EXPECT_TRUE(view->get_format(display_handle) != 0);
	EXPECT_TRUE(instanceof<Console_Format>(view->get_format(display_handle)));

	view->remove_display(display_handle);
}

TEST_F(View_Format_Test, Remove_Console_Format)
{
	display_handle = view->add_display(DISPLAY_TYPES::CONSOLE);

	view->remove_display(display_handle);
	EXPECT_TRUE(view->get_format(display_handle) == 0);
}


TEST_F(View_Format_Test, Add_File_Format)
{
	display_handle = view->add_display(DISPLAY_TYPES::FILE);
	EXPECT_TRUE(view->get_format(display_handle) != 0);
	EXPECT_TRUE(instanceof<File_Format>(view->get_format(display_handle)));

	view->remove_display(display_handle);
}

TEST_F(View_Format_Test, Remove_File_Format)
{
	display_handle = view->add_display(DISPLAY_TYPES::FILE);

	view->remove_display(display_handle);
	EXPECT_TRUE(view->get_format(display_handle) == 0);
}
#include "../../test_utilities/test_utilities.h"
#include "../../test_utilities/system_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/View/view_main.h"
#include "../../dev/View/format/file.h"

namespace
{
	class File_View_Test : public ::testing::Test
	{
	public:
		View_Handle display_handle = 0;
		virtual void SetUp()
		{
			display_handle = view::add_display(DISPLAY_TYPES::FILE);
			system_utilities::setup();
			system_utilities::start_system();
		}
		virtual void TearDown()
		{
			view::remove_display(display_handle);
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
	};
}

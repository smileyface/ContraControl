#include "../../test_utilities/test_utilities.h"
#include "../../test_utilities/system_utilities.h"

#include "../../test_utilities/pch.h"

#include "../../dev/View/view_main.h"
#include "../../dev/View/view/views.h"
#include "../../dev/View/format/file.h"

#include <sstream>

namespace
{
	class File_View_Test : public ::testing::Test
	{
	public:
		View_Handle display_handle = 0;
		File_Format* file_format_ptr = 0;
		virtual void SetUp()
		{
			display_handle = view::add_display(DISPLAY_TYPES::FILE);
			file_format_ptr = static_cast<File_Format*>(view::list_of_formats[display_handle]);
			system_utilities::setup();
			system_utilities::start_system();
		}
		virtual void TearDown()
		{
			view::remove_display(display_handle);
			system_utilities::stop_system();
			system_utilities::cleanup();
		}
		inline bool exists_test3(const std::string& name)
		{
			struct stat buffer;
			return (stat(name.c_str(), &buffer) == 0);
		}
	};
}


TEST_F(File_View_Test, Log_View_Create)
{
	View* view = file_format_ptr->add_view(VIEW_TYPE_ENUM::LOG);
	EXPECT_TRUE(instanceof<File_Log_View>(view));
	File_Log_View* log_view = static_cast<File_Log_View*>(view);
	EXPECT_TRUE(log_view->get_file_name().find(".log") != std::string::npos);
	EXPECT_TRUE(exists_test3(log_view->get_file_name()));
}

TEST_F(File_View_Test, File_Log_Write)
{
	File_Log_View* log_view = static_cast<File_Log_View*>(file_format_ptr->add_view(VIEW_TYPE_ENUM::LOG));
	LOG_INFO("This is a test message", "File_Log_Write Test");
	system_utilities::step(2);

	std::ifstream infile(log_view->get_file_name());
	std::string line;
	bool found = false;
	while(std::getline(infile, line))
	{
		if(line.find("This is a test message") != std::string::npos)
		{
			found = true;
		}
	}
	if(!found)
	{
		FAIL() << "Message not found in log file.";
	}

}

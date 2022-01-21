#ifndef VIEW_TYPE_ENUM_H
#define VIEW_TYPE_ENUM_H

enum class VIEW_TYPE_ENUM
{
	SYSTEM
};

static char* get_view_type_enum_as_string(VIEW_TYPE_ENUM view_type)
{
	switch (view_type)
	{
	case VIEW_TYPE_ENUM::SYSTEM:
		return "System";
	}
	return "";
}
#endif

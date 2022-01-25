#ifndef MODEL_VIEW_INTERFACE
#define MODEL_VIEW_INTERFACE

class View_Interfaces
{
public:
	class Main_Interface;
};

class View_Interfaces::Main_Interface
{
public:
	static void start_view();
	static void stop_view();
	static void add_view(int view_type);
};


#endif
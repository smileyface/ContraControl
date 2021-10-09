class Format
{
	extern std::map<std::string, View*> view_tree;

	virtual void initalize();
	virtual void add_view(std::string handle, View* view);
};

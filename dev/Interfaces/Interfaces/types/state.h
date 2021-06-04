class state_interface
{
	Device_Id
	template<class State>
	void (*mangler)(State&) {};
};
/*****************************************************************//**
 * \file   key_input_interface.h
 * \brief  
 * 
 * \author kason
 * \date   September 2022
 *********************************************************************/

#ifndef KEY_INPUT_INTERFACE_PRESS
#define KEY_INPUT_INTERFACE_PRESS

#include <functional>
#include <map>

enum class KEY_STATE
{
	PRESSED,
	RELEASED
};

/** Interface for individual keys */
class Key_Press_Interface
{
public:
	Key_Press_Interface();
	/**
	 * Constructor for defining common keycode.
	 * \param code common code.
	 */
	Key_Press_Interface(int code);

	/**
	 * Function to run when key is pressed.
	 */
	std::function<void()> on_press = [] () 
	{ };
	/**
	 * Function to run when key is released.
	 */
	std::function<void()> on_release = [] ()
	{ };
	/**
	 * Function to run when key is held.
	 */
	std::function<void()> on_hold = [] ()
	{ };

	/**
	 * set state of button
	 * \param new_val State of the button.
	 */
	void operator=(const int new_val);
	/**
	 * Determine if a key is the same as another key
	 * \param check_val other key to check against.
	 * \return if the two keys are the same.
	 */
	bool operator==(const Key_Press_Interface check_val);
private:
	bool pressed = false;
	int val;
	char code;
	int index_ = -1;
};
/** Shorthand for Key_Press_Interface */
typedef Key_Press_Interface KPI;

char KPI_to_acsii(std::pair<KPI, KEY_STATE> key_to_convert);

/** Common codes for keys */
namespace KEY
{
	/** Common codes for the numpad */
	namespace NUM_PAD
	{
		extern KPI NUM_0; ///<0 common code key on the numpad
		extern KPI NUM_1; ///<1 common code key on the numpad
		extern KPI NUM_2; ///<2 common code key on the numpad
		extern KPI NUM_3; ///<3 common code key on the numpad
		extern KPI NUM_4; ///<4 common code key on the numpad
		extern KPI NUM_5; ///<5 common code key on the numpad
		extern KPI NUM_6; ///<6 common code key on the numpad
		extern KPI NUM_7; ///<7 common code key on the numpad
		extern KPI NUM_8; ///<8 common code key on the numpad
		extern KPI NUM_9; ///<9 common code key on the numpad
	}
	extern KPI A; ///<A common code
	extern KPI B; ///<B common code
	extern KPI C; ///<C common code
	extern KPI D; ///<D common code
	extern KPI E; ///<E common code
	extern KPI F; ///<F common code
	extern KPI G; ///<G common code
	extern KPI H; ///<H common code
	extern KPI I; ///<I common code
	extern KPI J; ///<J common code
	extern KPI K; ///<K common code
	extern KPI L; ///<L common code
	extern KPI M; ///<M common code
	extern KPI N; ///<N common code
	extern KPI O; ///<O common code
	extern KPI P; ///<P common code
	extern KPI Q; ///<Q common code
	extern KPI R; ///<R common code
	extern KPI S; ///<S common code
	extern KPI T; ///<T common code
	extern KPI U; ///<U common code
	extern KPI V; ///<V common code
	extern KPI W; ///<W common code
	extern KPI X; ///<X common code
	extern KPI Y; ///<Y common code
	extern KPI Z; ///<Z common code
	extern KPI NUM_0; ///<0 numrow common code
	extern KPI NUM_1; ///<1 numrow common code
	extern KPI NUM_2; ///<2 numrow common code
	extern KPI NUM_3; ///<3 numrow common code
	extern KPI NUM_4; ///<4 numrow common code
	extern KPI NUM_5; ///<5 numrow common code
	extern KPI NUM_6; ///<6 numrow common code
	extern KPI NUM_7; ///<7 numrow common code
	extern KPI NUM_8; ///<8 numrow common code
	extern KPI NUM_9; ///<9 numrow common code

	extern KPI ENTER;
	extern KPI L_SHIFT;
	extern KPI L_CTRL;
	extern KPI L_ALT;
	extern KPI TAB;
}


#endif
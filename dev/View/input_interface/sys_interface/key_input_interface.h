#ifndef KEY_INPUT_INTERFACE_PRESS
#define KEY_INPUT_INTERFACE_PRESS

#include <functional>
#include <map>

class Key_Press_Interface
{
public:
	Key_Press_Interface();
	bool poll();

	std::function<void()> on_press;
	std::function<void()> on_release;
	std::function<void()> on_hold;

	void operator=(const int new_val);
private:
	bool pressed = false;
	int val;
};
typedef Key_Press_Interface KPI;

extern std::map<int, KPI> code_map;

namespace KEY
{
	namespace NUM_PAD
	{
		extern KPI NUM_0;
		extern KPI NUM_1;
		extern KPI NUM_2;
		extern KPI NUM_3;
		extern KPI NUM_4;
		extern KPI NUM_5;
		extern KPI NUM_6;
		extern KPI NUM_7;
		extern KPI NUM_8;
		extern KPI NUM_9;
	}
	extern KPI A;
	extern KPI B;
	extern KPI C;
	extern KPI D;
	extern KPI E;
	extern KPI F;
	extern KPI G;
	extern KPI H;
	extern KPI I;
	extern KPI J;
	extern KPI K;
	extern KPI L;
	extern KPI M;
	extern KPI N;
	extern KPI O;
	extern KPI P;
	extern KPI Q;
	extern KPI R;
	extern KPI S;
	extern KPI T;
	extern KPI U;
	extern KPI V;
	extern KPI W;
	extern KPI X;
	extern KPI Y;
	extern KPI Z;
	extern KPI NUM_0;
	extern KPI NUM_1;
	extern KPI NUM_2;
	extern KPI NUM_3;
	extern KPI NUM_4;
	extern KPI NUM_5;
	extern KPI NUM_6;
	extern KPI NUM_7;
	extern KPI NUM_8;
	extern KPI NUM_9;
}


#endif
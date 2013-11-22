#ifndef MOUSE_H
#define MOUSE_H


class Mouse
{
	public:
		static Mouse* ControlInstance();
		void MouseMove(int x, int y);
		void MouseClick(int button, int state, int x, int y);

	protected:
		Mouse();
};  // class declaration

#endif
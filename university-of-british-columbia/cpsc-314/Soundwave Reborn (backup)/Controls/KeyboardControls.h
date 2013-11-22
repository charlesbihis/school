#ifndef KEYBOARD_H
#define KEYBOARD_H


class Keyboard
{
  public:
    static Keyboard* ControlInstance();
	void InterpretKey(unsigned int key);
	void InterpretSpecialKey(unsigned int special_key);
	void PrintBasicHelp();
	void PrintCharacterHelp();

	float cameraspeed;
	bool inverted;

  protected:
    Keyboard();
};  // class declaration

#endif
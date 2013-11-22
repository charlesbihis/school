#ifndef CHARACTER_H
#define CHARACTER_H


class Character
{
  public:	// ***** Accessors ***** //
    static Character *ControlInstance();
    float GetRotateSpeed();
	float GetRotateSpeedOld();
	int GetFogStart();
	int GetFogEnd();
			// ***** Manipulators ***** //

			// ***** Mutators ***** //
	void Reset();
	void PauseRotation();
	void IncreaseRotateSpeed();
	void DecreaseRotateSpeed();
	void ToggleFog();
	void SetFogStart(int new_value);
	void IncreaseFogStart();
	void DecreaseFogStart();
	void SetFogEnd(int new_value);
	void IncreaseFogEnd();
	void DecreaseFogEnd();

  protected:
    Character();

  private:
    //static Character control_instance;
    float rotate_speed;
	float rotate_speed_old;
	bool fog;
	int fog_start;
	int fog_end;
};  // class declaration

#endif
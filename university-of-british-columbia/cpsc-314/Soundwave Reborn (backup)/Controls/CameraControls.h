#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
	public:
		static Camera* ControlInstance();

		int temp_y;
		int temp_x;
		int camera_position_x;
		int camera_position_y;
		int camera_target_x;
		int camera_target_y;
		int depth;

	protected:
		Camera();
};  // class declaration

#endif
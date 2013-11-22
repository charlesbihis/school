#ifndef CAMERA_H
#define CAMERA_H

typedef struct tVector3					// expanded 3D vector struct
{			
	tVector3() {}	// constructor
	tVector3 (float new_x, float new_y, float new_z) // initialize constructor	 
	{x = new_x; y = new_y; z = new_z;}
	// overload + operator so that we easier can add vectors
	tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
	// overload - operator that we easier can subtract vectors
	tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
	// overload * operator that we easier can multiply by scalars
	tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
	// overload / operator that we easier can divide by a scalar
	tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}

	float x, y, z;						// 3D vector coordinates
}tVector3;


class Camera
{
  public:

	  //NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
	  int mWindowWidth;
	  int mWindowHeight;

	  tVector3 mPos;	
	  tVector3 mView;		
	  tVector3 mUp;			


    static Camera* ControlInstance();
	void Position_Camera(float pos_x,  float pos_y,  float pos_z, float view_x, float view_y, float view_z, float up_x,   float up_y,   float up_z);
    void Move_Camera(float cameraspeed);
    void Rotate_View(float x, float y, float z);
    void Mouse_Move();

  protected:
    Camera();
};  // class declaration

#endif
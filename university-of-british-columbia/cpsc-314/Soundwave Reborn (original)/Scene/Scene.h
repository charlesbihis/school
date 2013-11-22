#ifndef SCENE_H#define SCENE_H
class Scene
{
  public:
    Scene();
    void Draw();

	GLint GetCurrentLight();

  private:
    void DrawSpotlight();
	void DrawFloorlight();
	void DrawFloor();
	void DrawCageDome();
	void DrawGlassDome();
	void DrawVerticalGirder();
	void DrawHorizontalGirder(double start_value);
	void DrawPlatform();
	void DrawPath();

	GLint current_light;
};  // class declaration

#endif
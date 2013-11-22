#ifndef SCENE_H#define SCENE_H


class Scene
{
	public:
		static Scene* ControlInstance();
		void Draw();
		void DrawSkybox(float x, float y, float z, float width, float height, float length);
		void ToggleLight(unsigned int light);
		
		GLint GetCurrentLight();
		unsigned int skybox_textures[6];

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
		bool spotlight1_on;
		bool spotlight2_on;
		bool spotlight3_on;

	protected:
		Scene();
};  // class declaration

#endif

//-----------------------------------------------------------------------------
//           Name: ogl_particle_system.cpp
//         Author: Kevin Harris
//  Last Modified: 02/01/05
//    Description: This sample demonstrates how to create a particle system 
//                 using OpenGL's new GL_ARB_point_sprite extension, which
//                 creates point-rotated billboards on the GPU.
//
//   Control Keys: Up         - View moves forward
//                 Down       - View moves backward
//                 Left       - View strafes left
//                 Right      - View strafes Right
//                 Left Mouse - Perform looking
//                 Mouse      - Look about the scene
//                 F1         - Change active particle system
//                 F2         - Increase particle size
//                 F3         - Decrease particle size
//-----------------------------------------------------------------------------

#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include "resource.h"
#include "matrix4x4f.h"
#include "particlesystem.h"

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND   g_hWnd      = NULL;
HDC	   g_hDC       = NULL;
HGLRC  g_hRC       = NULL;
GLuint g_textureID = -1;

POINT  g_ptLastMousePosit;
POINT  g_ptCurrentMousePosit;
bool   g_bMousing = false;
float  g_fMoveSpeed = 25.0f;
float  g_fElpasedTime;
double g_dCurTime;
double g_dLastTime;

vector3f g_vEye(0.0f, 3.0f, 15.0f);  // Eye Position
vector3f g_vLook(0.0f, 0.0f, -1.0f); // Look Vector
vector3f g_vUp(0.0f, 1.0f, 0.0f);    // Up Vector
vector3f g_vRight(1.0f, 0.0f, 0.0f); // Right Vector

struct Vertex
{
	// GL_T2F_V3F
    float tu, tv;
    float x, y, z;
};

Vertex g_floorVertices[] =
{
    { 0.0f,1.0f, -5.0f, 0.0f, -5.0f },
    { 1.0f,1.0f,  5.0f, 0.0f, -5.0f },
    { 1.0f,0.0f,  5.0f, 0.0f,  5.0f },
    { 0.0f,0.0f, -5.0f, 0.0f,  5.0f }
};

int g_nActiveSystem = 1;
CParticleSystem *g_pParticleSystems[6];

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void loadTexture(void);
void init(void);
void render(void);
void shutDown(void);
void getRealTimeUserInput(void);
void updateViewMatrix(void);
void initParticles(void);

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR     lpCmdLine,
					int       nCmdShow )
{
	WNDCLASSEX winClass; 
	MSG        uMsg;

    memset(&uMsg,0,sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
    winClass.hIcon	       = LoadIcon(hInstance, (LPCTSTR)IDI_OPENGL_ICON);
    winClass.hIconSm	   = LoadIcon(hInstance, (LPCTSTR)IDI_OPENGL_ICON);
	winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;
	
	if( !RegisterClassEx(&winClass) )
		return E_FAIL;

	g_hWnd = CreateWindowEx( NULL, "MY_WINDOWS_CLASS", 
                             "OpenGL - Particle System",
						     WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					         0, 0, 640, 480, NULL, NULL, hInstance, NULL );

	if( g_hWnd == NULL )
		return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );
    UpdateWindow( g_hWnd );

	init();
    initParticles();

	while( uMsg.message != WM_QUIT )
	{
		if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &uMsg );
			DispatchMessage( &uMsg );
		}
        else
		{
			g_dCurTime     = timeGetTime();
			g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
			g_dLastTime    = g_dCurTime;

		    render();
		}
	}

	shutDown();

    UnregisterClass( "MY_WINDOWS_CLASS", hInstance );

	return uMsg.wParam;
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc( HWND   hWnd, 
							 UINT   msg, 
							 WPARAM wParam, 
							 LPARAM lParam )
{
    switch( msg )
	{
        case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;

				case VK_F1:
				{
					++g_nActiveSystem;

					if( g_nActiveSystem >= 6 )
						g_nActiveSystem = 0;

					g_pParticleSystems[g_nActiveSystem]->RestartParticleSystem();
				}
				break;

				case VK_F2:
				{
					float fSize = g_pParticleSystems[g_nActiveSystem]->GetSize();

					fSize += 1.0f;

					if( fSize >= g_pParticleSystems[g_nActiveSystem]->GetMaxPointSize() )
						fSize = g_pParticleSystems[g_nActiveSystem]->GetMaxPointSize();

					g_pParticleSystems[g_nActiveSystem]->SetSize( fSize );
				}
				break;

				case VK_F3:
				{
					float fSize = g_pParticleSystems[g_nActiveSystem]->GetSize();

					fSize -= 1.0f;

					if( fSize <= 1.0f )
						fSize = 1.0f;

					g_pParticleSystems[g_nActiveSystem]->SetSize( fSize );
				}
				break;
			}
		}
        break;

        case WM_LBUTTONDOWN:
		{
			g_bMousing = true;
		}
		break;

		case WM_LBUTTONUP:
		{
			g_bMousing = false;
		}
		break;

        case WM_SIZE:
		{
			int nWidth  = LOWORD(lParam); 
			int nHeight = HIWORD(lParam);
			glViewport(0, 0, nWidth, nHeight);

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			gluPerspective( 45.0, (GLdouble)nWidth / (GLdouble)nHeight, 0.1, 1000.0);
		}
		break;

		case WM_CLOSE:
		{
			PostQuitMessage(0);	
		}

        case WM_DESTROY:
		{
            PostQuitMessage(0);
		}
        break;
		
		default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Name: loadTexture()
// Desc: 
//-----------------------------------------------------------------------------
void loadTexture(void)
{
	AUX_RGBImageRec *pTextureImage = auxDIBImageLoad( ".\\ogl.bmp" );

    if( pTextureImage != NULL )
	{
        glGenTextures( 1, &g_textureID );

		glBindTexture( GL_TEXTURE_2D, g_textureID );

		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexImage2D( GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY, 0,
				GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data );
	}

	if( pTextureImage )
	{
		if( pTextureImage->data )
			free( pTextureImage->data );

		free( pTextureImage );
	}
}

//-----------------------------------------------------------------------------
// Name: getRealTimeUserInput()
// Desc: 
//-----------------------------------------------------------------------------
void getRealTimeUserInput( void )
{
	//
	// Get mouse input...
	//

	POINT mousePosit;
	GetCursorPos( &mousePosit );
	ScreenToClient( g_hWnd, &mousePosit );

	g_ptCurrentMousePosit.x = mousePosit.x;
	g_ptCurrentMousePosit.y = mousePosit.y;

	matrix4x4f matRotation;

	if( g_bMousing )
	{
		int nXDiff = (g_ptCurrentMousePosit.x - g_ptLastMousePosit.x);
		int nYDiff = (g_ptCurrentMousePosit.y - g_ptLastMousePosit.y);

		if( nYDiff != 0 )
		{
			matRotation.rotate( -(float)nYDiff / 3.0f, g_vRight );
			matRotation.transformVector( &g_vLook );
			matRotation.transformVector( &g_vUp );
		}

		if( nXDiff != 0 )
		{
			matRotation.rotate( -(float)nXDiff / 3.0f, vector3f(0.0f, 1.0f, 0.0f) );
			matRotation.transformVector( &g_vLook );
			matRotation.transformVector( &g_vUp );
		}
	}

	g_ptLastMousePosit.x = g_ptCurrentMousePosit.x;
	g_ptLastMousePosit.y = g_ptCurrentMousePosit.y;

	//
	// Get keyboard input...
	//

	unsigned char keys[256];
	GetKeyboardState( keys );

	vector3f tmpLook  = g_vLook;
	vector3f tmpRight = g_vRight;

	// Up Arrow Key - View moves forward
	if( keys[VK_UP] & 0x80 )
		g_vEye -= tmpLook*-g_fMoveSpeed*g_fElpasedTime;

	// Down Arrow Key - View moves backward
	if( keys[VK_DOWN] & 0x80 )
		g_vEye += (tmpLook*-g_fMoveSpeed)*g_fElpasedTime;

	// Left Arrow Key - View side-steps or strafes to the left
	if( keys[VK_LEFT] & 0x80 )
		g_vEye -= (tmpRight*g_fMoveSpeed)*g_fElpasedTime;

	// Right Arrow Key - View side-steps or strafes to the right
	if( keys[VK_RIGHT] & 0x80 )
		g_vEye += (tmpRight*g_fMoveSpeed)*g_fElpasedTime;

	// Home Key - View elevates up
	if( keys[VK_HOME] & 0x80 )
		g_vEye.y += g_fMoveSpeed*g_fElpasedTime; 

	// End Key - View elevates down
	if( keys[VK_END] & 0x80 )
		g_vEye.y -= g_fMoveSpeed*g_fElpasedTime;
}

//-----------------------------------------------------------------------------
// Name: init()
// Desc: 
//-----------------------------------------------------------------------------
void init( void )
{
	GLuint PixelFormat;

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 16;
    pfd.cDepthBits = 16;
	
	g_hDC = GetDC( g_hWnd );
	PixelFormat = ChoosePixelFormat( g_hDC, &pfd );
	SetPixelFormat( g_hDC, PixelFormat, &pfd);
	g_hRC = wglCreateContext( g_hDC );
	wglMakeCurrent( g_hDC, g_hRC );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_TEXTURE_2D);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	loadTexture();
}

//-----------------------------------------------------------------------------
// Name: shutDown()
// Desc: 
//-----------------------------------------------------------------------------
void shutDown( void )	
{
    glDeleteTextures( 1, &g_textureID );

	for( int i = 0; i < 6; ++i )
	{
		if( g_pParticleSystems[i] != NULL )
		{
			delete g_pParticleSystems[i];
			g_pParticleSystems[i] = NULL;
		}
	}

	if( g_hRC != NULL )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( g_hRC );
		g_hRC = NULL;
	}

	if( g_hDC != NULL )
	{
		ReleaseDC( g_hWnd, g_hDC );
		g_hDC = NULL;
	}
}

//-----------------------------------------------------------------------------
// Name: initParticles()
// Desc: 
//-----------------------------------------------------------------------------
void initParticles( void )
{
	//
    // Exploding burst
	//
    
    g_pParticleSystems[0] = new CParticleSystem();

    g_pParticleSystems[0]->SetTexture( ".\\particle.bmp" );
    g_pParticleSystems[0]->SetMaxParticles( 100 );
    g_pParticleSystems[0]->SetNumToRelease( 100 );
    g_pParticleSystems[0]->SetReleaseInterval( 0.05f );
    g_pParticleSystems[0]->SetLifeCycle( 0.5f );
    g_pParticleSystems[0]->SetSize( 30.0f );
    g_pParticleSystems[0]->SetColor( vector3f( 1.0f, 0.0f, 0.0f ));
    g_pParticleSystems[0]->SetPosition( vector3f( 0.0f, 5.0f, 0.0f) );
    g_pParticleSystems[0]->SetVelocity( vector3f( 0.0f, 0.0f, 0.0f) );
    g_pParticleSystems[0]->SetGravity( vector3f( 0.0f, 0.0f, 0.0f) );
    g_pParticleSystems[0]->SetWind( vector3f( 0.0f, 0.0f, 0.0f) );
    g_pParticleSystems[0]->SetVelocityVar( 10.0f );

    g_pParticleSystems[0]->Init();

	//
    // Wind blown fountain
	//

	g_pParticleSystems[1] = new CParticleSystem();

    g_pParticleSystems[1]->SetTexture( ".\\particle.bmp" );
    g_pParticleSystems[1]->SetMaxParticles( 500 );
    g_pParticleSystems[1]->SetNumToRelease( 5 );
    g_pParticleSystems[1]->SetReleaseInterval( 0.05f );
    g_pParticleSystems[1]->SetLifeCycle( 4.0f );
    g_pParticleSystems[1]->SetSize( 30.0f );
    g_pParticleSystems[1]->SetColor( vector3f( 1.0f, 1.0f, 1.0f ));
    g_pParticleSystems[1]->SetPosition( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[1]->SetVelocity( vector3f( 0.0f, 5.0f, 0.0f ) );
    g_pParticleSystems[1]->SetGravity( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[1]->SetWind( vector3f( 2.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[1]->SetVelocityVar( 1.5f );

    g_pParticleSystems[1]->Init();

	//
    // Omni-directiional emission expanding into space with no air resistence
	//

    g_pParticleSystems[2] = new CParticleSystem();

    g_pParticleSystems[2]->SetTexture( ".\\particle.bmp" );
    g_pParticleSystems[2]->SetMaxParticles( 2048 );
    g_pParticleSystems[2]->SetNumToRelease( 10 );
    g_pParticleSystems[2]->SetReleaseInterval( 0.05f );
    g_pParticleSystems[2]->SetLifeCycle( 5.0f );
    g_pParticleSystems[2]->SetSize( 30.0f );
    g_pParticleSystems[2]->SetColor( vector3f( 1.0f, 1.0f, 1.0f ));
    g_pParticleSystems[2]->SetPosition( vector3f( 0.0f, 0.0f, 0.0f) );
    g_pParticleSystems[2]->SetVelocity( vector3f( 0.0f, 0.0f, 0.0f) );
    g_pParticleSystems[2]->SetGravity( vector3f( 0.0f, 0.0f, 0.0f) );

    g_pParticleSystems[2]->SetWind( vector3f( 0.0f, 0.0f, 0.0f) );
    g_pParticleSystems[2]->SetAirResistence( false );

    g_pParticleSystems[2]->SetVelocityVar(2.0f);

    g_pParticleSystems[2]->Init();
 
	//
    // Fountain particles behave like paint spots when striking a plane as 
	// the wind blowing them towards us
	//

    g_pParticleSystems[3] = new CParticleSystem();

    g_pParticleSystems[3]->SetTexture( ".\\particle.bmp" );
    g_pParticleSystems[3]->SetMaxParticles( 100 );
    g_pParticleSystems[3]->SetNumToRelease( 10 );
    g_pParticleSystems[3]->SetReleaseInterval( 0.05f );
    g_pParticleSystems[3]->SetLifeCycle( 3.0f );
    g_pParticleSystems[3]->SetSize( 30.0f );
    g_pParticleSystems[3]->SetColor( vector3f( 1.0f, 1.0f, 1.0f ));
    g_pParticleSystems[3]->SetPosition( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[3]->SetVelocity( vector3f( 0.0f, 5.0f, 0.0f ) );
    g_pParticleSystems[3]->SetGravity( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[3]->SetWind( vector3f( 0.0f, 0.0f, -20.0f ) );
    g_pParticleSystems[3]->SetVelocityVar( 2.5f );

    g_pParticleSystems[3]->SetCollisionPlane( vector3f( 0.0f, 0.0f,1.0f ), 
                                          vector3f( 0.0f, 0.0f, -5.0f ),
                                          1.0f, CR_STICK );

    g_pParticleSystems[3]->Init();

	//
    // Fountain using a single collision plane acting as a floor
	//

    g_pParticleSystems[4] = new CParticleSystem();

    g_pParticleSystems[4]->SetTexture( ".\\particle.bmp" );
    g_pParticleSystems[4]->SetMaxParticles( 200 );
    g_pParticleSystems[4]->SetNumToRelease( 10 );
    g_pParticleSystems[4]->SetReleaseInterval( 0.05f );
    g_pParticleSystems[4]->SetLifeCycle( 5.0f );
    g_pParticleSystems[4]->SetSize( 30.0f );
    g_pParticleSystems[4]->SetColor( vector3f( 1.0f, 1.0f, 1.0f ));
    g_pParticleSystems[4]->SetPosition( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[4]->SetVelocity( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[4]->SetGravity( vector3f( 0.0f, -9.8f, 0.0f ) );
    g_pParticleSystems[4]->SetWind( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[4]->SetVelocityVar( 20.0f );

    g_pParticleSystems[4]->SetCollisionPlane( vector3f( 0.0f, 1.0f, 0.0f ), 
                                          vector3f( 0.0f, 0.0f, 0.0f ) );

    g_pParticleSystems[4]->Init();

	//
    // Fountain boxed-in by 6 collision planes
	//

    g_pParticleSystems[5] = new CParticleSystem();

    g_pParticleSystems[5]->SetTexture( ".\\particle.bmp" );
    g_pParticleSystems[5]->SetMaxParticles( 100 );
    g_pParticleSystems[5]->SetNumToRelease( 5 );
    g_pParticleSystems[5]->SetReleaseInterval( 0.05f );
    g_pParticleSystems[5]->SetLifeCycle( 5.0f );
    g_pParticleSystems[5]->SetSize( 30.0f );
    g_pParticleSystems[5]->SetColor( vector3f( 1.0f, 1.0f, 1.0f ));
    g_pParticleSystems[5]->SetPosition( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[5]->SetVelocity( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[5]->SetGravity( vector3f( 0.0f, -9.8f, 0.0f ) );
    g_pParticleSystems[5]->SetWind( vector3f( 0.0f, 0.0f, 0.0f ) );
    g_pParticleSystems[5]->SetVelocityVar( 20.0f );

    // Create a series of planes to collide with
    g_pParticleSystems[5]->SetCollisionPlane( vector3f( 0.0f, 1.0f, 0.0f ), 
                                          vector3f( 0.0f, 0.0f, 0.0f ) ); // Floor

    g_pParticleSystems[5]->SetCollisionPlane( vector3f( 1.0f, 0.0f, 0.0f ), 
                                          vector3f(-3.0f, 0.0f, 0.0f ) ); // Left Wall

    g_pParticleSystems[5]->SetCollisionPlane( vector3f(-1.0f, 0.0f, 0.0f ), 
                                          vector3f( 3.0f, 0.0f, 0.0f ) ); // Right Wall

    g_pParticleSystems[5]->SetCollisionPlane( vector3f( 0.0f, 0.0f, 1.0f ), 
                                          vector3f( 0.0f, 0.0f,-3.0f ) ); // Front Wall

    g_pParticleSystems[5]->SetCollisionPlane( vector3f( 0.0f, 0.0f,-1.0f ), 
                                          vector3f( 0.0f, 0.0f, 3.0f ) ); // Back Wall

    g_pParticleSystems[5]->SetCollisionPlane( vector3f( 0.0f,-1.0f, 0.0f ), 
                                          vector3f( 0.0f, 5.0f, 0.0f ) ); // Ceiling

    g_pParticleSystems[5]->Init();
}

//-----------------------------------------------------------------------------
// Name : updateViewMatrix() 
// Desc : Builds a view matrix suitable for OpenGL.
//
// Here's what the final view matrix should look like:
//
//  |  rx   ry   rz  -(r.e) |
//  |  ux   uy   uz  -(u.e) |
//  | -lx  -ly  -lz   (l.e) |
//  |   0    0    0     1   |
//
// Where r = Right vector
//       u = Up vector
//       l = Look vector
//       e = Eye position in world space
//       . = Dot-product operation
//
//-----------------------------------------------------------------------------
void updateViewMatrix( void )
{
    matrix4x4f view;
    view.identity();

    g_vLook.normalize();
 
    g_vRight = vector3f::crossProduct(g_vLook, g_vUp);
    g_vRight.normalize();

    g_vUp = vector3f::crossProduct(g_vRight, g_vLook);
    g_vUp.normalize();

    view.m[0] =  g_vRight.x;
    view.m[1] =  g_vUp.x;
    view.m[2] = -g_vLook.x;
    view.m[3] =  0.0f;

    view.m[4] =  g_vRight.y;
    view.m[5] =  g_vUp.y;
    view.m[6] = -g_vLook.y;
    view.m[7] =  0.0f;

    view.m[8]  =  g_vRight.z;
    view.m[9]  =  g_vUp.z;
    view.m[10] = -g_vLook.z;
    view.m[11] =  0.0f;

    view.m[12] = -vector3f::dotProduct(g_vRight, g_vEye);
    view.m[13] = -vector3f::dotProduct(g_vUp, g_vEye);
    view.m[14] =  vector3f::dotProduct(g_vLook, g_vEye);
    view.m[15] =  1.0f;

    glMultMatrixf( view.m );
}

//-----------------------------------------------------------------------------
// Name: render()
// Desc: 
//-----------------------------------------------------------------------------
void render( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	getRealTimeUserInput();

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	updateViewMatrix();

    //
	// The particle system will need to know how much time has passed since 
	// the last time it was updated, so we'll need to keep track of how much   
	// time has elapsed since the last frame update...
	//

	g_pParticleSystems[g_nActiveSystem]->Update( (float)g_fElpasedTime );
    
	//
	// Render the floor...
	//

	glBindTexture( GL_TEXTURE_2D, g_textureID );
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    glInterleavedArrays( GL_T2F_V3F, 0, g_floorVertices );
    glDrawArrays( GL_QUADS, 0, 4 );

	//
	// Prepare to render particle system
	//

	//
	// Enabling GL_DEPTH_TEST and setting glDepthMask to GL_FALSE makes the 
    // Z-Buffer read-only, which helps remove graphical artifacts generated 
    // from  rendering a list of particles that haven't been sorted by 
    // distance to the eye.
	//
    // Enabling GL_BLEND and setting glBlendFunc to GL_DST_ALPHA with GL_ONE 
    // allows particles, which overlap, to alpha blend with each other 
    // correctly.
	//

    glEnable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );

	glEnable( GL_BLEND );
    glBlendFunc( GL_DST_ALPHA, GL_ONE );

    //
	// Render particle system
	//

	glBindTexture( GL_TEXTURE_2D, g_pParticleSystems[g_nActiveSystem]->GetTextureID() );
    g_pParticleSystems[g_nActiveSystem]->Render();

    //
    // Reset OpenGL states...
	//

    glDepthMask( GL_TRUE );
    glDisable( GL_BLEND );

	SwapBuffers( g_hDC );
}

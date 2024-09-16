//*****************************************************************************
// Application Class
//
//(c) 2003-2006 by Martin Christen. All Rights reserved.
//******************************************************************************/

#include "glApplication.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <string>

using namespace cwc;

std::list<glApplication*> glApplication::_gAppInstances;

//-----------------------------------------------------------------------------

glApplication::glApplication()
{
   _gAppInstances.push_back(this);
   
   int argc = 1;
   std::string argv = "CWApp";
   
   glutInit(&argc, (char **)argv.c_str());
}

//-----------------------------------------------------------------------------

glApplication::~glApplication()
{
   // remove this instance from application list
   std::list<glApplication*>::iterator i = _gAppInstances.begin();
   
   while (i!=_gAppInstances.end())
   {
      if (*i == this)
      {
         _gAppInstances.erase(i);
         return;
      } 
      
      i++;   
   }
}

//-----------------------------------------------------------------------------

void glApplication::run(void)
{
   OnInit();
   MainLoop();
   OnExit();
}

//-----------------------------------------------------------------------------

bool glApplication::MainLoop()
{
   glutMainLoop();
   return true;
}

//-----------------------------------------------------------------------------


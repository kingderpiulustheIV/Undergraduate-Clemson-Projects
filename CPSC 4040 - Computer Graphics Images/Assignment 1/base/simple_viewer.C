// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 1
// 9/11/2025
#include <vector>
#include <string>
#include "StarterViewer.h"
#include "oiiostuff.h"

using namespace starter;

int main( int argc, char** argv )
{

   simple_read();
   StarterViewer* viewer = CreateViewer();

   std::vector<std::string> args;

   for(int i=0;i<argc;i++)
   {
      std::string s(argv[i]);
      args.push_back(s);
   }
   viewer->Init(args);

   viewer->MainLoop();

}

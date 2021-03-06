#include "vtkObject.h"

#include <vtkstd/string> 
#include <vtksys/ios/sstream>

class Output
{
public:
  Output()
    {
    }
  Output(const Output&);
  void operator=(const Output&);
  ~Output(){}
  vtksys_ios::ostringstream Stream;

  int ProcessFile(const char* file, const char* title)
    {
    FILE* fp = fopen(file, "r");
    if ( !fp )
      {
      cout << "Canot open file: " << file << endl;
      return VTK_ERROR;
      }
    int ch;
    this->Stream << "// Define the " << title << " interfaces." << endl
      << "//" << endl 
      << "// Generated from file: " << file << endl
      << "//" << endl
      << "const char* " << title << " =" 
      << endl << "\"";
    while ( ( ch = fgetc(fp) ) != EOF )
      {
      if ( ch == '\n' )
        {
        this->Stream << "\\n\"" << endl << "\"";
        }
      else if ( ch == '\\' )
        {
        this->Stream << "\\\\";
        }
      else if ( ch == '\"' )
        {
        this->Stream << "\\\"";
        }
      else if ( ch != '\r' )
        {
        this->Stream << (unsigned char)ch;
        }
      }
    this->Stream << "\\n\";" << endl;
    fclose(fp);
    return VTK_OK;
    }
};

int main(int argc, char* argv[])
{
  if ( argc < 4 )
    {
    cout << "Usage: " << argv[0] << " <output-file> <input-path> <title>" << endl;
    return 1;
    }
  Output ot;
  ot.Stream << "// Loadable modules" << endl
    << "//" << endl
    << "// Generated by " << argv[0] << endl
    << "//" << endl
            << "#ifndef __vtkKWCommonPro" << argv[3] << "_h" << endl
            << "#define __vtkKWCommonPro" << argv[3] << "_h" << endl
    << "" << endl;

  vtkstd::string output = argv[1];
  vtkstd::string input = argv[2];

  if ( ot.ProcessFile(input.c_str(), argv[3]) != VTK_OK )
    {
    cout << "Problem generating header file from XML file: " << input.c_str() << endl;
    return 1;
    }
  ot.Stream << "" << endl
    << "#endif" << endl;
  FILE* fp = fopen(output.c_str(), "w");
  if ( !fp )
    {
    cout << "Cannot open output file: " << output.c_str() << endl;
    return 1;
    }
  fprintf(fp, "%s", ot.Stream.str().c_str());
  fclose(fp);
  return 0;
}

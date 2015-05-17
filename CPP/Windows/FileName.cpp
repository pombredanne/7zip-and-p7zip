// Windows/FileName.cpp

#include "StdAfx.h"

#include "Windows/FileName.h"
#include "Common/Wildcard.h"

// FIXME
namespace NWindows {
namespace NFile {
namespace NDir {
bool MyGetFullPathName(CFSTR path, FString &resFullPath);
}}}

namespace NWindows {
namespace NFile {
namespace NName {

bool IsAbsolutePath(const wchar_t *s) { return s[0] == WCHAR_PATH_SEPARATOR; } // FIXME


void NormalizeDirPathPrefix(CSysString &dirPath)
{
  if (dirPath.IsEmpty())
    return;
  if (dirPath.ReverseFind(kDirDelimiter) != dirPath.Len() - 1)
    dirPath += kDirDelimiter;
}

#ifndef _UNICODE
void NormalizeDirPathPrefix(UString &dirPath)
{
  if (dirPath.IsEmpty())
    return;
  if (dirPath.Back() != WCHAR_PATH_SEPARATOR)
    dirPath += WCHAR_PATH_SEPARATOR;
}
#endif

/*
 * Resolve dot '.' and dotdot '..' folders in path string s to ensure that
 * extracted files and directories are always created under the extraction
 * directory and not outside.
 * Fix for p7zip bug #157
 * Note: this is the original function from 7zip 9.38 ported to 7zip
 */
static bool ResolveDotsFolders(UString &s)
{
  s.Replace(L'\\', WCHAR_PATH_SEPARATOR);
  for (int i = 0;;)
  {
    wchar_t c = s[i];
    if (c == 0)
      return true;
    if (c == '.' && (i == 0 || s[i - 1] == WCHAR_PATH_SEPARATOR))
    {
      wchar_t c1 = s[i + 1];
      if (c1 == '.')
      {
        wchar_t c2 = s[i + 2];
        if (c2 == WCHAR_PATH_SEPARATOR || c2 == 0)
        {
          if (i == 0)
            return false;
          int k = i - 2;
          for (; k >= 0; k--)
            if (s[k] == WCHAR_PATH_SEPARATOR)
              break;
          unsigned num;
          if (k >= 0)
          {
            num = i + 2 - k;
            i = k;
          }
          else
          {
            num = (c2 == 0 ? (i + 2) : (i + 3));
            i = 0;
          }
          s.Delete(i, num);
          continue;
        }
      }
      else
      {
        if (c1 == WCHAR_PATH_SEPARATOR || c1 == 0)
        {
          unsigned num = 2;
          if (i != 0)
            i--;
          else if (c1 == 0)
            num = 1;
          s.Delete(i, num);
          continue;
        }
      }
    }
    i++;
  }
}

/*
 * Build a fullPath based on a dirPrefix (possibly NULL) and a path.
 * Resolve dirPrefix and path to ensure that there is no relative dotdot 
 * in the paths.
 */
bool GetFullPath(CFSTR dirPrefix, CFSTR path, FString &fullPath)
{
  if (dirPrefix)
  {
    UString resolvedDirPrefix = fs2us(dirPrefix);
    if (!ResolveDotsFolders(resolvedDirPrefix))
      resolvedDirPrefix = us2fs(dirPrefix);
    fullPath = resolvedDirPrefix;
  }

  UString resolvedPath = fs2us(path);
  if (!ResolveDotsFolders(resolvedPath))
    resolvedPath = us2fs(path);

  fullPath += resolvedName;

  return true;
}

/*
 * Build a fullPath based on a directory path.
 */
bool GetFullPath(CFSTR path, FString &fullPath)
{
  return GetFullPath(NULL, path, fullPath);
}

}}}

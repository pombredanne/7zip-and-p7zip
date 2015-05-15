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

bool IsAbsolutePath(const wchar_t *s) { return s[0] == WCHAR_PATH_SEPARATOR || s[0] == WIN_WCHAR_PATH_SEPARATOR; }


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
  if (dirPath.ReverseFind(wchar_t(kDirDelimiter)) != dirPath.Len() - 1)
     dirPath += wchar_t(kDirDelimiter);
}
#endif


static bool ResolveDotsFolders(UString &s)
{
  printf("##DBG CPP/Windows/FileName.cpp::ResolveDotsFolders: initial: s = '%ls'\n", (const wchar_t *) s);
  s.Replace(L'\\', WCHAR_PATH_SEPARATOR);
  s.Replace(L'//', WCHAR_PATH_SEPARATOR);
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
  printf("##DBG CPP/Windows/FileName.cpp::ResolveDotsFolders: resolved: s = '%ls'\n", (const wchar_t *) s);
}


bool GetFullPath(CFSTR dirPrefix, CFSTR s, FString &res)
{
  res = FString(dirPrefix);
  printf("##DBG CPP/Windows/FileName.cpp::GetFullPath: initial: res = '%ls'\n", (const wchar_t *) res);
  UString rem = fs2us(s);
  if (!ResolveDotsFolders(rem)) 
  {
    res += FString(s);
  }
  else 
  {
    res += us2fs(rem);
  }
  printf("##DBG CPP/Windows/FileName.cpp::GetFullPath: resolved: res = '%ls'\n", (const wchar_t *) res);
  return true;
}


}}}

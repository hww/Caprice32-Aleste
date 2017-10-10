/* capzip.h */

EXTERN_C int zip_extract (TCHAR *pchZipFile, TCHAR *pchFileName, uLong dwOffset, const TCHAR* chAppPath);
EXTERN_C int zip_dir (t_zip_info *zi);

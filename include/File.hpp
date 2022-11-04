#ifndef FILE_H
#define FILE_H

#include <cstdarg>
#include <cassert>
#include <cstdio>



/* #Self-documenting and/or Exception-safe encapsulation for a C-style FILE stream,
   #with all the normal functions used with C files (the 'f' at the start of names was removed).
! For Unique files, when initializing the object, the FILE*'s lifetime will be handled by the object's destructor.
! To get the underlying C-style FILE stream, use 'stream()'. You can also take over the file's ownership by using 'steal_stream()'.
!
! Do not pass by reference, as every copy is internally a raw-pointer copy.
! Never pass Unique files to functions which don't own, the object implicitly converts to non-Unique when passed to a function requiring a non-owning file.
!
! When copying an owning object to a non-owning one, the owning object still holds its ownership.
! Owning objects can only use move constructors, non-owning ones can also use copy constructors.
!
! 'const' for these objects means the underlying FILE* cannot be reassigned, it doesn't stop you from using methods which modify the implementation details.
!
! Note: avoid including "File_object_implementation.hpp".
*/

namespace File
{
	/* Order of definitions matters! */
	
	#define FILE_OBJECT_IMPL__NAME InputFile
	#define FILE_OBJECT_IMPL__READER
	#include "impl/File_object_implementation.hpp"
	
	#define FILE_OBJECT_IMPL__NAME OutputFile
	#define FILE_OBJECT_IMPL__WRITER
	#include "impl/File_object_implementation.hpp"
	
	#define FILE_OBJECT_IMPL__NAME IOFile
	#define FILE_OBJECT_IMPL__READER
	#define FILE_OBJECT_IMPL__WRITER
	#include "impl/File_object_implementation.hpp"
	
	#define FILE_OBJECT_IMPL__NAME UniqueInputFile
	#define FILE_OBJECT_IMPL__OWNER
	#define FILE_OBJECT_IMPL__READER
	#include "impl/File_object_implementation.hpp"
	
	#define FILE_OBJECT_IMPL__NAME UniqueOutputFile
	#define FILE_OBJECT_IMPL__OWNER
	#define FILE_OBJECT_IMPL__WRITER
	#include "impl/File_object_implementation.hpp"
	
	#define FILE_OBJECT_IMPL__NAME UniqueIOFile
	#define FILE_OBJECT_IMPL__OWNER
	#define FILE_OBJECT_IMPL__READER
	#define FILE_OBJECT_IMPL__WRITER
	#include "impl/File_object_implementation.hpp"
}

#endif /* FILE_H */

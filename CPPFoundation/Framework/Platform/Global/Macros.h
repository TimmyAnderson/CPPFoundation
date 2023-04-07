//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#if !defined(MACRO_FILE_NAME)
#define MACRO_FILE_NAME __FILE__
#endif
#if !defined(MACRO_FUNCTION_NAME)
#define MACRO_FUNCTION_NAME __func__
#endif
#if !defined(MACRO_LINE_NUMBER)
#define MACRO_LINE_NUMBER static_cast<Size>(__LINE__)
#endif
#if !defined(MACRO_DEPRECATED)
#define MACRO_DEPRECATED [[deprecated]]
#endif
#undef GetMessage
#undef GetUserName
#undef CopyFile
#undef MoveFile
#undef DeleteFile
#undef CreateDirectory
#undef RemoveDirectory
#undef GetCurrentDirectory
#undef SetCurrentDirectory
#undef GetObject
#undef min
#undef max
#elif defined(PLATFORM_LINUX)
#if !defined(MACRO_FILE_NAME)
#define MACRO_FILE_NAME __FILE__
#endif
#if !defined(MACRO_FUNCTION_NAME)
#define MACRO_FUNCTION_NAME __func__
#endif
#if !defined(MACRO_LINE_NUMBER)
#define MACRO_LINE_NUMBER __LINE__
#endif
#if !defined(MACRO_DEPRECATED)
#define MACRO_DEPRECATED  __attribute_deprecated__
#endif
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
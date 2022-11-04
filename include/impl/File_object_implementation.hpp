class FILE_OBJECT_IMPL__NAME
{
private:
	FILE *m_file;
public:
	[[gnu::always_inline]]
	FILE_OBJECT_IMPL__NAME(std::nullptr_t) noexcept
		: m_file(nullptr)
	{
	}
	
	[[gnu::always_inline]]
	FILE_OBJECT_IMPL__NAME(FILE* file) noexcept
		: m_file(file)
	{
	}
	
	[[gnu::always_inline]]
	FILE_OBJECT_IMPL__NAME(FILE_OBJECT_IMPL__NAME &&other) noexcept
	{
		*this = std::move(other);
	}
	
	FILE_OBJECT_IMPL__NAME& operator=(FILE_OBJECT_IMPL__NAME &&other) noexcept
	{
		assert(this != &other);
		
		if (this->m_file != nullptr) {
			fclose(m_file);
		}
		this->m_file = other.m_file;
		other.m_file = nullptr;
		
		return *this;
	}
	
	[[nodiscard, gnu::always_inline]]
	FILE* stream(void) const noexcept
	{
		return m_file;
	}
	
	
	
#ifdef FILE_OBJECT_IMPL__OWNER
	[[nodiscard]]
	inline FILE* steal_stream(void) noexcept
	{
		FILE *const f = m_file;
		m_file = nullptr;
		return f;
	}
	
	~FILE_OBJECT_IMPL__NAME(void) noexcept
	{
		if (m_file != nullptr) {
			::fclose(m_file);
		}
	}
	
	int close(void) noexcept
	{
		const int res = ::fclose(m_file);
		m_file = nullptr;
		return res;
	}
	
#else /* !OWNER */
	[[gnu::always_inline]]
	FILE_OBJECT_IMPL__NAME(const FILE_OBJECT_IMPL__NAME &other) noexcept
		: m_file(other.m_file)
	{
	}
	
	[[gnu::always_inline]]
	FILE_OBJECT_IMPL__NAME& operator=(const FILE_OBJECT_IMPL__NAME &other) noexcept
	{
		this->m_file = other.m_file;
		return *this;
	}
#endif /* OWNER */
	
	
	
#ifdef FILE_OBJECT_IMPL__READER
  #ifndef FILE_OBJECT_IMPL__WRITER
	[[gnu::always_inline]]
	FILE_OBJECT_IMPL__NAME(const char *filename) noexcept
	{
		this->open(filename);
	}
  #endif /* READER && !WRITER */
	
  #ifdef FILE_OBJECT_IMPL__OWNER
	operator InputFile(void) const noexcept
	{
		return InputFile(m_file);
	}
  #endif /* READER && OWNER */
	
	[[gnu::format(scanf, 2, 3)]]
	int scanf(const char *fmt, ...) const noexcept
	{
		va_list args;
		va_start(args, fmt);
		const int res = this->vscanf(fmt, args);
		
		va_end(args);
		return res;
	}
	
	[[gnu::always_inline]]
	int vscanf(const char *fmt, va_list args) const noexcept
	{
		return ::vfscanf(m_file, fmt, args);
	}
	
	[[gnu::always_inline]]
	size_t read(void *ptr, size_t size, size_t nmemb) const noexcept
	{
		return ::fread(ptr, size, nmemb, m_file);
	}
	
	[[gnu::always_inline]]
	char* gets(char *s, int size) const noexcept
	{
		return ::fgets(s, size, m_file);
	}
	
	[[gnu::always_inline]]
	int getc(void) const noexcept
	{
		return ::fgetc(m_file);
	}
	
	[[gnu::always_inline]]
	int ungetc(int c) const noexcept
	{
		return ::ungetc(c, m_file);
	}
#endif /* READER */
	
	
	
#ifdef FILE_OBJECT_IMPL__WRITER
	[[gnu::always_inline]]
	FILE_OBJECT_IMPL__NAME(const char *filename, bool truncate) noexcept
	{
		this->open(filename, truncate);
	}
	
  #ifdef FILE_OBJECT_IMPL__OWNER
	operator OutputFile(void) const
	{
		return OutputFile(m_file);
	}
  #endif /* WRITER && OWNER */
	
	[[gnu::format(printf, 2, 3)]]
	int printf(const char *fmt, ...) const noexcept
	{
		va_list args;
		va_start(args, fmt);
		const int res = this->vprintf(fmt, args);
		
		va_end(args);
		return res;
	}
	
	[[gnu::always_inline]]
	int vprintf(const char *fmt, va_list args) const noexcept
	{
		return ::vfprintf(m_file, fmt, args);
	}
	
	[[gnu::always_inline]]
	size_t write(const void *ptr, size_t size, size_t nmemb) const noexcept
	{
		return ::fwrite(ptr, size, nmemb, m_file);
	}
	
	[[gnu::always_inline]]
	int puts(const char *s) const noexcept
	{
		return ::fputs(s, m_file);
	}
	
	[[gnu::always_inline]]
	int putc(int c) const noexcept
	{
		return ::fputc(c, m_file);
	}
	
	[[gnu::always_inline]]
	int flush(void) const noexcept
	{
		return ::fflush(m_file);
	}
#endif /* WRITER */
	
	
	
#if defined(FILE_OBJECT_IMPL__READER) && defined(FILE_OBJECT_IMPL__WRITER)
  #ifdef FILE_OBJECT_IMPL__OWNER
	operator IOFile(void) const noexcept
	{
		return IOFile(m_file);
	}
	
  #else /* !OWNER */
	operator InputFile(void)  const noexcept
	{
		return InputFile(m_file);
	}
	
	operator OutputFile(void) const noexcept
	{
		return OutputFile(m_file);
	}
  #endif /* READER && WRITER && OWNER */
	
	[[gnu::always_inline]]
	void open(const char *filename, bool truncate) noexcept
	{
		m_file = ::fopen(filename, (truncate ? "w+" : "r+"));
	}
	
#elif defined(FILE_OBJECT_IMPL__READER)
	[[gnu::always_inline]]
	void open(const char *filename) noexcept
	{
		m_file = ::fopen(filename, "r");
	}
	
#elif defined(FILE_OBJECT_IMPL__WRITER)
	[[gnu::always_inline]]
	void open(const char *filename, bool truncate) noexcept
	{
		m_file = ::fopen(filename, (truncate ? "w" : "r+"));
	}
#endif /* READER && WRITER */
	
	
	
	[[gnu::always_inline]]
	void clearerr(void) const noexcept { ::clearerr(m_file); }
	
	[[gnu::always_inline, nodiscard]]
	int eof(void) const noexcept { return ::feof(m_file); }
	
	[[gnu::always_inline, nodiscard]]
	int error(void) const noexcept { return ::ferror(m_file); }
	
	[[gnu::always_inline]]
	void rewind(void) const noexcept { ::rewind(m_file); }
	
	[[gnu::always_inline, nodiscard]]
	int seek(long offset, int whence) const noexcept { return ::fseek(m_file, offset, whence); }
	
	[[gnu::always_inline, nodiscard]]
	long tell(void) const noexcept { return ::ftell(m_file); }
	
	[[gnu::always_inline, nodiscard]]
	int fgetpos(fpos_t *pos) const noexcept { return ::fgetpos(m_file, pos); }
	
	[[gnu::always_inline, nodiscard]]
	int fsetpos(const fpos_t *pos) const noexcept { return ::fsetpos(m_file, pos); }
};


#ifdef FILE_OBJECT_IMPL__NAME
  #undef FILE_OBJECT_IMPL__NAME
#endif

#ifdef FILE_OBJECT_IMPL__OWNER
  #undef FILE_OBJECT_IMPL__OWNER
#endif

#ifdef FILE_OBJECT_IMPL__READER
  #undef FILE_OBJECT_IMPL__READER
#endif

#ifdef FILE_OBJECT_IMPL__WRITER
  #undef FILE_OBJECT_IMPL__WRITER
#endif

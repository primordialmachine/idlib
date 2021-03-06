///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "idlib/platform.hpp"

#if defined (ID_WINDOWS)

#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE 1

#include "idlib/utility/suffix.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#include "idlib/exception.hpp"

#include "idlib/filesystem/header.in"

namespace internal {

struct directory_stream_windows
{
	enum class state
	{
		open,
		closed,
		end,
		error,
	};

	directory_stream_windows()
		: m_state(state::closed),
		  m_handle(INVALID_HANDLE_VALUE),
		  m_data()
	{}
	
	~directory_stream_windows()
	{
		close();
	}
	
	bool has_value() const
	{ return state::open == m_state; }

	std::string get_value() const
	{ if (!has_value()) throw std::runtime_error("enumerator has no value"); 
      return m_data.cFileName; }
	
	void close()
	{
		if (state::error == m_state || state::error == m_state || state::open == m_state)
		{
			FindClose(m_handle);
			m_handle = INVALID_HANDLE_VALUE;
			m_state = state::closed;
		}
	}
	
	std::string make_search_string(const std::string& pathname)
	{
		// must not be empty
		// must not end with / or \
		// must not contain wildcards
		static const std::vector<char> forbidden = 
		{
			'?',
			'*',
		};
		if (pathname.empty() ||
			is_suffix(pathname, std::string("/")) ||
			is_suffix(pathname, std::string("\\")) ||
            pathname.cend() != std::find_first_of(pathname.cbegin(), pathname.cend(), forbidden.cbegin(), forbidden.cend()))
		{
			throw runtime_error(__FILE__, __LINE__, "invalid pathname");
		}
		return pathname + "/*";
	}
	
	void open(const std::string& pathname)
	{
		close();
		SetLastError(0);
		m_handle = FindFirstFileA(make_search_string(pathname).c_str(), &m_data);
		if (INVALID_HANDLE_VALUE == m_handle)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND) m_state = state::end;
			else m_state = state::error;
			SetLastError(0);
		}
		m_state = state::open;
		// Skip '.' and '..'.
		if (state::open == m_state && is_dot_or_dot_dot())
		{
			next();
		}
	}

	void next()
	{
		if (state::error == m_state || state::end == m_state)
		{ return; }

		SetLastError(0);
		BOOL result = FindNextFileA(m_handle, &m_data);
		if (!result)
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) m_state = state::end;
			else m_state = state::error;
			SetLastError(0);
		}
		// Skip '.' and '..'.
		if (state::open == m_state && is_dot_or_dot_dot())
		{
			next();
		}
	}
	
	bool is_dot_or_dot_dot()
	{
		const char *name = m_data.cFileName;
		if (name[0] == '.')
		{
			if (name[1] == '\0' || (name[1] == '.' && name[2] == '\0'))
			{
				return true;
			}
		}
		return false;
	}
	
	state m_state;

	HANDLE m_handle;

	WIN32_FIND_DATAA m_data;
	
}; // struct directory_stream_windows

} // namespace internal

#include "idlib/filesystem/footer.in"

#endif

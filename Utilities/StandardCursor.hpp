#ifndef STANDARCURSOR_HPP
#define STANDARCURSOR_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifdef SFML_SYSTEM_WINDOWS
	#include <windows.h>
#elif defined(SFML_SYSTEM_LINUX)
	#include <X11/cursorfont.h>
	#include <X11/Xlib.h>
#else
	#error this OS is not yet supported by te cursor library.
#endif

namespace sf
{
	class StandardCursor
	{
	private:
		#ifdef SFML_SYSTEM_WINDOWS
			HCURSOR Cursor;
		#else
			XID Cursor;
			Display* display;
		#endif
	
	public:
		enum TYPE{ WAIT, TEXT, NORMAL, HAND /*, ... */ };
		StandardCursor(const TYPE t);
		void set(const sf::WindowHandle& aWindowHandle) const;
		~StandardCursor();
	};
}

#endif // STANDARCURSOR_HPP

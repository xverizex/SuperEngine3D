#ifndef ENGINE_MAIN_HEADER_H
#define ENGINE_MAIN_HEADER_H

class WindowSize {
	public:
		static WindowSize *getInstance ();
		
		uint32_t width;
		uint32_t height;
	private:
		WindowSize();

		
};

#endif

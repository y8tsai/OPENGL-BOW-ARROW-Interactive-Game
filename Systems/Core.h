#ifndef __CORE_H__
#define __CORE_H__

class Core {
public:
	Core();
	~Core();
	
	void StartUp();
	void Shutdown();
	void Stop();

private:
	void SetupKeybinds();
	bool running;
};

#endif
#include <thread>

class scoped_thread {
	   std::thread t;
	public:
		explicit scoped_thread(std::thread other):t(std::move(other)) {
			if (!t.joinable())
				throw std::logic_error("No thread");
		}
		~scoped_thread() {
			t.join();
		}
		scoped_thread(scoped_thread const&)=delete;
		scoped_thread& operator=(scoped_thread const&)=delete;
};
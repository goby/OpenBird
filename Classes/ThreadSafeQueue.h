#ifndef _THREADSAFEQUEUE_H_
#define _THREADSAFEQUEUE_H_

template<typename T>
class ThreadSafeQueue
{
public:
    void push_back( T && item ) {
        std::lock_guard<std::mutex> g( _mutex );
        _q.push_back( std::forward<T>(item) );
    }

    void push_back( T const & item ) {
        std::lock_guard<std::mutex> g( _mutex );
        _q.push_back( item );
    }
    
	T &front(){
		std::lock_guard<std::mutex> g( _mutex );
        return _q.front();
	}

    void pop_front() {            
        std::lock_guard<std::mutex> g( _mutex );
        if ( !_q.empty() ) 
		{
			_q.pop_front();
		}
    }

    bool empty() {
        std::lock_guard<std::mutex> g( _mutex );
        return _q.empty();
    }

    void clear() {
        std::lock_guard<std::mutex> g( _mutex );
        _q.clear();
    }

    void clear( std::function< void( T & ) > f ) {
        std::lock_guard<std::mutex> g( _mutex );
        for( auto &o : _q ) f( o );
        _q.clear();
    }

private:
    std::mutex      _mutex;
    std::deque<T>   _q;
};

#endif